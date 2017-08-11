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

using namespace std;


//====================================================================================================
//структуры
//====================================================================================================

//параметры пользователя
struct SUser
{
 CSafeString Name;//имя
 CSafeString JobTitle;//должность
 CSafeString Description;//описание
 CSafeString Telephone;//телефон
 CSafeString UserGUID;//уникальный идентификатор пользователя 
 bool Leader;//является ли начальником
 //дополнительные данные
 bool ChangeData;//изменились данные сотрудника
};

//====================================================================================================
//класс-обёртка для вектора хранения пользователей
//====================================================================================================

class CVectorUser
{
 protected: 
  unsigned long Version;//номер версии структуры
  //заголовок для загрузки и сохранения данных
  #pragma pack(1)
  struct SHeader
  {
   unsigned long NameSize;//размер имени
   unsigned long JobTitleSize;//размер должности
   unsigned long TelephoneSize;//размер телефонных данных
   unsigned long DescriptionSize;//размер описания
   unsigned long UserGUIDSize;//размер GUID
   bool Leader;//является ли начальником
  };
  #pragma pack()
  //переменные
  vector<SUser> vector_SUser;
 public:
  //конструктор
  CVectorUser();
  //деструктор
  ~CVectorUser(); 
  //функции
  bool Save(char *filename);//сохранить
  bool Load(char *filename);//загрузить
  bool AddNew(const SUser &sUser);//добавить новый элемент
  void Clear(void);//очистить список
  bool FindByUserGUID(const CSafeString &guid,SUser &sUser);//найти по GUID пользователя
  bool FindByUserGUIDAndResetChangeData(const CSafeString &guid,SUser &sUser);//найти по GUID пользователя и отметить, что данные не изменены
  bool DeleteByUserGUID(const CSafeString &guid);//удалить по GUID пользователя
  bool ChangeByUserGUID(const CSafeString &guid,const SUser &sUser);//заменить по GUID пользователя
  size_t Size(void);//получить количество пользователей
  bool PopBack(SUser &sUser);//получить последнего пользователя и удалить его
  bool PushBack(const SUser &sUser);//добавить пользователя в конец
  vector<SUser>& GetVectorSUser(void);//получить ссылку на вектор пользователей
 protected:
  //функции
 
};
#endif