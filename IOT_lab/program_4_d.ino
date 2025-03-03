#define LAMP  8  // Choose the pin for the RELAY
#define PIR 13   // Choose the input pin (for PIR sensor)

void setup() {
  Serial.begin(9600);
  pinMode(LAMP, OUTPUT); // Declare lamp as output
  pinMode(PIR, INPUT);   // Declare PIR sensor as input
}

void loop() {
  int value_ldr = analogRead(A4);    // Read LDR value
  int value_pir = digitalRead(PIR);  // Read PIR sensor value
  
  Serial.println(value_ldr);         // Print LDR value
  Serial.println(value_pir);         // Print PIR sensor value
  
  if (value_ldr < 300 && value_pir == HIGH) { // If it's dark and motion is detected
    digitalWrite(LAMP, HIGH);  // Turn ON the light
    delay(6000);               // Keep the light on for 6 seconds
  } else {
    digitalWrite(LAMP, LOW);   // Turn OFF the light
  }
}
