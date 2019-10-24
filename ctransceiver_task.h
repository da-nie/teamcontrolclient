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



//====================================================================================================
//класс приёмо-передатчика данных заданий
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
  bool ReadCTaskInArray(char *ptr,size_t &offset,size_t max_length,CTask &cTask);//получение задания из массива принятых данных
  bool SendTaskDataToServer(SOCKET socket_server,const CTask &cTask,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные задания
  bool SendTaskDataToServerInPackage(SOCKET socket_server,const CTask &cTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//передать серверу данные задания в виде полного пакета
  bool GetTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос базы данных заданий
  bool GetCommonTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//запрос базы данных общих заданий
  bool GetTaskAnswer(char *ptr,size_t size,CTask &cTask);//считать задачу из ответа сервера
};

#endif
