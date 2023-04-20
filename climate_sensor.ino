#include <SD.h> // SD library for file reading and modifications 
#include <DHT.h> // DHT library for climate sensor
#include <LiquidCrystal.h> // LCD library

#define DHTPIN 4 // connect DHT11 sensor to I/O pin 4 on I2C module
#define DHTTYPE DHT11 // specify DHT sensor type
#define SD_CS 7 // chip select pin for SD card module

// Circuit setup : 
//    microSD card adapter
//        Serial Clock in digital pin 13
//        MISO in digital pin 12
//        MOSI in digital pin 11 
//    LCD display
//        RS in digital pin 8
//        E in digital pin 9
//        D4 in digital pin 4
//        D5 in digital pin 5
//        D6 in digital pin 6
//        D7 in digital pin 7

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // create LCD object and specify pin connections

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // initialize LCD display with 16 columns and 2 rows
  if (!SD.begin(SD_CS)) {
    Serial.println("Error initializing SD card.");
    lcd.print("Error initializing SD card."); // display error message on LCD
    return;
  }
  Serial.println("SD card initialized.");
  lcd.print("SD works"); // display success message on LCD
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

  lcd.clear(); // clear LCD display
  lcd.setCursor(0, 0); // set cursor to first row, first column
  lcd.print("Humidity: "); // display values on LCD
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 1); // set cursor to second row, first column
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print("C");

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
    lcd.print("Error opening file."); // display error message on LCD
  }

  delay(300000); // take readings every 10 seconds
}
