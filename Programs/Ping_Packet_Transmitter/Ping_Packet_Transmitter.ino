//Ping_Transmitter.ino
#define programname "Ping_Packet_Transmitter"
#define programversion "V1.1"
#define authorname "Stuart Robinson"
#include <Arduino.h>

/*
*****************************************************************************************************************************
  LoRaTracker Test Programs

  Copyright of the author Stuart Robinson - 20/12/2018

  http://www.LoRaTracker.uk

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

  This test program has been written to enable simple checks to be made on the operation of antennas. The transmitter
  can sends a simple FM tone, this can be used by a matching receiver to measure the strength of signal transmitted.
  The measurement device could be a low cost SDR, or for field or portable use an RF Explorer or a tracker board with
  display setup as an RSSI meter. 

  Do not forget to fit an antenna to the LoRa device, you can destroy it if you use it without and antenna
********************************************************************************************************************************
*/


#include "Pin_Definitions.h"


/*
**************************************************************************************************
  Changes:


  To do:


******************************************************************************************************
*/

unsigned int testloop = 0;

#include <SPI.h>
#include "Settings.h"
#include "LoRa5.h"
#include "BufferRW.h"

uint16_t seq;                               //if the HAB packet is used, there is a sequence number sent that increases          

void loop()
{

  testloop++;

  Serial.print(F("Test Loop "));
  Serial.println(testloop);
  Serial.println();
  Serial.flush();


#ifdef SendTestpacket
    Serial.print(F("Send Test Packet "));
    Serial.flush();
    Send_Test_Packet('1');
    Serial.println();
    delay(packet_delaymS);
#endif


#ifdef SendBinaryLocation
    Serial.print(F("Send Binary Location Packet "));
    Serial.flush();
    Send_Binary_Location_Packet();
    Serial.println();
    delay(packet_delay);
#endif


#ifdef SendHABPacket
    Serial.print(F("Send HAB Packet "));
    Serial.flush();
    Send_HAB_Packet();
    Serial.println();
    delay(packet_delay);
#endif
    
    Serial.println();

    Serial.print(F("Waiting "));
    Serial.print(loop_WaitmS);
    Serial.println(F("mS"));
    delay(loop_WaitmS);
 
}


void Send_Test_Packet(char lmode)
{
  //build and send test packet
 uint16_t index;
 uint8_t temp;
  if (transmit_power > 9)
  {
    lora_TXBUFF[0] = '1';
    lora_TXBUFF[1] = ((transmit_power - 10) + 0x30);
  }
  else
  {
    lora_TXBUFF[0] = '0';
    lora_TXBUFF[1] = (transmit_power + 0x30);
    
  }

  lora_TXBUFF[2] = lmode;

  lora_TXEnd = 2;

  if (TestPacketLength > 251)
  {
  temp = 251;
  }
  else
  {
  temp = TestPacketLength;  
  }

  for (index = 6; index <= temp; index++)
  {
  lora_TXBUFF[index] = '#';
  }

  lora_TXEnd = temp - 3;
  
  Serial.print(F(" "));
  digitalWrite(LED1, HIGH);
  lora_TXBuffPrint(0);
  lora_Send(0, lora_TXEnd, Testpacket, Broadcast, ThisNode, 10, transmit_power, NoStrip);
  digitalWrite(LED1, LOW);
  Serial.print(F(" TX Time "));
  Serial.print(lora_TXTime);
  Serial.print("mS ");
}



void Send_Binary_Location_Packet()
{
  Write_Float(0, TestLatitude, lora_TXBUFF);
  Write_Float(4, TestLongitude, lora_TXBUFF);
  Write_UInt(8, TestAltitude, lora_TXBUFF);
  Write_Byte(10, config_byte, lora_TXBUFF);
  lora_TXEnd = 10;
  digitalWrite(LED1, HIGH);
  lora_TXBuffPrint(2);
  lora_Send(0, lora_TXEnd, LocationBinaryPacket, Broadcast, ThisNode, 10, transmit_power, NoStrip);
  digitalWrite(LED1, LOW);
  Serial.print(F(" TX Time "));
  Serial.print(lora_TXTime);
  Serial.print("mS ");
}


void Send_HAB_Packet()
{
  byte Count;
  Count = buildHABPayload();
  lora_TXEnd = Count;
  lora_TXBuffPrint(0);
  Serial.print(F(" "));
  digitalWrite(LED1, HIGH);
  lora_Send(0, Count, HABPacket, Broadcast, ThisNode, 10, transmit_power, NoStrip);   //send the packet, data is in TXbuff from lora_TXStart to lora_TXEnd
  digitalWrite(LED1, LOW);
  Serial.print(F(" TX Time "));
  Serial.print(lora_TXTime);
  Serial.print("mS ");
}


