//caudalimetro_yf401_libs
volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor = 5;    //Sensor conectado en el pin 5
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
  frecuencia=NumPulsos; //Hz(pulsos por segundo)
  return frecuencia;
}


void setup(){
  Serial.begin(9600);
  //yfs401
  pinMode(PinSensor, INPUT); 
  attachInterrupt(0,ContarPulsos,RISING); //(Interrupcion 0(Pin5),funcion,Flanco de subida)
}

void loop(){
  //yfs401
  float frecuencia=ObtenerFrecuencia(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  
  Serial.print ("Caudal: "); 
  Serial.print (caudal_L_m,3); 
  Serial.print (" L/m");
}

