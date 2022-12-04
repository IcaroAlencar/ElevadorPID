/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

#define TRIG 4 // D2 pino trig
#define ECHO 5 // D1 pino echo
#define SOUND_SPEED 0.035 // cm/us
#define D5 14 // Sobe


long duration;
float distanceCm, distanceCmAnt;

//#define PIN_INPUT 0
//#define PIN_OUTPUT 3

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=1, Ki=0.5, Kd=0.1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  //Input = analogRead(PIN_INPUT);
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{

  //limpando a TRIG
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  //pulso de 10us
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  //buscando distancia
  duration = pulseIn(ECHO, HIGH);

  distanceCm = duration*SOUND_SPEED/2;

  Input = distanceCm;
  myPID.Compute();
  analogWrite(D5,Output);


}
