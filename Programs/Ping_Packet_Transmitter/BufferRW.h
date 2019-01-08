//Binary_Test.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 20/12/18

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program writes and reads variables to and from the buffer address passed. It is normally used together with the LoRa
  TX and RX buffers.


  To Do:

*******************************************************************************************************************************
*/

void Write_Byte(byte addr, byte x, byte localbuff[])
{
  localbuff[addr] = x;
}


void Write_Int(byte addr, int x,  byte localbuff[])
{
  localbuff[addr] = lowByte(x);
  localbuff[addr + 1] = highByte(x);
}


void Write_UInt(byte addr, unsigned int x,  byte localbuff[])
{
  localbuff[addr] = lowByte(x);
  localbuff[addr + 1] = highByte(x);
}


void Write_Float(byte addr, float x,  byte localbuff[])
{
  byte i, j;

  union
  {
    byte b[4];
    float f;
  } data;
  data.f = x;

  for (i = 0; i < 4; i++)
  {
    j = data.b[i];
    localbuff[addr + i] = j;
  }
}


byte Read_Byte(byte addr, byte localbuff[])
{
  return localbuff[addr];
}


float Read_Float(byte addr, byte localbuff[])
{
  byte i, j;

  union
  {
    byte b[4];
    float f;
  } readdata;

  for (i = 0; i < 4; i++)
  {
    j = localbuff[addr + i];
    readdata.b[i] = j;
  }
  return readdata.f;
}


int Read_Int(byte addr, byte localbuff[])
{
  byte lowbyte, highbyte;
  lowbyte = localbuff[addr];
  highbyte = localbuff[addr + 1];
  return (lowbyte + (highbyte * 256));
}


unsigned int Read_UInt(byte addr, byte localbuff[])
{
  byte lowbyte, highbyte;
  lowbyte = localbuff[addr];
  highbyte = localbuff[addr + 1];
  return (lowbyte + (highbyte * 256));
}

