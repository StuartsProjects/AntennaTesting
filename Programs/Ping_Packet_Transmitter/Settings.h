//Test_Settings.h
/*
******************************************************************************************************

LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 20/12/18

http://www.LoRaTracker.uk

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
#define Bandwidth BW125000                        //LoRa bandwidth
#define SpreadingFactor SF12                      //LoRa spreading factor
#define CodeRate CR45                             //LoRa coding rate


const byte transmit_power = 10;                   //power for transmissions
const uint32_t loop_WaitmS = 2000;                //number of milli seconds to wait between transmissions  
const uint32_t packet_delaymS = 500;              //mS between packets to allow for screen updates on receiver etc
const unsigned int tone_lengthmS = 3000;          //tone length in mS
const unsigned int tone_frequencyHz = 500;        //tone frequency in hertz


#define SendTestpacket                            //Enable send of test packet
#define TestPacketLength 100                        //allows packet to be made long enough for power level measurements etc
//#define SendBinaryLocation                        //Enable send of binary short location payload
//#define SendHABPacket                             //Enable send of HAB Style packet
unsigned char Flight_ID[15] = "LoRaTracker1";       //used for the HAB style packet

#define lora_RXBUFF_Size 1
#define lora_TXBUFF_Size 128

const char ThisNode = 'P';                        //node number goes out as part of packet addressing 
const float TestLatitude  = 51.48230;             //GPS co-ordinates to use for test
const float TestLongitude  = -3.18136;            //Cardiff castle keep, used for testing purposes 
const float TestAltitude = 25.5;
const uint8_t config_byte = 0xAA; 

//********************************************************

#define Serial_Monitor_Baud 115200                //this is baud rate used for the Arduino IDE Serial Monitor


