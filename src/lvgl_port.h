#ifndef LVGL_PORT_H
#define LVGL_PORT_H

#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
static TFT_eSPI tft = TFT_eSPI();
#endif
    void lvgl_begin();
    void lvgl_handler();  

#ifdef __cplusplus
extern "C" {
#endif

void TFT_SET_BL(uint8_t Value);  
void start_wifi_scan(void);
void start_wifi_connect(const char *ssid, const char *password);
bool save_wifi_credentials(const char *ssid, const char *password);
bool load_wifi_credentials(char *ssid, char *password);


#ifdef __cplusplus
}
#endif

#endif
