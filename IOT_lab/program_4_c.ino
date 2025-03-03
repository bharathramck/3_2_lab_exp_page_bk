int Buzzer = 6;       // Choose the pin for the Buzzer
int inputPin = 2;     // Choose the input pin for PIR sensor
int ledPin = 13;      // LED pin (you can change this pin number if needed)
int pirState = LOW;   // We start, assuming no motion detected
int val = 0;           // Variable for reading the pin status

void setup() {
  pinMode(ledPin, OUTPUT);      // Declare LED as output
  pinMode(Buzzer, OUTPUT);      // Declare Buzzer as output
  pinMode(inputPin, INPUT);     // Declare PIR sensor as input
  Serial.begin(9600);           // Start serial communication
}

void loop() {
  val = digitalRead(inputPin);           // Read input value from PIR sensor
  int value_ldr = analogRead(A0);        // Read LDR value

  // Check if LDR value is low and motion is detected by PIR sensor
  if ((value_ldr < 300) && (val == HIGH)) {
    if (val == HIGH) {                  // Check if the input is HIGH (motion detected)
      digitalWrite(ledPin, HIGH);       // Turn LED ON
      digitalWrite(Buzzer, HIGH);       // Turn Buzzer ON
      delay(5000);                      // Keep LED and Buzzer ON for 5 seconds

      if (pirState == LOW) {            // If motion was previously not detected
        Serial.println("Motion detected!");  // Print motion detected message
        pirState = HIGH;                // Update the state to HIGH (motion detected)
      }
    } else {
      digitalWrite(ledPin, LOW);        // Turn LED OFF
      digitalWrite(Buzzer, LOW);        // Turn Buzzer OFF

      if (pirState == HIGH) {           // If motion was previously detected
        Serial.println("Motion ended!");  // Print motion ended message
        pirState = LOW;                 // Update the state to LOW (no motion detected)
      }
    }
  }
}
