#ifndef CTRANSCEIVER_TASK_H
#define CTRANSCEIVER_TASK_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-����������� ������ �������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include <list>
#include <vector>
#include <string>
#include "cdocument_main.h"
#include "protocol.h"
#include "ctransceiver.h"

using namespace std;

//====================================================================================================
//����� �����-����������� ������ �������
//====================================================================================================

class CTransceiver_Task:public CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver_Task(void);
  //����������
  ~CTransceiver_Task();
  //������� ������
  bool ReadSTaskInArray(char *ptr,size_t &offset,size_t max_length,STask &sTask);//��������� ������� �� ������� �������� ������
  bool SendTaskDataToServer(SOCKET socket_server,const STask &sTask,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ������ �������
  bool SendTaskDataToServerInPackage(SOCKET socket_server,const STask &sTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ������ ������� � ���� ������� ������
  bool GetTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ ���� ������ �������
  bool GetTaskAnswer(char *ptr,size_t size,STask &sTask);//������� ������ �� ������ �������
};

#endif
