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

using namespace std;

//====================================================================================================
//макроопределения
//====================================================================================================

//тип проекта
enum PROJECT_TYPE
{
 //нет типа
 PROJECT_TYPE_NONE,
 //проект на удаление
 PROJECT_TYPE_DELETED,
 //проект на изменение
 PROJECT_TYPE_CHANGED,
 //проект на добавление
 PROJECT_TYPE_ADDED
};

//====================================================================================================
//структуры
//====================================================================================================

//параметры проекта
struct SProject
{
 CSafeString ProjectName;//проект
 CSafeString ProjectGUID;//идентификатор проекта
 //дополнительные данные
 PROJECT_TYPE ProjectType;//тип проекта
 bool ChangeData;//изменились данные проекта
};

//====================================================================================================
//класс-обёртка для вектора хранения проектов
//====================================================================================================

class CVectorProject
{
 protected: 
  //заголовок для загрузки и сохранения данных
  #pragma pack(1)
  struct SHeader
  {
   unsigned long ProjectNameSize;//задание
   unsigned long ProjectGUIDSize;//идентификатор задания
   PROJECT_TYPE ProjectType;//тип проекта
  };
  #pragma pack()
  //переменные
  vector<SProject> vector_SProject;
 public:
  //конструктор
  CVectorProject();
  //деструктор
  ~CVectorProject(); 
  //функции
  bool Save(char *filename);//сохранить
  bool Load(char *filename);//загрузить
  bool AddNew(const SProject &sProject);//добавить новый элемент
  void Clear(void);//очистить список
  bool FindByProjectGUID(const CSafeString &guid,SProject &sProject);//найти по GUID проекта
  bool FindByProjectGUIDAndResetChangeData(const CSafeString &guid,SProject &sProject);//найти по GUID проекта и отметить, что данные не изменены
  bool DeleteByProjectGUID(const CSafeString &guid);//удалить по GUID проекта
  bool ChangeByProjectGUID(const CSafeString &guid,const SProject &sProject);//заменить по GUID проекта
  size_t Size(void);//получить количество проектов
  bool PopBack(SProject &sProject);//получить последний проект и удалить его
  bool PushBack(const SProject &sProject);//добавить проект в конец
  vector<SProject>& GetVectorSProject(void);//получить ссылку на вектор проектов
 protected:
  //функции
 
};
#endif