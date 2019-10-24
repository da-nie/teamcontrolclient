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
#include "cuser.h"



//====================================================================================================
//�����-������ ��� ������� �������� �������������
//====================================================================================================

class CVectorUser
{
 protected: 
  unsigned long Version;//����� ������ ���������
  //����������
  std::vector<CUser> vector_CUser;
 public:
  //�����������
  CVectorUser();
  //����������
  ~CVectorUser(); 
  //�������
  bool Save(char *filename);//���������
  bool Load(char *filename);//���������
  bool AddNew(const CUser &cUser);//�������� ����� �������
  void Clear(void);//�������� ������
  bool FindByUserGUID(const CSafeString &guid,CUser &cUser);//����� �� GUID ������������
  bool FindByUserGUIDAndResetChangeData(const CSafeString &guid,CUser &cUser);//����� �� GUID ������������ � ��������, ��� ������ �� ��������
  bool DeleteByUserGUID(const CSafeString &guid);//������� �� GUID ������������
  bool ChangeByUserGUID(const CSafeString &guid,const CUser &cUser);//�������� �� GUID ������������
  size_t Size(void);//�������� ���������� �������������
  bool PopBack(CUser &cUser);//�������� ���������� ������������ � ������� ���
  bool PushBack(const CUser &cUser);//�������� ������������ � �����
  std::vector<CUser>& GetVectorCUser(void);//�������� ������ �� ������ �������������
 protected:
  //�������
 
};
#endif