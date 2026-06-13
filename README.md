# ESP32 ChronoSense: IoT Weather & Time Station

An ESP32-powered desk companion that synchronises with network time servers over Wi-Fi to display exact Indian Standard Time (IST) alongside micro-climate metrics (Temperature & Humidity) fetched via a DHT22 sensor onto a 0.96" SSD1306 OLED display.

## 🚀 Features
* **NTP Time Sync:** Automatically syncs precise time over Wi-Fi, eliminating the need for an external RTC module.
* **12-Hour AM/PM Display:** Features a clean, scannable visual layout tracking Hours, Minutes, Seconds, and Day/Date.
* **Live Micro-Climate Metrics:** Polls real-time ambient temperature and humidity data using the digital DHT22 sensor.
* **Optimised Rendering Layout:** Leverages the lightweight `U8g2` library utilizing full page-buffer rendering to prevent screen flicker.

---

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP32 (DevKit v1 or equivalent)
* **Display:** 0.96" SSD1306 OLED Screen (128x64 pixels, I2C version)
* **Sensor:** DHT22 (AM2302) Temperature & Humidity Sensor
* **Prototyping:** Breadboard, Jumper wires, and a Micro-USB cable

### Wiring Pinout

| SSD1306 OLED Pin | ESP32 GPIO Pin | Wire Color (Schematic) |
| :--- | :--- | :--- |
| **GND** | GND | Black |
| **VCC** | 3V3 | Red |
| **SCL** | GPIO 22 | Orange |
| **SDA** | GPIO 21 | Green |

| DHT22 Sensor Pin | ESP32 GPIO Pin | Wire Color (Schematic) |
| :--- | :--- | :--- |
| **GND (-)** | GND | Black |
| **VCC (+)** | 3V3 / 5V | Red |
| **DAT (Out)** | GPIO 4 | Pink |

---

## 💻 Software Dependencies
Ensure you have the following libraries installed in your Arduino IDE or PlatformIO project setup:
1. **U8g2** by Oliver (For OLED screen driving)
2. **DHT sensor library** by Adafruit (For DHT22 processing)
3. **Adafruit Unified Sensor** by Adafruit (Core sensor requirement)



