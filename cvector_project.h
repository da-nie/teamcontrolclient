#ifndef CVECTOR_PROJECT_H
#define CVECTOR_PROJECT_H

//====================================================================================================
//описание
//====================================================================================================

//Класс-обёртка для вектора хранения проектов

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include <vector>
#include "stdafx.h"
#include "cproject.h"

using namespace std;

//====================================================================================================
//класс-обёртка для вектора хранения проектов
//====================================================================================================

class CVectorProject
{
 protected: 
  unsigned long Version;//номер версии структуры
  //переменные
  vector<CProject> vector_CProject;
 public:
  //конструктор
  CVectorProject();
  //деструктор
  ~CVectorProject(); 
  //функции
  bool Save(char *filename);//сохранить
  bool Load(char *filename);//загрузить
  bool AddNew(const CProject &cProject);//добавить новый элемент
  void Clear(void);//очистить список
  bool FindByProjectGUID(const CSafeString &guid,CProject &cProject);//найти по GUID проекта
  bool FindByProjectGUIDAndResetChangeData(const CSafeString &guid,CProject &cProject);//найти по GUID проекта и отметить, что данные не изменены
  bool DeleteByProjectGUID(const CSafeString &guid);//удалить по GUID проекта
  bool ChangeByProjectGUID(const CSafeString &guid,const CProject &cProject);//заменить по GUID проекта
  size_t Size(void);//получить количество проектов
  bool PopBack(CProject &cProject);//получить последний проект и удалить его
  bool PushBack(const CProject &cProject);//добавить проект в конец
  vector<CProject>& GetVectorCProject(void);//получить ссылку на вектор проектов
 protected:
  //функции
 
};
#endif