#ifndef CDOCUMENT_MAIN_H
#define CDOCUMENT_MAIN_H

//====================================================================================================
//описание
//====================================================================================================

//Класс документов для списка пользователей.

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include <list>
#include <vector>
#include "stdafx.h"
#include "craiiccriticalsection.h"
#include "cvector_task.h"
#include "cvector_user.h"
#include "cvector_project.h"

using namespace std;

//====================================================================================================
//макроопределения
//====================================================================================================

//GUID, отвечающее за всех пользователей
#define ALL_USER_GUID "{5F133563-3C76-41EE-9038-743DAAC8949A}"

//====================================================================================================
//структуры
//====================================================================================================

//настройки клиента
struct SClientSettings
{
 unsigned short ServerPort;//порт сервера
 BYTE ServerIP[4];//адрес сервера
 char Login[255];//логин
 char Password[255];//пароль
 unsigned long MyGUIDSize;//размер нашего GUID
};

//настройки отображения данных
struct SShowState
{
 bool OutTask_Show_Cancelled;//показывать ли отменённые задания в списке выданных
 bool OutTask_Show_Done;//показывать ли выполненные задания в списке выданных
 bool OutTask_Show_NotRead;//показывать ли не прочитанные задания в списке выданных
 bool OutTask_Show_Finished;//показывать ли завершённые задания в списке выданных
 bool OutTask_Show_IsRunning;//показывать ли выполняющиеся задания в списке выданных
 bool OutTask_Show_Readed;//показывать ли прочитанные задания в списке выданных

 bool MyTask_Show_Cancelled;//показывать ли отменённые задания в списке полученных
 bool MyTask_Show_Done;//показывать ли выполненные задания в списке полученных
 bool MyTask_Show_NotRead;//показывать ли не прочитанные задания в списке полученных
 bool MyTask_Show_Finished;//показывать ли завершённые задания в списке полученных
 bool MyTask_Show_IsRunning;//показывать ли выполняющиеся задания в списке полученных
 bool MyTask_Show_Readed;//показывать ли прочитанные задания в списке полученных
};

//====================================================================================================
//класс документов
//====================================================================================================

class CDocument_Main:public CDocument
{
 protected:
  //-Переменные класса-------------------------------------------------------
  //структура защищённых переменных
  struct SProtectedVariables
  {
   CUser cUser_Selected;//выбранный пользователь
   bool UserIsSelected;//есть ли выбраный пользователь
   bool OnShow;//нужно ли показать окно

   CVectorUser cVectorUser;//список пользователей
   CVectorTask cVectorTask;//список заданий
   CVectorProject cVectorProject;//список проектов

   bool OnUpdateView;//требуется ли обновить видам данные 

   CSafeString MyGUID;//наш GUID, полученный после авторизации
   bool OnLine;//подключены ли мы к серверу
   CSafeString MyName;//имя пользователя
   bool Leader;//является ли пользователь руководителем

   bool RestartWithLoader;//нужна ли перезагрузка через загрузчик

   bool NotReadTaskState;//есть ли непрочитанные задания

   SClientSettings sClientSettings;//настройки клиента

   CVectorTask cVectorTask_TransferToServer;//задания для передачи на сервер
   CVectorProject cVectorProject_TransferToServer;//проекты для передачи на сервер

   SShowState sShowState;//настройки отображения данных


   CCriticalSection cCriticalSection;//критическая секция для доступа к структуре
  } sProtectedVariables;
 public:
  //-Конструктор класса------------------------------------------------------
  CDocument_Main(void);
  //-Деструктор класса-------------------------------------------------------
  ~CDocument_Main();
  //-Функции класса----------------------------------------------------------
  void RestartWithLoader(void);//выполнить перезагрузку через загрузчик
  bool GetRestartWithLoaderState(void);//получить, нужна ли перезагрузка через загрузчик

  void DeleteFinishedTask(long year,long month,long day);//удалить все выданные нами и завершённые задания до даты включительно
  bool GetNotReadTaskState(void);//получить, есть ли непрочитанные задания
  void SetNotReadTaskState(bool state);//задать, есть ли непрочитанные задания

