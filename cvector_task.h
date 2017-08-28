#ifndef CVECTOR_TASK_H
#define CVECTOR_TASK_H

//====================================================================================================
//��������
//====================================================================================================

//�����-������ ��� ������� �������� �������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include <vector>
#include <algorithm>
#include "stdafx.h"
#include "ctask.h"

using namespace std;

//====================================================================================================
//�����-������ ��� ������� �������� �������
//====================================================================================================

class CVectorTask
{
 protected: 
  unsigned long Version;//����� ������ ���������
  //����������
  vector<CTask> vector_CTask;
 public:
  //�����������
  CVectorTask();
  //����������
  ~CVectorTask(); 
  //�������
  bool Save(char *filename);//���������
  bool Load(char *filename);//���������
  bool AddNew(const CTask &cTask);//�������� ����� �������
  void Clear(void);//�������� ������
  void SortByDate(void);//���������� ������� �� ���� �� �����������
  bool FindByTaskGUID(const CSafeString &guid,CTask &cTask);//����� �� GUID �������
  bool FindByFromUserGUID(const CSafeString &guid,CTask &cTask);//����� �� GUID ������������ �� �������� �������
  bool FindByForUserGUID(const CSafeString &guid,CTask &cTask);//����� �� GUID ������������ ��� �������� �������
  bool FindByProjectGUID(const CSafeString &guid,CTask &cTask);//����� �� GUID �������
  bool DeleteByTaskGUID(const CSafeString &guid);//������� �� GUID �������
  bool ChangeByTaskGUID(const CSafeString &guid,const CTask &cTask);//�������� �� GUID �������
  size_t Size(void);//�������� ���������� �������
  bool PopBack(CTask &cTask);//�������� ��������� ������� � ������� ���
  bool PushBack(const CTask &cTask);//�������� ������� � �����
  vector<CTask>& GetVectorCTask(void);//�������� ������ �� ������ �����
  vector<CTask> CreateVectorCTaskByForUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ ��� �������� �������
  vector<CTask> CreateVectorCTaskByFromUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ �� �������� �������
  vector<CTask> CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
  vector<CTask> CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//������� ������ ����� �� ������� �� ������������
 protected:
  //�������
 
};
#endif