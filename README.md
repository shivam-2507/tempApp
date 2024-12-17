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

### Clone this Repository

1. Clone the repository to your local machine using Git:

   ```bash
   git clone https://github.com/yourusername/esp32-weather-station.git
   ```

### ESP32 Setup
1. **PlatformIO** is used for ESP32 development. 
2. The ESP32 code is located in the `src/main.cpp` file.
3. To connect the ESP32 to Wi-Fi, open `src/main.cpp` and enter your **Wi-Fi SSID** and **password** in the designated fields:

   ```cpp
   const char* ssid = "your_wifi_ssid";  // Enter your Wi-Fi SSID here
   const char* password = "your_wifi_password";  // Enter your Wi-Fi password here
   	```
4. To get the ESP32’s IP address, run the Wi-Fi Test file located in the src folder. This will print the IP address to the serial monitor. Paste this IP address into the iOS app to establish the connection
5. Get the LCD memory address by running `src/screenMemoryAddress.cpp` and reading the serial monitor

   ```cpp
	int lcdColumns = 16;
	int lcdRows = 2;
	LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);
	```
6. Replacing the 3F with the memory address will allow the LCD Screen to work

### iOS App Setup
1. Xcode is used for the iOS app development.
2. The app code is located in ESP32 Temp App/ContentView.swift.
3. In ContentView.swift, replace the placeholder <ESP32_IP> in the fetchData() function with the IP address of your ESP32 from the previous step:

```swift
guard let url = URL(string: "http://<ESP32_IP>/data") else {
    showErrorMessage("Invalid URL")
    return
}
```
   
4. This will enable the iOS app to fetch and display the data from the ESP32.
5. The app can also be downloaded to any iOS device by following the instruction in the Xcode IDE.

---

### Hardware Requirements
- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor
- 16x2 I2C LCD 
- Breadboard and jumper wires

### Software Requirements
- PlatformIO for ESP32 development
- Xcode for iOS app development
- Libraries:
	- DHT (for the DHT11 sensor)
	- LiquidCrystal_I2C (for the LCD)
	- ESPAsyncWebServer (for the RESTful API)

---
### Troubleshooting
- Ensure that the Wi-Fi credentials are correct in both the ESP32 code and the iOS app.
- Check the ESP32 serial monitor for any connection issues or errors.
- If the app fails to fetch data, verify that the ESP32 is correctly serving data on the provided IP address.
