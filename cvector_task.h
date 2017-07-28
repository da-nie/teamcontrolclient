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
#include "stdafx.h"

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
 CString FromUserGUID;//�� ������������
 CString ForUserGUID;//��� ������������
 CString ProjectGUID;//�� �������
 CString Task;//�������
 long State;//���������
 long Year;//���
 long Month;//�����
 long Day;//�����
 long Index;//������ �������
 CString TaskGUID;//������������� �������
 //�������������� ������
 bool ChangeData;//���������� ������ �������
 TASK_TYPE TaskType;//��� �������
 CString ForUser;//��� ������������
 CString FromUser;//�� ������������

 //�������� ��������� �� ����
 bool operator<(const STask &sTask) const
 {
  if (sTask==*(this)) return(false);
  if (sTask>*(this)) return(false);
  return(true);
 }
 bool operator>(const STask &sTask) const
 {
  if (Year>sTask.Year) return(true);
  if (Year<sTask.Year) return(false);
  if (Month>sTask.Month) return(true);
  if (Month<sTask.Month) return(false);
  if (Day>sTask.Day) return(true);
  return(false);
 }
 bool operator==(const STask &sTask) const
 {
  if (Year!=sTask.Year) return(false);
  if (Month!=sTask.Month) return(false);
  if (Day!=sTask.Day) return(false);
  return(true);
 }
};

//====================================================================================================
//�����-������ ��� ������� �������� �������
//====================================================================================================

class CVectorTask
{
 protected: 
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
  bool FindByTaskGUID(const CString &guid,STask &sTask);//����� �� GUID �������
  bool FindByFromUserGUID(const CString &guid,STask &sTask);//����� �� GUID ������������ �� �������� �������
  bool FindByForUserGUID(const CString &guid,STask &sTask);//����� �� GUID ������������ ��� �������� �������
  bool FindByProjectGUID(const CString &guid,STask &sTask);//����� �� GUID �������
  bool DeleteByTaskGUID(const CString &guid);//������� �� GUID �������
  bool ChangeByTaskGUID(const CString &guid,const STask &sTask);//�������� �� GUID �������
  size_t Size(void);//�������� ���������� �������
  bool PopBack(STask &sTask);//�������� ��������� ������� � ������� ���
  bool PushBack(const STask &sTask);//�������� ������� � �����
  vector<STask>& GetVectorSTask(void);//�������� ������ �� ������ �����
  vector<STask> CreateVectorSTaskByForUserGUID(const CString &guid);//������� ������ ����� �� GUID ������������ ��� �������� �������
  vector<STask> CreateVectorSTaskByFromUserGUID(const CString &guid);//������� ������ ����� �� GUID ������������ �� �������� �������
  vector<STask> CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CString &guid_one,const CString &guid_two);//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
  vector<STask> CreateVectorSTaskByProjectGUIDFromUserGUID(const CString &guid_project,const CString &guid_from_user);//������� ������ ����� �� ������� �� ������������
 protected:
  //�������
 
};
#endif