byte buildHABPayload()
{
  //build the long tracker payload
  unsigned int index, index2, hours, mins, seconds, alt, sats, volts, internaltemperature, resets;
  unsigned int ramc_Current_config, TRStatus, runmAhr, GPSfixtime, len;
  unsigned int CRC;
  byte Count;
  byte max_length = 128;
  float calibration;
  char LatArray[10], LonArray[10], CalibrationArray[10];
  char node[2];
  seq++;
  hours = 10;
  mins = 10;
  seconds = 10;
  dtostrf(TestLatitude, 7, 5, LatArray);
  dtostrf(TestLongitude, 7, 5, LonArray);
  alt = TestAltitude;
  sats = 5;
  volts = 3999;
  internaltemperature = -10;
  resets = 11;
  ramc_Current_config = 0x02;
  TRStatus = 0x81;
  runmAhr = 45;
  calibration = 2000;
  dtostrf(calibration, 3, 1, CalibrationArray);
  GPSfixtime = 4.5;

  len = sizeof(lora_TXBUFF);
  memset(lora_TXBUFF, 0, len);                                 //clear array to 0s

  node[0] = ThisNode;
  node[1] = 0;

  Count = snprintf((char*) lora_TXBUFF,
                   max_length,
                   "$$$$%s%s,%d,%02d:%02d:%02d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d",
                   Flight_ID,
                   node,
                   seq,
                   hours,
                   mins,
                   seconds,
                   LatArray,
                   LonArray,
                   alt,
                   sats,
                   volts,
                   internaltemperature,
                   resets,
                   ramc_Current_config,
                   TRStatus,
                   runmAhr,
                   CalibrationArray,
                   GPSfixtime
                  );

  CRC = 0xffff;                                               //start value for CRC16

  for (index = 4; index < Count; index++)                     //element 4 is first character after $$$$ at start
  {
    CRC ^= (((unsigned int)lora_TXBUFF[index]) << 8);
    for (index2 = 0; index2 < 8; index2++)
    {
      if (CRC & 0x8000)
        CRC = (CRC << 1) ^ 0x1021;
      else
        CRC <<= 1;
    }
  }

  lora_TXBUFF[Count++] = '*';
  lora_TXBUFF[Count++] = Hex((CRC >> 12) & 15);                //add the checksum bytes to the end
  lora_TXBUFF[Count++] = Hex((CRC >> 8) & 15);
  lora_TXBUFF[Count++] = Hex((CRC >> 4) & 15);
  lora_TXBUFF[Count] = Hex(CRC & 15);
  return Count;
}


char Hex(byte lchar)
{
  //used in CRC calculation in buildHABPacket
  char Table[] = "0123456789ABCDEF";
  return Table[lchar];
}


void PrintPacket()
{
  byte index;
  for (index = 0; index <= lora_TXEnd; index++)
  {
    Serial.write(lora_TXBUFF[index]);
  }
}


void Led_FlashStart()
{
  byte index;
  for (index = 0; index <= 4; index++)
  {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
}


void System_Error()
{
  while (1)
  {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
}


void init_TXPingTest()
{
  float freq_temp;
  lora_Setup(lora_NSS, lora_NReset, lora_DIO0);
  lora_SetFreqInt(Frequency, CalibrationOffset);
  freq_temp = lora_GetFreqFloat();
  Serial.print(F("Set to Frequency "));
  Serial.print(freq_temp, 3);
  Serial.println(F("Mhz"));
  lora_SetModem2(Bandwidth, SpreadingFactor, CodeRate, Explicit);  //setup the LoRa modem parameters for test
}


void setup()
{
  pinMode(LED1, OUTPUT);		                    //setup pin for LED
  Led_FlashStart();

  Serial.begin(Serial_Monitor_Baud);            //setup Serial console ouput
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("Compiled "));
  Serial.print(__TIME__);
  Serial.print(F(" "));
  Serial.println(__DATE__);
  Serial.println(F(authorname));
  Serial.println();

  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  pinMode(lora_NReset, INPUT);			           //LoRa Device reset line
  pinMode (lora_NSS, OUTPUT);			             //LoRa Device select line
  digitalWrite(lora_NSS, HIGH);


  if (lora_CheckDevice() == true)
  {
    Serial.println(F("LoRa Device Found"));
  }
  else
  {
    Serial.println(F("LoRa Device Error"));
    System_Error();
  }

  lora_Print();
  Serial.println();

  init_TXPingTest();                               
}

