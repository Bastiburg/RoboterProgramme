#include <math.h>

double pi = M_PI;



int velocity = 140;
int drehGeschwindigkeit = 70;
int gegenfahrGeschwindigkeit = 20;

int fahrzeit = 10000;
int FahrzeitVH = 400;
int FahrzeitS = 400;

byte motor1PWM = 10;   // Vorne Links
byte motor1DIR = 11;

byte motor2PWM = 9;   // Vorne Rechts
byte motor2DIR = 8;

byte motor3PWM = 5;   // Hinten Rechts
byte motor3DIR = 6;

byte motor4PWM = 3;    // Hinten Links
byte motor4DIR = 4;

boolean richtungVL = false; // Vorne Links            false entspreicht LOW, true entspricht HIGH
boolean richtungVR = false; // Vorne Rechts
boolean richtungHL = false; // Hinten Links
boolean richtungHR = false; // Hinten Rechts

//boolean printMotor = false;

double g1V(int degree, int sp) {
  return fabs(sp - 10) * (double)cos((pi / 180) * (degree + 45)); // Berechnung der Motorwerte für die Motoren auf der "realen Achse" genutzt wird dies für die Motoren 1 und 3
}   // degree: fahrtwinkel gegen den Uhrzeigersinn von 0-359°;  sp: geschwindigkeit in Bewegungsrichtung; correct: kann für Korrektur durch Kompass genutzt werden;

double g2V(int degree, int sp) {
  return sp * (double)sin((pi / 180) * (degree + 45 )); // Berechnung der Motorwerte für die Motoren auf der "imaginären Achse" genutzt wird dies für die Motoren 2 und 4
}     // degree: fahrtwinkel gegen den Uhrzeigersinn von 0-359°;  sp: geschwindigkeit in Bewegungsrichtung; correct: kann für Korrektur durch Kompass genutzt werden;

void motorStop(byte m) {
  switch (m) {
    case 1:
      analogWrite(motor1PWM, 0);
      break;
    case 2:
      analogWrite(motor2PWM, 0);
      break;
    case 3:
      analogWrite(motor3PWM, 0);
      break;
    case 4:
      analogWrite(motor4PWM, 0);
      break;
  }
  delay(50);
}

