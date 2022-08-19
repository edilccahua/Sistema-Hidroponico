int time=0;
//importar_librerias
//RELAY
int pinrelay = 2;

//SENSOR_DHT11
//temperaturaHumedadAmbiental
#include <dht.h>
dht DHT;
#define DHT11_PIN 8   //uso del pin8

//SENSOR_DS18B20
//temperaturaDelAgua_LIBS
#include <OneWire.h>                
#include <DallasTemperature.h>
OneWire ourWire(3);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire);    //Se declara una variable u objeto para nuestro sensor

//SENSOR_YF-S401
//caudalimetro
volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor = 9;    //Sensor conectado en el pin 5
float factor_conversion=7.5; //para convertir de frecuencia a caudal, segun fabricante

//Función que se ejecuta en interrupción
void ContarPulsos (){ 
  NumPulsos++;  //incrementamos la variable de pulsos
} 

//Función para obtener frecuencia de los pulsos
int ObtenerFrecuencia(){
  int frecuencia;
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  Serial.begin(9600); //al ser interrumpido, tambien aperturamos el 
  frecuencia=NumPulsos; //Hz(pulsos por segundo)
  return frecuencia;
}

void dht11(){
  //PARA SENSOR DHT201, SENSOR DE TEMPERATURA Y HUMEDAD AMBIENTAL
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

void DS18B20(){
  //PARA SENSOR DE TEMPERATURA DEL AGUA
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  Serial.print("Temperatura del agua = ");
  Serial.print(temp);
  Serial.println(" C");
}

void yfs401(){
  //yfs401
  float frecuencia=ObtenerFrecuencia(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m

  //Enviamos por el puerto serie
  
  Serial.print ("Caudal del agua = ");
  Serial.print (caudal_L_m,3); 
  Serial.print (" L/m"); 
}
void setup(){
  //relay
  pinMode(pinrelay, OUTPUT);
  digitalWrite(pinrelay, HIGH);
  
  //dht11
  Serial.begin(9600);
  
  //tempAgua
  sensors.begin();

  //yfs401
  pinMode(PinSensor, INPUT); 
  attachInterrupt(0,ContarPulsos,RISING); //(Interrupcion 0,funcion,Flanco de subida)
}

void loop(){
  Serial.print ("\n");
  Serial.print ("lectura nro: ");
  Serial.print (time/3);
  Serial.print ("\n");
  
  dht11();
  delay(1000);

  DS18B20();
  delay(1000); 
  
  yfs401();
  delay(1000);

  time = time + 3;	//al tener delay de 3000ms en el loop, entonces aprox son 3 seg.
  
  if(time == 300){	//si se cumplen 300s o 10min  aprox
    Serial.print ("\n");
    digitalWrite(pinrelay, LOW);
    Serial.println("DESCANSANDO...");
    delay(12000);	//se descansa un tiempo de 5min o 120000ms
    digitalWrite(pinrelay, HIGH);
    Serial.println("DE NUEVO AL TRABAJO...");
    delay(1000);
    time=0;
  }
}

