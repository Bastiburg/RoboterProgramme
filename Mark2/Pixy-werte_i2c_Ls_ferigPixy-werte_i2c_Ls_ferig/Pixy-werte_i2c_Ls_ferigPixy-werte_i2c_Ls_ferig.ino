//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//
  
#include <Pixy2.h>
#include <Wire.h>
// This is the main Pixy object 
Pixy2 pixy;
int x = 0;
void setup()
{
  Serial.begin(115200);
 
   Wire.begin(3);
  Wire.onRequest(requestEvent);

  pixy.init();
}

void loop()
{ 
  
    
}

void requestEvent()
{
 
  static int i = 0;
  //uint16_t blocks;

 pixy.ccc.getBlocks();
  x = pixy.ccc.blocks[i].m_x;    //get x position
  
  
    if (x < 250)
    {
      Wire.write(x);
      Wire.write(0);
    }
    else {

      x = x - 250;
      Wire.write(x);
      Wire.write(250);

    }

}

