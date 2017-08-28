#ifndef CTASK_H
#define CTASK_H

//====================================================================================================
//описание
//====================================================================================================

//Класс задания

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include "csafestring.h"
#include "cdate.h"
#include "protocol.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//тип задания
enum TASK_TYPE
{
 //нет типа
 TASK_TYPE_NONE,
 //задание на удаление
 TASK_TYPE_DELETED,
 //задание на изменение
 TASK_TYPE_CHANGED,
 //задание на добавление
 TASK_TYPE_ADDED
};

//====================================================================================================
//класс задания
//====================================================================================================
class CTask
{
 private:
  //заголовок для загрузки и сохранения данных
  #pragma pack(1)
  struct SHeader
  {
   long Index;//индекс задания
   unsigned long FromUserGUIDSize;//от пользователя
   unsigned long ForUserGUIDSize;//для пользователя
   unsigned long ProjectGUIDSize;//по проекту
   unsigned long TaskSize;//задание
   unsigned long TaskGUIDSize;//идентификатор задания
   unsigned long AnswerSize;//ответ
   long State;//состояние
   long Year;//год
   long Month;//месяц
   long Day;//число    
   TASK_TYPE TaskType;//тип задания
  };
  #pragma pack()

  long Index;//индекс задания
  CSafeString FromUserGUID;//от пользователя
  CSafeString ForUserGUID;//для пользователя
  CSafeString ProjectGUID;//по проекту
  CSafeString Task;//задание
  long State;//состояние
  CDate cDate;//срок
  CSafeString TaskGUID;//идентификатор задания
  CSafeString Answer;//ответ на задание
  //дополнительные данные
  bool ChangeData;//изменились данные задания
  TASK_TYPE TaskType;//тип задания
  CSafeString ForUser;//для пользователя
  CSafeString FromUser;//от пользователя
  //-Переменные класса-------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CTask(void);
  //-Деструктор класса-------------------------------------------------------
  ~CTask();
  //-Функции класса----------------------------------------------------------
  //операции сравнения заданий
  bool operator<(const CTask &cTask) const
  {
   if (cTask==*(this)) return(false);
   if (cTask>*(this)) return(false);
   return(true);
  }
  bool operator>(const CTask &cTask) const
  {
   if (cDate>cTask.cDate) return(true);
   if (cDate==cTask.cDate) 
   {
    if (Index>cTask.Index) return(true);
    return(false);
   }
   return(false);
  }
  bool operator==(const CTask &cTask) const
  {
   if (cDate==cTask.cDate && Index==cTask.Index) return(true);
   return(false);
  }

  const long& GetIndex(void) const;//получиь индекс
  const CSafeString& GetFromUserGUID(void) const;//получить уникальный идентификатор от какого пользователя задание
  const CSafeString& GetForUserGUID(void) const;//получить уникальный идентификатор для какого пользователя задание
  const CSafeString& GetProjectGUID(void) const;//получить уникальный идентификатор проекта
  const CSafeString& GetTask(void) const;//получить задание
  const long& GetState(void) const;//получиь состояние задания
  const CDate& GetDate(void) const;//получить срок задания
  const CSafeString& GetTaskGUID(void) const;//получить уникальный идентификатор задания
  const CSafeString& GetAnswer(void) const;//получить ответ на задание
  const bool& GetChangeData(void) const;//получить, изменились ли данные задания
  const TASK_TYPE& GetTaskType(void) const;//получить тип задания
  const CSafeString& GetForUser(void) const;//получить имя пользователя для которого задание
  const CSafeString& GetFromUser(void) const;//получить имя пользователя от которого задание

  void SetIndex(const long& index);//задать индекс
  void SetFromUserGUID(const char *from_user_guid);//задать уникальный идентификатор от какого пользователя задание
  void SetForUserGUID(const char *for_user_guid);//задать уникальный идентификатор для какого пользователя задание
  void SetProjectGUID(const char *project_guid);//задать уникальный идентификатор проекта
  void SetTask(const char *task);//задать задание
  void SetState(const long &state);//получиь состояние задания
  void SetDate(const CDate &cDate_Set);//задать срок задания
  void SetTaskGUID(const char *task_guid);//задать уникальный идентификатор задания
  void SetAnswer(const char *answer);//задать ответ на задание
  void SetChangeData(const bool& change_data);//задать изменились ли данные задания
  void SetTaskType(TASK_TYPE task_type);//задать тип задания
  void SetForUser(const char *for_user);//задать имя пользователя для которого задание
  void SetFromUser(const char *from_user);//задать имя пользователя от которого задание

  bool IsFromOrForUserGUID(const char *guid) const;//это задание от или для пользователя с уникальным идентификатором
  bool IsForUserGUID(const char *guid) const;//это задание для пользователя с уникальным идентификатором
  bool IsFromUserGUID(const char *guid) const;//это задание от пользователя с уникальным идентификатором
  bool IsProjectGUID(const char *guid) const;//это задание по проекту с уникальным идентификатором
  bool IsTaskGUID(const char *guid) const;//верный ли TaskGUID

  bool Save(FILE *file) const;//сохранить данные
  bool Load(FILE *file);//загрузить данные
};
#endif
