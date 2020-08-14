//RSSI_Meter_LCD.ino
#define programname "RSSI_Meter_LCD"
#define programversion "V1.0"
#define authorname "Stuart Robinson"
#include <Arduino.h>

/*
*****************************************************************************************************************************
  Tracker Test Programs

  Copyright of the author Stuart Robinson - 02/12/18

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit
  permission of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended 
  purpose and free from errors.
*****************************************************************************************************************************
*/


/*
********************************************************************************************************************************
  Program operation.

  This program using the LoRa device as an RSSI meter, the signal level seen is printed to serial terminal or printed
  to a display.

  Do not forget to fit an antenna to the LoRa device, you can destroy it if you use it without and antenna
********************************************************************************************************************************
*/

#include "Pin_Definitions.h"

/*
**************************************************************************************************
  Changes:
  Changed to LoRa5.h 
  To do:

******************************************************************************************************
*/


#include "Settings.h"
#include <SPI.h>
#include "LoRa5.h"
#include <Wire.h>

#include <LiquidCrystal_I2C.h>                       //www.4tronix.co.uk/arduino/sketches/LiquidCrystal_V1.2.1.zip
LiquidCrystal_I2C disp(LCDI2C_Address, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //Set the LCD I2C address and pins used

void loop()
{
  uint8_t i;
  int8_t BackGroundRSSI;
  int16_t noise_level = 0;
  float display_rssi;

  for (i = 1; i <= 100; i++)
  {
    BackGroundRSSI = lora_ReadBackgroundRSSI();    //get the background noise level
    noise_level = noise_level + BackGroundRSSI;
    delay(5);
  }

  display_rssi = (float) noise_level / 100;
  Serial.print(display_rssi);
  Serial.println(F("dBm"));

  disp.setCursor(1, 1);
  disp.print(display_rssi, 1);
  disp.print(" dBm   ");

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


void init_RXLoRa()
{
  //setup for testmode
  lora_Setup(lora_NSS, lora_NReset, lora_DIO0);
  lora_SetFreqInt(Frequency, CalibrationOffset);
  lora_SetModem2(BW62500, SF8, CR45, Explicit);   //setup the LoRa modem parameters needed for reading RSSI
}


void setup()
{
  pinMode(LED1, OUTPUT);		                     //setup pin for PCB LED

  led_FlashStart();

  Serial.begin(Serial_Monitor_Baud);             //setup Serial console ouput
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("Compiled "));
  Serial.print(__TIME__);
  Serial.print(F(" "));
  Serial.println(__DATE__);
  Serial.println(F(authorname));
  Serial.println();

  Serial.println();
  pinMode(lora_NReset, INPUT);		               //setup pin for LoRa device reset line
  pinMode (lora_NSS, OUTPUT);		                 //setup pin for LoRa device slave select
  digitalWrite(lora_NSS, HIGH);

  SPI.begin();				                           //initialize SPI
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  if (lora_CheckDevice() == true)
  {
    Serial.println(F("LoRa Device Found"));

    init_RXLoRa();				                       //Do the initial LoRa Setup
    Serial.print(F("LoRa Tone "));
    digitalWrite(LED1, HIGH);
    lora_Tone(1000, 1000, 2, lora_TonePin);      //Transmit an FM tone, 1000hz, 1000ms
    digitalWrite(LED1, LOW);
    Serial.println();

  }
  else
  {
    Serial.println(F("LoRa Device Error"));
    systemerror();
  }

  Serial.println();
  lora_Print();
  Serial.println();

  Wire.begin();

  Serial.println(F("Using 20x4 LCD Display"));
  disp.begin(20, 4);                             //initialize the lcd for 20 chars 4 lines, turn on backlight
  disp.setCursor(0, 0);
  disp.print(F("RSSI Meter"));
  disp.setCursor(0, 1);
  disp.print(F("Starting"));
  delay(1000);
  disp.setCursor(0, 1);
  disp.clear();

  Serial.println(F("RSSI Meter Starting"));
  
  init_RXLoRa();                                //re-do setup after tone
  lora_RXONLoRa();

}


