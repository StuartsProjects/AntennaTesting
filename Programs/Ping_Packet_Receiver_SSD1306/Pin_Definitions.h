//Pin_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  To Do:

*******************************************************************************************************************************
*/
/*
******************************************************************************************************
  Definitions for pins used to connect to the LoRa device in this program
******************************************************************************************************
*/


#define lora_DIO2 6                  //pin number for tone generation, connects to LoRa device pin DIO2
#define LED1 8                       //pin number for LED on Tracker
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define lora_NSS 10                  //pin number where the NSS line for the LoRa device is connected
#define lora_DIO0 2                  //used to read RX ready
#define SD_CS 4                      //Arduino pin number for SD card select for LCD receiver
#define Switch1 3                    //switch is used to close current log
