#ifndef CTRANSCEIVER_USER_H
#define CTRANSCEIVER_USER_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-����������� ������ �������������

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
//����� �����-����������� ������ �������������
//====================================================================================================

class CTransceiver_User:public CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver_User(void);
  //����������
  ~CTransceiver_User();
  //������� ������
  bool ReadCUserInArray(char *ptr,size_t &offset,size_t max_length,CUser &cUser);//��������� ���������� �� ������� �������� ������
  bool GetUserBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ ���� ������ �������������
  bool GetUserAnswer(char *ptr,size_t size,CUser &cUser);//������� ������������ �� ������ �������
};

#endif
