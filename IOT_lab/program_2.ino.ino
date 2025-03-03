#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
const int trigPin = 3; // Trig pin for the ultrasonic sensor
const int echoPin = 2; // Echo pin for the ultrasonic sensor

long duration; // Duration of the pulse
int distance; // Calculated distance in cm

void setup() {
  lcd.begin(); // Initializes the interface to the LCD display
  lcd.backlight(); // Turns on the LCD backlight
  pinMode(trigPin, OUTPUT); // Sets the trig pin as an output
  pinMode(echoPin, INPUT); // Sets the echo pin as an input
  Serial.begin(9600); // Initializes serial communication at 9600 baud
}

void loop() {
  lcd.clear(); // Clears the LCD screen
  
  digitalWrite(trigPin, LOW); // Sets the trig pin low to prepare for the next pulse
  delayMicroseconds(2); // Small delay to ensure the trig pin is stable
  digitalWrite(trigPin, HIGH); // Sends a high pulse to the trig pin
  delayMicroseconds(10); // Keeps the trig pin high for 10 microseconds
  digitalWrite(trigPin, LOW); // Sets the trig pin low to stop sending the pulse
  
  duration = pulseIn(echoPin, HIGH); // Measures the time it takes for the pulse to return
  distance = duration * 0.0340 / 2; // Calculates the distance based on the duration
  
  Serial.print("Distance: "); // Prints the distance to the serial monitor
  Serial.println(distance); // Prints the measured distance
  
  lcd.setCursor(0, 0); // Sets the cursor to the first column of the first row
  lcd.print("Distance: "); // Prints the text "Distance: "
  lcd.print(distance); // Prints the measured distance
  lcd.print(" cm"); // Adds the unit "cm" to the display
  
  delay(1000); // Waits for 1 second before repeating the loop
}
