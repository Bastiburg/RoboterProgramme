#include <Wire.h>
byte bufLS[8];
int i = 0;

void getRawLightsensorValues() {
  Wire.requestFrom(2, 8);

  while (Wire.available() && i < 8)
  {
    bufLS[i] = Wire.read();

    i++;
  }
  i = 0;
}

byte analyseLightsensorValues()  // gibt an in welche Richtung der Roboter vonder Linie wegfahren
{
  

  if (bufLS[0] == 1 || bufLS[4] == 1) {
    return 2;   //Rueckwaerts();
  }

  else if (bufLS[1] == 1 || bufLS[5] == 1) {
    return 4;   //Links();
  }

  else if (bufLS[2] == 1 || bufLS[6] == 1) {
    return 1;   //Vorwaerts();
  }

  else if (bufLS[3] == 1 || bufLS[7] == 1) {
    return 3;   //Rechts();
  } else {
    return 0;
  }

}
