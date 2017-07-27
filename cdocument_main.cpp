#include "cdocument_main.h"
#include "cthreadclient.h"


#include "ctreeview_kit.h"

extern CThreadClient cThreadClient;//���������� �����

//====================================================================================================
//����������� ������
//====================================================================================================
CDocument_Main::CDocument_Main(void) 
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.Load("user_list.bin");
   sProtectedVariables.cVectorTask.Load("task_list.bin");
   sProtectedVariables.cVectorProject.Load("project_list.bin");
   sProtectedVariables.cVectorTask_TransferToServer.Load("task_to_server.bin");
   sProtectedVariables.cVectorProject_TransferToServer.Load("project_to_server.bin");

   sProtectedVariables.UserIsSelected=false;
   sProtectedVariables.OnUpdateView=false;
   sProtectedVariables.MyGUID="";
   sProtectedVariables.OnLine=false;
   sProtectedVariables.OnShow=false;
   sProtectedVariables.NotReadTaskState=false;
   cThreadClient.SetDocument(this);

   sProtectedVariables.sShowState.OutTask_Show_Cancelled=true;
   sProtectedVariables.sShowState.OutTask_Show_Done=true;
   sProtectedVariables.sShowState.OutTask_Show_NotRead=true;
   sProtectedVariables.sShowState.OutTask_Show_Finished=false;
   sProtectedVariables.sShowState.OutTask_Show_IsRunning=true;
   sProtectedVariables.sShowState.OutTask_Show_Readed=true;

   sProtectedVariables.sShowState.MyTask_Show_Cancelled=false;
   sProtectedVariables.sShowState.MyTask_Show_Done=false;
   sProtectedVariables.sShowState.MyTask_Show_NotRead=true;
   sProtectedVariables.sShowState.MyTask_Show_Finished=false;
   sProtectedVariables.sShowState.MyTask_Show_IsRunning=true;
   sProtectedVariables.sShowState.MyTask_Show_Readed=true;

   strcpy(sProtectedVariables.sClientSettings.Login,"");
   strcpy(sProtectedVariables.sClientSettings.Password,"");
   sProtectedVariables.sClientSettings.ServerIP[0]=127;
   sProtectedVariables.sClientSettings.ServerIP[1]=0;
   sProtectedVariables.sClientSettings.ServerIP[2]=0;
   sProtectedVariables.sClientSettings.ServerIP[3]=1;
   sProtectedVariables.sClientSettings.ServerPort=9090;
   sProtectedVariables.sClientSettings.MyGUIDSize=0;
   FILE *file=fopen("settings.bin","rb");
   if (file!=NULL)
   {
    fread(&sProtectedVariables.sClientSettings,sizeof(SClientSettings),1,file);
    char *my_guid=new char[sProtectedVariables.sClientSettings.MyGUIDSize+1];
    fread(my_guid,sizeof(char),sProtectedVariables.sClientSettings.MyGUIDSize,file);  
	my_guid[sProtectedVariables.sClientSettings.MyGUIDSize]=0;
    sProtectedVariables.MyGUID=my_guid;
	delete[](my_guid);
    fclose(file);
   }  
  }
 }
 cThreadClient.Start();
}
//====================================================================================================
//���������� ������
//====================================================================================================
CDocument_Main::~CDocument_Main() 
{
 cThreadClient.Stop();
 SaveState();
}


//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//������� ��� �������� ���� � ����������� ������� �� ���� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::DeleteFinishedTask(long year,long month,long day)
{
 STask sTask_Time;
 sTask_Time.Year=year;
 sTask_Time.Month=month;
 sTask_Time.Day=day;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector<STask> vector_STask=sProtectedVariables.cVectorTask.CreateVectorSTaskByFromUserGUID(sProtectedVariables.MyGUID);
   size_t size=vector_STask.size();
   for(size_t n=0;n<size;n++)
   {
    STask &sTask=vector_STask[n];
    if (sTask.State==TASK_STATE_FINISHED)
	{
     if (sTask>sTask_Time) continue;
     //������� �� ������� ������� ��� ���������� � �������
     while(sProtectedVariables.cVectorTask_TransferToServer.DeleteByTaskGUID(sTask.TaskGUID)==true);
     sTask.TaskType=TASK_TYPE_DELETED;
     sProtectedVariables.cVectorTask_TransferToServer.PushBack(sTask);
     sProtectedVariables.OnUpdateView=true;
	}
   }
  }
 }
}

