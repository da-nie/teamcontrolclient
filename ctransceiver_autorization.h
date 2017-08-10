#ifndef CTRANSCEIVER_AUTORIZATION_H
#define CTRANSCEIVER_AUTORIZATION_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-����������� ������ �����������

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
//����� �����-����������� ������ �����������
//====================================================================================================

class CTransceiver_Autorization:public CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver_Autorization(void);
  //����������
  ~CTransceiver_Autorization();
  //������� ������
  bool SendAutorization(SOCKET socket_server,const CSafeString &login,const CSafeString &password,CEvent &cEvent_Exit,bool &on_exit);//��������� ������ �����������
  bool GetAutorizationAnswer(char *ptr,size_t size,CSafeString &guid);//������� ��������� �����������
};

#endif
