//LoRa5.h
//Created from LoRa4.h from LoRaTracker library 08/12/18
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 09/12/18

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commerclora_setupial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is a LoRa library for the SX1272 or SX1276/8 devices. The setup of lora_RegModemConfig1 and lora_RegModemConfig2 is different on
  these versions of the LoRa device so there are different routines for the SX1272 and SX1276\8.

  The library defaults to SX1276\8 mode, to use the library for SX1272 make sure there is a define '#define UseSX1272' before including
  the library.
  

  LoRaWAN uses a different sync word (0x34) from the default (0x12) used by the LoRaTracker libraries. The library uses the
  default sync word, to use the LoRaWAN syncword make sure there is a define '#define UseLoRaWAN' before including this library.

  To Do:
  Add check for TX packet overflowing buffer ?
  Add option to enable for LORAWAN
  Add printout of FIFO, RX and TX
  Check lora_TXFIFOPrint() and lora_RXFIFOPrint() matches buffer prints
  Add relat capability
  Need to check queued send and wait packet
  DONE - Add check for RX packet longer than buffer can cope with.
  DONE Added option to use SX1272 or SX1276
  Add lora_SetFreqFloat
  Replace PACKETOK with function
  check no LoRa modem settings in lora_setup
  Test lora_GetFrequencyError() with SX1272
  Add a lora_SetFreqFloat
  Review lora_SendFIFO, used by relay
  Change to RSSI routine to use -164 for LF port -157 for HF port
  
  Changes:


*******************************************************************************************************************************
*/

#ifndef UseSX1272
//Constant names for bandwidth settings
const uint8_t BW7800 = 0;          //7.8khz
const uint8_t BW10400 = 16;        //10.4khz
const uint8_t BW15600 = 32;        //15.6khz
const uint8_t BW20800 = 48;        //20.8khz
const uint8_t BW31200 = 64;        //31.2khz
const uint8_t BW41700 = 80;        //41.7khz
const uint8_t BW62500 = 96;        //62.5khz
const uint8_t BW125000 = 112;      //125khz
const uint8_t BW250000 = 128;      //250khz
const uint8_t BW500000 = 144;      //500khz
#endif


#ifdef UseSX1272
//Constant names for bandwidth settings, only 3 bandwidths supported on SX1272
const byte BW125000 = 0;        //125khz
const byte BW250000 = 64;       //250khz
const byte BW500000 = 128;      //500khz
#endif

//Constant names for Spreading Factors
const uint8_t SF6 = 6;
const uint8_t SF7 = 7;
const uint8_t SF8 = 8;
const uint8_t SF9 = 9;
const uint8_t SF10 = 10;
const uint8_t SF11 = 11;
const uint8_t SF12 = 12;


#ifndef UseSX1272
//Constant names for coding rate settings
const byte CR45 = 2;            //4:5
const byte CR46 = 4;            //4:6
const byte CR47 = 6;            //4:7
const byte CR48 = 8;            //4:8
#endif


#ifdef UseSX1272
//Constant names for coding rate settings
const uint8_t CR45 = 8;             //4:5
const uint8_t CR46 = 16;            //4:6
const uint8_t CR47 = 24;            //4:7
const uint8_t CR48 = 32;            //4:8
#endif


#ifdef UseSX1272
//Constant names for LoRa Header Settings
const uint8_t Explicit    = 0;     //Use to set explicit header
const uint8_t Implicit    = 4;     //Use to set implicit header
const uint8_t LowDoptON = 0x01;    //value to turn low data rate optimization on
const uint8_t LowDoptOFF = 0x00;   //value to turn low data rate optimization off
#endif


#ifndef UseSX1272
//Constant names for LoRa Header Settings
const uint8_t Explicit    = 0;     //Use to set explicit header
const uint8_t Implicit    = 1;     //Use to set implicit header
const uint8_t LowDoptON = 0x08;    //value to turn low data rate optimization on
const uint8_t LowDoptOFF = 0x00;   //value to turn low data rate optimization off
#endif


//Miscellaneous definitions
const uint8_t Deviation = 0x52;    //typical 5Khz deviation for 5khz FM style tones
const uint8_t PrintASCII = 0;      //value to cause buffer print to appear as ASCII
const uint8_t PrintDecimal = 1;    //value to cause buffer print to appear as decimal numbers
const uint8_t PrintHEX = 2;        //value to cause buffer print to appear as hexadecimal numbers
const uint8_t Strip = 1;           //value for setting stip of addressing information on packet
const uint8_t NoStrip = 0;         //value for sending addressing information as part of packet


//SX1278 Register names
const uint8_t lora_RegFifo = 0x00;
const uint8_t lora_WRegFifo = 0x80;
const uint8_t lora_RegOpMode = 0x01;
const uint8_t lora_RegFdevLsb = 0x05;
const uint8_t lora_RegFrMsb = 0x06;
const uint8_t lora_RegFrMid = 0x07;
const uint8_t lora_RegFrLsb = 0x08;
const uint8_t lora_RegPaConfig = 0x09;
const uint8_t lora_RegOcp = 0x0B;
const uint8_t lora_RegLna = 0x0C;
const uint8_t lora_RegFifoAddrPtr = 0x0D;
const uint8_t lora_RegFifoTxBaseAddr = 0x0E;
const uint8_t lora_RegFifoRxBaseAddr = 0x0F;
const uint8_t lora_RegFifoRxCurrentAddr = 0x10;
const uint8_t lora_RegIrqFlagsMask = 0x11;
const uint8_t lora_RegIrqFlags = 0x12;
const uint8_t lora_RegRxNbBytes = 0x13;
const uint8_t lora_RegRxHeaderCntValueMsb = 0x14;
const uint8_t lora_RegRxHeaderCntValueLsb = 0x15;
const uint8_t lora_RegRxPacketCntValueMsb = 0x16;
const uint8_t lora_RegRxPacketCntValueLsb = 0x17;
const uint8_t lora_RegPktSnrValue = 0x19;
const uint8_t lora_RegPktRssiValue = 0x1A;
const uint8_t lora_RegRssiValue = 0x1B;
const uint8_t lora_RegHopChannel = 0x1C;
const uint8_t lora_RegModemConfig1 = 0x1D;
const uint8_t lora_RegModemConfig2 = 0x1E;
const uint8_t lora_RegSymbTimeoutLsb = 0x1F;
const uint8_t lora_RegPreambleLsb = 0x21;
const uint8_t lora_RegPayloadLength = 0x22;
const uint8_t lora_RegFifoRxByteAddr = 0x25;
const uint8_t lora_RegModemConfig3 = 0x26;
const uint8_t lora_RegFeiMsb = 0x28;
const uint8_t lora_RegFeiMid = 0x29;
const uint8_t lora_RegFeiLsb = 0x2A;
const uint8_t lora_RegPacketConfig2 = 0x31;
const uint8_t lora_RegInvertIQ = 0x33;
const uint8_t lora_RegSyncWord = 0x39;
const uint8_t lora_RegDioMapping = 0x40;
const uint8_t lora_RegDioMapping2 = 0x41;
const uint8_t lora_RegVersion = 0x42;
const uint8_t lora_RegPllHop = 0x44;


