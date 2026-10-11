//#include <boarddefs.h>
//#include <IRremote.h>
//#include <IRremoteInt.h>

#include <QTRSensors.h>
#include <SparkFun_TB6612.h>
//int receiver = 11; 
//IRrecv irrecv(receiver);
//decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h
 

QTRSensors qtr;
const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];

// definimos pines TB6612 y sensores

#define AIN1 2//
#define BIN1 7//
#define AIN2 4//
#define BIN2 8// TB6612FNG
#define PWMA 5//
#define PWMB 6//
#define STBY 9//

#define ADC_SHARP A0//sensor oponente



// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup(){
 Serial.begin(9600);
 // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A1, A2}, SensorCount);
  qtr.setEmitterPin(255);
  //irrecv.enableIRIn();
   
}


void loop(){
//LEEMOS SENSORES FIN DOHYO
 qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 2500 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
   if (sensorValues[i] < 200){
    Serial.print(sensorValues[i]);
    Serial.print('\t');
      digitalWrite(10,HIGH);
     forward(motor1, motor2, 255);
     digitalWrite(10,LOW);
    
   }
   //SENSOR SHARP
// Leemos el promedio de la entrada analógica 0 :
 int ADC_SHARP ADC0_promedio(20);
  if (sensorValues[i] > 100 && analogRead(A0)>350){
    
    back(motor1, motor2, 255);
    }
  else{
    right(motor1, motor2, 180);
    delay(100);
    left(motor1, motor2, 180);
     }
   }
 }
void ALT(){

  (motor1, motor2, 0);
}
int ADC0_promedio(int n){
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}
 