  void SaveState(void);//сохранить состояние
  bool FindByUserGUIDAndResetChangeData(const CSafeString &guid,CUser &cUser);//найти пользователя по GUID и сбросить новизну данных
  bool FindByUserGUID(const CSafeString &guid,CUser &cUser);//найти пользователя по GUID

  bool FindByProjectGUIDAndResetChangeData(const CSafeString &guid,CProject &cProject);//найти проект по GUID и сбросить новизну данных
  bool FindByProjectGUID(const CSafeString &guid,CProject &cProject);//найти проект по GUID

  void GetMyParam(bool &on_line,CSafeString &guid,CSafeString &name,bool &leader);//получить наши параметры
  void SetMyParam(const bool &on_line,const CSafeString &guid,const CSafeString &name,const bool &leader);//задать наши параметры
  void SetOnLine(const bool &on_line);//установить, есть ли подключение
  void GetShowState(SShowState &sShowState);//получить параметры отображения данных
  void SetShowState(SShowState &sShowState);//задать параметры отображения данных

  void GetClientSettings(SClientSettings &sClientSettings);//получить настройки клиента
  void SetClientSettings(const SClientSettings &sClientSettings);//установить настройки клиента (клиента будет перезапущен)

  CVectorUser GetCVectorUser(void);//получить список пользователей
  CVectorTask GetCVectorTask(void);//получить список заданий
  CVectorProject GetCVectorProject(void);//получить список проектов

  void SetUserBook(CVectorUser &cVectorUser_Set);//задать список пользователей
  void SetTaskBook(CVectorTask &cVectorTask_Set);//задать список заданий
  void SetProjectBook(CVectorProject &cVectorProject_Set);//задать список проектов

  void OnDeletedUser(const CUser &cUser);//был удалён пользователь
  void OnAddedUser(const CUser &cUser);//был добавлен пользователь
  void OnChangedUser(const CUser &cUser);//был изменён пользователь

  void OnDeletedTask(const CTask &cTask);//было удалёно задание
  void OnAddedTask(const CTask &cTask);//было добавлено задание
  void OnChangedTask(const CTask &cTask);//было изменёно задание

  void OnDeletedProject(const CProject &cProject);//был удалён проект
  void OnAddedProject(const CProject &cProject);//был добавлен проект
  void OnChangedProject(const CProject &cProject);//был изменёно задание

  void SetSelectedUser(const CUser &cUser);//установить выбранного пользователя
  void ResetSelectedUser(void);//отменить выбор пользователя
  bool GetSelectedUser(CUser &cUser);//получить выбранного пользователя

  bool AddTask(CTask &cTask);//добавить задание
  bool DeleteTask(CTask &cTask);//удалить задание
  bool ChangeTask(CTask &cTask);//изменить задание

  bool AddProject(CProject &cProject);//добавить проект
  bool DeleteProject(CProject &cProject);//удалить проект
  bool ChangeProject(CProject &cProject);//изменить проект

  vector<CTask> CreateVectorCTaskByForUserGUID(const CSafeString &guid);//создать вектор задач по GUID пользователя для которого задание
  vector<CTask> CreateVectorCTaskByFromUserGUID(const CSafeString &guid);//создать вектор задач по GUID пользователя от которого задание
  vector<CTask> CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//создать вектор задач по GUID пользователя один для которого задание от пользователя два
  vector<CTask> CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//создать вектор задач по проекту от пользователя

  bool PopTaskTransferToServer(CTask &cTask);//получить задание для передачи на сервер
  void PushTaskTransferToServer(const CTask &cTask);//добавить задание для передачи на сервер

  bool PopProjectTransferToServer(CProject &cProject);//получить проект для передачи на сервер
  void PushProjectTransferToServer(const CProject &cProject);//добавить проект для передачи на сервер

  bool GetOnShowAndResetOnShow(void);//получить, нужно ли показать окно и сбросить флаг необходимости показа

  void Processing(void);//цикл обработки
 protected:
  //-Функции класса----------------------------------------------------------  
  void FindAllMyParam(void);//определить все наши параметры (имя, руководитель ли)
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CDocument_Main) 
};

#endif
