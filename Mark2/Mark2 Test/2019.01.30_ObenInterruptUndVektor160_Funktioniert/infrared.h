#include<Wire.h>
#define TCAADDR 0x70

int rawDirectionF = 0;
int rawDirectionB = 0;
byte sensorFront = 3;
byte sensorBack = 2;

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();

}

struct InfraredResult
{
  byte Direction;
  byte Strength;
};

class InfraredSeeker
{
  public:
    static void Initialize();
    static boolean Test();
    static void ReadACRaw(byte* buffer);
    static void ReadDCRaw(byte* buffer);
    static InfraredResult ReadAC();
    static InfraredResult ReadDC();
    static int DirectionAngle(byte Direction);
  private:
    static InfraredResult PopulateValues(byte* buffer);
    static void ReadValues(byte OffsetAddress, byte* buffer);
    static const int Address = 0x10 / 2; //Divide by two as 8bit-I2C address is provided
};

void InfraredSeeker::Initialize()
{
  Wire.begin();
  Wire.beginTransmission(InfraredSeeker::Address);
  Wire.write(0x00);
  Wire.endTransmission();
  while (Wire.available() > 0)
    Wire.read();
}

boolean InfraredSeeker::Test()
{
  Wire.beginTransmission(InfraredSeeker::Address);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.requestFrom(InfraredSeeker::Address, 16);
  char Manufacturer_Model[16];
  while (Wire.available() < 16);
  for (byte i = 0; i < 16; i++)
  {
    Manufacturer_Model[i] = Wire.read();
  }
  while (Wire.available() > 0)
    Wire.read();
  return strncmp(Manufacturer_Model, "HiTechncNewIRDir", 16) == 0;
}

void InfraredSeeker::ReadValues(byte OffsetAddress, byte* buffer)
{
  Wire.beginTransmission(InfraredSeeker::Address);
  Wire.write(OffsetAddress);
  Wire.endTransmission();
  Wire.requestFrom(InfraredSeeker::Address, 6);
  while (Wire.available() < 6);
  for (byte i = 0; i < 6; i++)
  {
    buffer[i] = Wire.read();
  }
  while (Wire.available() > 0)
    Wire.read();
}

void InfraredSeeker::ReadACRaw(byte* buffer)
{
  ReadValues(0x49, buffer);
}

void InfraredSeeker::ReadDCRaw(byte* buffer)
{
  ReadValues(0x42, buffer);
}

InfraredResult InfraredSeeker::PopulateValues(byte* buffer)
{
  InfraredResult Data;
  Data.Direction = buffer[0];
  if (buffer[0] != 0)
  {
    if (buffer[0] % 2 == 0)
    {
      Data.Strength = (buffer[buffer[0] / 2] + buffer[buffer[0] / 2 + 1]) / 2;
    }
    else
    {
      Data.Strength = buffer[buffer[0] / 2 + 1];
    }
  }
  else
  {
    Data.Strength = 0;
  }
  return Data;
}

InfraredResult InfraredSeeker::ReadAC()
{
  byte buffer[6];
  ReadACRaw(buffer);
  return PopulateValues(buffer);
}

InfraredResult InfraredSeeker::ReadDC()
{
  byte buffer[6];
  ReadDCRaw(buffer);
  return PopulateValues(buffer);
}

int DirectionAngle(byte Direction)
{
  return Direction * 30 - 150;
}

int getInfraredDirection(byte sensor) {
  tcaselect(sensor);
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  return InfraredBall.Direction;
}

int getInfraredStrength(byte sensor) {
  tcaselect(sensor);
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  return InfraredBall.Strength;
}

int ballDirection(int rawDirectionF, int rawDirectionB, int strengthF, int strengthB) {
  if (strengthF > strengthB)
  {
    if (rawDirectionF == 5)
    {
      return 12;

    }
    else if (rawDirectionF == 6)
    {
      return 1;

    }
    else if (rawDirectionF == 7)
    {
      return 2;

    }
    else if (rawDirectionF == 8)
    {
      return 32;

    }
    else if (rawDirectionF == 4 )
    {
      return 11;

    }
    else if (rawDirectionF == 3)
    {
      return 10;

    }
    else if (rawDirectionF == 2)
    {
      return 92;

    }
  } else {
    if (rawDirectionB == 5)
    {
      return 6;

    }
    else if (rawDirectionB == 6)
    {
      return 7;

    }
    else if (rawDirectionB == 7)
    {
      return 8;

    }
    else if (rawDirectionB == 8)
    {
      return 91;

    }
    else if (rawDirectionB == 4)
    {
      return 5;

    }
    else if (rawDirectionB == 3)
    {
      return 4;

    }
    else if (rawDirectionB == 2)
    {
      return 31;

    }


  }
}



