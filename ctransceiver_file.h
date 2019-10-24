#ifndef CTRANSCEIVER_FILE_H
#define CTRANSCEIVER_FILE_H

//====================================================================================================
//описание
//====================================================================================================

//Класс приёмо-передатчика файлов

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include <list>
#include <vector>
#include <string>
#include "cdocument_main.h"
#include "protocol.h"
#include "ctransceiver.h"



//====================================================================================================
//класс приёмо-передатчика файлов
//====================================================================================================

class CTransceiver_File:public CTransceiver
{
 protected:
 public:  
  //конструктор
  CTransceiver_File(void);
  //деструктор
  ~CTransceiver_File();
  //функции класса
  bool GetClientProgrammCRC(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос CRC программы
  bool GetClientProgrammAndLoader(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос программы и загрузчика
  bool ReadCRCInArray(char *ptr,size_t &offset,size_t max_length,unsigned long &crc16);//считать CRC из ответа сервера
  bool ReadClientProgrammAndLoaderInArray(char *ptr,size_t &offset,size_t max_length);//считать и записать программу из ответа сервера
 protected:
  bool SaveFileAndCompareCRC(char *ptr,size_t size,const CSafeString &file_name,unsigned long original_crc16);//сохранить файл и сравнить его CRC

};

#endif