//----------------------------------------------------------------------------------------------------
//��������, ���� �� ������������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::GetNotReadTaskState(void)
{ 
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.NotReadTaskState);	   
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������, ���� �� ������������� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetNotReadTaskState(bool state)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.NotReadTaskState=state;
  }
 }
}


//----------------------------------------------------------------------------------------------------
//��������� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SaveState(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.Save("user_list.bin");
   sProtectedVariables.cVectorTask.Save("task_list.bin");
   sProtectedVariables.cVectorProject.Save("project_list.bin");
   sProtectedVariables.cVectorTask_TransferToServer.Save("task_to_server.bin");
   sProtectedVariables.cVectorProject_TransferToServer.Save("project_to_server.bin");
   FILE *file=fopen("settings.bin","wb");
   if (file!=NULL)
   {
    sProtectedVariables.sClientSettings.MyGUIDSize=sProtectedVariables.MyGUID.GetLength();
    fwrite(&sProtectedVariables.sClientSettings,sizeof(SClientSettings),1,file);
    const char *s_ptr;
    s_ptr=sProtectedVariables.MyGUID;
    fwrite(s_ptr,sProtectedVariables.MyGUID.GetLength(),1,file);
    fclose(file);
   }
  }
 }
}
//----------------------------------------------------------------------------------------------------
//����� ������������ �� GUID � �������� ������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByUserGUIDAndResetChangeData(const CString &guid,SUser &sUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorUser.FindByUserGUIDAndResetChangeData(guid,sUser));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//����� ������������ �� GUID
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByUserGUID(const CString &guid,SUser &sUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorUser.FindByUserGUID(guid,sUser));
  }
 }
 return(false);
}

//----------------------------------------------------------------------------------------------------
//����� ������ �� GUID � �������� ������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByProjectGUIDAndResetChangeData(const CString &guid,SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorProject.FindByProjectGUIDAndResetChangeData(guid,sProject));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//����� ������ �� GUID
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByProjectGUID(const CString &guid,SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorProject.FindByProjectGUID(guid,sProject));
  }
 }
 return(false);
}


//----------------------------------------------------------------------------------------------------
//�������� ���� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::GetMyParam(bool &on_line,CString &guid)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   guid=sProtectedVariables.MyGUID;
   on_line=sProtectedVariables.OnLine;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������ ���� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetMyParam(const bool &on_line,const CString &guid)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.MyGUID=guid;
   sProtectedVariables.OnLine=on_line;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ��������� ����������� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::GetShowState(SShowState &sShowState)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sShowState=sProtectedVariables.sShowState;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������ ��������� ����������� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetShowState(SShowState &sShowState)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.sShowState=sShowState;
  }
 }
}

//----------------------------------------------------------------------------------------------------
//�������� ��������� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::GetClientSettings(SClientSettings &sClientSettings)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sClientSettings=sProtectedVariables.sClientSettings;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//���������� ��������� ������� (������� ����� �����������)
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetClientSettings(const SClientSettings &sClientSettings)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.sClientSettings=sClientSettings;
   sProtectedVariables.UserIsSelected=false;
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.MyGUID="";
   sProtectedVariables.OnLine=false;
   sProtectedVariables.cVectorUser.Clear();
   sProtectedVariables.cVectorTask.Clear();
  }
 }
 SaveState();
 //������������� ������ � ������ �����������
 cThreadClient.Start();
}

