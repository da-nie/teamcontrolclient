#ifndef CUSER_H
#define CUSER_H

//====================================================================================================
//описание
//====================================================================================================

//Класс пользователя

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "craiifilein.h"
#include "craiifileout.h"

#include "stdafx.h"
#include "csafestring.h"

//====================================================================================================
//класс пользователя
//====================================================================================================
class CUser
{
 private:
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

  CSafeString Name;//имя
  CSafeString Login;//логин
  CSafeString Password;//пароль
  CSafeString JobTitle;//должность
  CSafeString Description;//описание
  CSafeString Telephone;//телефон
  CSafeString UserGUID;//уникальный идентификатор пользователя
  bool Leader;//является ли руководителем
  //дополнительные данные
  bool ChangeData;//изменились данные сотрудника

  //-Переменные класса-------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CUser(void);
  //-Деструктор класса-------------------------------------------------------
  ~CUser();
  //-Функции класса----------------------------------------------------------
  const CSafeString& GetName(void) const;//получить имя
  const CSafeString& GetLogin(void) const;//получить логин
  const CSafeString& GetPassword(void) const;//получить пароль
  const CSafeString& GetJobTitle(void) const;//получить должность
  const CSafeString& GetDescription(void) const;//получить описание
  const CSafeString& GetTelephone(void) const;//получить телефон
  const CSafeString& GetUserGUID(void) const;//получить уникальный идентификатор пользователя
  const bool& GetLeader(void) const;//получить, является ли руководителем
  const bool& GetChangeData(void) const;//получить, изменились ли данные сотрудника

  void SetName(const char *name);//задать имя
  void SetLogin(const char *login);//задать логин
  void SetPassword(const char *password);//задать пароль
  void SetJobTitle(const char *job_title);//задать должность
  void SetDescription(const char *description);//задать описание
  void SetTelephone(const char *telephone);//задать телефон
  void SetUserGUID(const char *user_guid);//задать уникальный идентификатор пользователя
  void SetLeader(bool leader);//задать, является ли руководителем
  void SetChangeData(bool change_data);//задать, изменились ли данные сотрудника

  bool IsLoginAndPassword(const char *login,const char *password) const;//верный ли логин и пароль
  bool IsUserGUID(const char *guid) const;//верный ли UserGUID

  bool Save(CRAIIFileOut &cRAIIFileOut) const;//сохранить данные
  bool Load(CRAIIFileIn &cRAIIFileIn);//загрузить данные
};
#endif
