#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

//====================================================================================================
//��������
//====================================================================================================

//����� ����������� ������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include <list>
#include <vector>
#include "protocol.h"
#include "cdocument_main.h"
#include "cvector_task.h"
#include "craiiccriticalsection.h"
#include "ctransceiver_user.h"
#include "ctransceiver_task.h"
#include "ctransceiver_project.h"
#include "ctransceiver_file.h"
#include "ctransceiver_autorization.h"
#include "ctransceiver_ping.h"

using namespace std;

//====================================================================================================
//����������������
//====================================================================================================

//������ ������
enum WORKING_MODE
{
 //��������
 WORKING_MODE_WAIT,
 //��������� ����������� ����� ��������� �� �������
 WORKING_MODE_GET_CLIENT_PROGRAMM_CRC,
 //�������� ����������� ����� ���������
 WORKING_MODE_WAIT_CLIENT_PROGRAMM_CRC,
 //�������� ���������� ���������
 WORKING_MODE_WAIT_UPDATE,
 //��������� ���������� ��������� � ���������� � �������
 WORKING_MODE_GET_CLIENT_PROGRAMM_AND_LOADER,
 //�����������
 WORKING_MODE_AUTORIZATION,
 //�������� �����������
 WORKING_MODE_CHECK_AUTORIZATION,
 //������ ������ ���� ������ �� �������
 WORKING_MODE_GET_USER_BOOK,
 //�������� ������ ���� ������ �� �������
 WORKING_MODE_WAIT_GET_USER_BOOK,
 //������ ������ ���� ������� �� �������
 WORKING_MODE_GET_TASK_BOOK,
 //�������� ������ ���� ������� �� �������
 WORKING_MODE_WAIT_GET_TASK_BOOK,
 //������ ������ ���� �������� �� �������
 WORKING_MODE_GET_PROJECT_BOOK,
 //�������� ������ ���� �������� �� �������
 WORKING_MODE_WAIT_GET_PROJECT_BOOK
};

//====================================================================================================
//����� ����������� ������
//====================================================================================================

class CThreadClient
{
 //������������� �������
 friend UINT ThreadClient(LPVOID pParam);//������� ������
 protected:

  vector<unsigned char> vector_Data;//�������� ������

  CEvent cEvent_Exit;//���������� �� ����� �� ������
  CWinThread *cWinThread_Thread;//����� ���������
  CDocument_Main *cDocument_Main_Ptr;//��������� �� ��������
  char *Buffer;//����� �����/��������   

  bool StuffingEnabled;//������� �� ������������

  WORKING_MODE WorkingMode;//������� ����� ������ � ��������

  CTransceiver_Ping cTransceiver_Ping;//�����-���������� ������ ��������� ��� �������� �����
  CTransceiver_User cTransceiver_User;//�����-���������� ������ �������������
  CTransceiver_Task cTransceiver_Task;//�����-���������� ������ �������
  CTransceiver_Project cTransceiver_Project;//�����-���������� ������ ��������
  CTransceiver_File cTransceiver_File;//�����-���������� ������ ��������� � ����������
  CTransceiver_Autorization cTransceiver_Autorization;//�����-���������� ������ �����������

 public:  
  //�����������
  CThreadClient(void);
  //����������
  ~CThreadClient();
   void Start(void);//��������� �����
   void Stop(void);//���������� �����
   void SetDocument(CDocument_Main *cDocument_Main_Set_Ptr);//������ ����� ���������
 protected:
  void SaveTaskVector(char *filename,const vector<CTask> &vector_CTask);//���������� ������� �������
  void Processing(void);//�������� ���� ���������
  bool LinkProcessing(SOCKET socket_server,bool &on_exit);//��������� ������ � ��������
  bool TaskProcessing(SOCKET socket_server,bool &on_exit);//��������� �������
  bool ProjectProcessing(SOCKET socket_server,bool &on_exit);//��������� ��������
  bool PingProcessing(SOCKET socket_server,bool &on_exit);//��������� ��������� �������� �����

  bool ExecuteCommand_GetClientProgrammCRC(SOCKET socket_server,bool &on_exit);//���������� ������� ������� ����������� ����� ��������� �� �������
  bool ExecuteCommand_GetClientProgrammAndLoader(SOCKET socket_server,bool &on_exit);//���������� ������� ������� ��������� � ����������

  bool ExecuteCommand_Autorization(SOCKET socket_server,bool &on_exit);//���������� ������� �����������
  bool ExecuteCommand_GetUserBook(SOCKET socket_server,bool &on_exit);//���������� ������� ������� ���� �������������
  bool ExecuteCommand_GetTaskBook(SOCKET socket_server,bool &on_exit);//���������� ������� ������� ���� �������
  bool ExecuteCommand_GetProjectBook(SOCKET socket_server,bool &on_exit);//���������� ������� ������� ���� ��������

  void NewDataFromServer(SOCKET socket_server,char *data,unsigned long length,bool &on_exit);//������� ������ �� �������
  void ExecuteAnswer_ClientProgrammCRC(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ����������� ����� ���������� ��������� �� �������
  void ExecuteAnswer_ClientProgrammAndLoader(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ���������� ��������� � ���������� � ���������� ����������
  void ExecuteAnswer_GetUserBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ���� �����������
  void ExecuteAnswer_GetTaskBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ���� �������
  void ExecuteAnswer_GetProjectBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ���� ��������
  void ExecuteAnswer_Ok(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��
  void ExecuteAnswer_AutorizationOk(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ����������� �������
  void ExecuteAnswer_Error(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ������
  void ExecuteAnswer_GetDeletedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ��������� ����������
  void ExecuteAnswer_GetAddedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ������������ ����������
  void ExecuteAnswer_GetChangedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ���������� ����������

  void ExecuteAnswer_GetDeletedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ��������� �������
  void ExecuteAnswer_GetAddedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ������������ �������
  void ExecuteAnswer_GetChangedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ���������� �������

  void ExecuteAnswer_GetDeletedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ��������� �������
  void ExecuteAnswer_GetAddedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ������������ �������
  void ExecuteAnswer_GetChangedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit);//��������� ������: ��������� ������ ���������� �������

  bool ConnectAsServer(SOCKET &server,CSafeString host_name,long port,bool &on_exit);//����������� � �������
  bool SetSocketNoBlockMode(SOCKET socket_set,bool state);//������� �������������� ������ ��� ������
};

#endif