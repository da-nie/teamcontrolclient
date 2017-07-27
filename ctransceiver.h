#ifndef CTRANSCEIVER_H
#define CTRANSCEIVER_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-�����������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include <list>
#include <vector>
#include <string>
#include "cdocument_main.h"
#include "protocol.h"

using namespace std;
//====================================================================================================
//����� �����-�����������
//====================================================================================================

class CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver(void);
  //����������
  ~CTransceiver();
 protected:
  bool SendBeginPackage(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//��������� ��� ������ ������
  bool SendEndPackage(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//��������� ��� ����� ������
  bool SendQuestion(SOCKET socket_server,SERVER_ANSWER answer,const char *data,unsigned long size,CEvent &cEvent_Exit,bool &on_exit);//��������� ������ �������
  bool SendPart(SOCKET socket_server,const char *data,unsigned long size,CEvent &cEvent_Exit,bool &on_exit);//��������� ������ ������� � ����������� �������������
  bool SendData(SOCKET socket_server,const char *package,long size,CEvent &cEvent_Exit,bool &on_exit);//��������� ������ �������
  void Pause(long time_ms);//�����
  void SetString(CString &text,char *buffer,long length);//������ ������ �� �������
};

#endif



