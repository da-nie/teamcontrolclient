#include "ctransceiver_file.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_File::CTransceiver_File(void)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTransceiver_File::~CTransceiver_File()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//запрос CRC программы
//----------------------------------------------------------------------------------------------------
bool CTransceiver_File::GetClientProgrammCRC(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=SERVER_COMMAND_GET_CLIENT_PROGRAMM_CRC;
 //начинаем передачу пакета
 if (SendBeginPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sHeader),sizeof(SServerCommand::SHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendEndPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//запрос программы и загрузчика
//----------------------------------------------------------------------------------------------------
bool CTransceiver_File::GetClientProgrammAndLoader(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=SERVER_COMMAND_GET_CLIENT_PROGRAMM_AND_LOADER;
 //начинаем передачу пакета
 if (SendBeginPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sHeader),sizeof(SServerCommand::SHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendEndPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//считать CRC из ответа сервера
//----------------------------------------------------------------------------------------------------
bool CTransceiver_File::ReadCRCInArray(char *ptr,size_t &offset,size_t max_length,unsigned long &crc16)
{
 if (offset+sizeof(SServerAnswer::SClientProgrammCRCHeader)>max_length) return(false);
 SServerAnswer::SClientProgrammCRCHeader *sServerAnswer_sClientProgrammCRCHeader_Ptr=reinterpret_cast<SServerAnswer::SClientProgrammCRCHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::SClientProgrammCRCHeader);
 crc16=sServerAnswer_sClientProgrammCRCHeader_Ptr->CRC;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//считать и записать программу из ответа сервера
//----------------------------------------------------------------------------------------------------
bool CTransceiver_File::ReadClientProgrammAndLoaderInArray(char *ptr,size_t &offset,size_t max_length)
{
 if (offset+sizeof(SServerAnswer::SClientProgrammAndLoaderDataHeader)>max_length) return(false);
 SServerAnswer::SClientProgrammAndLoaderDataHeader *sServerAnswer_sClientProgrammAndLoaderDataHeader_Ptr=reinterpret_cast<SServerAnswer::SClientProgrammAndLoaderDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::SClientProgrammAndLoaderDataHeader);
 unsigned long programm_crc16=sServerAnswer_sClientProgrammAndLoaderDataHeader_Ptr->ProgrammCRC;
 unsigned long loader_crc16=sServerAnswer_sClientProgrammAndLoaderDataHeader_Ptr->LoaderCRC;
 unsigned long programm_size=sServerAnswer_sClientProgrammAndLoaderDataHeader_Ptr->ProgrammSize;
 unsigned long loader_size=sServerAnswer_sClientProgrammAndLoaderDataHeader_Ptr->LoaderSize;
 if (offset+programm_size+loader_size>max_length) return(false);

 //сохраняем программу и загрузчик
 if (SaveFileAndCompareCRC(ptr+offset,loader_size,"TeamControlLoader.exe",loader_crc16)==false) return(false);
 offset+=loader_size;
 if (SaveFileAndCompareCRC(ptr+offset,programm_size,"TeamControlClient_New.exe",programm_crc16)==false) return(false);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//сохранить файл и сравнить его CRC
//----------------------------------------------------------------------------------------------------
bool CTransceiver_File::SaveFileAndCompareCRC(char *ptr,size_t size,const CSafeString &file_name,unsigned long original_crc16)
{
 FILE *file=fopen(file_name,"wb");
 if (file==NULL) return(false);
 unsigned short crc16=0;
 for(size_t n=0;n<size;n++,ptr++)
 {
  unsigned char byte=*ptr;
  crc16^=(byte<<8);
  for (unsigned char i=0;i<8;i++) 
  { 
   if (crc16&0x8000) crc16=(crc16<<1)^0x1021;
                else crc16<<=1;
  }
  if (fwrite(&byte,sizeof(unsigned char),1,file)<=0)
  {
   fclose(file);
   return(false);
  }
 }
 fclose(file);
 if (crc16!=original_crc16) return(false);
 return(true);
}