#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (10)


Adafruit_BNO055 bno = Adafruit_BNO055();

int rechterSchwellenwert = 10;
int linkerSchwellenwert = 350;

int aktuellerKompasswert = 0;
int anfangswert = 0;
int kompassWert;

float kompass ()
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  /* Display the floating point data */
  //Serial.print("X: ");
  aktuellerKompasswert = euler.x();
  //Serial.print(aktuellerKompasswert);               //euler.x() ist der Befehl zum auslesen des Kompass





  delay(BNO055_SAMPLERATE_DELAY_MS);
}


int getCompassValue() {
  kompass();
  kompassWert = aktuellerKompasswert - anfangswert;
  if (kompassWert < 0)
  {
    kompassWert = 360 + kompassWert;
  }
  return (int) kompassWert;
}


int driveCorrection(int b) {
  if (b > rechterSchwellenwert && b <=180) {
    if (b > rechterSchwellenwert && b <= (rechterSchwellenwert + 10)) {
      return -10;
    } else if ((b > rechterSchwellenwert + 10) && b <= (rechterSchwellenwert + 20)) {
      return -10;
    } else if ((b > rechterSchwellenwert + 20) && b <= (rechterSchwellenwert + 30)) {
      return -20;
    } else if ((b > rechterSchwellenwert + 30) && b <= (rechterSchwellenwert + 40)) {
      return -20;
    } else if ((b > rechterSchwellenwert + 40) && b <= (rechterSchwellenwert + 50)) {
      return -20;
    } else if ((b > rechterSchwellenwert + 50) && b <= (rechterSchwellenwert + 60)) {
      return -30;
    } else if ((b > rechterSchwellenwert + 60) && b <= (rechterSchwellenwert + 70)) {
      return -40;
    } else if ((b > rechterSchwellenwert + 70) && b <= (rechterSchwellenwert + 80)) {
      return -40;
    } else if ((b > rechterSchwellenwert + 80) && b <= (rechterSchwellenwert + 90)) {
      return -50;
    } else if ((b > rechterSchwellenwert + 90) && b <= (rechterSchwellenwert + 100)) {
      return -50;
    } else if ((b > rechterSchwellenwert + 100) && b <= (rechterSchwellenwert + 110)) {
      return -60;
    } else if ((b > rechterSchwellenwert + 110) && b <= (rechterSchwellenwert + 120)) {
      return -60;
    } else if ((b > rechterSchwellenwert + 120) && b <= (rechterSchwellenwert + 130)) {
      return -70;
    } else if ((b > rechterSchwellenwert + 130) && b <= (rechterSchwellenwert + 140)) {
      return -70;
    } else if ((b > rechterSchwellenwert + 140) && b <= (rechterSchwellenwert + 150)) {
      return -80;
    } else if ((b > rechterSchwellenwert + 150) && b <= (rechterSchwellenwert + 160)) {
      return -80;
    } else if ((b > rechterSchwellenwert + 160) && b <= 180) {
      return -90;
    }
  } else if (b < linkerSchwellenwert && b > 180) {
    if (b < linkerSchwellenwert && b >= (linkerSchwellenwert - 10)) {
      return 10;
    } else if ((b < linkerSchwellenwert -10) && b >= (linkerSchwellenwert - 20)) {
      return 10;
    } else if ((b < linkerSchwellenwert -20) && b >= (linkerSchwellenwert - 30)) {
      return 20;
    } else if ((b < linkerSchwellenwert -30) && b >= (linkerSchwellenwert - 40)) {
      return 20;
    } else if ((b < linkerSchwellenwert -40) && b >= (linkerSchwellenwert - 50)) {
      return 20;
    } else if ((b < linkerSchwellenwert -50) && b >= (linkerSchwellenwert - 60)) {
      return 30;
    } else if ((b < linkerSchwellenwert -60) && b >= (linkerSchwellenwert - 70)) {
      return 40;
    } else if ((b < linkerSchwellenwert -70) && b >= (linkerSchwellenwert - 80)) {
      return 40;
    } else if ((b < linkerSchwellenwert -80) && b >= (linkerSchwellenwert - 90)) {
      return 50;
    } else if ((b < linkerSchwellenwert -90) && b >= (linkerSchwellenwert - 100)) {
      return 50;
    } else if ((b < linkerSchwellenwert -100) && b >= (linkerSchwellenwert - 110)) {
      return 60;
    } else if ((b < linkerSchwellenwert -110) && b >= (linkerSchwellenwert - 120)) {
      return 60;
    } else if ((b < linkerSchwellenwert -120) && b >= (linkerSchwellenwert - 130)) {
      return 70;
    } else if ((b < linkerSchwellenwert -130) && b >= (linkerSchwellenwert - 140)) {
      return 70;
    } else if ((b < linkerSchwellenwert -140) && b >= (linkerSchwellenwert - 150)) {
      return 80;
    } else if ((b < linkerSchwellenwert -150) && b >= (linkerSchwellenwert - 160)) {
      return 80;
    } else if ((b < linkerSchwellenwert -160) && b > 180) {
      return 90;
    }
  } else {
    return 0;
  }
}