/*
**************************************************************************************************
  Varialbles  definistions
**************************************************************************************************
*/

uint8_t  lora_RXStart;               //start of packet data in RXbuff
uint8_t  lora_RXEnd;                 //end of packet data in RXbuff
uint8_t  lora_RXPacketType;          //type number of received packet
uint8_t  lora_RXDestination;         //destination address of received packet
uint8_t  lora_RXSource;              //source address of received packet
uint32_t lora_RXpacketCount;         //count of received packets

uint8_t  lora_TXStart;               //start of packet data in TX buffer
uint8_t  lora_TXEnd;                 //end of packet data in TX buffer
uint8_t  lora_TXPacketType;          //type number of transmitted packet
uint8_t  lora_TXDestination;         //destination address of transmitted packet
uint8_t  lora_TXSource;              //source address of transmitted packet
uint16_t lora_TXpacketCount;         //count of transmitted packets

int8_t lora_PacketRSSI;              //RSSI of received packet
int8_t lora_PacketSNR;               //signal to noise ratio of received packet
uint8_t lora_RXPacketL;              //length of packet received, includes source, destination and packet type.
uint8_t lora_TXPacketL;              //length of packet received, includes source, destination and packet type.
uint8_t lora_Power;                  //power setting for mode
uint8_t keypress;

uint32_t lora_RXCRCerrorCount = 0;
uint32_t lora_RXHeadererrorCount = 0;
uint32_t lora_PhantomPacketCount = 0;
uint32_t lora_PacketOKCount = 0;

uint32_t lora_TXTime;                 //used to record TX On time
uint32_t lora_StartTXTime;            //used to record when TX starts
uint32_t lora_RXTime;                 //used to record RX On time
uint32_t lora_StartRXTime;            //used to record when RX starts
uint32_t lora_CurrentFreq;            //used to store current frequncy, needed for afc function

boolean PayloadhasCRC = false;
boolean CRCError = false;
boolean HeaderOK = false;
boolean PacketOK = false;


//we need to detect if there is no definition for the buffer sizes to avoid a compile error
//if the #defines are missing

#ifndef lora_RXBUFF_Size                  //detect if no buffer size defined
#define lora_RXBUFF_Size 1                
#endif

#ifndef lora_TXBUFF_Size                  //detect if no buffer size defined
#define lora_TXBUFF_Size 1
#endif

uint8_t  lora_RXBUFF[lora_RXBUFF_Size];   //buffer where received packets are stored
uint8_t  lora_TXBUFF[lora_TXBUFF_Size];   //buffer for packet to send

//precalculated values for frequency error calculation
const PROGMEM  float bandwidth[] = {0.1309, 0.1745, 0.2617, 0.3490, 0.5234, 0.6996, 1.049, 2.097, 4.194, 8.389};


/*
**************************************************************************************************
  Packet name definistions
**************************************************************************************************
*/

const char ACK = 'A';                   //Acknowledge
const char AFC = 'a';                   //AFC packet 
const char LinkReport = 'B';            //HAB Style in CSV ASCII format
const char bLinkReport = 'b';           //binary style link report
const char ClearToSend = 'C';           
const char ClearToSendCommand = 'c';
const char Error = 'E';                 
const char NoFix = 'F';                 //GPS no fix  
const char NoGPS = 'G';                 //No GPS found    
const char GLONASSDetected = 'g';       //Glonass output from GPS detected   
const char IsLost = 'H';                //packet to notify of lost status (Help)
const char Info = 'i';                  //binary info packet
const char PowerUp = 'P';               //sent on tracker start 
const char Memory = 'M';                //Memory write command  
const char NACK = 'N';                  //Not Acknowledge, rejected
const char NACKCommand = 'n';           //Command not accepted
const char Repeated = 'R';              //Marks packet as repeated 
const char LocationCSVPacket = 'S';     //Short loacation packet in CSV ASCII format
const char LocationBinaryPacket = 's';  //Short location packet in binary format
const char Testpacket = 'T';            //Test packet
const char Test = 'T';                  //Test
const char Timepacket = 't';            //seconds up time
const char Wakeup = 'W';                //Wakeup from snooze
const char ResetTracker = 'X';          //Reset tracker   
const char Config1 = 'Y';               //Change config1 byte
const char Config0 = 'Z';               //Change config0 byte 

const char Bind = '#';                  //Bind packet
const char Sensor1 = '!';               //Sensor packet1
const char Sensor2 = '"';               //Sensor packet2
const char WritePacketMemory = '0';     //Write bytes to Memory
const char TestMode1 = '1';             //used to switch to Testmode1 settings
const char TestMode2 = '2';             //used to switch to Testmode2 settings
const char INCFreq = '3';               //Increase frequency 
const char DECFreq = '4';               //Decrease frequency
const char InfoRelay = '5';             //used to relay screen SNR and RSSI in ping test. 
const char LMLCSVPacket = '8';          //short LML payload; lat,lon,alt in CSV ASCII format
const char LMLCSVPacket_Repeated = '9'; //short LML payload that has been repeated

const char Broadcast = '*';             //Broadcast address
const char PacketStart = '$';           //Command packets have a payload of at least one byte, so put this at start
const char HABPacket = '$';             //HAB Style location payload in CSV ASCII format


/*
**************************************************************************************************
  Library Functions
**************************************************************************************************
*/

void lora_Write(uint8_t Reg, uint8_t RegData)
{
  //write a byte to a LoRa register
  digitalWrite(lora_NSS, LOW);       //set NSS low
  SPI.transfer(Reg | 0x80);          //mask address for write
  SPI.transfer(RegData);             //write the byte
  digitalWrite(lora_NSS, HIGH);      //set NSS high
}


uint8_t lora_Read(uint8_t Reg)
{
  //read a byte from a LoRa register
  uint8_t RegData;
  digitalWrite(lora_NSS, LOW);       //set NSS low
  SPI.transfer(Reg & 0x7F);          //mask address for read
  RegData = SPI.transfer(0);         //read the byte
  digitalWrite(lora_NSS, HIGH);      //set NSS high
  return RegData;
}

#ifndef UseSX1272
int16_t lora_GetFrequencyError()
{
  uint16_t msb, mid, lsb;
  int16_t freqerr;
  uint8_t bw;
  float bwconst;
  
  msb = lora_Read(lora_RegFeiMsb);
  mid = lora_Read(lora_RegFeiMid);
  lsb = lora_Read(lora_RegFeiLsb);
  bw = lora_Read(lora_RegModemConfig1) & (0xF0);
  bw = bw >> 4;
  bwconst = pgm_read_float_near(bandwidth + bw);
  
  freqerr = msb << 12;                     //shift lower 4 bits of msb into high 4 bits of freqerr
  mid = (mid << 8) + lsb;
  mid = (mid >> 4);
  freqerr = freqerr + mid;

  freqerr = (int16_t) (freqerr * bwconst);

  return freqerr;
}
#endif




