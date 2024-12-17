/*#include <Arduino.h>
#include <WiFi.h>

// Replace these with your actual Wi-Fi credentials
const char *ssid = "";        // Wi-Fi SSID
const char *password = ""; // Wi-Fi Password

void wifiTask(void *parameter)
{
    // Start the Wi-Fi connection
    WiFi.begin(ssid, password);

    // Wait for the Wi-Fi connection to establish
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to Wi-Fi...");
    }

    // Once connected, print the IP address to the Serial Monitorq
    Serial.println("Connected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); // This is where you get the IP address
}

void setup()
{
    // Start Serial communication
    Serial.begin(115200);
    Serial.println("ESP32 WiFi Connection Example");

    // Create the WiFi task (use FreeRTOS task if needed)
    xTaskCreate(wifiTask, "WiFi Task", 4096, NULL, 1, NULL);
}

void loop()
{
    // Empty loop since Wi-Fi task is handled by FreeRTOS task
}*/
