#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

//====================================================================================================
//описание
//====================================================================================================

//Класс клиентского потока

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include <list>
#include <vector>
#include "protocol.h"
#include "cdocument_main.h"
#include "cvector_task.h"
#include "craiiccriticalsection.h"
#include "ctransceiver_user.h"
#include "ctransceiver_task.h"
#include "ctransceiver_project.h"
#include "ctransceiver_file.h"
#include "ctransceiver_autorization.h"
#include "ctransceiver_ping.h"

using namespace std;

//====================================================================================================
//макроопределения
//====================================================================================================

//режимы работы
enum WORKING_MODE
{
 //ожидание
 WORKING_MODE_WAIT,
 //получение контрольной суммы программы на сервере
 WORKING_MODE_GET_CLIENT_PROGRAMM_CRC,
 //ожидание контрольной суммы программы
 WORKING_MODE_WAIT_CLIENT_PROGRAMM_CRC,
 //ожидание обновления программы
 WORKING_MODE_WAIT_UPDATE,
 //получение клиентской программы и загрузчика с сервера
 WORKING_MODE_GET_CLIENT_PROGRAMM_AND_LOADER,
 //авторизация
 WORKING_MODE_AUTORIZATION,
 //проверка авторизации
 WORKING_MODE_CHECK_AUTORIZATION,
 //запрос полной базы данных от сервера
 WORKING_MODE_GET_USER_BOOK,
 //ожидание полной базы данных от сервера
 WORKING_MODE_WAIT_GET_USER_BOOK,
 //запрос полной базы заданий от сервера
 WORKING_MODE_GET_TASK_BOOK,
 //ожидание полной базы заданий от сервера
 WORKING_MODE_WAIT_GET_TASK_BOOK,
 //запрос полной базы проектов от сервера
 WORKING_MODE_GET_PROJECT_BOOK,
 //ожидание полной базы проектов от сервера
 WORKING_MODE_WAIT_GET_PROJECT_BOOK
};

//====================================================================================================
//класс клиентского потока
//====================================================================================================

class CThreadClient
{
 //дружественные функции
 friend UINT ThreadClient(LPVOID pParam);//функция потока
 protected:

  vector<unsigned char> vector_Data;//принятые данные

  CEvent cEvent_Exit;//требование на выход из потока
  CWinThread *cWinThread_Thread;//поток обработки
  CDocument_Main *cDocument_Main_Ptr;//указатель на документ
  char *Buffer;//буфер приёма/передачи   

  bool StuffingEnabled;//включён ли байтстаффинг

  WORKING_MODE WorkingMode;//текущий режим работы с сервером

  CTransceiver_Ping cTransceiver_Ping;//приёмо-передатчик данных сообщения для проверки связи
  CTransceiver_User cTransceiver_User;//приёмо-передатчик данных пользователей
  CTransceiver_Task cTransceiver_Task;//приёмо-передатчик данных заданий
  CTransceiver_Project cTransceiver_Project;//приёмо-передатчик данных проектов
  CTransceiver_File cTransceiver_File;//приёмо-передатчик файлов программы и загрузчика
  CTransceiver_Autorization cTransceiver_Autorization;//приёмо-передатчик данных авторизации

 public:  
  //конструктор
  CThreadClient(void);
  //деструктор
  ~CThreadClient();
   void Start(void);//запустить поток
   void Stop(void);//остановить поток
   void SetDocument(CDocument_Main *cDocument_Main_Set_Ptr);//задать класс документа
 protected:
  void SaveTaskVector(char *filename,const vector<CTask> &vector_CTask);//сохранение массива заданий
  void Processing(void);//основной цикл обработки
  bool LinkProcessing(SOCKET socket_server,bool &on_exit);//обработка обмена с сервером
  bool TaskProcessing(SOCKET socket_server,bool &on_exit);//обработка заданий
  bool ProjectProcessing(SOCKET socket_server,bool &on_exit);//обработка проектов
  bool PingProcessing(SOCKET socket_server,bool &on_exit);//обработка сообщений проверки связи

  bool ExecuteCommand_GetClientProgrammCRC(SOCKET socket_server,bool &on_exit);//выполнение команды запроса контрольной суммы программы на сервере
  bool ExecuteCommand_GetClientProgrammAndLoader(SOCKET socket_server,bool &on_exit);//выполнение команды запроса программы и загрузчика

  bool ExecuteCommand_Autorization(SOCKET socket_server,bool &on_exit);//выполнение команды авторизации
  bool ExecuteCommand_GetUserBook(SOCKET socket_server,bool &on_exit);//выполнение команды запроса базы пользователей
  bool ExecuteCommand_GetTaskBook(SOCKET socket_server,bool &on_exit);//выполнение команды запроса базы заданий
  bool ExecuteCommand_GetProjectBook(SOCKET socket_server,bool &on_exit);//выполнение команды запроса базы проектов

  void NewDataFromServer(SOCKET socket_server,char *data,unsigned long length,bool &on_exit);//приняты данные от сервера
  void ExecuteAnswer_ClientProgrammCRC(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение контрольной суммы клиентской программы на сервере
  void ExecuteAnswer_ClientProgrammAndLoader(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение клиентской программы и загрузчика и выполнение обновления
  void ExecuteAnswer_GetUserBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение базы сотрудников
  void ExecuteAnswer_GetTaskBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение базы заданий
  void ExecuteAnswer_GetProjectBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение базы проектов
  void ExecuteAnswer_Ok(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: ок
  void ExecuteAnswer_AutorizationOk(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: авторизация принята
  void ExecuteAnswer_Error(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: ошибка
  void ExecuteAnswer_GetDeletedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных удалённого сотрудника
  void ExecuteAnswer_GetAddedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных добавленного сотрудника
  void ExecuteAnswer_GetChangedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных изменённого сотрудника

  void ExecuteAnswer_GetDeletedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных удалённого задания
  void ExecuteAnswer_GetAddedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных добавленного задания
  void ExecuteAnswer_GetChangedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных изменённого задания

  void ExecuteAnswer_GetDeletedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных удалённого проекта
  void ExecuteAnswer_GetAddedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных добавленного проекта
  void ExecuteAnswer_GetChangedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//обработка ответа: получение данных изменённого проекта

  bool ConnectAsServer(SOCKET &server,CSafeString host_name,long port,bool &on_exit);//подключение к серверу
  bool SetSocketNoBlockMode(SOCKET socket_set,bool state);//задание неблокирующего режима для сокета
};

#endif