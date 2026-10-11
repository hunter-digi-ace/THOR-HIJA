#include <IRremote.h>
int receptor = 11;
int led = 13;
IRrecv irrecv(receptor);
decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA LA RECEPCIÓN
  pinMode(led, OUTPUT);
}
 
void loop()
{
 if (irrecv.decode(&codigo))
 {
Serial.println(codigo.value, DEC);

      if (codigo.value==16720095)//CÓDIGO DEL NÚMERO CERO PARA ACTIVAR LED 0xFF6897
      {
         digitalWrite(led,HIGH);
      }

      if (codigo.value==16736415)//CÓDIGO DEL NÚMERO UNO PARA DESACTIVAR LED
      {
         digitalWrite(led,LOW);
      }
    
delay(500);
irrecv.resume();

 }
}
