//Settings.h for receiver
/*
******************************************************************************************************

LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.

To Do:

******************************************************************************************************
*/

//*******  Setup Test Parameters Here ! ***************

//LoRa Modem Parameters
const uint32_t Frequency = 434400000;             //frequency of transmissions
const uint16_t CalibrationOffset = 0;             //adjustment for frequency in Hz, assumed at room temp

#define Bandwidth BW125000                        //LoRa bandwidth
#define SpreadingFactor SF12                      //LoRa spreading factor
#define CodeRate CR45                             //LoRa coding rate

const uint8_t ThisNode = 'R';                     //node number goes out as part of packet addressing 

#define lora_RXBUFF_Size 256                      //RXBUFF to hold full packet                      
#define lora_TXBUFF_Size 1                        //TXBUFF not used 

//#define UseSX1272
//#define UseLoRaWAN


//*******  Setup Program options Here ! ***************


#define UseDisplay                                //to use a display, enable this define 
//#define UseI2CLCD                                 //to use a 20x4 LCD with a PCF8574 backpack, enable this define
#define UseSD1306                               //to use an SD1306 I2C display, enable this define                             

#define SD1306_Address 0x3C                       //define I2C address foe SD1306
//#define LCDI2C_Address 0x3F                       //define I2C address for PCF8574 LCD backpack, usually 0x27 or 0x3F

#define EnableTone                                //Enable ident tone at startup, do not enable if using LNA on receiver