void lora_PrintHEXByte0x(uint8_t temp)
{
  //print a byte, adding 0x
  Serial.print(F("0x"));
  if (temp < 0x10)
  {
    Serial.print(F("0"));
  }
  Serial.print(temp, HEX);
}


void lora_PrintHEXByte(uint8_t temp)
{
  if (temp < 0x10)
  {
    Serial.print(F("0"));
  }
  Serial.print(temp, HEX);
}


#ifdef UseSX1272
uint32_t lora_returnbandwidth(uint8_t BWregvalue)
{
  switch (BWregvalue)
  {
    case 0:
      return 125000;

    case 64:
      return 250000;

    case 128:
      return 500000;

    default:
      break;
  }
  return 0xFFFF;                      //so that a bandwidth not set can be identified
}
#endif



#ifndef UseSX1272
uint32_t lora_returnbandwidth(byte BWregvalue)
{
  switch (BWregvalue)
  {
    case 0:
      return 7800;

    case 16:
      return 10400;

    case 32:
      return 15600;

    case 48:
      return 20800;

    case 64:
      return 31200;

    case 80:
      return 41700;

    case 96:
      return 62500;

    case 112:
      return 125000;

    case 128:
      return 250000;

    case 144:
      return 500000;

    default:
      break;
  }
  return 0xFFFF;                      //so that a bandwidth not set can be identified
}

#endif


#ifdef UseSX1272
uint32_t lora_returnSetBandwidth()
{
  uint8_t temp;
  uint32_t templong;
  temp = lora_Read(lora_RegModemConfig1);
  temp = (temp & 0xC0);
  templong = lora_returnbandwidth(temp);
  return templong;
}
#endif


#ifndef UseSX1272
uint32_t lora_returnSetBandwidth()
{
  uint8_t temp;
  uint32_t templong;
  temp = lora_Read(lora_RegModemConfig1);
  temp = (temp & 0xF0);
  templong = lora_returnbandwidth(temp);
  return templong;
}
#endif


#ifdef UseSX1272
uint8_t lora_returnSetOptimisation()
{
  uint8_t temp;
  temp = lora_Read(lora_RegModemConfig1);
  temp = (temp & 0x01);
  return temp;
}
#endif


#ifndef UseSX1272
uint8_t lora_returnSetOptimisation()
{
  uint8_t temp;
  temp = lora_Read(lora_RegModemConfig3);
  temp = (temp & 0x08) >> 3;
  return temp;
}
#endif


#ifdef UseSX1272
uint8_t lora_returnSetCodingRate()
{
  uint8_t temp;
  temp = lora_Read(lora_RegModemConfig1);
  temp = ((temp & 0x38) >> 3) + 4;
  return temp;
}
#endif


#ifndef UseSX1272
uint8_t lora_returnSetCodingRate()
{
  uint8_t temp;
  temp = lora_Read(lora_RegModemConfig1);
  temp = ((temp & 0x0E) >> 1) + 4;
  return temp;
}
#endif


uint8_t lora_DeviceReturnVersion()
{
  uint8_t temp;
  temp = lora_Read(lora_RegVersion);
  return temp;
}


uint8_t lora_returnSetSpreadingFactor()
{
  uint8_t temp;
  temp = lora_Read(lora_RegModemConfig2);
  temp = (temp & 0xf0) >> 4;
  return temp;
}


void lora_PrintOptimisation()
{
  boolean temp;
  temp = lora_returnSetOptimisation();
  if (temp)
  {
    Serial.print(F("On"));
  }
  else
  {
    Serial.print(F("Off"));
  }
}


void lora_DevicePrintVersion()
{
  uint8_t temp;
  temp = lora_DeviceReturnVersion();
  Serial.print(F("Version "));
  lora_PrintHEXByte0x(temp);
 }


void lora_PrintCodingRate()
{
  Serial.print(lora_returnSetCodingRate());
}


void lora_PrintBandwidth()
{
  Serial.print(lora_returnSetBandwidth());
}


void lora_PrintSpreadingFactor()
{
  Serial.print(lora_returnSetSpreadingFactor());
}


void lora_PrintRegister(uint8_t reg)
{
  uint8_t temp;
  temp = lora_Read(reg);
  lora_PrintHEXByte(temp);
}


void lora_PrintRXbufferSize()
{
uint16_t temp;
temp = sizeof(lora_RXBUFF);
Serial.print(F("RXBUFF size "));
Serial.print(temp);
}


void lora_PrintTXbufferSize()
{
uint16_t temp;
temp = sizeof(lora_TXBUFF);
Serial.print(F("TXBUFF size "));
Serial.print(temp);
}


boolean lora_IsHeaderValid()
{
return (bitRead(lora_Read(lora_RegIrqFlags), 4));               //read bit which indicates valid header
}


boolean lora_IsPayloadHasCRC()
{
return (bitRead(lora_Read(lora_RegHopChannel), 6));             //read bit which indicates payload has a CRC
}


boolean lora_IsPayloadCRCFail()
{
return (bitRead(lora_Read(lora_RegIrqFlags), 5));               //read bit which indicates CRC error
}


boolean lora_IsPacketValid()
{
  //checks if packet OK, increases error counts and OK count;

  PayloadhasCRC = bitRead(lora_Read(lora_RegHopChannel), 6);     //read bit which indicates payload has a CRC
  CRCError = bitRead(lora_Read(lora_RegIrqFlags), 5);            //read bit which indicates CRC error
  HeaderOK = bitRead(lora_Read(lora_RegIrqFlags), 4);            //read bit which indicates valid header

  if (!HeaderOK)
  {
  lora_RXHeadererrorCount++;  
  }

  if ((HeaderOK) && (PayloadhasCRC) &&  (CRCError))
  {
  lora_RXCRCerrorCount++;    
  }

  if ((HeaderOK) && (!PayloadhasCRC) && (!CRCError))             //if Payload has CRC bit clear CRC error flag is low, packet is phantom
  {
    lora_PhantomPacketCount++;
  }

  if ((HeaderOK) && (PayloadhasCRC) &&  (!CRCError))             //if Payload has CRC bit is set and CRC error flag is low, packet is valid
  {
  lora_PacketOKCount++;
  return true;
  }
  else
  {
  //PacketOK = false;
  return false; 
  }

}


float lora_CalcSymbolTime(float Bandwidth, uint8_t SpreadingFactor)
{
  //calculates symbol time from passed bandwidth (lbandwidth) and Spreading factor (lSF)and returns in mS
  float symbolTimemS;
  symbolTimemS = (Bandwidth / pow(2, SpreadingFactor));
  symbolTimemS = (1000 / symbolTimemS);
  return symbolTimemS;
}


