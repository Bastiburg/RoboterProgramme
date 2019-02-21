#include <math.h>

int FahrzeitVH = 700; // Fahrzeit Vorne/Hinten
int FahrzeitS = 600; // Fahrzeit Seite
int imKreisGeschw = 20;

double pi = M_PI;

byte motor1PWM = 11;   // Vorne Links
byte motor1DIR = 12;

byte motor2PWM = 6;   // Vorne Rechts
byte motor2DIR = 7;

byte motor3PWM = 5;   // Hinten Rechts
byte motor3DIR = 4;

byte motor4PWM = 3;    // Hinten Links
byte motor4DIR = A1;    //Bernd: 2; Jochen: A1;

byte MotorBrake = A6;

//boolean printMotor = false;

double g1V(int degree, int sp) {
  return fabs(sp - 10) * (double)cos((pi / 180) * (degree + 45)); // Berechnung der Motorwerte für die Motoren auf der "realen Achse" genutzt wird dies für die Motoren 1 und 3
}   // degree: fahrtwinkel gegen den Uhrzeigersinn von 0-359°;  sp: geschwindigkeit in Bewegungsrichtung; correct: kann für Korrektur durch Kompass genutzt werden;

double g2V(int degree, int sp) {
  return sp * (double)sin((pi / 180) * (degree + 45 )); // Berechnung der Motorwerte für die Motoren auf der "imaginären Achse" genutzt wird dies für die Motoren 2 und 4
}     // degree: fahrtwinkel gegen den Uhrzeigersinn von 0-359°;  sp: geschwindigkeit in Bewegungsrichtung; correct: kann für Korrektur durch Kompass genutzt werden;


void g1(double v, int correct) {
  if (correct <= -40) {
    analogWrite(motor1PWM, 100);
    digitalWrite(motor1DIR, HIGH);
    analogWrite(motor3PWM, 100);
    digitalWrite(motor3DIR, HIGH);
  } else if (correct >= 40) {
    analogWrite(motor1PWM, 100);
    digitalWrite(motor1DIR, LOW);
    analogWrite(motor3PWM, 100);
    digitalWrite(motor3DIR, LOW);
  } else {
    if (v < 0) {
      analogWrite(motor1PWM, (int)fabs((v * -1) - correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert
      digitalWrite(motor1DIR, HIGH);
      analogWrite(motor3PWM, (int)fabs((v * -1) + correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert
      digitalWrite(motor3DIR, LOW);
      /*if (printMotor) {
        Serial.print("Motor 1: ");
        Serial.print((v * -1)-correct);
        Serial.print(" ");
        Serial.println("Drerichtung: 1");
        Serial.print("Motor 3: ");
        Serial.print((v * -1)+correct);
        Serial.print(" ");
        Serial.println("Drerichtung: 0");
        }*/
    } else if (v > 0) {
      analogWrite(motor1PWM, (int)fabs(v + correct));
      digitalWrite(motor1DIR, LOW);
      analogWrite(motor3PWM, (int)fabs(v - correct));
      digitalWrite(motor3DIR, HIGH);
      /*if (printMotor) {
        Serial.print("Motor 1: ");
        Serial.print(v);
        Serial.print(" ");
        Serial.println("Drerichtung: 0"); // 0 bedeutet rechts drehen
        Serial.print("Motor 3: ");
        Serial.print(v);
        Serial.print(" ");
        Serial.println("Drerichtung: 1"); // 1 bedeutet links drehen
        }*/
    }
  }
}

void g2(double v, int correct) {
  if (correct <= -40) {
    analogWrite(motor2PWM, 100);
    digitalWrite(motor1DIR, HIGH);
    analogWrite(motor4PWM, 100);
    digitalWrite(motor3DIR, HIGH);
  } else if (correct >= 40) {
    analogWrite(motor2PWM, 100);
    digitalWrite(motor1DIR, LOW);
    analogWrite(motor4PWM, 100);
    digitalWrite(motor3DIR, LOW);
  } else {
    if (v < 0) {
      analogWrite(motor2PWM, (int)fabs((v * -1) + correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert
      digitalWrite(motor2DIR, LOW);
      analogWrite(motor4PWM, (int)fabs((v * -1) - correct)); //Bei negativer Geschwindigkeit muss der Wert für den Motor positiv sein, lediglich die Drehrichtung wird geändert
      digitalWrite(motor4DIR, HIGH);
      /*if (printMotor) {
        Serial.print("Motor 2: ");
        Serial.print((v * -1)+correct);
        Serial.print(" ");
        Serial.println("Drerichtung: 0");
        Serial.print("Motor 4: ");
        Serial.print((v * -1)-correct);
        Serial.print(" ");
        Serial.println("Drerichtung: 1");
        }*/
    } else if (v > 0) {
      analogWrite(motor2PWM, (int)fabs(v - correct));
      digitalWrite(motor2DIR, HIGH);
      analogWrite(motor4PWM, (int)fabs(v + correct));
      digitalWrite(motor4DIR, LOW);
      /*if (printMotor) {
        Serial.print("Motor 2: ");
        Serial.print(v);
        Serial.print(" ");
        Serial.println("Drerichtung: 1");
        Serial.print("Motor 4: ");
        Serial.print(v);
        Serial.print(" ");
        Serial.println("Drerichtung: 0");
        }*/
    }
  }
}

void drive(int angle, int velocity, int correct) {
  g1(g1V(angle, velocity), correct); //Ansteurung der Motoren mit der berechneten Geschwindigkeit
  g2(g2V(angle, velocity), correct);
}

void Brake()
{
  analogWrite(MotorBrake, HIGH);
  analogWrite(motor1PWM, 0   );
  digitalWrite(motor1DIR, LOW);
  analogWrite(motor2PWM, 0  );
  digitalWrite(motor2DIR, HIGH);
  analogWrite(motor3PWM, 0 );
  digitalWrite(motor3DIR, HIGH);
  analogWrite(motor4PWM, 0  );
  digitalWrite(motor4DIR, LOW);
}

void drehenGegenUhr()
{
  digitalWrite(motor1DIR, HIGH);
  analogWrite(motor1PWM, imKreisGeschw);
  digitalWrite(motor2DIR, HIGH);
  analogWrite(motor2PWM, imKreisGeschw);
  digitalWrite(motor3DIR, HIGH);
  analogWrite(motor3PWM, imKreisGeschw);
  digitalWrite(motor4DIR, HIGH);
  analogWrite(motor4PWM, imKreisGeschw);

}

void drehenImUhr()
{
  digitalWrite(motor1DIR, LOW);
  analogWrite(motor1PWM, imKreisGeschw);
  digitalWrite(motor2DIR, LOW);
  analogWrite(motor2PWM, imKreisGeschw);
  digitalWrite(motor3DIR, LOW);
  analogWrite(motor3PWM, imKreisGeschw);
  digitalWrite(motor4DIR, LOW);
  analogWrite(motor4PWM, imKreisGeschw);

}

void ausrichtenAnLinie()
{
  getCompassValue();
  if (kompassWert > 10 && kompassWert < 181)
  {
    drehenGegenUhr();
  }
  if (kompassWert < 350 && kompassWert > 180)
  {
    drehenImUhr();
  }
}
