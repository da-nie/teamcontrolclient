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



//====================================================================================================
//����� �����-����������� ������ �������
//====================================================================================================

class CTransceiver_Task:public CTransceiver
{
 protected:
  unsigned long Version;//����� ������ ���������
 public:  
  //�����������
  CTransceiver_Task(void);
  //����������
  ~CTransceiver_Task();
  //������� ������
  bool ReadCTaskInArray(char *ptr,size_t &offset,size_t max_length,CTask &cTask);//��������� ������� �� ������� �������� ������
  bool SendTaskDataToServer(SOCKET socket_server,const CTask &cTask,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ������ �������
  bool SendTaskDataToServerInPackage(SOCKET socket_server,const CTask &cTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ������ ������� � ���� ������� ������
  bool GetTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ ���� ������ �������
  bool GetCommonTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ ���� ������ ����� �������
  bool GetTaskAnswer(char *ptr,size_t size,CTask &cTask);//������� ������ �� ������ �������
};

#endif
