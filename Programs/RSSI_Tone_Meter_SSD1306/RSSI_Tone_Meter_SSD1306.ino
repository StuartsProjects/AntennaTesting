//RSSI_Meter_LCD.ino
#define programname "RSSI_Meter_SSD1306"
#define programversion "V1.0"
#define authorname "Stuart Robinson"
#include <Arduino.h>

/*
*****************************************************************************************************************************
  LoRaTracker Test Programs

  Copyright of the author Stuart Robinson - 20/12/18

  http://www.LoRaTracker.uk

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

#include <Adafruit_SSD1306.h>                        //https://github.com/adafruit/Adafruit_SSD1306
#define OLED_RESET -1
Adafruit_SSD1306 disp(OLED_RESET);

#define Serial_Monitor_Baud 115200                   //this is baud rate used for the Arduino IDE Serial Monitor

void loop()
{
  uint8_t i;
  int8_t BackGroundRSSI;
  int16_t noise_level = 0;
  float display_rssi;

  for (i = 1; i <= 50; i++)
  {
    BackGroundRSSI = lora_ReadBackgroundRSSI();    //get the background noise level
    noise_level = noise_level + BackGroundRSSI;
    delay(5);
  }

  display_rssi = (float) noise_level / 50;
  Serial.print(display_rssi);
  Serial.println(F("dBm"));
  disp.clearDisplay();
  disp.setCursor(1, 12);
  disp.print(display_rssi, 1);
  disp.print(" dBm   ");
  disp.display();

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
  Serial.println(F(programname));
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
    lora_Tone(1000, 1000, 2, lora_DIO0);         //Transmit an FM tone, 1000hz, 1000ms
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

  Serial.println(F("Using SSD1306"));
  disp.begin(SSD1306_SWITCHCAPVCC, SSD1306_Address);           //initialize with the I2C addr 0x3C (for the 128x64)
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(WHITE);
  disp.setCursor(0, 0);
  disp.print(F("RSSI Meter"));
  disp.setCursor(0, 12);
  disp.print(F("Starting"));
  disp.display();
  delay(1000);
  disp.clearDisplay();

  Serial.println(F("RSSI Meter Starting"));
  
  init_RXLoRa();                                //re-do setup after tone
  lora_RXONLoRa();

}


