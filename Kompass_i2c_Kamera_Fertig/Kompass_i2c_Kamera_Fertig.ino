#include <Wire.h>
#include "kompass.h"
#define TCAADDR 0x70
int x = 0;
byte x1;
byte x2;

void setup() {
Serial.begin(9600);
  Wire.begin(2);
  pinMode(8, INPUT_PULLUP); // Kompass Schalter
//  Wire.onRequest(requestEvent);
  if (!bno.begin()) {           //Kompass
    // There was a problem detecting the BNO055 ... check your connections
    while (1);
  }
  (1000);
  bno.setExtCrystalUse(true);
  while (digitalRead(8) == 1) { //testweise
    kompass();
    //   Serial.println("while");
  }
  anfangswert = aktuellerKompasswert;
}

void loop() {

//Serial.println(getCompassValue());

  kompass();
  x = getCompassValue();
  Wire.beginTransmission(4);
  //Serial.println(x);
  x1 = x/2;
  if (x % 2 == 1) {
    x2 = x1+1;
  }
  Wire.write(x1);
  Wire.write(x2);
   Wire.endTransmission();
  delay(100);
}
