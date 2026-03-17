<div align="center">

<img src="https://img.shields.io/badge/ESP32-Embedded-blue?style=for-the-badge&logo=espressif&logoColor=white"/>
<img src="https://img.shields.io/badge/UI-LVGL-4CAF50?style=for-the-badge"/>
<img src="https://img.shields.io/badge/License-MIT-orange?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge"/>

# ESP32 Touchscreen QR Web UI

**A complete embedded device combining touchscreen UI, WiFi configuration, and a built-in web server.**  
Send any URL or text from your browser → instantly display a QR code on the device screen.

[Features](#-key-features) · [Hardware](#-hardware) · [UI](#-device-ui) · [Web Interface](#-web-interface) · [Architecture](#-system-architecture) · [Wiki](#-wiki--documentation) · [License](#-license)

</div>

---

## Overview

This project demonstrates how to integrate **embedded UI, networking, and web interaction** into a complete embedded system built on the **ESP32** platform.

- Users configure WiFi directly from the touchscreen 
- The device hosts its own **web server** accessible at `esp32.local`
- Any browser can send text or URLs to the device
- The ESP32 immediately generates and renders a **QR code** via LVGL

Designed as a **practical reference for embedded developers** exploring LVGL, async web serving, and ESP32 UI systems.

---

## 🔧 Hardware

Custom ESP32 display board used in this project.

| Front | Back |
|:-----:|:----:|
| ![Front](img/hardware_front.png) | ![Back](img/hardware_back.png) |

---

## 📱 Device UI

The device UI is built with **LVGL** and fully controlled via touchscreen — no external tools or serial monitor required.

| Home Screen | Settings | WiFi List | Enter Password |
|:-----------:|:--------:|:---------:|:---------:|
| ![Home](img/home_scr.jpg) | ![Settings](img/setting_scr.jpg) | ![Scan](img/wifi_list.jpg) | ![List](img/wifi_pass.jpg) |

**UI Highlights:**
- Home screen displays the live-generated **QR code**
- Settings panel with **brightness control**
- WiFi scanning and selection directly on-device
- Clean, responsive embedded interface

---

## 🌐 Web Interface

Once connected to a network, the ESP32 serves a responsive web UI accessible from any browser.

| Light Mode | Dark Mode |
|:----------:|:---------:|
| ![Light](img/light_mode.PNG) | ![Dark](img/dark_mode.PNG) |

---

## 🎬 Web UI Demo

Example interaction — from browser to device display.

| Web UI Demo |
|:-----------:|
| ![Demo](img/webrun.PNG) |

**Workflow:**
1. Open `http://esp32.local` or IP adrress scan with QR, in any browser
2. Type a URL or any text
3. Hit Send → ESP32 generates the QR code
4. QR code appears instantly on the touchscreen

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| 🖥️ Touchscreen UI | Full LVGL interface with brightness control and WiFi setup |
| 📡 WiFi Config | Scan and connect to networks directly from the device, save wifi ssid pass into NVS |
| 🌐 Embedded Web Server | Async HTTP server hosted entirely on the ESP32 |
| 📲 QR Code Generation | Dynamic QR from any URL or text, rendered via LVGL |
| 🔗 mDNS Access | Reach the device at `esp32.local` on your local network |
| 💾 File Storage | Web assets stored in LittleFS |
| 🌙 Dark / Light Mode | Web UI supports both themes |
| 🔄 Auto QR on Connect | Displays device web address QR after WiFi connection |
| 🧱 Modular Firmware | Clean, structured codebase for easy extension |

---

## 🏗️ System Architecture

```
Browser / Mobile Device
        │
        │  HTTP Request (esp32.local)
        ▼
  ┌─────────────────┐
  │  ESP32 Web      │
  │  Server         │  ← Async Web Server + LittleFS
  └────────┬────────┘
           │
           │  Parsed URL or Text
           ▼
  ┌─────────────────┐
  │  QR Code        │
  │  Generator      │  ← Runs on ESP32
  └────────┬────────┘
           │
           ▼
  ┌─────────────────┐
  │  LVGL UI        │
  │  Renderer       │  ← Framebuffer → SPI Display
  └────────┬────────┘
           │
           ▼
  Touchscreen Display
```

---

## 🛠️ Software Stack

| Component | Technology |
|-----------|------------|
| Firmware | ESP32 (Arduino / ESP-IDF) |
| UI Framework | LVGL |
| File System | LittleFS / SPIFFS |
| Web Server | WebServer : ESPmDNS |
| QR Generation | On-device QR library |
| Network Discovery | mDNS (`esp32.local`) |

---

## 📖 Wiki / Documentation

> 📝 **Wiki is currently in progress.** The following pages are planned:

| Page | Status |
|------|--------|
| [Getting Started](https://www.elecrow.com/wiki/ESP32_Miner_LCD-2.8_inch_PlatformIO.html#overview) | ✅ Available  |
| [LVGL UI Customization](https://www.elecrow.com/wiki/ESP32_Miner_LCD-2.8_inch_PlatformIO.html#design-ui-file-with-squareline-studio) | ✅ Available |
| Hardware Setup & Wiring | 🔜 Coming soon |
| Flashing & First Boot | 🔜 Coming soon |
| Web Interface Guide | 🔜 Coming soon |
| LittleFS File Upload | 🔜 Coming soon |
| API Reference | 🔜 Coming soon |
| Troubleshooting | 🔜 Coming soon |

If you'd like to contribute to the documentation, feel free to open an issue or PR.

---
## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

<div align="center">
  <sub>Built with ❤️ CYD + LVGL</sub>
</div>
