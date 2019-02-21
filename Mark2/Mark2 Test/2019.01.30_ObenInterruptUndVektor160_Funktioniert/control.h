int speedForward = 0;
int angle = 0;
int correct = 0;


byte Direction = 0;

int irAuswertung(int bDir) {
  switch (bDir) {
    case 12:
      return 0;
      break;
    case 1:
      return 290;
      break;
    case 2:
      return 240;
      break;
    case 31:
      return 225;
      break;
    case 32:
      return 225;
      break;
    case 4:
      return 200;
      break;
    case 5:
      return 180;
      break;
    case 6:
      return 140;
      break;
    case 7:
      return 180;
      break;
    case 8:
      return 160;
      break;
    case 91:
      return 135;
      break;
    case 92:
      return 135;
      break;
    case 10:
      return 90;
      break;
    case 11:
      return 30;
      break;
  }
  return 1000;
}

void run(int bDir, int speedValue, boolean p) {
  
    if (irAuswertung(bDir) < 360) {
      drive(irAuswertung(bDir), speedValue, driveCorrection(getCompassValue()));
    } else if (irAuswertung(bDir) == 1000) {
      Brake();
    
  }
  if (p) {
    //Serial.println(irAuswertung(bDir));
    /*Serial.print("InrarotsensorV: ");
    Serial.print(getInfraredDirection(sensorFront));
    Serial.print(" InrarotsensorH: ");
    Serial.print(getInfraredDirection(sensorBack));
    Serial.print(" StärkeV: ");
    Serial.print(getInfraredStrength(sensorFront));
    Serial.print(" StärkeH: ");
    Serial.println(getInfraredStrength(sensorBack));*//*


      Serial.print(" InrarotsensorH: ");
      Serial.print(isb);*/
    /*Serial.print(" KompassAnfangswert: ");
      Serial.print(anfangswert);
      Serial.print(" aktuellerKompasswert: ");
      Serial.print(aktuellerKompasswert);
      Serial.print(" Kompass: ");
      Serial.println(c);*/
    /*Serial.print(" KompassKorrektur: ");
      Serial.print(correct);
      Serial.print(" Geschw.: ");
      Serial.print(speedForward);
      Serial.print(" Fahrtwinkel: ");
      Serial.println(angle);*/
  }
}



