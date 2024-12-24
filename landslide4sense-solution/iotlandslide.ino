
#define BLYNK_TEMPLATE_ID "TMPL3jm0_Ykkx"
#define BLYNK_TEMPLATE_NAME "landslide detection1"
#define BLYNK_AUTH_TOKEN "OJNCRUj5UerXhcuAvYg9P7y_RiE9-GcK"



#include <DHT.h>
#include <WiFi.h>
//#include <ESP8266WiFi.h>         // For ESP8266 Wi-Fi connection
#include <BlynkSimpleEsp32.h>  // For Blynk using ESP8266
#include <Blynk.h>               // Include the main Blynk library


// For ESP32, replace the two includes above with <WiFi.h> and <BlynkSimpleEsp32.h>

#define DHTPIN 13    // Pin connected to DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Constants for sensors
const int soilMoisturePin = 35;  // Analog pin for soil moisture sensor
const int rainDropPin = 34;      // Analog pin for rain drop sensor
const int tiltSensorPin = 12;     // Digital pin for tilt sensor

const int rainThreshold = 100;   // Set your rain drop threshold value (0-1023)
unsigned long rainStartTime = 0; // Track time when rain starts
bool isRaining = false;          // Track if it is raining

// Blynk configuration
// #define BLYNK_TEMPLATE_ID "TMPL3C022gbv2"
// #define BLYNK_DEVICE_NAME "Landslide Detection"
// #define BLYNK_AUTH_TOKEN "WQ6waxYc-2m686xIBZmyj7-R4t7urF2e"

char auth[] = "OJNCRUj5UerXhcuAvYg9P7y_RiE9-GcK";  // Blynk Auth Token
char ssid[] = "Toy";  // Your Wi-Fi SSID
char pass[] = "toy12345"; // Your Wi-Fi Password

void setup() {
  Serial.begin(115200);
  
  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize DHT sensor
  dht.begin();

  // Set pin modes
  pinMode(soilMoisturePin, INPUT);
  pinMode(rainDropPin, INPUT);
  pinMode(tiltSensorPin, INPUT);
  pinMode(23,OUTPUT);
}

void loop() {
  Blynk.run();  // Run Blynk

  // Read sensors
  float soilMoistureValue = map(analogRead(soilMoisturePin),0,4095,4095,0);
  float rainDropValue = map(analogRead(rainDropPin),0,4095,4095,0);
  int tiltSensorValue = digitalRead(tiltSensorPin);
  
  // Read DHT11 values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Display values on Serial Monitor
  Serial.print("Humidity (%): ");
  Serial.println(humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println(temperature, 2);

  Serial.print("Soil Moisture (%): ");
  Serial.println(soilMoistureValue * 100 / 4096);

  Serial.print("Rain Drop Sensor Value: ");
  Serial.println(rainDropValue);

  // Send values to Blynk App
  Blynk.virtualWrite(V0, temperature);  // Temperature
  Blynk.virtualWrite(V1, humidity);     // Humidity
  Blynk.virtualWrite(V2, soilMoistureValue); // Soil moisture
  Blynk.virtualWrite(V3, rainDropValue);     // Rain drop sensor

  // Check for rain (analog value above threshold)
  if (rainDropValue > rainThreshold && !isRaining) {
    isRaining = true;
    rainStartTime = millis();  // Start tracking rain duration
    Serial.println("Rain has started.");
    Blynk.logEvent("rainstarted",String("Rain has started!"));
  } 
  else if (rainDropValue <= rainThreshold && isRaining) {
    unsigned long rainDuration = (millis() - rainStartTime) / 1000;  // Duration in seconds
    Serial.print("Rain stopped. Duration: ");
    Serial.print(rainDuration);
    Serial.println("seconds");

    String message = "Rain has stopped! Duration: " + String(rainDuration) + " seconds";
    Blynk.logEvent("rainstopped",message);
    isRaining = false;
  }

  // Check tilt sensor for landslide warning
  if (tiltSensorValue == LOW) {
    Serial.println("Warning: Landslide occurring!");
    Blynk.logEvent("landslide_detection","Warning: Landslide detected!");
    digitalWrite(23,HIGH);
  } else {
    Serial.println("Be safe!");
  }
  
  delay(2000);  // Delay for readability
}