#include "DHT.h"
#include "ThingSpeak.h"
#include "WiFi.h"

const char* ssid = "INFINITUMDIAZ_2.4";              //SSID del router.
const char* password = "Xk83yF65Zf";                //Contraseña del router.

unsigned long channelID = 1923323;                //ID del canal.
const char* WriteAPIKey = "C67GGD6EG9S9X3LD";     //Write API Key del canal.

WiFiClient cliente;
//Declaracion de variables
int mq135;
const int measurePin = 34; 
const int ledPower = 22;  
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
DHT dht(23, DHT11);


void setup(){
  
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conectado!");

  ThingSpeak.begin(cliente);
  
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  Serial.begin(9600);
  dht.begin();
}
void loop(){


  voMeasured = analogRead(measurePin); 

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); 
  delayMicroseconds(sleepTime);
  
  //Calculos matematicos
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;

  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  
  //microgramos/metro cúbico ( µg/m3)
  mq135=analogRead(35);

  Serial.print("  Gases(ppm):");
  Serial.print(mq135);
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
  //Envio de datos a ThingSpeak
  ThingSpeak.setField (1,t);
  ThingSpeak.setField (2,h);
  ThingSpeak.setField (3,dustDensity);
  ThingSpeak.setField (4,mq135);
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak!");
  delay(14000);
}
