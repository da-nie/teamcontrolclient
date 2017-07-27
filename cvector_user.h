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
 CString Name;//���
 CString JobTitle;//���������
 CString Description;//��������
 CString Telephone;//�������
 CString UserGUID;//���������� ������������� ������������ 
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
  bool FindByUserGUID(const CString &guid,SUser &sUser);//����� �� GUID ������������
  bool FindByUserGUIDAndResetChangeData(const CString &guid,SUser &sUser);//����� �� GUID ������������ � ��������, ��� ������ �� ��������
  bool DeleteByUserGUID(const CString &guid);//������� �� GUID ������������
  bool ChangeByUserGUID(const CString &guid,const SUser &sUser);//�������� �� GUID ������������
  size_t Size(void);//�������� ���������� �������������
  bool PopBack(SUser &sUser);//�������� ���������� ������������ � ������� ���
  bool PushBack(const SUser &sUser);//�������� ������������ � �����
  vector<SUser>& GetVectorSUser(void);//�������� ������ �� ������ �������������
 protected:
  //�������
 
};
#endif