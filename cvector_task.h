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
#include "ctask.h"

using namespace std;

//====================================================================================================
//класс-обёртка для вектора хранения заданий
//====================================================================================================

class CVectorTask
{
 protected: 
  unsigned long Version;//номер версии структуры
  //переменные
  vector<CTask> vector_CTask;
 public:
  //конструктор
  CVectorTask();
  //деструктор
  ~CVectorTask(); 
  //функции
  bool Save(char *filename);//сохранить
  bool Load(char *filename);//загрузить
  bool AddNew(const CTask &cTask);//добавить новый элемент
  void Clear(void);//очистить список
  void SortByDate(void);//сортировка заданий по дате по возрастанию
  bool FindByTaskGUID(const CSafeString &guid,CTask &cTask);//найти по GUID задания
  bool FindByFromUserGUID(const CSafeString &guid,CTask &cTask);//найти по GUID пользователя от которого задание
  bool FindByForUserGUID(const CSafeString &guid,CTask &cTask);//найти по GUID пользователя для которого задание
  bool FindByProjectGUID(const CSafeString &guid,CTask &cTask);//найти по GUID проекта
  bool DeleteByTaskGUID(const CSafeString &guid);//удалить по GUID задания
  bool ChangeByTaskGUID(const CSafeString &guid,const CTask &cTask);//заменить по GUID задания
  size_t Size(void);//получить количество заданий
  bool PopBack(CTask &cTask);//получить последнее задание и удалить его
  bool PushBack(const CTask &cTask);//добавить задание в конец
  vector<CTask>& GetVectorCTask(void);//получить ссылку на вектор задач
  vector<CTask> CreateVectorCTaskByForUserGUID(const CSafeString &guid);//создать вектор задач по GUID пользователя для которого задание
  vector<CTask> CreateVectorCTaskByFromUserGUID(const CSafeString &guid);//создать вектор задач по GUID пользователя от которого задание
  vector<CTask> CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//создать вектор задач по GUID пользователя один для которого задание от пользователя два
  vector<CTask> CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//создать вектор задач по проекту от пользователя
 protected:
  //функции
 
};
#endif