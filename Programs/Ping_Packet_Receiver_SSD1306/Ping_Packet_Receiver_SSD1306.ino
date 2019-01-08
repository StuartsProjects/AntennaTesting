//Ping_Packet_Receiver_SSD1306.ino
#define programversion "V1.0"
#define authorname "Stuart Robinson"

/*
**************************************************************************************************

  LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 03/1/18

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without
  the explicit permission of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
  intended purpose and free from errors.

  Changes:

  To do:
  Add print LoRa settings to display

******************************************************************************************************
*/

#include <Arduino.h>
#include "Pin_Definitions.h"

boolean SD_Found = false;                   //set if SD card found at program startup
uint32_t Mode1_Packet_Count = 0;
uint8_t Mode1_Max_Power = 0;
uint32_t Mode1_Cycles = 0;

#include "Settings.h"
#include <SPI.h>
#include "LoRa5.h"

#ifdef UseI2CLCD
#include <LiquidCrystal_I2C.h>              //https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/  - download LiquidCrystal_V1.2.1.zip
LiquidCrystal_I2C disp(LCDI2C_Address, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //Set the LCD I2C address and pins used
#endif

#ifdef UseSD1306
#include "SSD1306Ascii.h"                   //https://github.com/greiman/SSD1306Ascii
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire disp;
#endif


void loop()
{

  checkforpacket();
}


void checkforpacket()
{
  //check if a packet has been received

  if (lora_readRXreadyDIO0())
  {
    lora_RXOFF();                                    //stop more packets comming in
    lora_ReadPacketDetails();                        //read packet details
    PacketOK = lora_IsPacketValid();                 //checks if packet is OK, updates counts, updates HeaderOK, PayloadhasCRC, CRCError

    digitalWrite(LED1, HIGH);
    Serial.print(F("RX "));
    lora_ReadPacket();

    lora_PrintReceptionInfo();
    Serial.print("  ");
    lora_AddressInfo();

    digitalWrite(LED1, LOW);

    if (PacketOK)
    {
      processPacket();
    }
    else
    {
      Serial.println(F("  Packet Error"));

#ifdef UseDisplay
      disp.setCursor(70, 3);
      disp.print(F("Error"));
      delay(1000);
      disp.setCursor(70, 3);
      disp.print(F("     "));
#endif

    }
    lora_RXONLoRa();                                 //ready for next
  }
}


void processPacket()
{

  if (lora_RXPacketType == Testpacket)
  {

#ifdef UseDisplay
    disp.clear();
    writescreen_PacketDetails();
    writescreen_SNR();
    writescreen_RSSI();
#endif

    lora_RXONLoRa();
  }
}


void systemerror()
{
  while (1)
  {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
}


void led_FlashStart()
{
  uint8_t i;
  for (i = 0; i <= 4; i++)
  {
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
}

void init_LoRaTest1()
{
  lora_SetFreqInt(Frequency, CalibrationOffset);                      //Setup the LoRa frequency
  lora_SetModem2(Bandwidth, SpreadingFactor, CodeRate, Explicit);  //Setup the LoRa modem parameters
}


/*****************************************************************************/
//  Start Display routines
/*****************************************************************************/

#ifdef UseDisplay

void writescreen_RSSI()
{
  disp.setCursor(0, 0);
  disp.print(F("RSSI "));
  disp.print(lora_PacketRSSI);                  //now print the SNR
  disp.print(F("dBm"));
}


void writescreen_SNR()
{
  disp.setCursor(0, 1);
  disp.print(F("SNR "));
  disp.print(lora_PacketSNR);                  //now print the SNR
  disp.print(F("dB "));
}


void writescreen_PacketDetails()
{
  disp.setCursor(0, 2);
  disp.print(F("Length "));                       //send count to LCD
  disp.print(lora_RXPacketL);               //send count to LCD
  disp.setCursor(0, 3);
  disp.print(F("Count "));
  disp.print(lora_RXpacketCount);
}

#endif

/*****************************************************************************/
//  End Display routines
/*****************************************************************************/


void setup()
{
  pinMode(LED1, OUTPUT);		                      //setup pin for PCB LED
  led_FlashStart();

  Serial.begin(115200);                           //setup Serial console ouput
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("Compiled "));
  Serial.print(__TIME__);
  Serial.print(F(" "));
  Serial.println(__DATE__);
  Serial.println(F(authorname));
  Serial.println();
  Serial.println();

  SPI.begin();                                   //initialize SPI
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  pinMode (lora_NSS, OUTPUT);                     //setup pin for LoRa device slave select
  digitalWrite(lora_NSS, HIGH);

  pinMode(lora_NReset, INPUT);		                //setup pin for LoRa device reset line
  pinMode (lora_DIO0, INPUT);                     //setup pin for LoRa device slave select
  pinMode(Switch1, INPUT_PULLUP);                 //setup pin for switch

#ifdef UseDisplay

#ifdef UseSD1306
  disp.begin(&Adafruit128x64, SD1306_Address);
  disp.setFont(Adafruit5x7);
  disp.set1X();
#endif

#ifdef UseI2CLCD
  disp.begin(20, 4);                              //initialize the lcd for 20 chars 4 lines
  disp.backlight();                               //turn on backlight, if option available
#endif

  Serial.println(F("Display Option Selected"));
  disp.clear();
  disp.setCursor(0, 0);
  disp.print(F("Starting"));
#endif


  if (lora_CheckDevice() == true)
  {
#ifdef EnableTone
    init_LoRaTest1();
    Serial.println(F("LoRa Tone"));
    digitalWrite(LED1, HIGH);
    lora_Tone(1000, 1000, 2, lora_DIO2);                      //Transmit an FM tone, 1000hz, 1000ms
    digitalWrite(LED1, LOW);
    Serial.println();
#endif
  }
  else
  {
    Serial.println(F("LoRa Device Error"));
    systemerror();
  }

  lora_Setup(lora_NSS, lora_NReset, lora_DIO0);
  init_LoRaTest1();
  lora_RXONLoRa();

  Serial.println();
  lora_Print();
  Serial.println();

  lora_PrintLoRaSettings();

  Serial.println();
  Serial.println(F("Receiver ready"));

#ifdef UseDisplay
  float freq_temp = lora_GetFreqFloat();
  disp.setCursor(0, 0);
  disp.print(F("Ready    "));
  disp.setCursor(0, 1);
  disp.print(freq_temp, 3);
  disp.print(F("Mhz"));
#endif

}


