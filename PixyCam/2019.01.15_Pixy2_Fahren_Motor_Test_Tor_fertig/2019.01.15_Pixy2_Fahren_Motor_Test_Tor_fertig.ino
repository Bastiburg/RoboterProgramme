/**
 * motorwinkel getauscht, links rum
 */


#include <Wire.h>

int komp = 0;
byte k1 = 0;
byte k2 = 0;
int correct = 0;
byte bDir;
byte warten = 0;
int c = 0;
byte c1 = 0;
byte c2 = 0;
int w = 0;
byte w1 = 0;
byte w2 = 0;
int v = 30;   //Drehgeschwindigkeit
int winkel = 0;
#include "motoren.h"

void setup() {
  Wire.begin(4);
  Serial.begin(115200);
 Wire.onReceive(receiveEvent);
  pinMode(motor1PWM, OUTPUT);   //Motoren
  pinMode(motor1DIR, OUTPUT);
  pinMode(motor2PWM, OUTPUT);
  pinMode(motor2DIR, OUTPUT);
  pinMode(motor3PWM, OUTPUT);
  pinMode(motor3DIR, OUTPUT);
  pinMode(motor4PWM, OUTPUT);
  pinMode(motor4DIR, OUTPUT);
  TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
  TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz

}

void loop()
{
  /*
  winkel = 90;
  drive();
  */
  
  Wire.requestFrom(3, 4);

  while (Wire.available())
  {
    c1 = Wire.read(); // receive a byte as character
    c2 = Wire.read();
    c = c1 + c2;
    Serial.println(c);

    w1 = Wire.read(); // receive a byte as character
    w2 = Wire.read();
    w = w1 + w2;
  }
  
  if (w > 20)
  {
    if ( c == 0 )
    {
      brake();
    }

    else if (c < 100 )
    {  
      winkel = 30;
      //winkel = 270;
      drive();
    }

    else if (c > 220)
    {
      winkel = 330;
      //winkel = 90;
      drive();
    }

    else if (100 <= c <= 220)
    {
      winkel = 1;
      drive();
    }
  }
}

void drehenR()
{
  analogWrite(motor1PWM, v);
  analogWrite(motor2PWM, v);
  analogWrite(motor3PWM, v);
  analogWrite(motor4PWM, v);
  digitalWrite(motor1DIR, LOW);         // LOW = dreht sich nach rechts
  digitalWrite(motor2DIR, LOW);
  digitalWrite(motor3DIR, LOW);
  digitalWrite(motor4DIR, LOW);

}

void drehenL()
{
  analogWrite(motor1PWM, v);
  analogWrite(motor2PWM, v);
  analogWrite(motor3PWM, v);
  analogWrite(motor4PWM, v);
  digitalWrite(motor1DIR, HIGH);         // HIGH = dreht sich nach links
  digitalWrite(motor2DIR, HIGH);
  digitalWrite(motor3DIR, HIGH);
  digitalWrite(motor4DIR, HIGH);

}
void nichts ()
{
  analogWrite(motor1PWM, 0);
  analogWrite(motor2PWM, 0);
  analogWrite(motor3PWM, 0);
  analogWrite(motor4PWM, 0);
}

void receiveEvent()
{
  //Serial.println("kompi");

  if (Wire.available() )
  {
    while (Wire.available() )
    {
      k1 = Wire.read();
      k2 = Wire.read();
      komp = k1 + k2;
      //Serial.println(komp);
    }
  }
}


