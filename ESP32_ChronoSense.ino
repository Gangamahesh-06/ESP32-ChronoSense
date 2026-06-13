#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <WiFi.h>
#include <DHT.h>
#include "time.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// DHT22 Configuration
#define DHTPIN 4 
#define DHTTYPE DHT22     
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi & NTP Settings for India Standard Time (IST)
const char* ssid     = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;       // UTC +5:30 = 19800 seconds
const int   daylightOffset_sec = 0;      // No DST in India

void setup(void) {
  Serial.begin(115200);
  
  // Initialize peripherals
  u8g2.begin();
  dht.begin();

  // Connect to Wi-Fi to sync clock
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(10, 35, "Connecting Wi-Fi...");
  u8g2.sendBuffer();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Synchronize internal ESP32 clock with the NTP server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop(void) {
  // Clear the screen buffer at the start of every frame
  u8g2.clearBuffer();

  // 1. Fetch and Display Time & Date
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(15, 20, "Syncing Time...");
  } else {
    char timeHourMin[10], timeSec[5], amPmStr[5], dateStr[20];
    
    strftime(timeHourMin, sizeof(timeHourMin), "%I:%M", &timeinfo); 
    strftime(timeSec, sizeof(timeSec), ":%S", &timeinfo);   
    strftime(amPmStr, sizeof(amPmStr), "%P", &timeinfo);       
    strftime(dateStr, sizeof(dateStr), "%A, %b %d", &timeinfo);    

    // Draw Time 
    u8g2.setFont(u8g2_font_10x20_tf); 
    u8g2.drawStr(15, 22, timeHourMin);   
    u8g2.drawStr(62, 22, timeSec);
    // Draw AM/PM
    u8g2.setFont(u8g2_font_8x13_tf);
    u8g2.drawStr(98, 22, amPmStr);
    // Draw Date
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(15, 38, dateStr);
  }

  // 2. Fetch and Display DHT22 Data
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  u8g2.setFont(u8g2_font_6x12_tf);
  
  // Check if sensor reading failed
  if (isnan(t) || isnan(h)) {
    u8g2.drawStr(15, 58, "Sensor Error");
  } else {
    // Format temperature and humidity strings
    char tempStr[20];
    char humStr[20];
    snprintf(tempStr, sizeof(tempStr), "T: %.1f C", t);
    snprintf(humStr, sizeof(humStr), "H: %.1f%%", h);
    
    // Draw Environment metrics on the bottom layout line
    u8g2.drawStr(10, 58, tempStr);
    u8g2.drawStr(75, 58, humStr);
  }

  // Push the freshly drawn frame onto the physical screen
  u8g2.sendBuffer();
  delay(1000); 
}