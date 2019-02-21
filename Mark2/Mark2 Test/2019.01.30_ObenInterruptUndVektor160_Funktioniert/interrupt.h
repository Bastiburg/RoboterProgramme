byte interruptPin = 2;
byte interruptBottom = 8;

boolean volatile interrupted = false;

void interruptMethod() {
  Brake();

  interrupted = true;
}

void awayFromLine() {
  int bDir = ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack));;
  getRawLightsensorValues();
  Direction = analyseLightsensorValues();
  if (Direction > 0) {
    Brake();
    if (Direction == 1) {
      drive(0, 100, 0);
      delay(FahrzeitVH);
      Brake();
      while ( bDir == 91 || bDir == 8 || bDir == 7 || bDir == 6 || bDir == 5 || bDir == 4 || bDir == 31 ) {
        bDir = ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack));
        ausrichtenAnLinie();
      }
    } else if (Direction == 2) {
      drive(180, 100, 0);
      delay(FahrzeitVH);
      Brake();
      while ( bDir == 32 || bDir == 2  || bDir == 1 || bDir == 12 || bDir == 11 || bDir == 10 || bDir == 92  ) {
        bDir =  ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack));
        ausrichtenAnLinie();
      }
    }
    else if (Direction == 3) {
      drive(270, 100, 0);
      delay(FahrzeitS);
      Brake();
      while (bDir == 8 || bDir == 91 || bDir == 92 || bDir == 10  || bDir == 7  || bDir == 11  ) {
        bDir = ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack));
        ausrichtenAnLinie();
      }
    }
    else if (Direction == 4) {
      drive(90, 100, 0);
      delay(FahrzeitS);
      Brake();
      while (bDir == 2 || bDir == 32 || bDir == 31 || bDir == 4  || bDir == 1  || bDir == 5 ) {
        bDir = ballDirection(getInfraredDirection(sensorFront), getInfraredDirection(sensorBack), getInfraredStrength(sensorFront), getInfraredStrength(sensorBack));
        ausrichtenAnLinie();
      }
    }
  }
}

void checkInterrupt()
{
  if (interrupted == true)
  {
    Brake();
    int bDir;
    interrupted = false;
    analyseLightsensorValues();
    awayFromLine();
    digitalWrite(interruptBottom, HIGH);
    digitalWrite(interruptBottom, LOW);


  }
}