uint8_t lora_GetOptimisation(uint8_t Bandwidth, uint8_t SpreadingFactor)
{
  //from the passed bandwidth (bandwidth) and spreading factor this routine
  //calculates whether low data rate optimisation should be on or off

  uint32_t tempBandwidth;
  float symbolTime;
  tempBandwidth = lora_returnbandwidth(Bandwidth);
  symbolTime = lora_CalcSymbolTime(tempBandwidth, SpreadingFactor);

#ifdef LORADEBUG
  Serial.print(F("Symbol Time "));
  Serial.print(symbolTime, 3);
  Serial.println(F("mS"));
#endif

  if (symbolTime > 16)
  {
#ifdef LORADEBUG
    Serial.println(F("LDR Opt on"));
#endif
    return LowDoptON;
  }
  else
  {
#ifdef LORADEBUG
    Serial.println(F("LDR Opt off"));
#endif
    return LowDoptOFF;
  }
}


#ifdef UseSX1272
void lora_ResetDev()
{
  //resets the LoRa device, NReset is high for reset on SX1272
  #ifdef LORADEBUG
  Serial.println(F("lora_ResetDev() SX1272"));
  #endif
  
  pinMode(lora_NReset, OUTPUT);        //set LoRa Device reset line to output
  digitalWrite(lora_NReset, HIGH);     //ensure reset line is high
  delay(1);
  digitalWrite(lora_NReset, LOW);      //ensure reset line is low
  pinMode(lora_NReset, INPUT);         //set LoRa Device reset line to Input
  delay(6);                            //wait to ensure device is ready
}
#endif


#ifndef UseSX1272
void lora_ResetDev()
{
  //resets the LoRa device, NReset is low for reset on SX1276/8
  #ifdef LORADEBUG
  Serial.println(F("lora_ResetDev() SX1276/8"));
  #endif
  
  pinMode(lora_NReset, OUTPUT);        //set LoRa Device reset line to output
  digitalWrite(lora_NReset, LOW);      //ensure reset line is low
  delay(1);
  digitalWrite(lora_NReset, HIGH);     //ensure reset line is high
  pinMode(lora_NReset, INPUT);         //set LoRa Device reset line to Input
  delay(6);                            //wait to ensure device is ready
}
#endif


int16_t lora_GetFrequencyErrorInt()
{
  uint16_t msb, mid, lsb;
  int16_t freqerr;
  uint8_t bw;
  float bwconst;

  msb = lora_Read(lora_RegFeiMsb);
  mid = lora_Read(lora_RegFeiMid);
  lsb = lora_Read(lora_RegFeiLsb);
  bw = lora_Read(lora_RegModemConfig1) & (0xF0);
  bw = bw >> 4;
  bwconst = pgm_read_float_near(bandwidth + bw);

  freqerr = msb << 12;                     //shift lower 4 bits of msb into high 4 bits of freqerr
  mid = (mid << 8) + lsb;
  mid = (mid >> 4);
  freqerr = freqerr + mid;

  freqerr = (int16_t) (freqerr * bwconst);

  return freqerr;
}


void lora_SetFreqInt(uint64_t freq64, int16_t loffset)
{
  lora_CurrentFreq = freq64;
  freq64 = freq64 + loffset;
  freq64 = ((uint64_t)freq64 << 19) / 32000000;
  lora_Write(lora_RegFrMsb, (uint8_t)(freq64 >> 16));
  lora_Write(lora_RegFrMid, (uint8_t)(freq64 >> 8));
  lora_Write(lora_RegFrLsb, (uint8_t)(freq64 >> 0));
}



float lora_GetFreqFloat()
{
  //get the current set LoRa frequency, return as float
  uint8_t lora_LFMsb, lora_LFMid, lora_LFLsb;
  uint32_t lora_Ltemp;
  float lora_Ltemp1;
  lora_LFMsb = lora_Read(lora_RegFrMsb);
  lora_LFMid = lora_Read(lora_RegFrMid);
  lora_LFLsb = lora_Read(lora_RegFrLsb);
  lora_Ltemp = ((lora_LFMsb * 0x10000ul) + (lora_LFMid * 0x100ul) + lora_LFLsb);
  lora_Ltemp1 = ((lora_Ltemp * 61.03515625) / 1000000ul);
  return lora_Ltemp1;
}


uint32_t lora_GetFreqInt()
{
  //get the current set LoRa device frequency, return as long integer
  uint8_t Msb, Mid, Lsb;
  uint32_t uinttemp;
  float floattemp;
  Msb = lora_Read(lora_RegFrMsb);
  Mid = lora_Read(lora_RegFrMid);
  Lsb = lora_Read(lora_RegFrLsb);
  floattemp = ((Msb * 0x10000ul) + (Mid * 0x100ul) + Lsb);
  floattemp = ((floattemp * 61.03515625) / 1000000ul);
  uinttemp = (uint32_t)(floattemp * 1000000);
  return uinttemp;
}


void lora_PrintFrequencyFloat()
{
float tempfrequency;
tempfrequency = lora_GetFreqFloat();
Serial.print(tempfrequency,3);
}


void lora_PrintFrequencyInt()
{
uint32_t tempfrequency;
tempfrequency = lora_GetFreqInt();
Serial.print(tempfrequency);
}


uint8_t lora_CheckDevice()
{
  //check there is a device out there, writes a register and reads back, puts original value back
  uint8_t RegData, RegDataTemp;
  RegDataTemp = lora_Read(lora_RegFrMid);
  lora_Write(lora_RegFrMid, 0xAA);
  RegData = lora_Read(lora_RegFrMid);         //Read RegFrMid
  lora_Write(lora_RegFrMid, RegDataTemp);     //put original value back
  if (RegData == 0xAA )
  {
    return true;
  }
  else
  {
    return false;
  }
}


boolean lora_GetSleepMode()
{
  uint8_t temp;
  temp = (lora_Read(lora_RegOpMode) & 0x07);
  return temp;
}


void lora_PrintSleepMode()
{
  uint8_t temp;
  temp = (lora_Read(lora_RegOpMode) & 0x07);
  if (temp)
  {
  Serial.println(F("Not in Sleep Mode"));  
  }
  else
  {
  Serial.println(F("In Sleep Mode")); 
  }
}


void lora_CheckSetSleepMode()
{
  //this routine checks the current mode and forces sleep mode if not set
  Serial.println(F("lora_CheckSetSleepMode()"));
  
  if (lora_GetSleepMode())   //if > 0 then not in sleep mode
  {
#ifdef LORADEBUG
    Serial.println(F("Setting sleep mode for LoRa configure"));
#endif
    lora_Write(lora_RegOpMode, 0x88);          //RegOpMode, need to set to sleep mode before configure for LoRa mode
    lora_Write(lora_RegOpMode, 0x88);          //go into LoRa mode
  }
}


uint8_t lora_GetSyncWord()
{
  uint8_t temp;
  temp = lora_Read(lora_RegSyncWord);                    //Read the syncword
  return temp;
}


void lora_PrintSyncWord()
{
  uint8_t temp;
  temp = lora_Read(lora_RegSyncWord);                    //Read the syncword
  lora_PrintHEXByte0x(temp);
}


