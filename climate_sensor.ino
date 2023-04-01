#include <SD.h>
#include <DHT.h>
#include <Wire.h>

#define DHTPIN 4 // connect DHT11 sensor to I/O pin 4 on I2C module
#define DHTTYPE DHT11
#define SD_CS 7 // chip select pin for SD card module

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  if (!SD.begin(SD_CS)) {
    Serial.println("Error initializing SD card.");
    return;
  }
  Serial.println("SD card initialized.");
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  String fileName = "Readings.txt";
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile) {
    dataFile.print("Humidity: ");
    dataFile.print(humidity);
    dataFile.print("% - Temperature: ");
    dataFile.print(temperature);
    dataFile.println("C");
    dataFile.close();
  }
  else {
    Serial.println("Error opening file.");
  }

  delay(10000);
}

