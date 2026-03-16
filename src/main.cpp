#include "lvgl_port.h"
#include "ui.h"
#include "ntp_service.h"
#include "qr_webserver.h"

// ================ Setup ================
void setup() {
    Serial.begin(115200);
    Serial.println("\n=== Starting Application ===");
    // Initialize LVGL and display
    lvgl_begin();
    // Initialize UI
    ui_init();
    ntp_begin(); 
}
// ================ Main Loop ================
void loop() {
    lvgl_handler(); // Handle LVGL tasks
    run_server();
    ntp_update();
}