void lora_PrintSyncWord0x()
{
  uint8_t temp;
  temp = lora_Read(lora_RegSyncWord);                    //Read the syncword
  Serial.print(F("0x"));
  lora_PrintHEXByte(temp);
}


#ifdef UseLoRaWAN
void lora_Setup(uint8_t NSS, uint8_t NReset, uint8_t DIO0)
{
  //initialize LoRa device registers and check its responding
  #ifdef LORADEBUG
  Serialln.print(F("lora_Setup() LoRaWAN"));
  #endif
  
  pinMode (NSS, OUTPUT);                      //LoRa Device select line
  digitalWrite(NSS, HIGH);
  pinMode(NReset, INPUT);                     //LoRa Device reset line
  pinMode (DIO0, INPUT);                      //LoRa DIO0 pin, used for RX ready
  
  lora_ResetDev();                            //Clear all registers to default
  lora_Write(lora_RegOpMode, 0x88);           //RegOpMode, need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOpMode, 0x88);           //set for LoRa mode
  lora_Write(lora_RegOcp, 0x2B);              //RegOcp
  lora_Write(lora_RegLna, 0x23);              //RegLna
  lora_Write(lora_RegSymbTimeoutLsb, 0xFF);   //RegSymbTimeoutLsb
  lora_Write(lora_RegPreambleLsb, 0x0C);      //RegPreambleLsb, default
  lora_Write(lora_RegFdevLsb, Deviation);     //LSB of deviation, 5kHz
  lora_Write(lora_RegSyncWord, 0x34);         //LoRaWAN sync word
  lora_Write(lora_RegInvertIQ, 0x27);         //default I\Q
  lora_Write(lora_RegPllHop, 0x2D);           //make sure fast hop mode not set
}
#endif


#ifndef UseLoRaWAN
void lora_Setup(uint8_t NSS, uint8_t NReset, uint8_t DIO0)
{
  //initialize LoRa device registers and check its responding
  #ifdef LORADEBUG
  Serial.println(F("lora_Setup() Default"));
  #endif
  
  pinMode (NSS, OUTPUT);                      //LoRa Device select line
  digitalWrite(NSS, HIGH);
  pinMode(NReset, INPUT);                     //LoRa Device reset line
  pinMode (DIO0, INPUT);                      //LoRa DIO0 pin, used for RX ready
  
  lora_ResetDev();                            //Clear all registers to default
  lora_Write(lora_RegOpMode, 0x88);           //RegOpMode, need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOpMode, 0x88);           //set for LoRa mode
  lora_Write(lora_RegOcp, 0x2B);              //RegOcp
  lora_Write(lora_RegLna, 0x23);              //RegLna
  lora_Write(lora_RegSymbTimeoutLsb, 0xFF);   //RegSymbTimeoutLsb
  lora_Write(lora_RegPreambleLsb, 0x0C);      //RegPreambleLsb, default
  lora_Write(lora_RegFdevLsb, Deviation);     //LSB of deviation, 5kHz
  lora_Write(lora_RegSyncWord, 0x12);         //default sync word
  lora_Write(lora_RegInvertIQ, 0x27);         //default I\Q
  lora_Write(lora_RegPllHop, 0x2D);           //make sure fast hop mode not set
}
#endif


void lora_TXONDirect(uint8_t TXPower)
{
  //turns on transmitter,in direct mode for FSK and audio  power level is from 2 to 17
#ifdef LORADEBUG
  Serial.print(F("lora_TXONDirect() "));
  Serial.print(TXPower);
  Serial.println(F("dBm "));
#endif
  lora_StartTXTime = millis();
  lora_Write(lora_RegPaConfig, (TXPower + 0xEE));
  lora_Write(lora_RegOpMode, 0x0B);           //TX on direct mode, low frequency mode
}


void lora_TXOFFDirect()
{
  //turns off transmitter
  #ifdef LORADEBUG
  Serial.print(F("lora_TXOFFDirect() "));
  #endif
  lora_TXTime = (millis() - lora_StartTXTime);
  lora_Write(lora_RegOpMode, 0x08);           //TX and RX to sleep, in direct mode
#ifdef LORADEBUG
  Serial.print(lora_TXTime);
  Serial.println(F("mS"));
#endif
}


void lora_TXOFFLoRa()
{
  //turns off transmitter
   #ifdef LORADEBUG
  Serial.print(F("lora_TXOFFLoRa() "));
  #endif
  lora_TXTime = (millis() - lora_StartTXTime);
  lora_Write(lora_RegOpMode, 0x88);           //TX and RX to sleep, in direct mode
#ifdef LORADEBUG
  Serial.print(lora_TXTime);
  Serial.println(F("mS"));
#endif
}


void lora_DirectSetup()
{
  //setup LoRa device for direct modulation mode
  #ifdef LORADEBUG
  Serial.println(F("lora_DirectSetup()"));
  #endif
  lora_Write(lora_RegOpMode, 0x08);
  lora_Write(lora_RegPacketConfig2, 0x00);    //set continuous mode
}


void lora_Tone(int16_t ToneFrequency, uint32_t ToneLength, uint8_t TXPower, uint8_t DIO2)
{
  //Transmit an FM audio tone without using tone library. Uses simple delayMicroseconds values that are assumed to be no more than
  //16383us or about 60Hz, lengths for low frequency tones will not be accurate.
  #ifdef LORADEBUG
  Serial.println(F("lora_Tone() "));
  #endif
  
  uint32_t ToneDelayus, Tone_end_mS;
  ToneDelayus = 500000 / ToneFrequency;

  pinMode (DIO2, OUTPUT);                      //Setuo pin for tone output
    
  lora_DirectSetup();
  lora_Write(lora_RegFdevLsb, Deviation);     //We are generating a tone so set the deviation, 5kHz
  Tone_end_mS = millis() + ToneLength;
  lora_TXONDirect(TXPower);
  pinMode(DIO2, OUTPUT);

  while (millis() < Tone_end_mS)
  {
    digitalWrite(DIO2, HIGH);
    delayMicroseconds(ToneDelayus);
    digitalWrite(DIO2, LOW);
    delayMicroseconds(ToneDelayus);
  }

  pinMode(DIO2, INPUT);
  lora_TXOFFDirect();
}


void lora_Print()
{
  //prints the contents of LoRa registers to serial monitor
  uint8_t Loopv1, Loopv2, Reg, RegData;

  Serial.print(F("Reg    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F"));
  Serial.println();
  Reg = 0;
  for (Loopv1 = 0; Loopv1 <= 7; Loopv1++)
  {
    Serial.print(F("0x"));
    Serial.print(Loopv1, HEX);              //print the register number
    Serial.print(F("0  "));
    for (Loopv2 = 0; Loopv2 <= 15; Loopv2++)
    {
      RegData = lora_Read(Reg);
      if (RegData < 0x10) {
        Serial.print(F("0"));
      }
      Serial.print(RegData, HEX);           //print the register number
      Serial.print(F(" "));
      Reg++;
    }
    Serial.println();
  }
}


