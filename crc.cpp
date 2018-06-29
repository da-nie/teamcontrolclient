#include "crc.h"

//----------------------------------------------------------------------------------------------------
//посчитать CRC16
//----------------------------------------------------------------------------------------------------
unsigned short CreateCRC16(unsigned short &crc16,const void *ptr,unsigned long length)
{
 const unsigned char *local_ptr=reinterpret_cast<const unsigned char*>(ptr);
 for(unsigned short n=0;n<length;n++,local_ptr++)
 {
  unsigned char byte=*local_ptr;
  crc16^=(byte<<8);
  for (unsigned char i=0;i<8;i++) 
  { 
   if (crc16&0x8000) crc16=(crc16<<1)^0x1021;
                else crc16<<=1;
  }
 }
 return(crc16);	
}
