/**
 * Funktioniert, bei hoher Geschwindigkeit fährt er über die Linie. Ballverfolgung ist noch verbesserungwürdig.
 * kann theoretisch auch für bernd eingesetzt werden
 */

#include <Wire.h>
#include "compass.h"
#include "motor.h"
#include "infrared.h"
#include "lightsensor.h"
#include "control.h"
#include "interrupt.h"

#define TCAADDR 0x70   // Adresse des Multiplexers wird festgelegt

boolean isSet = false;

boolean printSensorValues = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(MotorBrake, OUTPUT);
  pinMode(motor1PWM, OUTPUT);   //Motoren
  pinMode(motor1DIR, OUTPUT);
  pinMode(motor2PWM, OUTPUT);
  pinMode(motor2DIR, OUTPUT);
  pinMode(motor3PWM, OUTPUT);
  pinMode(motor3DIR, OUTPUT);
  pinMode(motor4PWM, OUTPUT);
  pinMode(motor4DIR, OUTPUT);
  pinMode(10, INPUT_PULLUP);    // Pullupschalter festlegen
  pinMode(9, INPUT_PULLUP);     // Pullupschalter festlegen
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptBottom, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptMethod, HIGH);

  InfraredSeeker::Initialize();
  tcaselect(2);
  tcaselect(3);


  if (!bno.begin()) {           //Kompass
    /* There was a problem detecting the BNO055 ... check your connections */
    //Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  (1000);
  bno.setExtCrystalUse(true);
  while (digitalRead(10) == 0) {
    kompass();
  }
  anfangswert = aktuellerKompasswert;
  isSet = true;
  //Serial.println(anfangswert);
}

void loop() {
/*int bDir = ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack));
Serial.print("bDir: ");
Serial.print(bDir);
Serial.print("   gradzahl: ");
Serial.println(irAuswertung(bDir));*/
 
 
 
 if(digitalRead(10) == 1 && !isSet){
    kompass();
    anfangswert = aktuellerKompasswert;
    isSet = true;
  } else if(digitalRead(10) == 0){
    isSet = false;
  }
  if(digitalRead(9) == 1){
    checkInterrupt();
  run(ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack)), 160, false); 
  // 160 funktioniert ziemlich zufallaessig, ab und zu mal aus dem Feld gemacht 
  // wenn safe dann auf 150
  checkInterrupt();
  } else {
    Brake();
  }
    
  
}