#ifdef UseSX1272
void lora_SetModem2(uint8_t Bandwidth, uint8_t SpreadingFactor, uint8_t CodeRate, uint8_t Header)
{
  #ifdef LORADEBUG
  Serial.println(F("lora_SetModem2() SX1272"));
  #endif
  
  uint8_t optimisation;
  //lora_CheckSetSleepMode();
  lora_Write(lora_RegOpMode, 0x88);           //need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOpMode, 0x88);           //now set LoRa mode
  optimisation = lora_GetOptimisation(Bandwidth, SpreadingFactor);
  lora_Write(lora_RegModemConfig1, (Bandwidth + CodeRate + Header + 0x02 + optimisation));   //0x02 turns on CRC for RX
  lora_Write(lora_RegModemConfig2, (SpreadingFactor * 16 + 7));
}
#endif


#ifndef UseSX1272
void lora_SetModem2(uint8_t Bandwidth, uint8_t SpreadingFactor, uint8_t CodeRate, uint8_t Header)
{
  #ifdef LORADEBUG
  Serial.println(F("lora_SetModem2() SX1276/8"));
  #endif
  
  uint8_t optimisation;
  //lora_CheckSetSleepMode();
  lora_Write(lora_RegOpMode, 0x88);           //need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOpMode, 0x88);           //now set LoRa mode
  lora_Write(lora_RegModemConfig1, (Bandwidth + CodeRate + Header));
  lora_Write(lora_RegModemConfig2, (SpreadingFactor * 16 + 7));
  optimisation = lora_GetOptimisation(Bandwidth, SpreadingFactor);
  lora_Write(lora_RegModemConfig3, optimisation);
}
#endif


void lora_PrintASCIIorHEX(uint8_t temp)
{
//Serial.println(F("lora_PrintASCIIorHEX()"));
if ( (temp < 0x10) || (temp > 0x7E) )
{
Serial.print(F(" ("));
lora_PrintHEXByte(temp);
Serial.print(F(") "));
}
else 
{
Serial.write(temp);
} 
}


/*
**************************************************************************************************
  Library Functions RX
**************************************************************************************************
*/ 

