# ESP32 Wi-Fi Weather Station 🌦️

A weather station project that measures temperature, humidity, and heat index using an **ESP32** and **DHT11 sensor**. The data is displayed on an **I2C LCD** and served over Wi-Fi through a **JSON API**. The iOS app fetches and displays the data.

---

## Features
### ESP32
- Measures **temperature**, **humidity**, and **heat index** using **DHT11 sensor**.
- Displays data on a **16x2 I2C LCD**.
- Serves data via a RESTful **JSON API**.

### iOS App (SwiftUI)
- Fetches data from the ESP32 over Wi-Fi.
- Displays data with dynamic backgrounds based on temperature/heat index.
- Shows error messages with alerts for any issues (like failed data fetch).

---

## Getting Started

### ESP32 Setup
1. **PlatformIO** is used for ESP32 development. 
2. The ESP32 code is located in the `src/main.cpp` file.
3. To connect the ESP32 to Wi-Fi, open `src/main.cpp` and enter your **Wi-Fi SSID** and **password** in the designated fields:

   ```cpp
   const char* ssid = "your_wifi_ssid";  // Enter your Wi-Fi SSID here
   const char* password = "your_wifi_password";  // Enter your Wi-Fi password here
