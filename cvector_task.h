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
#include "stdafx.h"

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
 CString FromUserGUID;//от пользователя
 CString ForUserGUID;//для пользователя
 CString ProjectGUID;//по проекту
 CString Task;//задание
 long State;//состояние
 long Year;//год
 long Month;//месяц
 long Day;//число
 long Index;//индекс задания
 CString TaskGUID;//идентификатор задания
 //дополнительные данные
 bool ChangeData;//изменились данные задания
 TASK_TYPE TaskType;//тип задания
 CString ForUser;//для пользователя
 CString FromUser;//от пользователя

 //операция сравнения по дате
 bool operator<(const STask &sTask) const
 {
  if (sTask==*(this)) return(false);
  if (sTask>*(this)) return(false);
  return(true);
 }
 bool operator>(const STask &sTask) const
 {
  if (Year>sTask.Year) return(true);
  if (Year<sTask.Year) return(false);
  if (Month>sTask.Month) return(true);
  if (Month<sTask.Month) return(false);
  if (Day>sTask.Day) return(true);
  return(false);
 }
 bool operator==(const STask &sTask) const
 {
  if (Year!=sTask.Year) return(false);
  if (Month!=sTask.Month) return(false);
  if (Day!=sTask.Day) return(false);
  return(true);
 }
};

//====================================================================================================
//класс-обёртка для вектора хранения заданий
//====================================================================================================

class CVectorTask
{
 protected: 
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
  bool FindByTaskGUID(const CString &guid,STask &sTask);//найти по GUID задания
  bool FindByFromUserGUID(const CString &guid,STask &sTask);//найти по GUID пользователя от которого задание
  bool FindByForUserGUID(const CString &guid,STask &sTask);//найти по GUID пользователя для которого задание
  bool FindByProjectGUID(const CString &guid,STask &sTask);//найти по GUID проекта
  bool DeleteByTaskGUID(const CString &guid);//удалить по GUID задания
  bool ChangeByTaskGUID(const CString &guid,const STask &sTask);//заменить по GUID задания
  size_t Size(void);//получить количество заданий
  bool PopBack(STask &sTask);//получить последнее задание и удалить его
  bool PushBack(const STask &sTask);//добавить задание в конец
  vector<STask>& GetVectorSTask(void);//получить ссылку на вектор задач
  vector<STask> CreateVectorSTaskByForUserGUID(const CString &guid);//создать вектор задач по GUID пользователя для которого задание
  vector<STask> CreateVectorSTaskByFromUserGUID(const CString &guid);//создать вектор задач по GUID пользователя от которого задание
  vector<STask> CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CString &guid_one,const CString &guid_two);//создать вектор задач по GUID пользователя один для которого задание от пользователя два
  vector<STask> CreateVectorSTaskByProjectGUIDFromUserGUID(const CString &guid_project,const CString &guid_from_user);//создать вектор задач по проекту от пользователя
 protected:
  //функции
 
};
#endif