//----------------------------------------------------------------------------------------------------
//�������� ������ �������������
//----------------------------------------------------------------------------------------------------
CVectorUser CDocument_Main::GetCVectorUser(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   CVectorUser cVectorUser_Copy=sProtectedVariables.cVectorUser;
   return(cVectorUser_Copy);
  }
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ������ �������
//----------------------------------------------------------------------------------------------------
CVectorTask CDocument_Main::GetCVectorTask(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   CVectorTask cVectorTask_Copy=sProtectedVariables.cVectorTask;
   return(cVectorTask_Copy);
  }
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ������ ��������
//----------------------------------------------------------------------------------------------------
CVectorProject CDocument_Main::GetCVectorProject(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   CVectorProject cVectorProject_Copy=sProtectedVariables.cVectorProject;
   return(cVectorProject_Copy);
  }
 }
}

//----------------------------------------------------------------------------------------------------
//������ ������ �������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetUserBook(CVectorUser &cVectorUser_Set)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser=cVectorUser_Set;
   sProtectedVariables.OnUpdateView=true;
  }
 } 
 SaveState();
}

//----------------------------------------------------------------------------------------------------
//������ ������ �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetTaskBook(CVectorTask &cVectorTask_Set)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorTask=cVectorTask_Set;
   sProtectedVariables.OnUpdateView=true;
  }
 } 
 SaveState();
}

//----------------------------------------------------------------------------------------------------
//������ ������ ��������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetProjectBook(CVectorProject &cVectorProject_Set)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorProject=cVectorProject_Set;
   sProtectedVariables.OnUpdateView=true;
  }
 } 
 SaveState();
}

//----------------------------------------------------------------------------------------------------
//��� ����� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnDeletedUser(const SUser &sUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.DeleteByUserGUID(sUser.UserGUID);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//��� �������� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnAddedUser(const SUser &sUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.AddNew(sUser);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//��� ������ ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnChangedUser(const SUser &sUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.ChangeByUserGUID(sUser.UserGUID,sUser);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
}


//----------------------------------------------------------------------------------------------------
//���� ������ �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnDeletedTask(const STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorTask.DeleteByTaskGUID(sTask.TaskGUID);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//���� ��������� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnAddedTask(const STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorTask.AddNew(sTask);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//���� ������� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnChangedTask(const STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {   
   sProtectedVariables.cVectorTask.ChangeByTaskGUID(sTask.TaskGUID,sTask);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 SaveState();
}


//----------------------------------------------------------------------------------------------------
//��� ����� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnDeletedProject(const SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorProject.DeleteByProjectGUID(sProject.ProjectGUID);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//��� �������� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnAddedProject(const SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorProject.AddNew(sProject);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//��� ������ ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnChangedProject(const SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {   
   sProtectedVariables.cVectorProject.ChangeByProjectGUID(sProject.ProjectGUID,sProject);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 SaveState();
}



//----------------------------------------------------------------------------------------------------
//���������� ���������� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetSelectedUser(const SUser &sUser)
{
 sProtectedVariables.UserIsSelected=true;
 sProtectedVariables.sUser_Selected=sUser;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.OnUpdateView=true;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ����� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::ResetSelectedUser(void)
{
 sProtectedVariables.UserIsSelected=false;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.OnUpdateView=true;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::GetSelectedUser(SUser &sUser)
{
 if (sProtectedVariables.UserIsSelected==false) return(false);
 sUser=sProtectedVariables.sUser_Selected;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::AddTask(STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sTask.TaskType=TASK_TYPE_ADDED;
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(sTask);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::DeleteTask(STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorTask_TransferToServer.DeleteByTaskGUID(sTask.TaskGUID)==true);
   sTask.TaskType=TASK_TYPE_DELETED;
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(sTask);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::ChangeTask(STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorTask_TransferToServer.DeleteByTaskGUID(sTask.TaskGUID)==true);
   sTask.TaskType=TASK_TYPE_CHANGED;
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(sTask);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 return(true);
}

//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::AddProject(SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProject.ProjectType=PROJECT_TYPE_ADDED;
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(sProject);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::DeleteProject(SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorProject_TransferToServer.DeleteByProjectGUID(sProject.ProjectGUID)==true);
   sProject.ProjectType=PROJECT_TYPE_DELETED;
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(sProject);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::ChangeProject(SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorProject_TransferToServer.DeleteByProjectGUID(sProject.ProjectGUID)==true);
   sProject.ProjectType=PROJECT_TYPE_CHANGED;
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(sProject);
   sProtectedVariables.OnUpdateView=true;
   sProtectedVariables.OnShow=true;
  }
 }
 return(true);
}


