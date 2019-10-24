#ifndef CVECTOR_USER_H
#define CVECTOR_USER_H

//====================================================================================================
//описание
//====================================================================================================

//Класс-обёртка для вектора хранения пользователей

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include <vector>
#include "stdafx.h"
#include "cuser.h"



//====================================================================================================
//класс-обёртка для вектора хранения пользователей
//====================================================================================================

class CVectorUser
{
 protected: 
  unsigned long Version;//номер версии структуры
  //переменные
  std::vector<CUser> vector_CUser;
 public:
  //конструктор
  CVectorUser();
  //деструктор
  ~CVectorUser(); 
  //функции
  bool Save(char *filename);//сохранить
  bool Load(char *filename);//загрузить
  bool AddNew(const CUser &cUser);//добавить новый элемент
  void Clear(void);//очистить список
  bool FindByUserGUID(const CSafeString &guid,CUser &cUser);//найти по GUID пользователя
  bool FindByUserGUIDAndResetChangeData(const CSafeString &guid,CUser &cUser);//найти по GUID пользователя и отметить, что данные не изменены
  bool DeleteByUserGUID(const CSafeString &guid);//удалить по GUID пользователя
  bool ChangeByUserGUID(const CSafeString &guid,const CUser &cUser);//заменить по GUID пользователя
  size_t Size(void);//получить количество пользователей
  bool PopBack(CUser &cUser);//получить последнего пользователя и удалить его
  bool PushBack(const CUser &cUser);//добавить пользователя в конец
  std::vector<CUser>& GetVectorCUser(void);//получить ссылку на вектор пользователей
 protected:
  //функции
 
};
#endif