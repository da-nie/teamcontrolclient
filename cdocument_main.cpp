#include "cdocument_main.h"
#include "cthreadclient.h"


#include "ctreeview_kit.h"

extern CThreadClient cThreadClient;//���������� �����

BEGIN_MESSAGE_MAP(CDocument_Main,CDocument)
END_MESSAGE_MAP()

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
   sProtectedVariables.cVectorTask_Common.Load("common_task_list.bin");
   sProtectedVariables.cVectorProject.Load("project_list.bin");
   sProtectedVariables.cVectorTask_TransferToServer.Load("task_to_server.bin");
   sProtectedVariables.cVectorProject_TransferToServer.Load("project_to_server.bin");

   sProtectedVariables.UserIsSelected=false;
   sProtectedVariables.OnUpdateView=false;
   sProtectedVariables.MyGUID="";
   sProtectedVariables.OnLine=false;
   sProtectedVariables.OnShow=false;
   sProtectedVariables.NotReadTaskState=false;
   sProtectedVariables.RestartWithLoader=false;
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
   sProtectedVariables.sShowState.ShowCommonTask=false;

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
//��������� ������������ ����� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::RestartWithLoader(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.RestartWithLoader=true;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//��������, ����� �� ������������ ����� ���������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::GetRestartWithLoaderState(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   bool restart=sProtectedVariables.RestartWithLoader;
   sProtectedVariables.RestartWithLoader=false;
   return(restart);
  }
 }
}

//----------------------------------------------------------------------------------------------------
//������� ��� �������� ���� � ����������� ������� �� ���� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::DeleteFinishedTask(long year,long month,long day)
{
 CDate cDate(year,month,day);
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector<CTask> vector_CTask=sProtectedVariables.cVectorTask.CreateVectorCTaskByFromUserGUID(sProtectedVariables.MyGUID);
   size_t size=vector_CTask.size();
   for(size_t n=0;n<size;n++)
   {
    CTask &cTask=vector_CTask[n];
    if (cTask.IsStateFinished()==true)
	{
     if (cTask.GetDate()>cDate) continue;
     //������� �� ������� ������� ��� ���������� � �������
     while(sProtectedVariables.cVectorTask_TransferToServer.DeleteByTaskGUID(cTask.GetTaskGUID())==true);
	 cTask.MarkForDelete();
     sProtectedVariables.cVectorTask_TransferToServer.PushBack(cTask);
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
   sProtectedVariables.cVectorTask_Common.Save("common_task_list.bin");
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
bool CDocument_Main::FindByUserGUIDAndResetChangeData(const CSafeString &guid,CUser &cUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorUser.FindByUserGUIDAndResetChangeData(guid,cUser));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//����� ������������ �� GUID
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByUserGUID(const CSafeString &guid,CUser &cUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorUser.FindByUserGUID(guid,cUser));
  }
 }
 return(false);
}

//----------------------------------------------------------------------------------------------------
//����� ������ �� GUID � �������� ������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByProjectGUIDAndResetChangeData(const CSafeString &guid,CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorProject.FindByProjectGUIDAndResetChangeData(guid,cProject));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//����� ������ �� GUID
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::FindByProjectGUID(const CSafeString &guid,CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorProject.FindByProjectGUID(guid,cProject));
  }
 }
 return(false);
}


//----------------------------------------------------------------------------------------------------
//�������� ���� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::GetMyParam(bool &on_line,CSafeString &guid,CSafeString &name,bool &leader)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   guid=sProtectedVariables.MyGUID;
   on_line=sProtectedVariables.OnLine;
   leader=sProtectedVariables.Leader;
   name=sProtectedVariables.MyName;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������ ���� ���������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetMyParam(const bool &on_line,const CSafeString &guid,const CSafeString &name,const bool &leader)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.MyGUID=guid;
   sProtectedVariables.OnLine=on_line;
   sProtectedVariables.Leader=leader;
   sProtectedVariables.MyName=name;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//����������, ���� �� �����������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetOnLine(const bool &on_line)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
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
   sProtectedVariables.cVectorProject.Clear();
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
//�������� ������ ����� �������
//----------------------------------------------------------------------------------------------------
CVectorTask CDocument_Main::GetCVectorTaskCommon(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   CVectorTask cVectorTask_Copy=sProtectedVariables.cVectorTask_Common;
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
 FindAllMyParam();
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
   sProtectedVariables.cVectorTask.SortByDate();
   sProtectedVariables.OnUpdateView=true;
  }
 } 
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//������ ������ ����� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetCommonTaskBook(CVectorTask &cVectorTask_Set)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorTask_Common=cVectorTask_Set;
   sProtectedVariables.cVectorTask_Common.SortByDate();
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
void CDocument_Main::OnDeletedUser(const CUser &cUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.DeleteByUserGUID(cUser.GetUserGUID());
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
 FindAllMyParam();
}
//----------------------------------------------------------------------------------------------------
//��� �������� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnAddedUser(const CUser &cUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.AddNew(cUser);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
 FindAllMyParam();
}
//----------------------------------------------------------------------------------------------------
//��� ������ ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnChangedUser(const CUser &cUser)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorUser.ChangeByUserGUID(cUser.GetUserGUID(),cUser);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
 FindAllMyParam();
}


