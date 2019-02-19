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
  aktuellerKompasswert = euler.x();
  delay(BNO055_SAMPLERATE_DELAY_MS);
}


int getCompassValue()
{
  kompass();
  kompassWert = aktuellerKompasswert - anfangswert;
  if (kompassWert < 0)
  {
    kompassWert = 360 + kompassWert;
  }
  return (int) kompassWert;
}




