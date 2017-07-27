#ifndef CTRANSCEIVER_TASK_H
#define CTRANSCEIVER_TASK_H

//====================================================================================================
//описание
//====================================================================================================

//Класс приёмо-передатчика данных заданий

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
//класс приёмо-передатчика данных заданий
//====================================================================================================

class CTransceiver_Task:public CTransceiver
{
 protected:
 public:  
  //конструктор
  CTransceiver_Task(void);
  //деструктор
  ~CTransceiver_Task();
  //функции класса
  bool ReadSTaskInArray(char *ptr,size_t &offset,size_t max_length,STask &sTask);//получение задания из массива принятых данных
  bool SendTaskDataToServer(SOCKET socket_server,const STask &sTask,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные задания
  bool SendTaskDataToServerInPackage(SOCKET socket_server,const STask &sTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные задания в виде полного пакета
  bool GetTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос базы данных заданий
  bool GetTaskAnswer(char *ptr,size_t size,STask &sTask);//считать задачу из ответа сервера
};

#endif