void g1(double v, int correct) {
  if (correct <= -40) {
    if (richtungVL == false) {
      richtungVL = true;
      motorStop(1);
      digitalWrite(motor1DIR, HIGH);
    }
    analogWrite(motor1PWM, drehGeschwindigkeit);
    if (richtungHR == false) {
      richtungHR = true;
      motorStop(3);
      digitalWrite(motor3DIR, HIGH);
    }
    analogWrite(motor3PWM, drehGeschwindigkeit);
  } else if (correct >= 40) {
    if (richtungVL == true) {
      richtungVL = false;
      motorStop(1);
      digitalWrite(motor1DIR, LOW);
    }
    analogWrite(motor1PWM, drehGeschwindigkeit);
    if (richtungHR == true) {
      richtungHR = false;
      motorStop(3);
      digitalWrite(motor3DIR, LOW);
    }
    analogWrite(motor3PWM, drehGeschwindigkeit);
  }
  else {
    if (v < 0) {
      if (richtungVL == false) {
        richtungVL = true;
        motorStop(1);
        digitalWrite(motor1DIR, HIGH);
      }
      analogWrite(motor1PWM, (int)fabs((v * -1) - correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert
      if (richtungHR == true) {
        richtungHR = false;
        motorStop(3);
        digitalWrite(motor3DIR, LOW);
      }
      analogWrite(motor3PWM, (int)fabs((v * -1) + correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert

    } else if (v > 0) {
      if (richtungVL == true) {
        richtungVL = false;
        motorStop(1);
        digitalWrite(motor1DIR, LOW);
      }
      analogWrite(motor1PWM, (int)fabs(v + correct));
      if (richtungHR == false) {
        richtungHR = true;
        motorStop(3);
        digitalWrite(motor3DIR, HIGH);
      }
      analogWrite(motor3PWM, (int)fabs(v - correct));
    }
  }
}

void g2(double v, int correct) {
  if (correct <= -40) {
    if (richtungVR == false) {
      richtungVR = true;
      motorStop(2);
      digitalWrite(motor2DIR, HIGH);
    }
    analogWrite(motor2PWM, drehGeschwindigkeit);
    if (richtungHL == false) {
      richtungHL = true;
      motorStop(4);
      digitalWrite(motor4DIR, HIGH);
    }
    analogWrite(motor4PWM, drehGeschwindigkeit);
  }
  else if (correct >= 40) {
    if (richtungVR == true) {
      richtungVR = false;
      motorStop(2);
      digitalWrite(motor2DIR, LOW);
    }
    analogWrite(motor2PWM, drehGeschwindigkeit);
    if (richtungHL == true) {
      richtungHL = false;
      motorStop(4);
      digitalWrite(motor4DIR, LOW);
    }
    analogWrite(motor4PWM, drehGeschwindigkeit);
  }
  else {
    if (v < 0) {
      if (richtungVR == true) {
        richtungVR = false;
        motorStop(2);
        digitalWrite(motor2DIR, LOW);
      }
      analogWrite(motor2PWM, (int)fabs((v * -1) + correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert
      if (richtungHL == false) {
        richtungHL = true;
        motorStop(4);
        digitalWrite(motor4DIR, HIGH);
      }
      analogWrite(motor4PWM, (int)fabs((v * -1) - correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert

    } else if (v > 0) {
      if (richtungVR == false) {
        richtungVR = true;
        motorStop(2);
        digitalWrite(motor2DIR, HIGH);
      }
      analogWrite(motor2PWM, (int)fabs(v - correct));
      if (richtungHL == true) {
        richtungHL = false;
        motorStop(4);
        digitalWrite(motor4DIR, LOW);
      }
      analogWrite(motor4PWM, (int)fabs(v + correct));
    }
  }
}

void drive() {
  g1(g1V(winkel, velocity), correct);
  g2(g2V(winkel, velocity), correct);
}

void brake() {
  analogWrite(motor1PWM, 0);
  analogWrite(motor2PWM, 0);
  analogWrite(motor3PWM, 0);
  analogWrite(motor4PWM, 0);
  //delay(50);
}
void gegenfahren() {
//brake();
 
  analogWrite(motor1PWM, gegenfahrGeschwindigkeit);
  analogWrite(motor2PWM, gegenfahrGeschwindigkeit);
  analogWrite(motor3PWM, gegenfahrGeschwindigkeit);
  analogWrite(motor4PWM, gegenfahrGeschwindigkeit);
  
  if (digitalRead(motor1DIR) == 1) {
    digitalWrite(motor1DIR, LOW);
    richtungVL = false;
  }
  else {
    digitalWrite(motor1DIR, HIGH);
    richtungVL = true;
  }
  if (digitalRead(motor2DIR) == 1) {
    digitalWrite(motor2DIR, LOW);
    richtungVR = false;
  }
  else {
    digitalWrite(motor2DIR, HIGH);
    richtungVR = true;
  }
  if (digitalRead(motor3DIR) == 1) {
    digitalWrite(motor3DIR, LOW);
    richtungHR = false;
  }
  else {
    digitalWrite(motor3DIR, HIGH);
    richtungHR = true;
  }
  if (digitalRead(motor4DIR) == 1) {
    digitalWrite(motor4DIR, LOW);
    richtungHL = true;
  }
  else {
    digitalWrite(motor4DIR, HIGH);
    richtungHL = true;
  }
}
  


/*
void awayFromLine()
{
  switch (richtung) {
    case 1:   //Hinten
    winkel = 1;
      drive();
      delay(FahrzeitVH*10);
      brake();
      while ( bDir == 91 || bDir == 8 || bDir == 7 || bDir == 6 || bDir == 5 || bDir == 4 || bDir == 31 || bDir == 100) {
        brake();
      }
      break;
    case 2:  //Vorne
      winkel = 180;
      drive();
      delay(FahrzeitVH*10);
      brake();
      while ( bDir == 32 || bDir == 2  || bDir == 1 || bDir == 12 || bDir == 11 || bDir == 10 || bDir == 92 || bDir == 100 ) {
        brake();
      }
      break;
    case 3: //Links
      winkel = 270;
      drive();
      delay(FahrzeitS*10);
      brake();
      while (bDir == 8 || bDir == 91 || bDir == 92 || bDir == 10  || bDir == 7  || bDir == 11 || bDir == 100 ) {
      }
      break;
    case 4: //Rechts
      winkel = 90;
      drive();
      delay(FahrzeitS*10);
      brake();
      while (bDir == 2 || bDir == 32 || bDir == 31 || bDir == 4  || bDir == 1  || bDir == 5 || bDir == 100 ) {
      }
      break;
  }
  //warten = 0;
}

void run()
{
   if (interruptet == true)
    {
    //  warten = 1;
    gegenfahren();
    delay(fahrzeit *10);
    brake();
    interruptet = false;
   // awayFromLine();
    }
 else if (winkel == 400)
  {
    brake();
  }
  else if (winkel < 360)
  {
    drive();
  }*/






