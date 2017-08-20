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
#include "cdate.h"

using namespace std;

//====================================================================================================
//����������������
//====================================================================================================

//��� �������
enum TASK_TYPE
{
 //��� ����
 TASK_TYPE_NONE,
 //������� �� ��������
 TASK_TYPE_DELETED,
 //������� �� ���������
 TASK_TYPE_CHANGED,
 //������� �� ����������
 TASK_TYPE_ADDED
};

//====================================================================================================
//���������
//====================================================================================================

//��������� �������
struct STask
{
 CSafeString FromUserGUID;//�� ������������
 CSafeString ForUserGUID;//��� ������������
 CSafeString ProjectGUID;//�� �������
 CSafeString Task;//�������
 long State;//���������
 CDate cDate;//����
 long Index;//������ �������
 CSafeString TaskGUID;//������������� �������
 //�������������� ������
 bool ChangeData;//���������� ������ �������
 TASK_TYPE TaskType;//��� �������
 CSafeString ForUser;//��� ������������
 CSafeString FromUser;//�� ������������
 CSafeString Answer;//�����

 //�������� ��������� �������
 bool operator<(const STask &sTask) const
 {
  if (sTask==*(this)) return(false);
  if (sTask>*(this)) return(false);
  return(true);
 }
 bool operator>(const STask &sTask) const
 {
  if (cDate>sTask.cDate) return(true);
  if (cDate==sTask.cDate) 
  {
   if (Index>sTask.Index) return(true);
   return(false);
  }
  return(false);
 }
 bool operator==(const STask &sTask) const
 {
  if (cDate==sTask.cDate && Index==sTask.Index) return(true);
  return(false);
 }
};

//====================================================================================================
//�����-������ ��� ������� �������� �������
//====================================================================================================

class CVectorTask
{
 protected: 
  unsigned long Version;//����� ������ ���������
  //��������� ��� �������� � ���������� ������
  #pragma pack(1)
  struct SHeader
  {
   long Index;//������ �������
   unsigned long FromUserGUIDSize;//�� ������������
   unsigned long ForUserGUIDSize;//��� ������������
   unsigned long ProjectGUIDSize;//�� �������
   unsigned long TaskSize;//�������
   unsigned long TaskGUIDSize;//������������� �������
   unsigned long AnswerSize;//�����
   long State;//���������
   long Year;//���
   long Month;//�����
   long Day;//�����    
   TASK_TYPE TaskType;//��� �������
  };
  #pragma pack()
  //����������
  vector<STask> vector_STask;
 public:
  //�����������
  CVectorTask();
  //����������
  ~CVectorTask(); 
  //�������
  bool Save(char *filename);//���������
  bool Load(char *filename);//���������
  bool AddNew(const STask &sTask);//�������� ����� �������
  void Clear(void);//�������� ������
  void SortByDate(void);//���������� ������� �� ���� �� �����������
  bool FindByTaskGUID(const CSafeString &guid,STask &sTask);//����� �� GUID �������
  bool FindByFromUserGUID(const CSafeString &guid,STask &sTask);//����� �� GUID ������������ �� �������� �������
  bool FindByForUserGUID(const CSafeString &guid,STask &sTask);//����� �� GUID ������������ ��� �������� �������
  bool FindByProjectGUID(const CSafeString &guid,STask &sTask);//����� �� GUID �������
  bool DeleteByTaskGUID(const CSafeString &guid);//������� �� GUID �������
  bool ChangeByTaskGUID(const CSafeString &guid,const STask &sTask);//�������� �� GUID �������
  size_t Size(void);//�������� ���������� �������
  bool PopBack(STask &sTask);//�������� ��������� ������� � ������� ���
  bool PushBack(const STask &sTask);//�������� ������� � �����
  vector<STask>& GetVectorSTask(void);//�������� ������ �� ������ �����
  vector<STask> CreateVectorSTaskByForUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ ��� �������� �������
  vector<STask> CreateVectorSTaskByFromUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ �� �������� �������
  vector<STask> CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
  vector<STask> CreateVectorSTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//������� ������ ����� �� ������� �� ������������
 protected:
  //�������
 
};
#endif