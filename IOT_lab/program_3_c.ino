#include <dht.h>
#include <LiquidCrystal.h>

dht DHT;
const int RS = 2, EN = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);  // Set Uno pins that are connected to the LCD, 4-bit mode

void setup() {
  lcd.begin(16, 2);  // Initialize the 16x2 LCD
}

void loop() {
  int readDHT = DHT.read11(8);  // Grab 40-bit data packet from DHT sensor
  
  lcd.clear();  // Clear the LCD screen
  lcd.setCursor(0, 0);  // Set cursor to first row, first column
  lcd.print("Temp: "); 
  lcd.print(DHT.temperature);  // Display temperature
  lcd.print("C");
  
  lcd.setCursor(0, 1);  // Set cursor to second row, first column
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);  // Display humidity
  lcd.print("%");
  
  delay(3000);  // Wait for 3 seconds before updating
}
