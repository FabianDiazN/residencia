#include "DHT.h"
//Declaracion de variables
int mq2;
int measurePin = A5; 
int ledPower = 12;  
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
DHT dht(3, DHT11);

void setup(){

  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  dht.begin();

}
void loop(){

  digitalWrite(ledPower,LOW); 
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); 

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); 
  delayMicroseconds(sleepTime);
  
  //Calculos matematicos
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;
  delay(1000);
  //Leer sensor de humedad/temperatura
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //leer sensor de gas
  mq2=analogRead(A2);

  Serial.print("  Gases(ppm):");
  Serial.print(mq2);
  Serial.print(",");
  //microgramos/metro cúbico ( µg/m3)
  Serial.print("  Densidad de polvo (ug/m3):");
  Serial.print(dustDensity);
  Serial.print(",");
  Serial.print("  Humedad:");
  Serial.print(h);
  Serial.print("%");
  Serial.print(",");
  Serial.print("  Temperatura: ");
  Serial.print(t);
  Serial.println(" C");

}
