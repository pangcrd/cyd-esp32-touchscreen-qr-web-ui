#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <lvgl.h>
#include "qr_webserver.h"



// ── UI callback ────────────────────────────────────────────────────────────
void update_wifi_list_ui(void *scan_result);



// ── Expose sang C files (ui_setting.c) ────────────────────────────────────
#ifdef __cplusplus
extern "C" {
#endif

void start_wifi_scan(void);
void start_wifi_connect(const char *ssid, const char *password);
// ── NVS ────────────────────────────────────────────────────────────────────
bool save_wifi_credentials(const char *ssid, const char *password);
bool load_wifi_credentials(char *ssid, char *password);

extern lv_obj_t *wifi_list;

#ifdef __cplusplus
}
#endif

#endif