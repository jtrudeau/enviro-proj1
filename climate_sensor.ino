#include <SD.h> // SD library for file reading and modifications 
#include <DHT.h> // DHT library for climate sensor

#define DHTPIN 4 // connect DHT11 sensor to I/O pin 4
#define DHTTYPE DHT11 // specify DHT sensor type
#define SD_CS 7 // chip select pin for SD card module

DHT dht(DHTPIN, DHTTYPE);

// Circuit setup : 
//    microSD card adapter
//        Serial Clock in digital pin 13
//        MISO in digital pin 12
//        MOSI in digital pin 11 
//    I2C module
//        SCL (Clock Line) in analog pin A5
//        SDA (Serial Data) in analog pin A4


void setup() {
  Serial.begin(9600);
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
