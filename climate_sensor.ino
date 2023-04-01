#include <SD.h> // SD library for file reading and modifications 
#include <DHT.h> // DHT library for climate sensor
#include <Wire.h> // Wire Library for I2C module configuration

#define DHTPIN 4 // connect DHT11 sensor to I/O pin 4 on I2C module
#define DHTTYPE DHT11 // specify DHT sensor type
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
  float humidity = dht.readHumidity(); // read values 
  float temperature = dht.readTemperature();
  Serial.print("Humidity: "); // print values in terminal
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  String fileName = "Readings.txt"; // name the file "Readings.txt"
  File dataFile = SD.open(fileName, FILE_WRITE); // open file named "Readings.txt" on SD card
  if (dataFile) {
    dataFile.print("Humidity: "); // print values to SD card
    dataFile.print(humidity);
    dataFile.print("% - Temperature: ");
    dataFile.print(temperature);
    dataFile.println("C");
    dataFile.close(); // close the file
  }
  else {
    Serial.println("Error opening file."); // print error message if file is missing
  }

  delay(10000); // take readings every 10 seconds
}

