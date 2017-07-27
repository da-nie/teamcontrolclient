#ifndef CTRANSCEIVER_PROJECT_H
#define CTRANSCEIVER_PROJECT_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-����������� ������ ��������

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
//����� �����-����������� ������ ��������
//====================================================================================================

class CTransceiver_Project:public CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver_Project(void);
  //����������
  ~CTransceiver_Project();
  //������� ������
  bool ReadSProjectInArray(char *ptr,size_t &offset,size_t max_length,SProject &sProject);//��������� ������� �� ������� �������� ������
  bool SendProjectDataToServer(SOCKET socket_server,const SProject &sProject,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ������ �������
  bool SendProjectDataToServerInPackage(SOCKET socket_server,const SProject &sProject,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ������ ������� � ���� ������� ������
  bool GetProjectBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ ���� ������ �������
  bool GetProjectAnswer(char *ptr,size_t size,SProject &sProject);//������� ������ �� ������ �������
};

#endif