//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ ��� �������� �������
//----------------------------------------------------------------------------------------------------
vector<STask> CDocument_Main::CreateVectorSTaskByForUserGUID(const CString &guid)
{
 vector<STask> vector_STask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_STask=sProtectedVariables.cVectorTask.CreateVectorSTaskByForUserGUID(guid);
  }
 }
 return(vector_STask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ �� �������� �������
//----------------------------------------------------------------------------------------------------
vector<STask> CDocument_Main::CreateVectorSTaskByFromUserGUID(const CString &guid)
{
 vector<STask> vector_STask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_STask=sProtectedVariables.cVectorTask.CreateVectorSTaskByFromUserGUID(guid);
  }
 }
 return(vector_STask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
//----------------------------------------------------------------------------------------------------
vector<STask> CDocument_Main::CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CString &guid_one,const CString &guid_two)
{
 vector<STask> vector_STask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_STask=sProtectedVariables.cVectorTask.CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(guid_one,guid_two);
  }
 }
 return(vector_STask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� ������� �� ������������
//----------------------------------------------------------------------------------------------------
vector<STask> CDocument_Main::CreateVectorSTaskByProjectGUIDFromUserGUID(const CString &guid_project,const CString &guid_from_user)
{
 vector<STask> vector_STask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_STask=sProtectedVariables.cVectorTask.CreateVectorSTaskByProjectGUIDFromUserGUID(guid_project,guid_from_user);
  }
 }
 return(vector_STask);
}

//----------------------------------------------------------------------------------------------------
//�������� ������� ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::PopTaskTransferToServer(STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorTask_TransferToServer.PopBack(sTask));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� ������� ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::PushTaskTransferToServer(const STask &sTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //���� � ������ ��� ���� ����� �������, �� �� ���������, ��� ��� ���� �������� ������� ����� ���������� ������� � �������,
   //� ���� � ������� ��������� ����� ����� �������, �� ��� ������ (������� ������������) ����� ������
   STask sTask_Local;
   if (sProtectedVariables.cVectorTask_TransferToServer.FindByTaskGUID(sTask.TaskGUID,sTask_Local)==true) return;
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(sTask);
  }
 }
}

//----------------------------------------------------------------------------------------------------
//�������� ������ ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::PopProjectTransferToServer(SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorProject_TransferToServer.PopBack(sProject));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::PushProjectTransferToServer(const SProject &sProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //���� � ������ ��� ���� ����� ������, �� �� ���������, ��� ��� ���� �������� ������� ����� ���������� ������ � �������,
   //� ���� � ������� �������� ����� ����� ������, �� ��� ������ (������� ������������) ����� ������
   SProject sProject_Local;
   if (sProtectedVariables.cVectorProject_TransferToServer.FindByProjectGUID(sProject.ProjectGUID,sProject_Local)==true) return;
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(sProject);
  }
 }
}



//----------------------------------------------------------------------------------------------------
//��������, ����� �� �������� ���� � �������� ���� ������������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::GetOnShowAndResetOnShow(void)
{
 bool ret;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   ret=sProtectedVariables.OnShow;
   sProtectedVariables.OnShow=false;
  }
 }
 return(ret);
}
//----------------------------------------------------------------------------------------------------
//���� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::Processing(void)
{
 bool update_view=false;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   update_view=sProtectedVariables.OnUpdateView;
   sProtectedVariables.OnUpdateView=false;
  }
 } 
 if (update_view==true) UpdateAllViews(NULL);//� ���� ����� �������� ���������� ����������� 
}
//====================================================================================================
//������
//====================================================================================================
IMPLEMENT_DYNCREATE(CDocument_Main,CDocument)