//----------------------------------------------------------------------------------------------------
//���� ������ �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnDeletedTask(const CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   if (cTask.IsFromOrForUserGUID(sProtectedVariables.MyGUID)==true)
   {
    //sProtectedVariables.OnShow=true;
   }
   sProtectedVariables.cVectorTask.DeleteByTaskGUID(cTask.GetTaskGUID());
   sProtectedVariables.cVectorTask_Common.DeleteByTaskGUID(cTask.GetTaskGUID());
   sProtectedVariables.cVectorTask.SortByDate();
   sProtectedVariables.OnUpdateView=true;   
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//���� ��������� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnAddedTask(const CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   if (cTask.IsFromOrForUserGUID(sProtectedVariables.MyGUID)==true)
   {
    sProtectedVariables.cVectorTask.AddNew(cTask);
    sProtectedVariables.cVectorTask.SortByDate();
	sProtectedVariables.OnShow=true;
   }
   if (cTask.IsCommon()==true) sProtectedVariables.cVectorTask_Common.AddNew(cTask);
   sProtectedVariables.cVectorTask_Common.SortByDate();
   sProtectedVariables.OnUpdateView=true;
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//���� ������� �������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnChangedTask(const CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {   
   if (cTask.IsFromOrForUserGUID(sProtectedVariables.MyGUID)==true)
   {
    sProtectedVariables.cVectorTask.ChangeByTaskGUID(cTask.GetTaskGUID(),cTask);
    sProtectedVariables.cVectorTask.SortByDate();
	//if (cTask.IsForUserGUID(sProtectedVariables.MyGUID)==true) sProtectedVariables.OnShow=true;
   }
   CTask cTask_Local;
   if (sProtectedVariables.cVectorTask_Common.FindByTaskGUID(cTask.GetTaskGUID(),cTask_Local)==true)//���� ������� ��� ���� � ������
   {
    if (cTask.IsCommon()==true) sProtectedVariables.cVectorTask_Common.ChangeByTaskGUID(cTask.GetTaskGUID(),cTask);
	                       else sProtectedVariables.cVectorTask_Common.DeleteByTaskGUID(cTask.GetTaskGUID());
   }
   else//������� ��� ��� � ������
   {
    if (cTask.IsCommon()==true) sProtectedVariables.cVectorTask_Common.AddNew(cTask);
   }
   sProtectedVariables.cVectorTask_Common.SortByDate();
   sProtectedVariables.OnUpdateView=true;   
  }
 }
 SaveState();
}


//----------------------------------------------------------------------------------------------------
//��� ����� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnDeletedProject(const CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorProject.DeleteByProjectGUID(cProject.GetProjectGUID());
   sProtectedVariables.OnUpdateView=true;   
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//��� �������� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnAddedProject(const CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.cVectorProject.AddNew(cProject);
   sProtectedVariables.OnUpdateView=true;   
  }
 }
 SaveState();
}
//----------------------------------------------------------------------------------------------------
//��� ������ ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::OnChangedProject(const CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {   
   sProtectedVariables.cVectorProject.ChangeByProjectGUID(cProject.GetProjectGUID(),cProject);
   sProtectedVariables.OnUpdateView=true;   
  }
 }
 SaveState();
}



//----------------------------------------------------------------------------------------------------
//���������� ���������� ������������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetSelectedUser(const CUser &cUser)
{
 sProtectedVariables.UserIsSelected=true;
 sProtectedVariables.cUser_Selected=cUser;
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
bool CDocument_Main::GetSelectedUser(CUser &cUser)
{
 if (sProtectedVariables.UserIsSelected==false) return(false);
 cUser=sProtectedVariables.cUser_Selected;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::AddTask(CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   cTask.MarkForAdd();
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(cTask);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::DeleteTask(CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorTask_TransferToServer.DeleteByTaskGUID(cTask.GetTaskGUID())==true);
   cTask.MarkForDelete();
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(cTask);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::ChangeTask(CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorTask_TransferToServer.DeleteByTaskGUID(cTask.GetTaskGUID())==true);
   cTask.MarkForChange();
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(cTask);
   sProtectedVariables.OnUpdateView=true;   
  }
 }
 return(true);
}

