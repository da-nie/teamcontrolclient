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
 bool OutTask_Show_Cancelled;//���������� �� ��������� ������� � ������ ��������
 bool OutTask_Show_Done;//���������� �� ����������� ������� � ������ ��������
 bool OutTask_Show_NotRead;//���������� �� �� ����������� ������� � ������ ��������
 bool OutTask_Show_Finished;//���������� �� ����������� ������� � ������ ��������
 bool OutTask_Show_IsRunning;//���������� �� ������������� ������� � ������ ��������
 bool OutTask_Show_Readed;//���������� �� ����������� ������� � ������ ��������

 bool MyTask_Show_Cancelled;//���������� �� ��������� ������� � ������ ����������
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
   CUser cUser_Selected;//��������� ������������
   bool UserIsSelected;//���� �� �������� ������������
   bool OnShow;//����� �� �������� ����

   CVectorUser cVectorUser;//������ �������������
   CVectorTask cVectorTask;//������ �������
   CVectorProject cVectorProject;//������ ��������

   bool OnUpdateView;//��������� �� �������� ����� ������ 

   CSafeString MyGUID;//��� GUID, ���������� ����� �����������
   bool OnLine;//���������� �� �� � �������
   CSafeString MyName;//��� ������������
   bool Leader;//�������� �� ������������ �������������

   bool RestartWithLoader;//����� �� ������������ ����� ���������

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
  void RestartWithLoader(void);//��������� ������������ ����� ���������
  bool GetRestartWithLoaderState(void);//��������, ����� �� ������������ ����� ���������

  void DeleteFinishedTask(long year,long month,long day);//������� ��� �������� ���� � ����������� ������� �� ���� ������������
  bool GetNotReadTaskState(void);//��������, ���� �� ������������� �������
  void SetNotReadTaskState(bool state);//������, ���� �� ������������� �������

  void SaveState(void);//��������� ���������
  bool FindByUserGUIDAndResetChangeData(const CSafeString &guid,CUser &cUser);//����� ������������ �� GUID � �������� ������� ������
  bool FindByUserGUID(const CSafeString &guid,CUser &cUser);//����� ������������ �� GUID

  bool FindByProjectGUIDAndResetChangeData(const CSafeString &guid,CProject &cProject);//����� ������ �� GUID � �������� ������� ������
  bool FindByProjectGUID(const CSafeString &guid,CProject &cProject);//����� ������ �� GUID

  void GetMyParam(bool &on_line,CSafeString &guid,CSafeString &name,bool &leader);//�������� ���� ���������
  void SetMyParam(const bool &on_line,const CSafeString &guid,const CSafeString &name,const bool &leader);//������ ���� ���������
  void SetOnLine(const bool &on_line);//����������, ���� �� �����������
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

  void OnDeletedUser(const CUser &cUser);//��� ����� ������������
  void OnAddedUser(const CUser &cUser);//��� �������� ������������
  void OnChangedUser(const CUser &cUser);//��� ������ ������������

  void OnDeletedTask(const CTask &cTask);//���� ������ �������
  void OnAddedTask(const CTask &cTask);//���� ��������� �������
  void OnChangedTask(const CTask &cTask);//���� ������� �������

  void OnDeletedProject(const CProject &cProject);//��� ����� ������
  void OnAddedProject(const CProject &cProject);//��� �������� ������
  void OnChangedProject(const CProject &cProject);//��� ������� �������

  void SetSelectedUser(const CUser &cUser);//���������� ���������� ������������
  void ResetSelectedUser(void);//�������� ����� ������������
  bool GetSelectedUser(CUser &cUser);//�������� ���������� ������������

  bool AddTask(CTask &cTask);//�������� �������
  bool DeleteTask(CTask &cTask);//������� �������
  bool ChangeTask(CTask &cTask);//�������� �������

  bool AddProject(CProject &cProject);//�������� ������
  bool DeleteProject(CProject &cProject);//������� ������
  bool ChangeProject(CProject &cProject);//�������� ������

  vector<CTask> CreateVectorCTaskByForUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ ��� �������� �������
  vector<CTask> CreateVectorCTaskByFromUserGUID(const CSafeString &guid);//������� ������ ����� �� GUID ������������ �� �������� �������
  vector<CTask> CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two);//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
  vector<CTask> CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user);//������� ������ ����� �� ������� �� ������������

  bool PopTaskTransferToServer(CTask &cTask);//�������� ������� ��� �������� �� ������
  void PushTaskTransferToServer(const CTask &cTask);//�������� ������� ��� �������� �� ������

  bool PopProjectTransferToServer(CProject &cProject);//�������� ������ ��� �������� �� ������
  void PushProjectTransferToServer(const CProject &cProject);//�������� ������ ��� �������� �� ������

  bool GetOnShowAndResetOnShow(void);//��������, ����� �� �������� ���� � �������� ���� ������������� ������

  void Processing(void);//���� ���������
 protected:
  //-������� ������----------------------------------------------------------  
  void FindAllMyParam(void);//���������� ��� ���� ��������� (���, ������������ ��)
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CDocument_Main) 
};

#endif
