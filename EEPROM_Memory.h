//EEPROM_Memory.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  To Do:

*******************************************************************************************************************************
*/

#include <EEPROM.h>


void Memory_Start()
{
 //left empty for future use
}


void Memory_End()
{
 //left empty for future use 
}



void Memory_WriteByte(unsigned int addr, byte x)
{
  //write a byte to the EEPROM
  EEPROM.put(addr, x);
}


void Memory_WriteUInt(unsigned int addr, unsigned int x)
{
  EEPROM.put(addr, x);
}


void Memory_WriteInt(unsigned int addr, int x)
{
  EEPROM.put(addr, x);
}


void Memory_WriteULong(unsigned int addr, unsigned long x)
{
  EEPROM.put(addr, x);
}

void Memory_WriteFloat(unsigned int addr, float x)
{
  EEPROM.put(addr, x);
}


byte Memory_ReadByte(unsigned int addr)
{
  byte x;
  EEPROM.get(addr, x);
  return x;
}

float Memory_ReadFloat(unsigned int addr)
{
  float x;
  EEPROM.get(addr, x);
  return x;
}

int Memory_ReadInt(unsigned int addr)
{
  int x;
  EEPROM.get(addr, x);
  return x;
}


unsigned int Memory_ReadUInt(unsigned int addr)
{
  unsigned int x;
  EEPROM.get(addr, x);
  return x;
}


unsigned long Memory_ReadULong(unsigned int addr)
{
  unsigned long x;
  EEPROM.get(addr, x);
  return x;
}



/***************************************************************************
  Start of general purpose memory routines
***************************************************************************/

unsigned int Memory_CRC(unsigned int startaddr, unsigned int endaddr)
{
  uint16_t i, CRC;

  CRC = 0xffff;                                         //start value for CRC16
  byte j; 

  for (i = startaddr; i <= endaddr; i++)                //element 4 is first character after $$$$ at start
  {
    CRC ^= ((uint16_t)Memory_ReadByte(i) << 8);
    for (j = 0; j < 8; j++)
    {
      if (CRC & 0x8000)
        CRC = (CRC << 1) ^ 0x1021;
      else
        CRC <<= 1;
    }
  }
  return CRC;

}



void Print_Memory(uint16_t start_addr, uint16_t end_addr)
{
  //print the contents of Memory
  //byte data;
 // unsigned int i;
   
  uint8_t value;
  for (uint16_t a = start_addr; a <= end_addr; a++) 
  {
    value = Memory_ReadByte(a);
    if ((a % 16) == 0) 
    {
      Serial.print(F("\n 0x")); 
      if (a < 0x10) 
      {
       Serial.print('0');
      }
      Serial.print(a, HEX); 
      Serial.print(F(": "));
    }
    Serial.print(F("0x")); 
    if (value < 0x10) 
      Serial.print('0');
    Serial.print(value, HEX); 
    Serial.print(F(" "));
  }
  Serial.println();
}




void Memory_Set(unsigned int startaddr, unsigned int endaddr, byte lval)
{
  unsigned int i;
  for (i = startaddr; i <= endaddr; i++)
  {
    Memory_WriteByte(i, lval);
  }
}




