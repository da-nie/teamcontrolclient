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

using namespace std;

//====================================================================================================
//����������������
//====================================================================================================

//��� �������
enum PROJECT_TYPE
{
 //��� ����
 PROJECT_TYPE_NONE,
 //������ �� ��������
 PROJECT_TYPE_DELETED,
 //������ �� ���������
 PROJECT_TYPE_CHANGED,
 //������ �� ����������
 PROJECT_TYPE_ADDED
};

//====================================================================================================
//���������
//====================================================================================================

//��������� �������
struct SProject
{
 CSafeString ProjectName;//������
 CSafeString ProjectGUID;//������������� �������
 //�������������� ������
 PROJECT_TYPE ProjectType;//��� �������
 bool ChangeData;//���������� ������ �������
};

//====================================================================================================
//�����-������ ��� ������� �������� ��������
//====================================================================================================

class CVectorProject
{
 protected: 
  //��������� ��� �������� � ���������� ������
  #pragma pack(1)
  struct SHeader
  {
   unsigned long ProjectNameSize;//�������
   unsigned long ProjectGUIDSize;//������������� �������
   PROJECT_TYPE ProjectType;//��� �������
  };
  #pragma pack()
  //����������
  vector<SProject> vector_SProject;
 public:
  //�����������
  CVectorProject();
  //����������
  ~CVectorProject(); 
  //�������
  bool Save(char *filename);//���������
  bool Load(char *filename);//���������
  bool AddNew(const SProject &sProject);//�������� ����� �������
  void Clear(void);//�������� ������
  bool FindByProjectGUID(const CSafeString &guid,SProject &sProject);//����� �� GUID �������
  bool FindByProjectGUIDAndResetChangeData(const CSafeString &guid,SProject &sProject);//����� �� GUID ������� � ��������, ��� ������ �� ��������
  bool DeleteByProjectGUID(const CSafeString &guid);//������� �� GUID �������
  bool ChangeByProjectGUID(const CSafeString &guid,const SProject &sProject);//�������� �� GUID �������
  size_t Size(void);//�������� ���������� ��������
  bool PopBack(SProject &sProject);//�������� ��������� ������ � ������� ���
  bool PushBack(const SProject &sProject);//�������� ������ � �����
  vector<SProject>& GetVectorSProject(void);//�������� ������ �� ������ ��������
 protected:
  //�������
 
};
#endif