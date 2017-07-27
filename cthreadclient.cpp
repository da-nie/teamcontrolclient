#include "cthreadclient.h"

//====================================================================================================
//���������� ����������
//====================================================================================================

CThreadClient cThreadClient;//��������� �����

//====================================================================================================
//����������������
//====================================================================================================

//���� �������
#define THREAD_SERVER_PORT 9090
//������ ������ �����
#define BUFFER_SIZE 16384

//====================================================================================================
//������� ������
//====================================================================================================

UINT ThreadClient(LPVOID pParam)
{
 CThreadClient *cThreadClient_Ptr=reinterpret_cast<CThreadClient*>(pParam);
 if (cThreadClient_Ptr==NULL) return(0);
 cThreadClient_Ptr->Processing(); 
 return(0);
}
//====================================================================================================
//����������� ������
//====================================================================================================
CThreadClient::CThreadClient(void)
{
 Buffer=new char[BUFFER_SIZE];
 cWinThread_Thread=NULL;
 cDocument_Main_Ptr=NULL;
 WorkingMode=WORKING_MODE_WAIT;
 StuffingEnabled=false;
}
//====================================================================================================
//���������� ������
//====================================================================================================
CThreadClient::~CThreadClient()
{ 
 Stop();
 delete[](Buffer);
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//���������� ������� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::SaveTaskVector(char *filename,const vector<STask> &vector_STask)
{

}
//----------------------------------------------------------------------------------------------------
//��������� �����
//----------------------------------------------------------------------------------------------------
void CThreadClient::Start(void)
{
 Stop();
 cEvent_Exit.ResetEvent();
 cWinThread_Thread=AfxBeginThread((AFX_THREADPROC)ThreadClient,this);
 cWinThread_Thread->m_bAutoDelete=FALSE;
}
//----------------------------------------------------------------------------------------------------
//���������� �����
//----------------------------------------------------------------------------------------------------
void CThreadClient::Stop(void)
{ 
 if (cWinThread_Thread!=NULL)
 {
  cEvent_Exit.SetEvent();
  WaitForSingleObject(cWinThread_Thread->m_hThread,INFINITE);
  delete(cWinThread_Thread);
  cWinThread_Thread=NULL;    
 }
}
//----------------------------------------------------------------------------------------------------
//������ ����� ���������
//----------------------------------------------------------------------------------------------------
void CThreadClient::SetDocument(CDocument_Main *cDocument_Main_Set_Ptr)
{
 cDocument_Main_Ptr=cDocument_Main_Set_Ptr;
}
//----------------------------------------------------------------------------------------------------
//�������� ���� ���������
//----------------------------------------------------------------------------------------------------
void CThreadClient::Processing(void)
{
 char Host[255];
 sprintf(Host,"127.0.0.1");
 if (cDocument_Main_Ptr!=NULL)
 {
  SClientSettings sClientSettings;
  cDocument_Main_Ptr->GetClientSettings(sClientSettings);
  sprintf(Host,"%i.%i.%i.%i",sClientSettings.ServerIP[0],sClientSettings.ServerIP[1],sClientSettings.ServerIP[2],sClientSettings.ServerIP[3]);
 }
 const long connected_pause_ms=1000;//����� ����� ������������� � �������
 const long wait_pause_ms=1;//����� ����� ��������� �������
 while(1)
 {  
  if (WaitForSingleObject(cEvent_Exit.m_hObject,connected_pause_ms)==WAIT_OBJECT_0) break;//������� ������ �� �����
  //������������ � �������
  SOCKET socket_server=INVALID_SOCKET;
  bool on_exit;
  bool is_connected=ConnectAsServer(socket_server,Host,THREAD_SERVER_PORT,on_exit);//������������ � �������
  if (on_exit==true) break;//��������� �����
  if (is_connected==false) continue;
  //����������� �����������
  vector_Data.clear();
  vector_Data.reserve(MAX_PACKAGE_LENGTH);
  StuffingEnabled=false;
  WorkingMode=WORKING_MODE_AUTORIZATION;  
  //��������� ������� � ��������� ������ �� �������
  on_exit=false;
  while(1)
  {
   if (WaitForSingleObject(cEvent_Exit.m_hObject,wait_pause_ms)==WAIT_OBJECT_0)//������� ������ �� �����
   {
    on_exit=true;
	break;
   }
   if (LinkProcessing(socket_server,on_exit)==false) break;//��������� ���������� �� �������
   if (on_exit==true) break;
  }
  //����������� �� �������
  //�������� ����� ������� � ����������� �����
  SetSocketNoBlockMode(socket_server,false);
  //��������� ������
  shutdown(socket_server,SD_BOTH);
  closesocket(socket_server);  
  //�������, ���� �����
  if (on_exit==true) break;
  if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetMyParam(false,"");
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ������ � ��������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::LinkProcessing(SOCKET socket_server,bool &on_exit)
{
 const long timeout_us=5000;//������� �� �������

 on_exit=false;
 //����������� ������
 fd_set Readen;
 FD_ZERO(&Readen);//�������� ������
 fd_set Exeption;
 FD_ZERO(&Exeption);//�������� ������
 FD_SET(socket_server,&Readen);//��������� ����� �������
 FD_SET(socket_server,&Exeption);//��������� ����� �������
 //��� ������� � �������
 timeval timeout;
 timeout.tv_sec=0;
 timeout.tv_usec=timeout_us;//������� �� �������
 //����������, �� ��������� �� ���� � ��������?
 if (select(0,&Readen,0,&Exeption,&timeout)>0)
 {
  //�� ��������� �� ���������� �� ������ �������?
  if (FD_ISSET(socket_server,&Exeption)) 
  {
   return(false);//��������� ���������������
  }
  //�� ������ �� ������ � �������?
  if (FD_ISSET(socket_server,&Readen))
  {
   //��������� ������
   long received=recv(socket_server,Buffer,BUFFER_SIZE,0);
   if (received<=0) return(false);//������ �������� �������� ��� ������ ����������
   //����������� �������� �� ������� ������
   NewDataFromServer(socket_server,Buffer,received,on_exit);
   if (on_exit==true) return(true);   
  } 
 }
 //������ ������ �������
 if (WorkingMode==WORKING_MODE_AUTORIZATION) return(ExecuteCommand_Autorization(socket_server,on_exit));//�������� ������ �� �����������
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION) return(true);//��� �������� �����������
 if (WorkingMode==WORKING_MODE_GET_USER_BOOK) return(ExecuteCommand_GetUserBook(socket_server,on_exit));//�������� ������ �� ��������� ���� �������������
 if (WorkingMode==WORKING_MODE_WAIT_GET_USER_BOOK) return(true);//��� ������ �� ������ �� ��������� ���� �������������
 if (WorkingMode==WORKING_MODE_GET_TASK_BOOK) return(ExecuteCommand_GetTaskBook(socket_server,on_exit));//�������� ������ �� ��������� ���� �������
 if (WorkingMode==WORKING_MODE_WAIT_GET_TASK_BOOK) return(true);//��� ������ �� ������ �� ��������� ���� �������
 if (WorkingMode==WORKING_MODE_GET_PROJECT_BOOK) return(ExecuteCommand_GetProjectBook(socket_server,on_exit));//�������� ������ �� ��������� ���� ��������
 if (WorkingMode==WORKING_MODE_WAIT_GET_PROJECT_BOOK) return(true);//��� ������ �� ������ �� ��������� ���� ��������
 if (WorkingMode==WORKING_MODE_WAIT) 
 {
  if (TaskProcessing(socket_server,on_exit)==false) return(false);
  if (ProjectProcessing(socket_server,on_exit)==false) return(false);
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� �������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::TaskProcessing(SOCKET socket_server,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return(true);
 STask sTask;
 if (cDocument_Main_Ptr->PopTaskTransferToServer(sTask)==false) return(true);
 SERVER_COMMAND command=SERVER_COMMAND_NOTHING;
 if (sTask.TaskType==TASK_TYPE_DELETED) command=SERVER_COMMAND_DELETED_TASK;
 if (sTask.TaskType==TASK_TYPE_ADDED) command=SERVER_COMMAND_ADDED_TASK;
 if (sTask.TaskType==TASK_TYPE_CHANGED) command=SERVER_COMMAND_CHANGED_TASK;
 if (command==SERVER_COMMAND_NOTHING) return(true);
 bool ret=cTransceiver_Task.SendTaskDataToServerInPackage(socket_server,sTask,command,cEvent_Exit,on_exit);
 //� ������ ������ ���������� ������� ������� � �������
 if (ret==false || on_exit==true) cDocument_Main_Ptr->PushTaskTransferToServer(sTask);
 cDocument_Main_Ptr->SaveState();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� ��������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ProjectProcessing(SOCKET socket_server,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return(true);
 SProject sProject;
 if (cDocument_Main_Ptr->PopProjectTransferToServer(sProject)==false) return(true);
 SERVER_COMMAND command=SERVER_COMMAND_NOTHING;
 if (sProject.ProjectType==PROJECT_TYPE_DELETED) command=SERVER_COMMAND_DELETED_PROJECT;
 if (sProject.ProjectType==PROJECT_TYPE_ADDED) command=SERVER_COMMAND_ADDED_PROJECT;
 if (sProject.ProjectType==PROJECT_TYPE_CHANGED) command=SERVER_COMMAND_CHANGED_PROJECT;
 if (command==SERVER_COMMAND_NOTHING) return(true);
 bool ret=cTransceiver_Project.SendProjectDataToServerInPackage(socket_server,sProject,command,cEvent_Exit,on_exit);
 //� ������ ������ ���������� ������� ������� � �������
 if (ret==false || on_exit==true) cDocument_Main_Ptr->PushProjectTransferToServer(sProject);
 cDocument_Main_Ptr->SaveState();
 return(true);
}

//----------------------------------------------------------------------------------------------------
//���������� ������� �����������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_Autorization(SOCKET socket_server,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetMyParam(false,"");
 CString login="";
 CString password="";
 if (cDocument_Main_Ptr!=NULL)
 {
  SClientSettings sClientSettings;
  cDocument_Main_Ptr->GetClientSettings(sClientSettings);
  login=sClientSettings.Login;
  password=sClientSettings.Password;
 }
 if (cTransceiver_Autorization.SendAutorization(socket_server,login,password,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_CHECK_AUTORIZATION;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//���������� ������� ������� ���� �������������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetUserBook(SOCKET socket_server,bool &on_exit)
{
 if (cTransceiver_User.GetUserBook(socket_server,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_WAIT_GET_USER_BOOK;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//���������� ������� ������� ���� �������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetTaskBook(SOCKET socket_server,bool &on_exit)
{
 if (cTransceiver_Task.GetTaskBook(socket_server,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_WAIT_GET_TASK_BOOK;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//���������� ������� ������� ���� ��������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetProjectBook(SOCKET socket_server,bool &on_exit)
{
 if (cTransceiver_Project.GetProjectBook(socket_server,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_WAIT_GET_PROJECT_BOOK;
 return(true);
}

//----------------------------------------------------------------------------------------------------
//������� ������ �� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::NewDataFromServer(SOCKET socket_server,char *data,unsigned long length,bool &on_exit)
{
 long n;
 on_exit=false;
 SServerAnswer::SHeader sServerAnswer_sHeader; 
 //����������� �������� ������ 
 for(n=0;n<length;n++)
 {
  unsigned char byte=static_cast<unsigned char>(data[n]);
  if (StuffingEnabled==false)//������������ ��������
  {
   if (byte==PROTOCOL_STUFFING)//�������� ������������
   { 
    StuffingEnabled=true;
    continue;
   }
   if (byte==PROTOCOL_BEGIN_PACKAGE)//�������� ������ ������� ������
   {
    vector_Data.clear();
    continue;
   }
   if (byte==PROTOCOL_END_PACKAGE)//������� ������� ���������
   {
    sServerAnswer_sHeader=*(reinterpret_cast<SServerAnswer::SHeader*>(&vector_Data[0]));
    //�������������� �������� ������
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_USER_BOOK) ExecuteAnswer_GetUserBook(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_TASK_BOOK) ExecuteAnswer_GetTaskBook(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_PROJECT_BOOK) ExecuteAnswer_GetProjectBook(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_DELETED_USER) ExecuteAnswer_GetDeletedUser(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ADDED_USER) ExecuteAnswer_GetAddedUser(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CHANGED_USER) ExecuteAnswer_GetChangedUser(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_DELETED_TASK) ExecuteAnswer_GetDeletedTask(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ADDED_TASK) ExecuteAnswer_GetAddedTask(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CHANGED_TASK) ExecuteAnswer_GetChangedTask(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_DELETED_PROJECT) ExecuteAnswer_GetDeletedProject(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ADDED_PROJECT) ExecuteAnswer_GetAddedProject(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CHANGED_PROJECT) ExecuteAnswer_GetChangedProject(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_OK) ExecuteAnswer_Ok(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_AUTORIZATION_OK) ExecuteAnswer_AutorizationOk(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ERROR) ExecuteAnswer_Error(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (on_exit==true) return;
    vector_Data.clear();
    continue;
   }
  }
  else//������������ �������
  {
   if (byte==PROTOCOL_STUFFING_00) byte=0x00;
   if (byte==PROTOCOL_STUFFING_FE) byte=0xFE;
   if (byte==PROTOCOL_STUFFING_FF) byte=0xFF;
   StuffingEnabled=false;
  }
  //��������� ���� � �����
  vector_Data.push_back(byte);
  size_t cmd_length=vector_Data.size();
  if (cmd_length>=MAX_PACKAGE_LENGTH) vector_Data.clear();//��������� ������ �������  
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ���� �����������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetUserBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������������
 CVectorUser cVectorUser;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);
 while(offset<size)
 {
  SUser sUser;
  if (cTransceiver_User.ReadSUserInArray(ptr,offset,size,sUser)==false) break;
  sUser.ChangeData=false;
  cVectorUser.AddNew(sUser);
 } 
 cDocument_Main_Ptr->SetUserBook(cVectorUser);
 WorkingMode=WORKING_MODE_GET_TASK_BOOK; 
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ���� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetTaskBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 CVectorTask cVectorTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 while(offset<size)
 {
  STask sTask;
  if (cTransceiver_Task.ReadSTaskInArray(ptr,offset,size,sTask)==false) break;
  sTask.ChangeData=false;
  sTask.TaskType=TASK_TYPE_NONE;
  cVectorTask.PushBack(sTask);
 } 
 cDocument_Main_Ptr->SetTaskBook(cVectorTask);
 WorkingMode=WORKING_MODE_GET_PROJECT_BOOK;
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ���� ��������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetProjectBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 CVectorProject cVectorProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 while(offset<size)
 {
  SProject sProject;
  if (cTransceiver_Project.ReadSProjectInArray(ptr,offset,size,sProject)==false) break;
  sProject.ChangeData=false;
  sProject.ProjectType=PROJECT_TYPE_NONE;
  cVectorProject.PushBack(sProject);
 } 
 cDocument_Main_Ptr->SetProjectBook(cVectorProject);
 WorkingMode=WORKING_MODE_WAIT;
}

//----------------------------------------------------------------------------------------------------
//��������� ������: ��
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_Ok(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION)//�������� ������� �����������
 {
  if (command==SERVER_COMMAND_AUTORIZATION)
  {
   WorkingMode=WORKING_MODE_GET_USER_BOOK;
   return;
  }
  WorkingMode=WORKING_MODE_AUTORIZATION;
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ����������� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_AutorizationOk(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION)//�������� ������� �����������
 {
  if (command==SERVER_COMMAND_AUTORIZATION)
  {
   size_t size=vector_Data.size();
   char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
   CString guid;
   if (cTransceiver_Autorization.GetAutorizationAnswer(ptr,size,guid)==false) return;
   if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetMyParam(true,guid);
   WorkingMode=WORKING_MODE_GET_USER_BOOK;
   return;
  }
  WorkingMode=WORKING_MODE_AUTORIZATION;
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_Error(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION)//�������� ������� �����������
 {
  WorkingMode=WORKING_MODE_AUTORIZATION;
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ��������� ����������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetDeletedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������������
 SUser sUser;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_User.GetUserAnswer(ptr,size,sUser)==false) return;
 sUser.ChangeData=false;
 cDocument_Main_Ptr->OnDeletedUser(sUser);
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ������������ ����������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetAddedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 SUser sUser;
 //��������� ���� �������������
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_User.GetUserAnswer(ptr,size,sUser)==false) return;
 sUser.ChangeData=false;
 cDocument_Main_Ptr->OnAddedUser(sUser);
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ���������� ����������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetChangedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������������
 SUser sUser;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_User.GetUserAnswer(ptr,size,sUser)==false) return;
 sUser.ChangeData=true;
 cDocument_Main_Ptr->OnChangedUser(sUser);
}




//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ��������� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetDeletedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 STask sTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Task.GetTaskAnswer(ptr,size,sTask)==false) return;
 sTask.ChangeData=false;
 sTask.TaskType=TASK_TYPE_NONE;
 cDocument_Main_Ptr->OnDeletedTask(sTask);
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ������������ �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetAddedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 STask sTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Task.GetTaskAnswer(ptr,size,sTask)==false) return;
 sTask.ChangeData=false;
 sTask.TaskType=TASK_TYPE_NONE;
 cDocument_Main_Ptr->OnAddedTask(sTask);
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ���������� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetChangedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 STask sTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Task.GetTaskAnswer(ptr,size,sTask)==false) return;
 sTask.ChangeData=true;
 sTask.TaskType=TASK_TYPE_NONE;
 cDocument_Main_Ptr->OnChangedTask(sTask);
}

//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ��������� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetDeletedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 SProject sProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Project.GetProjectAnswer(ptr,size,sProject)==false) return;
 sProject.ChangeData=false;
 sProject.ProjectType=PROJECT_TYPE_NONE;
 cDocument_Main_Ptr->OnDeletedProject(sProject);
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ������������ �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetAddedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 SProject sProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Project.GetProjectAnswer(ptr,size,sProject)==false) return;
 sProject.ChangeData=false;
 sProject.ProjectType=PROJECT_TYPE_NONE;
 cDocument_Main_Ptr->OnAddedProject(sProject);
}
//----------------------------------------------------------------------------------------------------
//��������� ������: ��������� ������ ���������� �������
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetChangedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //��������� ���� �������
 SProject sProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Project.GetProjectAnswer(ptr,size,sProject)==false) return;
 sProject.ChangeData=true;
 sProject.ProjectType=PROJECT_TYPE_NONE;
 cDocument_Main_Ptr->OnChangedProject(sProject);
}


//----------------------------------------------------------------------------------------------------
//����������� � �������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ConnectAsServer(SOCKET &socket_server,CString host_name,long port,bool &on_exit)
{
 const long block_timeout_us=500000;//������� �� ��������� ����������

 on_exit=false;
 socket_server=INVALID_SOCKET;
 //������������ � �������
 socket_server=socket(AF_INET,SOCK_STREAM,0);//������ �����
 sockaddr_in target;
 target.sin_family=AF_INET;//�������� �������-��������
 target.sin_port=htons(port);//���� �������
 u_long addr=inet_addr(host_name);//IP-�������  
 if (addr==INADDR_NONE)//��� �� IP
 {
  hostent *host=gethostbyname(host_name); 
  if (host==NULL)
  {
   closesocket(socket_server);
   socket_server=INVALID_SOCKET;
   return(false);//������  
  }
  addr=*((u_long*)host->h_addr_list[0]);
 }
 target.sin_addr.s_addr=addr;
 //�������� ����� � ������������� �����
 if (SetSocketNoBlockMode(socket_server,true)==false)
 {
  closesocket(socket_server);
  socket_server=INVALID_SOCKET;
  return(false);//������
 }
 //������������ � �������
 if (WaitForSingleObject(cEvent_Exit.m_hObject,0)==WAIT_OBJECT_0)//������� ������ �� �����
 {
  SetSocketNoBlockMode(socket_server,false);
  closesocket(socket_server);
  socket_server=INVALID_SOCKET;
  on_exit=true;
  return(false);
 }
 if (connect(socket_server,(LPSOCKADDR)&target,sizeof(target))==SOCKET_ERROR)
 {
  int error_code=WSAGetLastError();
  if (error_code==WSAEWOULDBLOCK)
  {
   fd_set Writen;
   FD_ZERO(&Writen);//�������� ������
   FD_SET(socket_server,&Writen);//��������� �����
   timeval timeout;
   timeout.tv_sec=0;
   timeout.tv_usec=block_timeout_us;
   //����������, ��� �� �����������?
   if (select(0,NULL,&Writen,NULL,&timeout)>0)
   {
    return(true);
   }
   else
   {
    //�������� ����� � ����������� �����
    SetSocketNoBlockMode(socket_server,false);
    closesocket(socket_server);
    socket_server=INVALID_SOCKET;
    return(false);//������
   }
  }
 }
 //������������
 return(true); 
}

//----------------------------------------------------------------------------------------------------
//������� �������������� ������ ��� ������
//----------------------------------------------------------------------------------------------------
bool CThreadClient::SetSocketNoBlockMode(SOCKET socket_set,bool state)
{
 unsigned long nb=0;
 if (state==true) nb=1;
 if (ioctlsocket(socket_set,FIONBIO,(unsigned long *)&nb)==INVALID_SOCKET) return(false);
 return(true);
}