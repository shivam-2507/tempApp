#include <Arduino.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

const char *ssid = "wifinamehere";         // Your Wi-Fi SSID
const char *password = "wifipasswordhere"; // Your Wi-Fi password

AsyncWebServer server(80);
TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t lcdTaskHandle = NULL;

struct SensorData
{
  float humidity;
  float temperatureC;
  float temperatureF;
  float heatIndexC;
  float heatIndexF;
};

SensorData sensorData;

void wifiTask(void *parameter)
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String jsonResponse = "{\"humidity\": " + String(sensorData.humidity) +
                                    ", \"temperatureC\": " + String(sensorData.temperatureC) +
                                    ", \"temperatureF\": " + String(sensorData.temperatureF) +
                                    ", \"heatIndexC\": " + String(sensorData.heatIndexC) +
                                    ", \"heatIndexF\": " + String(sensorData.heatIndexF) +
                                    "}";
              request->send(200, "application/json", jsonResponse); });

  server.begin();
  vTaskDelete(NULL);
}

void sensorTask(void *parameter)
{
  while (true)
  {
    sensorData.humidity = dht.readHumidity();
    sensorData.temperatureC = dht.readTemperature();
    sensorData.temperatureF = dht.readTemperature(true);

    if (isnan(sensorData.humidity) || isnan(sensorData.temperatureC) || isnan(sensorData.temperatureF))
    {
      sensorData.humidity = -1;
      sensorData.temperatureC = -1;
      sensorData.temperatureF = -1;
    }
    else
    {
      sensorData.heatIndexC = dht.computeHeatIndex(sensorData.temperatureC, sensorData.humidity, false);
      sensorData.heatIndexF = dht.computeHeatIndex(sensorData.temperatureF, sensorData.humidity);
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void lcdTask(void *parameter)
{
  while (true)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    if (sensorData.humidity == -1)
    {
      lcd.print("Sensor Error!");
    }
    else
    {
      lcd.print("Humidity: ");
      lcd.print(sensorData.humidity);
      lcd.print("%");
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    lcd.clear();
    lcd.setCursor(0, 0);
    if (sensorData.temperatureC == -1)
    {
      lcd.print("Sensor Error!");
    }
    else
    {
      lcd.print("Temp: ");
      lcd.print(sensorData.temperatureC);
      lcd.print("°C");
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    lcd.clear();
    lcd.setCursor(0, 0);
    if (sensorData.temperatureF == -1)
    {
      lcd.print("Sensor Error!");
    }
    else
    {
      lcd.print("Temp: ");
      lcd.print(sensorData.temperatureF);
      lcd.print("°F");
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    lcd.clear();
    lcd.setCursor(0, 0);
    if (sensorData.heatIndexC == -1)
    {
      lcd.print("Sensor Error!");
    }
    else
    {
      lcd.print("HeatIdx: ");
      lcd.setCursor(0, 1);
      lcd.print(sensorData.heatIndexC);
      lcd.print("°C ");
      lcd.print(sensorData.heatIndexF);
      lcd.print("°F");
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  lcd.init();
  lcd.backlight();

  xTaskCreate(wifiTask, "WiFi Task", 4096, NULL, 1, &wifiTaskHandle);
  xTaskCreate(sensorTask, "Sensor Task", 4096, NULL, 1, &sensorTaskHandle);
  xTaskCreate(lcdTask, "LCD Task", 4096, NULL, 1, &lcdTaskHandle);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wi-Fi Disconnected! Reconnecting...");
    WiFi.reconnect();
    delay(5000);
  }
  else
  {
    delay(5000);
    Serial.println("Wi-Fi is connected!");
  }
}
