#ifndef CTRANSCEIVER_PROJECT_H
#define CTRANSCEIVER_PROJECT_H

//====================================================================================================
//описание
//====================================================================================================

//Класс приёмо-передатчика данных проектов

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
//класс приёмо-передатчика данных проектов
//====================================================================================================

class CTransceiver_Project:public CTransceiver
{
 protected:
 public:  
  //конструктор
  CTransceiver_Project(void);
  //деструктор
  ~CTransceiver_Project();
  //функции класса
  bool ReadCProjectInArray(char *ptr,size_t &offset,size_t max_length,CProject &cProject);//получение проекта из массива принятых данных
  bool SendProjectDataToServer(SOCKET socket_server,const CProject &cProject,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные проекта
  bool SendProjectDataToServerInPackage(SOCKET socket_server,const CProject &cProject,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные проекта в виде полного пакета
  bool GetProjectBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос базы данных заданий
  bool GetProjectAnswer(char *ptr,size_t size,CProject &cProject);//считать проект из ответа сервера
};

#endif
