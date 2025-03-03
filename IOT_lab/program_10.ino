#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 5
#define DHTTYPE DHT11
String apiKey = "OX9T8Y9OL9HD0UBP";
String Host_Name = "Pantech";
String Password = "pantech123";
SoftwareSerial ser(2, 3);
int i = 1;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  ser.begin(115200);
  ser.println("AT+RST");
  dht.begin();
  char inv = '"';
  String cmd = "AT+CWJAP";
  cmd += "=";
  cmd += inv;
  cmd += Host_Name;
  cmd += inv;
  cmd += ",";
  cmd += inv;
  cmd += Password;
  cmd += inv;
  ser.println(cmd);
}

void loop() {
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  String state1 = String(humidity);
  String state2 = String(temperature);
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";
  ser.println(cmd);
  Serial.println(cmd);

  if (ser.find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }

  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += String(state1);
  getStr += "&field2=";
  getStr += String(state2);
  getStr += "\r\n\r\n";

  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  Serial.println(cmd);

  if (ser.find(">")) {
    ser.print(getStr);
    Serial.print(getStr);
  } else {
    ser.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }

  delay(1000);
}
