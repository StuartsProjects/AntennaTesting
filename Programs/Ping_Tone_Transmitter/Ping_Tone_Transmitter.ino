//Ping_Transmitter.ino
#define programname "Ping_Transmitter"
#define programversion "V1.1"
#define authorname "Stuart Robinson"
#include <Arduino.h>

/*
*****************************************************************************************************************************
  Tracker Test Programs

  Copyright of the author Stuart Robinson - 20/12/2018

  

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

/*
********************************************************************************************************************************
  Connections

  The program uses the hardware SPI interface on the Arduino to connect to the LoRa device, so the SPI SCK, MOSI and MISO pins are
  assumed to be connected. The test transmitter program needs pins connected to act as chip select, and to generate the FM tones.
  The reset pin on the LoRa device can be ommited.

  You need to define the required pins below. 
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



void loop()
{

  testloop++;

  Serial.print(F("Test Loop "));
  Serial.println(testloop);
  Serial.println();
  Serial.flush();


  digitalWrite(LED1, HIGH);
  Serial.println(F("Transmitt Ping Tone "));
  lora_Tone(tone_frequencyHz, tone_lengthmS, transmit_power, lora_TonePin);    //Transmit a pseudo FM tone
  digitalWrite(LED1, LOW);
  delay(transmission_delaymS);
 
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

