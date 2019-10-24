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



//====================================================================================================
//�����-������ ��� ������� �������� �������
//====================================================================================================

class CVectorTask
{
 protected: 
  unsigned long Version;//����� ������ ���������
  //����������
  std::vector<CTask> vector_CTask;
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
  std::vector<CTask>& GetVectorCTask(void);//�������� ������ �� ������ �����
  std::vector<CTask> CreateVectorCTaskByForUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ ��� �������� �������
  std::vector<CTask> CreateVectorCTaskByFromUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ �� �������� �������
  std::vector<CTask> CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
  std::vector<CTask> CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//������� ������ ����� �� ������� �� ������������
  std::vector<CTask> CreateVectorCTaskByProjectGUID(const CSafeString &guid_project);//������� ������ ����� �� �������
 protected:
  //�������
 
};
#endif