#ifndef CTRANSCEIVER_H
#define CTRANSCEIVER_H

//====================================================================================================
//описание
//====================================================================================================

//Класс приёмо-передатчика

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include <list>
#include <vector>
#include <string>
#include "cdocument_main.h"
#include "protocol.h"

using namespace std;
//====================================================================================================
//класс приёмо-передатчика
//====================================================================================================

class CTransceiver
{
 protected:
 public:  
  //конструктор
  CTransceiver(void);
  //деструктор
  ~CTransceiver();
 protected:
  bool SendBeginPackage(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//отправить код начала пакета
  bool SendEndPackage(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//отправить код конца пакета
  bool SendQuestion(SOCKET socket_server,SERVER_ANSWER answer,const char *data,unsigned long size,CEvent &cEvent_Exit,bool &on_exit);//отправить запрос серверу
  bool SendPart(SOCKET socket_server,const char *data,unsigned long size,CEvent &cEvent_Exit,bool &on_exit);//отправить данные серверу с выполнением байтстаффинга
  bool SendData(SOCKET socket_server,const char *package,long size,CEvent &cEvent_Exit,bool &on_exit);//отправить данные серверу
  void Pause(long time_ms);//пауза
  void SetString(CString &text,char *buffer,long length);//задать строку по массиву
};

#endif



