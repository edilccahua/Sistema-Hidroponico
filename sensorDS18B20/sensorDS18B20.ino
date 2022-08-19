//SENSOR_DS18B20
//temperaturaDelAgua_LIBS
#include <OneWire.h>                //se requiero de libreria OneWire
#include <DallasTemperature.h> 		//Se requiere de libreria DallasTemperature
OneWire ourWire(3);                //Se establece el pin 3  como bus OneWire
DallasTemperature sensors(&ourWire);    //Se declara una variable u objeto para nuestro sensor

void setup(){
	Serial.begin(9600);
	sensors.begin();
}

void loop(){
  //PARA SENSOR DE TEMPERATURA DEL AGUA
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  Serial.print("Temperatura del agua = ");
  Serial.print(temp);
  Serial.println(" C");
  delay(1000);
}
