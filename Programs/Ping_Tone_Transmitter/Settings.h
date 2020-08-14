//Test_Settings.h
/*
******************************************************************************************************

Tracker Programs for Arduino

Copyright of the author Stuart Robinson - 20/12/18



These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.

This test settinfs file is identical to the transmitter settings file

To Do:

******************************************************************************************************
*/


//*******  Setup Test Parameters Here ! ***************

//LoRa Parameters
const unsigned long Frequency = 434400000;        //frequency of transmission
#define CalibrationOffset 0                       //adjustment for frequency in Hz, assumed at room temp
const byte transmit_power = 10;                   //power for transmissions

const unsigned int transmission_delaymS = 2000;   //mS delay between transmissions
const unsigned int tone_lengthmS = 3000;          //tone length in mS
const unsigned int tone_frequencyHz = 500;        //tone frequency in hertz

//********************************************************

#define Serial_Monitor_Baud 115200                //this is baud rate used for the Arduino IDE Serial Monitor


