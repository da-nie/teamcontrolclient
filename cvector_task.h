#ifndef CVECTOR_TASK_H
#define CVECTOR_TASK_H

//====================================================================================================
//описание
//====================================================================================================

//Класс-обёртка для вектора хранения заданий

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include <vector>
#include <algorithm>
#include "stdafx.h"
#include "cdate.h"

using namespace std;

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
//структуры
//====================================================================================================

//параметры задания
struct STask
{
 CSafeString FromUserGUID;//от пользователя
 CSafeString ForUserGUID;//для пользователя
 CSafeString ProjectGUID;//по проекту
 CSafeString Task;//задание
 long State;//состояние
 CDate cDate;//дата
 long Index;//индекс задания
 CSafeString TaskGUID;//идентификатор задания
 //дополнительные данные
 bool ChangeData;//изменились данные задания
 TASK_TYPE TaskType;//тип задания
 CSafeString ForUser;//для пользователя
 CSafeString FromUser;//от пользователя
 CSafeString Answer;//ответ

 //операция сравнения заданий
 bool operator<(const STask &sTask) const
 {
  if (sTask==*(this)) return(false);
  if (sTask>*(this)) return(false);
  return(true);
 }
 bool operator>(const STask &sTask) const
 {
  if (cDate>sTask.cDate) return(true);
  if (cDate==sTask.cDate) 
  {
   if (Index>sTask.Index) return(true);
   return(false);
  }
  return(false);
 }
 bool operator==(const STask &sTask) const
 {
  if (cDate==sTask.cDate && Index==sTask.Index) return(true);
  return(false);
 }
};

//====================================================================================================
//класс-обёртка для вектора хранения заданий
//====================================================================================================

class CVectorTask
{
 protected: 
  unsigned long Version;//номер версии структуры
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
  //переменные
  vector<STask> vector_STask;
 public:
  //конструктор
  CVectorTask();
  //деструктор
  ~CVectorTask(); 
  //функции
  bool Save(char *filename);//сохранить
  bool Load(char *filename);//загрузить
  bool AddNew(const STask &sTask);//добавить новый элемент
  void Clear(void);//очистить список
  void SortByDate(void);//сортировка заданий по дате по возрастанию
  bool FindByTaskGUID(const CSafeString &guid,STask &sTask);//найти по GUID задания
  bool FindByFromUserGUID(const CSafeString &guid,STask &sTask);//найти по GUID пользователя от которого задание
  bool FindByForUserGUID(const CSafeString &guid,STask &sTask);//найти по GUID пользователя для которого задание
  bool FindByProjectGUID(const CSafeString &guid,STask &sTask);//найти по GUID проекта
  bool DeleteByTaskGUID(const CSafeString &guid);//удалить по GUID задания
  bool ChangeByTaskGUID(const CSafeString &guid,const STask &sTask);//заменить по GUID задания
  size_t Size(void);//получить количество заданий
  bool PopBack(STask &sTask);//получить последнее задание и удалить его
  bool PushBack(const STask &sTask);//добавить задание в конец
  vector<STask>& GetVectorSTask(void);//получить ссылку на вектор задач
  vector<STask> CreateVectorSTaskByForUserGUID(const CSafeString &guid);//создать вектор задач по GUID пользователя для которого задание
  vector<STask> CreateVectorSTaskByFromUserGUID(const CSafeString &guid);//создать вектор задач по GUID пользователя от которого задание
  vector<STask> CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//создать вектор задач по GUID пользователя один для которого задание от пользователя два
  vector<STask> CreateVectorSTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//создать вектор задач по проекту от пользователя
 protected:
  //функции
 
};
#endif