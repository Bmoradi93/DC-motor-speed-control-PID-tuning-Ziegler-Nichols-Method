#include <FreqMeasure.h>
#include <math.h>
int motorA1 = 5;
int motorA2 = 6;
float Speed = 0;
float error = 0;
float pTerm, iTerm, dTerm;
float controllerOut = 0;
float setPoint = 30;
float Feedback = 0;
float sumError = 0;
float preError = 0;
float Kp = 0.03;
float Kd = 0.005;
float Ki = 0.005;
float command = 0;
int count = 0;
double sum;
void setup() {
  pinMode(5 , OUTPUT) ;
  pinMode(6 , OUTPUT) ;
  Serial.begin(9600) ;
  FreqMeasure.begin();
}
void loop() {

  if (FreqMeasure.available()){
sum = sum + FreqMeasure.read();
count = count +1 ;
if (count > 30){
  float frequency  = FreqMeasure.countToFrequency(sum/count) ;
  //Serial.println(frequency/500) ;
  Feedback = frequency/500;
  //Serial.println(Feedback) ;
  sum = 0 ;
  count = 0 ;
}
}
  error = (setPoint - Feedback);
  Serial.println(Feedback) ;
  sumError = sumError + error;
  pTerm = Kp*error;
  iTerm = Ki*sumError;
  dTerm = Kd*(error - preError);
  //dTerm = Kd*N*(1+N*sumError);
  if(iTerm>75)
  {
    iTerm = 75;
  }
  preError = error;
  controllerOut = pTerm + iTerm + dTerm;
  if(abs(controllerOut)>75)
  {
      controllerOut = 75;

  }
  Speed = controllerOut/75*255;
    digitalWrite(5 , LOW);
    analogWrite(6 , Speed);
}
