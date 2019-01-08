//Test_Settings.h
/*
******************************************************************************************************

LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 28/01/18

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.


To Do:

******************************************************************************************************
*/


#define LCDI2C_Address 0x3F                      //define I2C address for PCF8574 LCD backpack, usually 0x27 or 0x3F

const uint32_t Frequency = 434400000;            //RSSI listen frequency
#define CalibrationOffset 0                      //adjustment for frequency in Hz, assumed at room temp

#define Serial_Monitor_Baud 115200               //this is baud rate used for the Arduino IDE Serial Monitor