//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::AddProject(CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   cProject.MarkForAdd();
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(cProject);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::DeleteProject(CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorProject_TransferToServer.DeleteByProjectGUID(cProject.GetProjectGUID())==true);
   cProject.MarkForDelete();
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(cProject);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::ChangeProject(CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //������� �� ������� ������� ��� ���������� � �������
   while(sProtectedVariables.cVectorProject_TransferToServer.DeleteByProjectGUID(cProject.GetProjectGUID())==true);
   cProject.MarkForChange();
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(cProject);
   sProtectedVariables.OnUpdateView=true;
  }
 }
 return(true);
}


//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ ��� �������� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskByForUserGUID(const CSafeString &guid)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask.CreateVectorCTaskByForUserGUID(guid);
  }
 }
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ �� �������� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskByFromUserGUID(const CSafeString &guid)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask.CreateVectorCTaskByFromUserGUID(guid);
  }
 }
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask.CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(guid_one,guid_two);
  }
 }
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� ������� �� ������������
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask.CreateVectorCTaskByProjectGUIDFromUserGUID(guid_project,guid_from_user);
  }
 }
 return(vector_CTask);
}





//----------------------------------------------------------------------------------------------------
//������� ������ ����� ����� �� GUID ������������ ��� �������� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskCommonByForUserGUID(const CSafeString &guid)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask_Common.CreateVectorCTaskByForUserGUID(guid);
  }
 }
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �����
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskCommon(void)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask_Common.GetVectorCTask();
  }
 }
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� ����� �� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CDocument_Main::CreateVectorCTaskCommonByProjectGUID(const CSafeString &guid_project)
{
 vector<CTask> vector_CTask;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   vector_CTask=sProtectedVariables.cVectorTask_Common.CreateVectorCTaskByProjectGUID(guid_project);
  }
 }
 return(vector_CTask);
}



//----------------------------------------------------------------------------------------------------
//�������� ������� ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::PopTaskTransferToServer(CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorTask_TransferToServer.PopBack(cTask));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� ������� ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::PushTaskTransferToServer(const CTask &cTask)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //���� � ������ ��� ���� ����� �������, �� �� ���������, ��� ��� ���� �������� ������� ����� ���������� ������� � �������,
   //� ���� � ������� ��������� ����� ����� �������, �� ��� ������ (������� ������������) ����� ������
   CTask cTask_Local;
   if (sProtectedVariables.cVectorTask_TransferToServer.FindByTaskGUID(cTask.GetTaskGUID(),cTask_Local)==true) return;
   sProtectedVariables.cVectorTask_TransferToServer.PushBack(cTask);
  }
 }
}

//----------------------------------------------------------------------------------------------------
//�������� ������ ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::PopProjectTransferToServer(CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.cVectorProject_TransferToServer.PopBack(cProject));
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ ��� �������� �� ������
//----------------------------------------------------------------------------------------------------
void CDocument_Main::PushProjectTransferToServer(const CProject &cProject)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   //���� � ������ ��� ���� ����� ������, �� �� ���������, ��� ��� ���� �������� ������� ����� ���������� ������ � �������,
   //� ���� � ������� �������� ����� ����� ������, �� ��� ������ (������� ������������) ����� ������
   CProject cProject_Local;
   if (sProtectedVariables.cVectorProject_TransferToServer.FindByProjectGUID(cProject.GetProjectGUID(),cProject_Local)==true) return;
   sProtectedVariables.cVectorProject_TransferToServer.PushBack(cProject);
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
//��������, ����� �� ���������� ��������� ��� �������� ����� � �������� ���
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::GetSendPingAndReset(void)
{
 bool ret;
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   ret=sProtectedVariables.SendPing;
   sProtectedVariables.SendPing=false;
  }
 }
 return(ret);
}

//----------------------------------------------------------------------------------------------------
//������, ����� �� ���������� ��������� ��� �������� �����
//----------------------------------------------------------------------------------------------------
void CDocument_Main::SetSendPing(bool state)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.SendPing=state;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//��������� �� ���������� ����� �������
//----------------------------------------------------------------------------------------------------
bool CDocument_Main::IsShowCommonTask(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   return(sProtectedVariables.sShowState.ShowCommonTask);
  }
 }
 return(false);
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

//----------------------------------------------------------------------------------------------------
//���������� ��� ���� ��������� (���, ������������ ��)
//----------------------------------------------------------------------------------------------------
void CDocument_Main::FindAllMyParam(void)
{
 {
  CRAIICCriticalSection cRAIICCriticalSection(&sProtectedVariables.cCriticalSection);
  {
   sProtectedVariables.Leader=false;
   sProtectedVariables.MyName="";
   CUser cUser;
   if (sProtectedVariables.cVectorUser.FindByUserGUID(sProtectedVariables.MyGUID,cUser)==false) return;
   sProtectedVariables.Leader=cUser.GetLeader();
   sProtectedVariables.MyName=cUser.GetName();
  }
 } 
}

//====================================================================================================
//������
//====================================================================================================
IMPLEMENT_DYNCREATE(CDocument_Main,CDocument)