void lora_RXBuffPrint(uint8_t PrintType)
{
  //Print contents of RX buffer as ASCII,decimal or HEX
  //PrintType = 0 = ASCII
  //PrintType = 1 = Decimal
  //PrintType = 2 = HEX
  
  #ifdef LORADEBUG
  Serial.print(F("lora_RXBuffPrint("));
  Serial.print(PrintType);
  Serial.println(F(")"));
  #endif
  
  uint8_t bufferData;
  
  /* - Removed not part of buffer
  if (PrintType == 0)
  {
  lora_PrintASCIIorHEX(lora_RXPacketType);
  lora_PrintASCIIorHEX(lora_RXDestination);
  lora_PrintASCIIorHEX(lora_RXSource);
  }
  
  if (PrintType == 1)
  {
  Serial.print(lora_RXPacketType);
  Serial.print(F(" "));
  Serial.print(lora_RXDestination);
  Serial.print(F(" "));
  Serial.print(lora_RXSource);
  Serial.print(F(" "));
  }
  
  if (PrintType == 2)
  {
  lora_PrintHEXByte(lora_RXPacketType);
  Serial.print(F(" "));
  lora_PrintHEXByte(lora_RXDestination);
  Serial.print(F(" "));
  lora_PrintHEXByte(lora_RXSource);
  Serial.print(F(" "));
  }
  */
  
  
  for (uint8_t index = lora_RXStart; index <= lora_RXEnd; index++)
  {
    if (PrintType == 0)
    {
	 lora_PrintASCIIorHEX(lora_RXBUFF[index]); 
    }

    if (PrintType == 1)
    {
	  Serial.print(lora_RXBUFF[index]);
      Serial.print(F(" "));
    }

    if (PrintType == 2)
    {
      bufferData = lora_RXBUFF[index];
      if (bufferData < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(bufferData, HEX);
      Serial.print(F(" "));
    }
  }
}


void lora_FIFOPrint(uint8_t PrintType, uint8_t FIFOstart, uint8_t FIFOlength)
{
  //Print contents of FIFO as ASCII,decimal or HEX
  //PrintType = 0 = ASCII, 1 = Decimal, 2 = HEX
  //If ASCII is selcted, not pintable characters are converted to (00) style hex 
  
  #ifdef LORADEBUG
  Serial.print(F("lora_FIFOPrint("));
  Serial.print(PrintType);
  Serial.println(F(")"));
  #endif
    
  uint8_t FIFOData, index;
  
  lora_Write(lora_RegFifoAddrPtr, FIFOstart);        //set FIFO ptr
  
  digitalWrite(lora_NSS, LOW);               //start the burst read
  SPI.transfer(lora_RegFifo);                //address for burst read
  
  for (index = 1; index <= FIFOlength; index++)
  {

    FIFOData = SPI.transfer(0);

    if (PrintType == 0)
    {
    lora_PrintASCIIorHEX(FIFOData);
    }

    if (PrintType == 1)
    {
      lora_PrintHEXByte(FIFOData);
      Serial.print(F(" "));
    }

    if (PrintType == 2)
    {
      if (FIFOData < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(FIFOData, HEX);
      Serial.print(F(" "));
    }
  }
  digitalWrite(lora_NSS, HIGH);
}


void lora_RXFIFOPrint(uint8_t PrintType)
{
  #ifdef LORADEBUG
  Serial.print(F("lora_RXFIFOPrint("));
  Serial.print(PrintType);
  Serial.println(F(")"));
  #endif

uint8_t FIFOlength, FIFOstart;
FIFOlength = lora_Read(lora_RegRxNbBytes);
FIFOstart = lora_Read(lora_RegFifoRxBaseAddr);
lora_FIFOPrint(PrintType, FIFOstart, FIFOlength);
}


void lora_TXFIFOPrint(uint8_t PrintType)
{
//assume lora_RegFifoAddrPtr is last byte of TX packet written to FIFOuint8_t FIFOlength, FIFOstart;

  #ifdef LORADEBUG
  Serial.print(F("lora_TXFIFOPrint("));
  Serial.print(PrintType);
  Serial.println(F(")"));
  #endif
uint8_t FIFOlength, FIFOstart;
FIFOlength = lora_Read(lora_RegFifoAddrPtr) - lora_Read(lora_RegFifoTxBaseAddr) + 1;  
FIFOstart = lora_Read(lora_RegFifoTxBaseAddr);
lora_FIFOPrint(PrintType, FIFOstart, FIFOlength);
}


void lora_RXOFF()
{
  #ifdef LORADEBUG
  Serial.println(F("lora_RXOFF()"));
  #endif
  lora_Write(lora_RegOpMode, 0x89);                //to standby mode
  lora_RXTime = lora_RXTime + (millis() - lora_StartRXTime);
}


void lora_PrintAddressInfo()
{
  //print the information for packet last received
  #ifdef LORADEBUG
  Serial.println(F("lora_AddressInfo()"));
  #endif
  Serial.print(F("RXType,"));
  lora_PrintASCIIorHEX(lora_RXPacketType);
  Serial.print(F("  Destination,"));
  lora_PrintASCIIorHEX(lora_RXDestination);
  Serial.print(F("  Source,"));
  lora_PrintASCIIorHEX(lora_RXSource);

  Serial.print(F("  Length,"));
  Serial.print(lora_RXPacketL);
  Serial.print(F(" "));
}

void lora_PrintReceptionInfo()
{
  //print the information for packet last received
  //note, lora_PacketSNR has already been converted into a signed value
  //lora_PacketRSSI is a signed value also
  #ifdef LORADEBUG
  Serial.println(F("lora_PrintReceptionInfo()"));
  #endif
  
  Serial.print(F("SNR,"));
  Serial.print(lora_PacketSNR);
  Serial.print(F("dB"));

  Serial.print(F("  RSSI,"));
  Serial.print(lora_PacketRSSI);
  Serial.print(F("dB "));
  
  Serial.print(F("  Length,"));
  Serial.print(lora_Read(lora_RegRxNbBytes));
}


void lora_PrintLoRaSettings()
{
  #ifdef LORADEBUG
  Serial.println(F("lora_PrintLoRaSettings()"));
  #endif
  Serial.print(F("Frequency "));
  lora_PrintFrequencyFloat();
  Serial.println(F("Mhz"));

  Serial.print(F("Bandwidth "));
  lora_PrintBandwidth();
  Serial.println();

  Serial.print(F("Spreading Factor "));
  lora_PrintSpreadingFactor();
  Serial.println();

  Serial.print(F("Coding Rate "));
  lora_PrintCodingRate();
  Serial.println();

  Serial.print(F("Optimisation "));
  lora_PrintOptimisation();
  Serial.println();

  Serial.print(F("Sync Word "));
  lora_PrintSyncWord();
  Serial.println();
}


int8_t lora_returnRSSI(uint8_t RegData)
{
  RegData = (-164 + RegData);
  return RegData;
}


int8_t lora_returnSNR(uint8_t RegData)
{

  if (RegData > 127)
  {
    RegData =  ((255 - RegData) / 4) * (-1);
  }
  else
  {
    RegData = RegData / 4;
  }
  return RegData;
}

int8_t lora_ReadBackgroundRSSI()
{
int8_t BackgroundRSSI;
BackgroundRSSI = lora_returnRSSI(lora_Read(lora_RegRssiValue));
return BackgroundRSSI;
}

void lora_PrintBackgroundRSSI()
{
int8_t BackgroundRSSI;
BackgroundRSSI = lora_ReadBackgroundRSSI();
Serial.print(BackgroundRSSI);
}


void lora_ReadPacketDetails()
{
  //this just reads the packet information, date is not read from FIFO
  #ifdef LORADEBUG
  Serial.println(F("lora_ReadPacketDetails()"));
  #endif

  lora_PacketRSSI = lora_returnRSSI(lora_Read(lora_RegPktRssiValue));
  lora_PacketSNR = lora_returnSNR(lora_Read(lora_RegPktSnrValue));
}


void lora_ReadPacket()
{
  #ifdef LORADEBUG
  Serial.println(F("lora_ReadPacket()"));
  #endif
  uint8_t index, RegData, temp1, temp2;
  
  lora_RXpacketCount++;
  
  temp1 = lora_Read(lora_RegRxNbBytes);
  temp2 = lora_RXBUFF_Size - 1;
  
  lora_RXPacketL = min(temp1, temp2);        //ensure long packet cannot overwrite buffer end

  lora_PacketRSSI = lora_returnRSSI(lora_Read(lora_RegPktRssiValue));
  lora_PacketSNR = lora_returnSNR(lora_Read(lora_RegPktSnrValue));

  lora_Write(lora_RegFifoAddrPtr, 0);        //set RX FIFO ptr

  digitalWrite(lora_NSS, LOW);               //start the burst read
  SPI.transfer(lora_RegFifo);                //address for burst read

  lora_RXPacketType = SPI.transfer(0);
  lora_RXDestination = SPI.transfer(0);
  lora_RXSource = SPI.transfer(0);

  lora_RXStart = 0;
  lora_RXEnd = lora_RXPacketL - 4;           //calculate the end of the packet in the buffer

  for (index = lora_RXStart; index <= lora_RXEnd; index++)
  {
    RegData = SPI.transfer(0);
    lora_RXBUFF[index] = RegData;
  }
  digitalWrite(lora_NSS, HIGH);

}


void lora_RXONLoRa()
{
  //puts lora device into listen mode and receives packet exits with packet in array lora_RXBUFF(256)
  #ifdef LORADEBUG
  Serial.println(F("lora_RXONLoRa()"));
  #endif
  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegFifoRxBaseAddr, 0x00);
  lora_Write(lora_RegFifoAddrPtr, 0x00);
  lora_Write(lora_RegIrqFlagsMask, 0x00);                //allow all flags
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegDioMapping, 0x00);                  //DIO0 will be RXDone
  lora_Write(lora_RegOpMode, 0x8D);
  lora_StartRXTime = millis();
}


boolean lora_readRXreadyIRQ()
{
  //reads the IRQFlags register to see if a packet is ready, constant polling does affect LoRa sensitivity
  uint8_t RegData;
  RegData = (lora_Read(lora_RegIrqFlags) & 0x40);        //check if bit 6 is set   
  
  if (RegData)                                           //if > 0 then packet received
  {
    return true;
  }
  else
  {
    return false;
  }

}


boolean lora_readRXreadyDIO0()
{
  //reads the DIO0 pin to see if a packet is ready

  if (digitalRead(lora_DIO0))
  {
  return true;                  //packet arrived so return true
  }
  else
  {
  return false;                 //no packet arrived, return false
  }
}


uint8_t lora_waitPacket(char waitPacket, uint32_t waitSeconds)
{
  //wait time specified for a incoming packet, 0 = no timeout
  //returns a value of 0 for timeout, 1 for packet received
  #ifdef LORADEBUG
  Serial.println(F("lora_waitPacket()"));
  #endif
  int8_t PacketType = 0;                            //function can exit before PacketType is assigned but not not used, this creates a compiler warning
  uint32_t endtime;
  endtime = (millis() + (waitSeconds * 1000));
  lora_RXONLoRa();
#ifdef LORADEBUG
  Serial.print(F("Wait "));
  Serial.write(waitPacket);
  Serial.println();
#endif

  do
  {
    if (lora_readRXreadyDIO0())
	{
    if (lora_IsPacketValid())
    {
      lora_ReadPacket();
#ifdef LORADEBUG
      lora_AddressInfo();
      Serial.println();
#endif
      PacketType = lora_RXPacketType;
      lora_RXONLoRa();                          //ready for next and clear flags
    }
    else
    {
#ifdef LORADEBUG
      Serial.print(F("Packet error in lora_waitPacket()"));
#endif
    }
    }
    if ((waitSeconds > 0) && (millis() >= endtime))
    {
#ifdef LORADEBUG
      Serial.println(F("Timeout"));
#endif
      return 0;
    }

    if (Serial.available() > 0)
    {
#ifdef LORADEBUG
      Serial.println(F("Serial in ?"));
#endif
      keypress = 1;
      while (Serial.read() != -1);             //clear serial input buffer
      return 0;                                //treat a keypress as a timeout so return 0
    }

  }
  while ((PacketType !=  waitPacket));

  return 1;
}

