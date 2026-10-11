void setup() {
  // Comunicación seria a 9600 baudios
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}


void loop() {
  // Leemos el promedio de la entrada analógica 0 :
  int ADC_SHARP=ADC0_promedio(200);
  if(ADC_SHARP>350)
  {
    digitalWrite(9, HIGH);
    Serial.print("Objeto Detectado:");
    adelante;
  }
  else
  {
    digitalWrite(9, LOW);
    Serial.print("Objeto ausente:");
    derecha;
  }
  
  Serial.println(ADC_SHARP);
  delay(10);
}

int ADC0_promedio(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}
 void adelante(){

  
 }

 void atras(){

  
 }

 void derecha(){

  
 }

 void izquierda(){

  
 }
