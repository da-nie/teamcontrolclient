#ifndef CDOCUMENT_MAIN_H
#define CDOCUMENT_MAIN_H

//====================================================================================================
//��������
//====================================================================================================

//����� ���������� ��� ������ �������������.

//====================================================================================================
//������������ ����������
//====================================================================================================

#include <list>
#include <vector>
#include "stdafx.h"
#include "craiiccriticalsection.h"
#include "cvector_task.h"
#include "cvector_user.h"
#include "cvector_project.h"

using namespace std;

//====================================================================================================
//����������������
//====================================================================================================

//GUID, ���������� �� ���� �������������
#define ALL_USER_GUID "{5F133563-3C76-41EE-9038-743DAAC8949A}"

//====================================================================================================
//���������
//====================================================================================================

//��������� �������
struct SClientSettings
{
 unsigned short ServerPort;//���� �������
 BYTE ServerIP[4];//����� �������
 char Login[255];//�����
 char Password[255];//������
 unsigned long MyGUIDSize;//������ ������ GUID
};

//��������� ����������� ������
struct SShowState
{
 bool OutTask_Show_Cancelled;//���������� �� ���������� ������� � ������ ��������
 bool OutTask_Show_Done;//���������� �� ����������� ������� � ������ ��������
 bool OutTask_Show_NotRead;//���������� �� �� ����������� ������� � ������ ��������
 bool OutTask_Show_Finished;//���������� �� ����������� ������� � ������ ��������
 bool OutTask_Show_IsRunning;//���������� �� ������������� ������� � ������ ��������
 bool OutTask_Show_Readed;//���������� �� ����������� ������� � ������ ��������

 bool MyTask_Show_Cancelled;//���������� �� ���������� ������� � ������ ����������
 bool MyTask_Show_Done;//���������� �� ����������� ������� � ������ ����������
 bool MyTask_Show_NotRead;//���������� �� �� ����������� ������� � ������ ����������
 bool MyTask_Show_Finished;//���������� �� ����������� ������� � ������ ����������
 bool MyTask_Show_IsRunning;//���������� �� ������������� ������� � ������ ����������
 bool MyTask_Show_Readed;//���������� �� ����������� ������� � ������ ����������
};

//====================================================================================================
//����� ����������
//====================================================================================================

class CDocument_Main:public CDocument
{
 protected:
  //-���������� ������-------------------------------------------------------
  //��������� ���������� ����������
  struct SProtectedVariables
  {
   SUser sUser_Selected;//��������� ������������
   bool UserIsSelected;//���� �� �������� ������������
   bool OnShow;//����� �� �������� ����

   CVectorUser cVectorUser;//������ �������������
   CVectorTask cVectorTask;//������ �������
   CVectorProject cVectorProject;//������ ��������

   bool OnUpdateView;//��������� �� �������� ����� ������ 

   CString MyGUID;//��� GUID, ���������� ����� �����������
   bool OnLine;//���������� �� �� � �������

   bool NotReadTaskState;//���� �� ������������� �������

   SClientSettings sClientSettings;//��������� �������

   CVectorTask cVectorTask_TransferToServer;//������� ��� �������� �� ������
   CVectorProject cVectorProject_TransferToServer;//������� ��� �������� �� ������

   SShowState sShowState;//��������� ����������� ������

   CCriticalSection cCriticalSection;//����������� ������ ��� ������� � ���������
  } sProtectedVariables;
 public:
  //-����������� ������------------------------------------------------------
  CDocument_Main(void);
  //-���������� ������-------------------------------------------------------
  ~CDocument_Main();
  //-������� ������----------------------------------------------------------
  void DeleteFinishedTask(long year,long month,long day);//������� ��� �������� ���� � ����������� ������� �� ���� ������������
  bool GetNotReadTaskState(void);//��������, ���� �� ������������� �������
  void SetNotReadTaskState(bool state);//������, ���� �� ������������� �������

