#ifndef CTRANSCEIVER_TASK_H
#define CTRANSCEIVER_TASK_H

//====================================================================================================
//описание
//====================================================================================================

// ласс приЄмо-передатчика данных заданий

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
//класс приЄмо-передатчика данных заданий
//====================================================================================================

class CTransceiver_Task:public CTransceiver
{
 protected:
  unsigned long Version;//номер версии структуры
 public:  
  //конструктор
  CTransceiver_Task(void);
  //деструктор
  ~CTransceiver_Task();
  //функции класса
  bool ReadCTaskInArray(char *ptr,size_t &offset,size_t max_length,CTask &cTask);//получение задани€ из массива прин€тых данных
  bool SendTaskDataToServer(SOCKET socket_server,const CTask &cTask,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные задани€
  bool SendTaskDataToServerInPackage(SOCKET socket_server,const CTask &cTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные задани€ в виде полного пакета
  bool GetTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос базы данных заданий
  bool GetTaskAnswer(char *ptr,size_t size,CTask &cTask);//считать задачу из ответа сервера
};

#endif
