#ifndef CUSER_H
#define CUSER_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "craiifilein.h"
#include "craiifileout.h"

#include "stdafx.h"
#include "csafestring.h"

//====================================================================================================
//����� ������������
//====================================================================================================
class CUser
{
 private:
  //��������� ��� �������� � ���������� ������
  #pragma pack(1)
  struct SHeader
  {
   unsigned long NameSize;//������ �����
   unsigned long JobTitleSize;//������ ���������
   unsigned long TelephoneSize;//������ ���������� ������
   unsigned long DescriptionSize;//������ ��������
   unsigned long UserGUIDSize;//������ GUID
   bool Leader;//�������� �� �����������
  };
  #pragma pack()

  CSafeString Name;//���
  CSafeString Login;//�����
  CSafeString Password;//������
  CSafeString JobTitle;//���������
  CSafeString Description;//��������
  CSafeString Telephone;//�������
  CSafeString UserGUID;//���������� ������������� ������������
  bool Leader;//�������� �� �������������
  //�������������� ������
  bool ChangeData;//���������� ������ ����������

  //-���������� ������-------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CUser(void);
  //-���������� ������-------------------------------------------------------
  ~CUser();
  //-������� ������----------------------------------------------------------
  const CSafeString& GetName(void) const;//�������� ���
  const CSafeString& GetLogin(void) const;//�������� �����
  const CSafeString& GetPassword(void) const;//�������� ������
  const CSafeString& GetJobTitle(void) const;//�������� ���������
  const CSafeString& GetDescription(void) const;//�������� ��������
  const CSafeString& GetTelephone(void) const;//�������� �������
  const CSafeString& GetUserGUID(void) const;//�������� ���������� ������������� ������������
  const bool& GetLeader(void) const;//��������, �������� �� �������������
  const bool& GetChangeData(void) const;//��������, ���������� �� ������ ����������

  void SetName(const char *name);//������ ���
  void SetLogin(const char *login);//������ �����
  void SetPassword(const char *password);//������ ������
  void SetJobTitle(const char *job_title);//������ ���������
  void SetDescription(const char *description);//������ ��������
  void SetTelephone(const char *telephone);//������ �������
  void SetUserGUID(const char *user_guid);//������ ���������� ������������� ������������
  void SetLeader(bool leader);//������, �������� �� �������������
  void SetChangeData(bool change_data);//������, ���������� �� ������ ����������

  bool IsLoginAndPassword(const char *login,const char *password) const;//������ �� ����� � ������
  bool IsUserGUID(const char *guid) const;//������ �� UserGUID

  bool Save(CRAIIFileOut &cRAIIFileOut) const;//��������� ������
  bool Load(CRAIIFileIn &cRAIIFileIn);//��������� ������
};
#endif
