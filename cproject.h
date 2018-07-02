#ifndef CPROJECT_H
#define CPROJECT_H

//====================================================================================================
//описание
//====================================================================================================

// ласс проектов

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "craiifilein.h"
#include "craiifileout.h"

#include "stdafx.h"
#include "csafestring.h"
//====================================================================================================
//макроопределени€
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
//класс проектов
//====================================================================================================
class CProject
{
 private:
  //заголовок дл€ загрузки и сохранени€ данных
  #pragma pack(1)
  struct SHeader
  {
   unsigned long ProjectNameSize;//задание
   unsigned long ProjectGUIDSize;//идентификатор задани€
   PROJECT_TYPE ProjectType;//тип проекта
  };
  #pragma pack()

  CSafeString ProjectName;//название проекта
  CSafeString ProjectGUID;//уникальный идентификатор  
  //дополнительные данные
  PROJECT_TYPE ProjectType;//тип проекта
  bool ChangeData;//изменились данные проекта
  //-ѕеременные класса-------------------------------------------------------
 public:
  //- онструктор класса------------------------------------------------------
  CProject(void);
  //-ƒеструктор класса-------------------------------------------------------
  ~CProject();
  //-‘ункции класса----------------------------------------------------------
  const CSafeString& GetProjectName(void) const;//получить название
  const CSafeString& GetProjectGUID(void) const;//получить уникальный идентификатор
  const bool& GetChangeData(void) const;//получить, изменились ли данные проекта

  void SetProjectName(const char *project_name);//задать название
  void SetProjectGUID(const char *guid);//задать уникальный идентификатор
  void SetChangeData(const bool& change_data);//задать изменились ли данные проекта

  void MarkForWork(void);//отметить дл€ работы
  void MarkForDelete(void);//отметить дл€ удалени€
  void MarkForChange(void);//отметить дл€ замены
  void MarkForAdd(void);//отметить дл€ добавлени€

  bool IsMarkForWork(void) const;//отмечено ли дл€ работы
  bool IsMarkForDelete(void) const;//отмечено ли дл€ удалени€
  bool IsMarkForChange(void) const;//отмечено ли дл€ замены
  bool IsMarkForAdd(void) const;//отмечено ли дл€ добавлени€

  bool IsProjectGUID(const char *guid) const;//верный ли ProjectGUID

  bool Save(CRAIIFileOut &cRAIIFileOut) const;//сохранить данные
  bool Load(CRAIIFileIn &cRAIIFileIn);//загрузить данные
};
#endif
