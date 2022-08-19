//SENSOR_DHT11
//temperaturaHumedadAmbiental
#include <dht.h>   //Se requiere de la libreria DHTLib, de las librerias de arduino
dht DHT;
#define DHT11_PIN 8   //uso del pin8

void setup(){
  Serial.begin(9600); //Puerto para entrada  de los datos de sensor
}

void loop(){
  //PARA SENSOR DHT11, SENSOR DE TEMPERATURA Y HUMEDAD AMBIENTAL
  DHT.read11(DHT11_PIN);

  //TEMPERATURA//
  Serial.print("Temperatura ambiental = ");
  Serial.print(DHT.temperature);
  Serial.println(" C");

  //HUMEDAD RELATIVA//
  Serial.print("Humedad Relativa ambiental = ");
  Serial.print(DHT.humidity);
  Serial.println(" %");
}

