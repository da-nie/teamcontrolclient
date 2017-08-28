#ifndef CVECTOR_PROJECT_H
#define CVECTOR_PROJECT_H

//====================================================================================================
//��������
//====================================================================================================

//�����-������ ��� ������� �������� ��������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include <vector>
#include "stdafx.h"
#include "cproject.h"

using namespace std;

//====================================================================================================
//�����-������ ��� ������� �������� ��������
//====================================================================================================

class CVectorProject
{
 protected: 
  unsigned long Version;//����� ������ ���������
  //����������
  vector<CProject> vector_CProject;
 public:
  //�����������
  CVectorProject();
  //����������
  ~CVectorProject(); 
  //�������
  bool Save(char *filename);//���������
  bool Load(char *filename);//���������
  bool AddNew(const CProject &cProject);//�������� ����� �������
  void Clear(void);//�������� ������
  bool FindByProjectGUID(const CSafeString &guid,CProject &cProject);//����� �� GUID �������
  bool FindByProjectGUIDAndResetChangeData(const CSafeString &guid,CProject &cProject);//����� �� GUID ������� � ��������, ��� ������ �� ��������
  bool DeleteByProjectGUID(const CSafeString &guid);//������� �� GUID �������
  bool ChangeByProjectGUID(const CSafeString &guid,const CProject &cProject);//�������� �� GUID �������
  size_t Size(void);//�������� ���������� ��������
  bool PopBack(CProject &cProject);//�������� ��������� ������ � ������� ���
  bool PushBack(const CProject &cProject);//�������� ������ � �����
  vector<CProject>& GetVectorCProject(void);//�������� ������ �� ������ ��������
 protected:
  //�������
 
};
#endif