/*
**************************************************************************************************
  Library Functions TX
**************************************************************************************************
*/

void lora_TXBuffPrint(uint8_t PrintType)
{
  //Print contents of TX buffer as ASCII,decimal or HEX
  #ifdef LORADEBUG
  Serial.print(F("lora_TXBuffPrint("));
  Serial.print(PrintType);
  Serial.println(F(")"));
  #endif
  
  uint8_t index, bufferData;
    
  for (index = lora_TXStart; index <= lora_TXEnd; index++)
  {
    if (PrintType == 0)
    {
	lora_PrintASCIIorHEX(lora_TXBUFF[index]);
    }

    if (PrintType == 1)
    {
      Serial.print(lora_TXBUFF[index]);
      Serial.print(F(" "));
    }

    if (PrintType == 2)
    {
      bufferData = lora_TXBUFF[index];
      if (bufferData < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(bufferData, HEX);
      Serial.print(F(" "));
    }
  }
}


void lora_TXONLoRa(uint8_t TXPower)
{
  //turns on LoRa transmitter, Sends packet, power level is from 2 to 17

  #ifdef LORADEBUG
  Serial.print(F("lora_TXONLoRa() "));
  Serial.print(TXPower);
  Serial.println(F("dBm  "));
#endif
  lora_StartTXTime = millis();
  lora_Write(lora_RegPaConfig, (TXPower + 0xEE));   //set TX power
  lora_Write(lora_RegOpMode, 0x8B);                 //TX on direct mode, low frequency mode
}


void lora_Send(uint8_t TXBuffStart, uint8_t TXBuffEnd, char TXPacketType, char TXDestination, char TXSource, uint16_t TXTimeout, uint8_t TXPower, uint8_t StripAddress)
{
  #ifdef LORADEBUG
  Serial.println(F("lora_Send()"));
  #endif
  
  uint8_t index;
  uint8_t BufferData, RegData;
  uint8_t TXPacketL = 0;

  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegIrqFlagsMask, 0xF7);
  lora_Write(lora_RegFifoTxBaseAddr, 0x00);
  lora_Write(lora_RegFifoAddrPtr, 0x00);            //start burst read

  digitalWrite(lora_NSS, LOW);                      //Set NSS low
  SPI.transfer(lora_WRegFifo);                      //address for burst write

  if (!StripAddress)
  {
    SPI.transfer(TXPacketType);                     //Write the packet type
    SPI.transfer(TXDestination);                    //Destination node
    SPI.transfer(TXSource);                         //Source node
    TXPacketL = 3;                                  //We have added 3 header bytes
  }


  for (index = TXBuffStart; index <= TXBuffEnd; index++)
  {
    TXPacketL++;

    if (TXPacketL > 253)                            //check for overlong packet here, wraps around from limit at 251 to 0
    {
      TXPacketL--;                                  //remove increment to packet length
      break;
    }
    BufferData = lora_TXBUFF[index];
    SPI.transfer(BufferData);
  }

  digitalWrite(lora_NSS, HIGH);                     //finish the burst write
  lora_Write(lora_RegPayloadLength, TXPacketL);
  TXTimeout = TXTimeout * 945;                      //convert seconds to mS, delay in TX done loop is 1ms

  lora_TXONLoRa(TXPower);

  do
  {
    delay(1);
    TXTimeout--;
    RegData = lora_Read(lora_RegIrqFlags);
  }
  while (TXTimeout > 0 && RegData == 0) ;           //use a timeout counter, just in case the TX sent flag is missed

  lora_TXOFFLoRa();
}


uint8_t lora_QueuedSend(uint8_t TXBuffStart, uint8_t TXBuffEnd, char TXPacketType, char TXDestination, char TXSource, uint16_t TXTimeout, uint8_t TXPower, uint8_t Attempts, uint8_t StripAddress)
{
  //wait time specified for a incoming packet, 0 = no timeout
  //returns a value of 0 for timeout, 1 for packet sent and acknowledged
  #ifdef LORADEBUG
  Serial.println(F("lora_QueuedSend()"));
  #endif
  uint16_t tempAttempts = Attempts;             //to store value of lora_Attempts

#ifdef LORADEBUG
  Serial.print(F("Queue "));
  Serial.write(TXPacketType);
  Serial.write(TXDestination);
  Serial.write(TXSource);
  Serial.print(F(" Attempts "));
  Serial.println(Attempts);
#endif

  do
  {

    if (!lora_waitPacket(ClearToSendCommand, 0))    //returns a value of 0 for timeout, 1 for packet received, no timeout
    {
#ifdef LORADEBUG
      Serial.println(F("Exit QueuedSend"));
#endif
      return 0;                                     //either timeout or key exit
    }

    delay(1000);

#ifdef LORADEBUG
    Serial.print(F("Send "));
    Serial.write(TXPacketType);
    Serial.write(TXDestination);
    Serial.write(TXSource);
    Serial.print(F(" "));
#endif

    lora_Send(TXBuffStart, TXBuffEnd, TXPacketType, TXDestination, TXSource, TXTimeout, TXPower, StripAddress);

    if (lora_waitPacket(ACK, 5) == 1)               //when returns the value of lora_RXPacketType may be updated
    {
      return 1;
    }

    if (Serial.available() > 0)
    {
#ifdef LORADEBUG
      Serial.println(F("Serial in ?"));
#endif
      keypress = 1;
      while (Serial.read() != -1);                  //clear serial input buffer
      return 0;
    }

    if (tempAttempts != 0)
    {
      Attempts--;
    }
    else
    {
      Attempts = 1;
    }

  }
  while ( (lora_RXPacketType != ACK) && (Attempts > 0) );

#ifdef LORADEBUG
  Serial.println(F("Timeout Waiting for ACK"));
#endif
  return 0;
}


void lora_SendFIFO(byte lora_LPacketL, long lora_LTXTimeout, byte lora_LTXPower)
{
  //send contents of FIFO
  byte lora_LRegData;
  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegIrqFlagsMask, 0xF7);
  lora_Write(lora_RegPayloadLength, lora_LPacketL);
  lora_Write(lora_RegFifoTxBaseAddr, 0x00);
  lora_LTXTimeout = lora_LTXTimeout * 945;		                 //convert seconds to mS, delay in TX done loop is 1ms

  lora_TXONLoRa(lora_LTXPower);

  do
  {
    delay(1);
    lora_LTXTimeout--;
    lora_LRegData = lora_Read(lora_RegIrqFlags);
  }
  while (lora_LTXTimeout > 0 && lora_LRegData == 0) ;	                 //use a timeout counter, just in case the TX sent flag is missed
}
