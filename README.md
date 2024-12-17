# ESP32 Wi-Fi Weather Station

This project is a weather monitoring station built using an **ESP32**, which measures temperature, humidity, and heat index using a **DHT11 sensor**. The data is displayed on an **I2C LCD** and served over Wi-Fi as a JSON API.

## Features

- **Temperature and Humidity Measurement**: Uses the DHT11 sensor to measure temperature (°C and °F) and humidity (%).
- **Heat Index Calculation**: Computes heat index values in both Celsius and Fahrenheit.
- **LCD Display**: Displays real-time weather data on a 16x2 I2C LCD.
- **Wi-Fi Connectivity**: Connects to a Wi-Fi network and serves sensor data over a RESTful JSON API.
- **Multi-tasking with FreeRTOS**: Runs tasks for Wi-Fi, sensor reading, and LCD display concurrently.

---

## Hardware Requirements

- **ESP32** development board
- **DHT11 Temperature & Humidity Sensor**
- **16x2 I2C LCD** (Address: 0x3F)
- Connecting wires
- Breadboard or PCB for assembly

---

## Software Requirements

- **Arduino IDE** (with ESP32 board support installed)
- **Libraries**:
  - [DHT](https://github.com/adafruit/DHT-sensor-library)
  - [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
  - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

---

## Wiring Diagram

| ESP32 Pin | DHT11 Pin | LCD Pin |
|-----------|-----------|---------|
| 4         | Data      | -       |
| 3.3V      | VCC       | VCC     |
| GND       | GND       | GND     |
| -         | -         | SDA     |
| -         | -         | SCL     |

- Connect the **DHT11** data pin to GPIO 4.
- Connect the **LCD SDA** pin to ESP32's default SDA.
- Connect the **LCD SCL** pin to ESP32's default SCL.

---

## API

The ESP32 serves sensor data via a RESTful JSON API:

- **Endpoint**: `http://<ESP32_IP>/data`
- **Response**:
  ```json
  {
    "humidity": 45.6,
    "temperatureC": 24.7,
    "temperatureF": 76.5,
    "heatIndexC": 25.3,
    "heatIndexF": 77.5
  }
