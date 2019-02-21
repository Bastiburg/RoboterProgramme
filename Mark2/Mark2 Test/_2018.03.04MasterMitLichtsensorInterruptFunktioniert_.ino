#include <Wire.h>

byte a0 = 3;
byte a1 = 4;
byte a2 = 5;
byte a3 = 6;
byte interrupt = 12;
byte linienAbfrage[8];

boolean debug = true;
int messwert[8];

byte schwellenwert = 75;

boolean interruptAusgeloest = false;
byte interruptPin =  2 ;// Pin muss noch festgelegt werden
void setup()
{
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(interrupt, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);


  Wire.begin(2);                //I2C Adresse
  Wire.onRequest(requestEvent); //Funktion, die eine I2C Anfrage beantwortet
  digitalWrite(interrupt, LOW);
  Serial.begin(9600);

   attachInterrupt(digitalPinToInterrupt(interruptPin), interruptMethode, HIGH);

}

void loop()
{
  for (int i = 1; i < 9; i++)
  {

    if (i == 1)
    {
      s6();
      messwert[0] = analogRead(A0);
      if (debug == true)
      {
        Serial.print(messwert[0]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 2)
    {
      s13();
      messwert[1] = analogRead(A0);
      if (debug == true)
      {
        Serial.print(messwert[1]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 3)
    {
      s1();
      messwert[2] = analogRead(A0);
      if (debug == true)
      {
        Serial.print(messwert[2]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 4)
    {
      s3();
      messwert[3] = analogRead(A0);
      if (debug == true)
      {
        Serial.print(messwert[3]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 5)
    {
      s5();
      messwert[4] = analogRead(A0);

      if (debug == true)
      {
        Serial.print(messwert[4]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 6)
    {
      s14();
      messwert[5] = analogRead(A0);
      if (debug == true)
      {
        Serial.print(messwert[5]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 7)
    {
      s0();
      messwert[6] = analogRead(A0);
      if (debug == true)
      {
        Serial.print(messwert[6]);
        Serial.print("\t");
        //sensor ++;
      }
    }
    else if (i == 8)
    {
      s4();
      messwert[7] = analogRead(A0);
      if (debug == true)
      {
        Serial.println(messwert[7]);
        Serial.print("\t");
        //sensor == 1;
      }
    }
  }
  for (int i = 0; i < 8; i++)
  {
    if (messwert[i] < schwellenwert)
    {
      linienAbfrage[i] = 0;
    }
    else
    {
      linienAbfrage[i] = 1;
      if (interruptAusgeloest == false )
      {
        digitalWrite(interrupt, HIGH);
        interruptAusgeloest = true;
      }

    }
  }
  digitalWrite(interrupt, LOW);
}


void s0()
{
  digitalWrite(a0, LOW);
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(a3, LOW);
}

void s1()
{
  digitalWrite(a0, HIGH);
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(a3, LOW);
}

void s3()
{
  digitalWrite(a0, HIGH);
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(a3, LOW);
}

void s4()
{
  digitalWrite(a0, LOW);
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(a3, LOW);
}

void s5()
{
  digitalWrite(a0, HIGH);
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(a3, LOW);
}

void s6()
{
  digitalWrite(a0, LOW);
  digitalWrite(a1, HIGH);
  digitalWrite(a2, HIGH);
  digitalWrite(a3, LOW);
}

void s13()
{
  digitalWrite(a0, HIGH);
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(a3, HIGH);
}

void s14()
{
  digitalWrite(a0, LOW);
  digitalWrite(a1, HIGH);
  digitalWrite(a2, HIGH);
  digitalWrite(a3, HIGH);
}

void requestEvent()
{
  Wire.write(linienAbfrage, (size_t)8);

}

void interruptMethode()
{
  interruptAusgeloest = false;
}
