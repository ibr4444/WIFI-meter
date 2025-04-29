# WIFI-meter
ESP32 Wi-Fi Signal Strength Visualizer
======================================

This project uses an ESP32 and a TFT display to show real-time Wi-Fi signal strength (RSSI) using a bar graph.

----------------------------
Features
----------------------------
- Connects to a Wi-Fi network
- Measures signal strength (RSSI)
- Displays strength as a dynamic 4-bar graph
- Color-coded bars:
  - Green = Active signal level
  - Red   = Inactive bars

----------------------------
Requirements
----------------------------
Hardware:
- ESP32 development board
- TFT display (compatible with TFT_eSPI, e.g. ILI9341 or ST7735)

Libraries:
- WiFi.h (included with ESP32 core)
- TFT_eSPI (https://github.com/Bodmer/TFT_eSPI)

----------------------------
Wiring
----------------------------
Wire your TFT display according to your `User_Setup.h` configuration for the `TFT_eSPI` library.

----------------------------
Wi-Fi Configuration
----------------------------
Update your Wi-Fi credentials in the code:

```cpp
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
