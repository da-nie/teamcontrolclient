#ifndef CTRANSCEIVER_PING_H
#define CTRANSCEIVER_PING_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-����������� ������ ��������� ��� �������� �����

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
//����� �����-����������� ������ ��������� ��� �������� �����
//====================================================================================================

class CTransceiver_Ping:public CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver_Ping(void);
  //����������
  ~CTransceiver_Ping();
  //������� ������
  void SendPingDataToServerInPackage(SOCKET socket_server,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit);//�������� ������� ��������� ��� �������� �����
};

#endif
