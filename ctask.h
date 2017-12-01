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
   unsigned long AnswerReferenceSize;//ссылка в ответе исполнителя
   unsigned long TaskReferenceSize;//ссылка в задании

   long State;//состояние
   long Year;//год
   long Month;//месяц
   long Day;//число  
   bool AnswerNotRead;//задание не прочитано
   bool PlannedPosition;//задание является плановой позицией
   bool AnswerReferenceExist;//есть ссылка в ответе исполнителя
   bool TaskReferenceExist;//есть ссылка в задании
   bool Common;//задание является общим

   TASK_TYPE TaskType;//тип задания
  };
  #pragma pack()

  long Index;//индекс задания
  CSafeString FromUserGUID;//от пользователя
  CSafeString ForUserGUID;//для пользователя
  CSafeString ProjectGUID;//по проекту
  CSafeString Task;//задание
  long State;//состояние
  bool AnswerNotRead;//задание не прочитано
  bool PlannedPosition;//задание является плановой позицией
  bool AnswerReferenceExist;//есть ссылка в ответе исполнителя
  bool TaskReferenceExist;//есть ссылка в задании
  bool Common;//задание является общим
  CDate cDate;//срок
  CSafeString TaskGUID;//идентификатор задания
  CSafeString Answer;//ответ на задание
  CSafeString AnswerReference;//ссылка в ответе исполнителя
  CSafeString TaskReference;//ссылка в задании
  //дополнительные данные
  bool ChangeData;//изменились данные задания
  TASK_TYPE TaskType;//тип задания
  CSafeString ForUser;//для пользователя
  CSafeString FromUser;//от пользователя  
  CSafeString Project;//по проекту
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
  //const long& GetState(void) const;//получиь состояние задания
  const CDate& GetDate(void) const;//получить срок задания
  const CSafeString& GetTaskGUID(void) const;//получить уникальный идентификатор задания
  const CSafeString& GetAnswer(void) const;//получить ответ на задание
  const CSafeString& GetAnswerReference(void) const;//получить ссылку на файл в ответе исполнителя
  const CSafeString& GetTaskReference(void) const;//получить ссылку на файл в задании
  const bool& GetChangeData(void) const;//получить, изменились ли данные задания
  const CSafeString& GetForUser(void) const;//получить имя пользователя для которого задание
  const CSafeString& GetFromUser(void) const;//получить имя пользователя от которого задание
  const CSafeString& GetProject(void) const;//получить название проекта по которому задание
  bool GetAnswerNotRead(void) const;//получить, прочитан ли ответ на задание
  bool GetPlannedPosition(void) const;//получить, является ли задание плановой позицией
  bool GetAnswerReferenceExist(void) const;//получить, есть ли ссылка в ответе исполнителя
  bool GetTaskReferenceExist(void) const;//получить, есть ли ссылка в задании
  bool GetCommon(void) const;//получить, является ли задание общим

  void SetIndex(const long& index);//задать индекс
  void SetFromUserGUID(const char *from_user_guid);//задать уникальный идентификатор от какого пользователя задание
  void SetForUserGUID(const char *for_user_guid);//задать уникальный идентификатор для какого пользователя задание
  void SetProjectGUID(const char *project_guid);//задать уникальный идентификатор проекта
  void SetTask(const char *task);//задать задание
  //void SetState(const long &state);//получиь состояние задания
  void SetDate(const CDate &cDate_Set);//задать срок задания
  void SetTaskGUID(const char *task_guid);//задать уникальный идентификатор задания
  void SetAnswer(const char *answer);//задать ответ на задание
  void SetAnswerReference(const char *reference);//задать ссылку на файл в ответе исполнителя
  void SetTaskReference(const char *reference);//задать ссылку на файл в задании
  void SetChangeData(const bool& change_data);//задать изменились ли данные задания
  void SetForUser(const char *for_user);//задать имя пользователя для которого задание
  void SetFromUser(const char *from_user);//задать имя пользователя от которого задание
  void SetProject(const char *project);//задать название проекта по которому задание

  void SetAnswerNotRead(bool state);//установить, прочитан ли ответ на задание
  void SetPlannedPosition(bool state);//установить, является ли задание плановой позицией
  void SetAnswerReferenceExist(bool state);//задать, есть ли ссылка в ответе исполнителя
  void SetTaskReferenceExist(bool state);//задать, есть ли ссылка в задании
  void SetCommon(bool state);//задать, является ли задание общим

  void SetStateNoRead(void);//установить, что задание не прочитано
  void SetStateReaded(void);//установить, что задание прочитано и ожидает выполнения
  void SetStateIsRunning(void);//установить, что задание выполняется
  void SetStateDone(void);//установить, что задание выполнено
  void SetStateCancelled(void);//установить, что задание отклонено
  void SetStateFinished(void);//установить, что задание завершено  

  void MarkForWork(void);//отметить для работы
  void MarkForDelete(void);//отметить для удаления
  void MarkForChange(void);//отметить для замены
  void MarkForAdd(void);//отметить для добавления

  bool IsMarkForWork(void) const;//отмечено ли для работы
  bool IsMarkForDelete(void) const;//отмечено ли для удаления
  bool IsMarkForChange(void) const;//отмечено ли для замены
  bool IsMarkForAdd(void) const;//отмечено ли для добавления

  bool IsStateNoRead(void) const;//проверить, что задание не прочитано
  bool IsStateReaded(void) const;//проверить, что задание прочитано и ожидает выполнения
  bool IsStateIsRunning(void) const;//проверить, что задание выполняется
  bool IsStateDone(void) const;//проверить, что задание выполнено
  bool IsStateCancelled(void) const;//проверить, что задание отклонено
  bool IsStateFinished(void) const;//проверить, что задание завершено

  bool IsFromOrForUserGUID(const char *guid) const;//это задание от или для пользователя с уникальным идентификатором
  bool IsForUserGUID(const char *guid) const;//это задание для пользователя с уникальным идентификатором
  bool IsFromUserGUID(const char *guid) const;//это задание от пользователя с уникальным идентификатором
  bool IsProjectGUID(const char *guid) const;//это задание по проекту с уникальным идентификатором
  bool IsTaskGUID(const char *guid) const;//верный ли TaskGUID
  bool IsAnswerNotRead(void) const;//прочитан ли ответ на задание
  bool IsPlannedPosition(void) const;//является ли задание плановой позицией
  bool IsAnswerReferenceExist(void) const;//есть ли ссылка в ответе исполнителя
  bool IsTaskReferenceExist(void) const;//есть ли ссылка в задании
  bool IsCommon(void) const;//является ли задание общим
  bool IsEquivalent(const CTask &cTask);//эквивалентны ли задания

  bool Save(FILE *file) const;//сохранить данные
  bool Load(FILE *file);//загрузить данные
};
#endif
