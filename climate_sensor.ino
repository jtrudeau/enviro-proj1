#include <SD.h> // SD library for file reading and modifications 
#include <DHT.h> // DHT library for climate sensor
#include <LiquidCrystal.h> // LCD library

const int DHTPIN = 4;
const int DHTTYPE = DHT11;
const int SD_CS = 7;
const int rs = 8, en = 9, d4 = 5, d5 = 3, d6 = 6, d7 = 10;

// Circuit setup : 
//    microSD card adapter
//        Serial Clock in digital pin 13
//        MISO in digital pin 12
//        MOSI in digital pin 11 

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // create LCD object and specify pin connections

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // initialize LCD display with 16 columns and 2 rows
  if (!SD.begin(SD_CS)) {
    Serial.println("Error initializing SD card.");
    lcd.print("SD Error");
    delay(1000); // display error message on LCD
    return;
  }
  Serial.println("SD card initialized.");
  lcd.print("SD works");
  delay(1000); // display success message on LCD
  dht.begin(); 
}

void loop() {
  int humidity = dht.readHumidity(); // read values 
  float temperature = dht.readTemperature();
  Serial.print("Humidity: "); // print values in terminal
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  lcd.clear(); // clear LCD display
  lcd.setCursor(0,0);
  lcd.print("Humidity: "); // display values on LCD
  lcd.print(humidity);
  lcd.print("%   ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
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
    lcd.print("File error."); // display error message on LCD
  }
delay(300000);

}