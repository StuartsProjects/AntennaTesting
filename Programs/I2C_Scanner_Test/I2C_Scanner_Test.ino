#define programname "I2C_Scanner_Test"
#define programversion "V1.3"
#define dateproduced "29/11/2017"
#define aurthorname "Stuart Robinson"
#include <Arduino.h>

/*
*****************************************************************************************************************************
Tracker Test Programs

Copyright of the author Stuart Robinson - 29/11/2017



These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.
*****************************************************************************************************************************
*/

/*
********************************************************************************************************************************
Program operation

This test program has been scans the I2C bus for valid device, addresses of devices found are printed on the Arduino IDE Serial
monitor. 

Devices used by Tracker porgrams;

I2CDisplay_Backpack 0x08
PCF8574 I\O Expander 0x3F   (used by LCD display also)
UBLOX GPS 0x42
TC74 Temperature Sensor 0x4D (default, can be 0x48 to 0x4F depending on type)
PCF8563address 0x51
MB85RC16PNF FRAM 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57
BME280 Sensor 0x76 or 0x77

********************************************************************************************************************************
*/

/*
********************************************************************************************************************************
Connections

The program uses the standard I2C connections on Arduino.
********************************************************************************************************************************
*/


#include <Wire.h>
#include "I2C_Scanner.h"

#define Serial_Monitor_Baud 115200          //this is baud rate used for the Arduino IDE Serial Monitor

void loop()
{
  Serial.println();
  Serial.println();
  setup_I2CScan();
  run_I2CScan();
  delay(2500);
}


void setup()
{
  
  Serial.begin(Serial_Monitor_Baud);                                   //setup Serial console ouput
  Serial.println();
  Serial.println(F(programname));
  Serial.println(F(programversion));
  Serial.println(F(dateproduced));
  Serial.println(F(aurthorname));
  Serial.println();
  Wire.begin();
 }


