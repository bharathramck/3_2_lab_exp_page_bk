int sensor = 7;
int push_switch = 6;
int buzzer = 8;
int sensor_value;

void setup() {
  pinMode(sensor, INPUT);
  pinMode(push_switch, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  sensor_value = digitalRead(sensor);
  if (sensor_value == HIGH) {
    digitalWrite(buzzer, HIGH);
  }

  if (digitalRead(push_switch) == HIGH) {
    digitalWrite(buzzer, LOW);
  }
}

int sensor = 7;
int sensor_value;

void setup() {
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensor_value = digitalRead(sensor);
  Serial.println(sensor_value);
}
