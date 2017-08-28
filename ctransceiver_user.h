#ifndef CTRANSCEIVER_USER_H
#define CTRANSCEIVER_USER_H

//====================================================================================================
//описание
//====================================================================================================

//Класс приёмо-передатчика данных пользователей

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

using namespace std;

//====================================================================================================
//класс приёмо-передатчика данных пользователей
//====================================================================================================

class CTransceiver_User:public CTransceiver
{
 protected:
 public:  
  //конструктор
  CTransceiver_User(void);
  //деструктор
  ~CTransceiver_User();
  //функции класса
  bool ReadCUserInArray(char *ptr,size_t &offset,size_t max_length,CUser &cUser);//получение сотрудника из массива принятых данных
  bool GetUserBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос базы данных пользователей
  bool GetUserAnswer(char *ptr,size_t size,CUser &cUser);//считать пользователя из ответа сервера
};

#endif
