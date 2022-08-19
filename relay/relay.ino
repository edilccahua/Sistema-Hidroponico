//relay srd-05vdc
int pinrelay = 10; //se refine el pin de transmision de datos de relay

void setup(){
  Serial.begin(9600);
  pinMode(pinrelay, OUTPUT);
  digitalWrite(pinrelay, HIGH);
}

void loop(){
    digitalWrite(pinrelay, LOW);
    Serial.println("DESCANSANDO...");
    delay(12000);	//tiempo de apagado en ms
    digitalWrite(pinrelay, HIGH);
    Serial.println("DE NUEVO AL TRABAJO...");
    delay(1000);	//tiempo de encendido en ms
}
