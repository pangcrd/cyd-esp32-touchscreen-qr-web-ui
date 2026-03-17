#include "ntp_service.h"

// ── Internal state ───────────────────────────────────────────────────────────
static ntp_state_t  s_state             = NTP_STATE_WAITING_WIFI;
static bool         s_synced            = false;
static unsigned long s_last_sync_ms     = 0;
static unsigned long s_last_attempt_ms  = 0;
static char         s_time_buf[6]       = "--:--";

// ── Private helpers ──────────────────────────────────────────────────────────
static void _start_ntp()
{
    configTime(NTP_GMT_OFFSET_SEC, NTP_DAYLIGHT_OFFSET_SEC, NTP_SERVER);
    s_state = NTP_STATE_SYNCING;
    s_last_attempt_ms = millis();
    Serial.println("[NTP] configTime called, waiting for sync...");
}

// ── Public API ───────────────────────────────────────────────────────────────
void ntp_begin()
{
    s_state            = NTP_STATE_WAITING_WIFI;
    s_synced           = false;
    s_last_sync_ms     = 0;
    s_last_attempt_ms  = 0;
    strcpy(s_time_buf, "--:--");
    Serial.println("[NTP] Service initialized");
    lv_timer_create([](lv_timer_t* t) {
        lv_label_set_text(ui_wifistatus, ntp_get_time_str());
    }, 500, NULL);
}

void ntp_update()
{
    unsigned long now = millis();

    switch (s_state)
    {
        // ── Waiting for WiFi ──────────────────────────────────────────
        case NTP_STATE_WAITING_WIFI:
            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("[NTP] WiFi detected, starting NTP sync");
                _start_ntp();
            }
            break;

        // ── Call configTime, waiting for valid time ───────────────────────────
        case NTP_STATE_SYNCING:
        {
            // If WiFi is lost during sync → go back to waiting
            if (WiFi.status() != WL_CONNECTED) {
                Serial.println("[NTP] WiFi lost during sync, waiting...");
                s_state = NTP_STATE_WAITING_WIFI;
                break;
            }

            // Throttle: try every NTP_RETRY_INTERVAL_MS
            if (now - s_last_attempt_ms < NTP_RETRY_INTERVAL_MS) break;
            s_last_attempt_ms = now;

            struct tm timeinfo;
            if (getLocalTime(&timeinfo, 0)) {
                s_last_sync_ms = now;
                s_synced       = true;
                s_state        = NTP_STATE_SYNCED;
                Serial.printf("[NTP] Synced! Time: %02d:%02d:%02d\n",
                              timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
            }
            break;
        }

        // ── Call configTime, waiting for valid time ───────────────────────────
        case NTP_STATE_SYNCED:
            // If WiFi is lost → reset to waiting (time still valid from internal RTC)
            if (WiFi.status() != WL_CONNECTED) {
                Serial.println("[NTP] WiFi lost, will re-sync when reconnected");
                s_state = NTP_STATE_WAITING_WIFI;
                break;
            }

            if (now - s_last_sync_ms >= NTP_SYNC_INTERVAL_MS) {
                Serial.println("[NTP] Interval reached, re-syncing...");
                _start_ntp();
            }
            break;
    }
}
const char* ntp_get_time_str()
{
    bool show_colon = ((millis() / 500) % 2);

    if (!s_synced) {
        strcpy(s_time_buf, show_colon ? "--:--" : "-- --");
        return s_time_buf;
    }

    struct tm timeinfo;
    if (getLocalTime(&timeinfo, 0)) {
        snprintf(s_time_buf, sizeof(s_time_buf),
                 show_colon ? "%02d:%02d" : "%02d %02d",
                 timeinfo.tm_hour,
                 timeinfo.tm_min);
    }

    return s_time_buf;
}

bool ntp_is_synced()
{
    return s_synced;
}

ntp_state_t ntp_get_state()
{
    return s_state;
}

void ntp_force_resync()
{
    Serial.println("[NTP] Force resync requested");
    if (WiFi.status() == WL_CONNECTED) {
        _start_ntp();
    } else {
        s_state = NTP_STATE_WAITING_WIFI;
    }
}