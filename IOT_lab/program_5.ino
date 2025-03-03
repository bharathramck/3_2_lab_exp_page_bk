#include <stdlib.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SSID "WiFi Name"
#define PASS "WiFi Password"
#define IP "184.106.153.149"

String msg = "GET /update?key=Your_API_Key";
float temp;
int hum;
String tempC;
int error;

void setup() {
  Serial.begin(115200);
  Serial.println("AT");
  delay(5000);
  if (Serial.find("OK")) {
    connectWiFi();
  }
}

void loop() {
  error = 0;
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  char buffer[10];
  tempC = dtostrf(temp, 4, 1, buffer);
  updateTemp();
  
  if (error == 1) {
    return;
  }
  
  delay(5000);
}

void updateTemp() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);
  
  if (Serial.find("Error")) {
    return;
  }

  cmd = msg;
  cmd += "&field1=";
  cmd += tempC;
  cmd += "&field2=";
  cmd += String(hum);
  cmd += "\r\n";
  
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  
  if (Serial.find(">")) {
    Serial.print(cmd);
  } else {
    Serial.println("AT+CIPCLOSE");
    error = 1;
  }
}

boolean connectWiFi() {
  Serial.println("AT+CWMODE=1");
  delay(2000);
  
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  
  Serial.println(cmd);
  delay(5000);
  
  if (Serial.find("OK")) {
    return true;
  } else {
    return false;
  }
}
