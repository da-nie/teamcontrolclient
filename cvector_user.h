#ifndef CVECTOR_USER_H
#define CVECTOR_USER_H

//====================================================================================================
//��������
//====================================================================================================

//�����-������ ��� ������� �������� �������������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include <vector>
#include "stdafx.h"

using namespace std;


//====================================================================================================
//���������
//====================================================================================================

//��������� ������������
struct SUser
{
 CSafeString Name;//���
 CSafeString JobTitle;//���������
 CSafeString Description;//��������
 CSafeString Telephone;//�������
 CSafeString UserGUID;//���������� ������������� ������������ 
 bool Leader;//�������� �� �����������
 //�������������� ������
 bool ChangeData;//���������� ������ ����������
};

//====================================================================================================
//�����-������ ��� ������� �������� �������������
//====================================================================================================

class CVectorUser
{
 protected: 
  unsigned long Version;//����� ������ ���������
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
  //����������
  vector<SUser> vector_SUser;
 public:
  //�����������
  CVectorUser();
  //����������
  ~CVectorUser(); 
  //�������
  bool Save(char *filename);//���������
  bool Load(char *filename);//���������
  bool AddNew(const SUser &sUser);//�������� ����� �������
  void Clear(void);//�������� ������
  bool FindByUserGUID(const CSafeString &guid,SUser &sUser);//����� �� GUID ������������
  bool FindByUserGUIDAndResetChangeData(const CSafeString &guid,SUser &sUser);//����� �� GUID ������������ � ��������, ��� ������ �� ��������
  bool DeleteByUserGUID(const CSafeString &guid);//������� �� GUID ������������
  bool ChangeByUserGUID(const CSafeString &guid,const SUser &sUser);//�������� �� GUID ������������
  size_t Size(void);//�������� ���������� �������������
  bool PopBack(SUser &sUser);//�������� ���������� ������������ � ������� ���
  bool PushBack(const SUser &sUser);//�������� ������������ � �����
  vector<SUser>& GetVectorSUser(void);//�������� ������ �� ������ �������������
 protected:
  //�������
 
};
#endif