  void SaveState(void);//��������� ���������
  bool FindByUserGUIDAndResetChangeData(const CString &guid,SUser &sUser);//����� ������������ �� GUID � �������� ������� ������
  bool FindByUserGUID(const CString &guid,SUser &sUser);//����� ������������ �� GUID

  bool FindByProjectGUIDAndResetChangeData(const CString &guid,SProject &sProject);//����� ������ �� GUID � �������� ������� ������
  bool FindByProjectGUID(const CString &guid,SProject &sProject);//����� ������ �� GUID

  void GetMyParam(bool &on_line,CString &guid);//�������� ���� ���������
  void SetMyParam(const bool &on_line,const CString &guid);//������ ���� ���������
  void GetShowState(SShowState &sShowState);//�������� ��������� ����������� ������
  void SetShowState(SShowState &sShowState);//������ ��������� ����������� ������

  void GetClientSettings(SClientSettings &sClientSettings);//�������� ��������� �������
  void SetClientSettings(const SClientSettings &sClientSettings);//���������� ��������� ������� (������� ����� �����������)

  CVectorUser GetCVectorUser(void);//�������� ������ �������������
  CVectorTask GetCVectorTask(void);//�������� ������ �������
  CVectorProject GetCVectorProject(void);//�������� ������ ��������

  void SetUserBook(CVectorUser &cVectorUser_Set);//������ ������ �������������
  void SetTaskBook(CVectorTask &cVectorTask_Set);//������ ������ �������
  void SetProjectBook(CVectorProject &cVectorProject_Set);//������ ������ ��������

  void OnDeletedUser(const SUser &sUser);//��� ����� ������������
  void OnAddedUser(const SUser &sUser);//��� �������� ������������
  void OnChangedUser(const SUser &sUser);//��� ������� ������������

  void OnDeletedTask(const STask &sTask);//���� ������ �������
  void OnAddedTask(const STask &sTask);//���� ��������� �������
  void OnChangedTask(const STask &sTask);//���� �������� �������

  void OnDeletedProject(const SProject &sProject);//��� ����� ������
  void OnAddedProject(const SProject &sProject);//��� �������� ������
  void OnChangedProject(const SProject &sProject);//��� �������� �������

  void SetSelectedUser(const SUser &sUser);//���������� ���������� ������������
  void ResetSelectedUser(void);//�������� ����� ������������
  bool GetSelectedUser(SUser &sUser);//�������� ���������� ������������

  bool AddTask(STask &sTask);//�������� �������
  bool DeleteTask(STask &sTask);//������� �������
  bool ChangeTask(STask &sTask);//�������� �������

  bool AddProject(SProject &sProject);//�������� ������
  bool DeleteProject(SProject &sProject);//������� ������
  bool ChangeProject(SProject &sProject);//�������� ������

  vector<STask> CreateVectorSTaskByForUserGUID(const CString &guid);//������� ������ ����� �� GUID ������������ ��� �������� �������
  vector<STask> CreateVectorSTaskByFromUserGUID(const CString &guid);//������� ������ ����� �� GUID ������������ �� �������� �������
  vector<STask> CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CString &guid_one,const CString &guid_two);//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
  vector<STask> CreateVectorSTaskByProjectGUIDFromUserGUID(const CString &guid_project,const CString &guid_from_user);//������� ������ ����� �� ������� �� ������������

  bool PopTaskTransferToServer(STask &sTask);//�������� ������� ��� �������� �� ������
  void PushTaskTransferToServer(const STask &sTask);//�������� ������� ��� �������� �� ������

  bool PopProjectTransferToServer(SProject &sProject);//�������� ������ ��� �������� �� ������
  void PushProjectTransferToServer(const SProject &sProject);//�������� ������ ��� �������� �� ������

  bool GetOnShowAndResetOnShow(void);//��������, ����� �� �������� ���� � �������� ���� ������������� ������

  void Processing(void);//���� ���������
 protected:
  //-������� ������----------------------------------------------------------  
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CDocument_Main) 
};

#endif
