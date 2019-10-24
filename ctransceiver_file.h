#ifndef CTRANSCEIVER_FILE_H
#define CTRANSCEIVER_FILE_H

//====================================================================================================
//��������
//====================================================================================================

//����� �����-����������� ������

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
//����� �����-����������� ������
//====================================================================================================

class CTransceiver_File:public CTransceiver
{
 protected:
 public:  
  //�����������
  CTransceiver_File(void);
  //����������
  ~CTransceiver_File();
  //������� ������
  bool GetClientProgrammCRC(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ CRC ���������
  bool GetClientProgrammAndLoader(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit);//������ ��������� � ����������
  bool ReadCRCInArray(char *ptr,size_t &offset,size_t max_length,unsigned long &crc16);//������� CRC �� ������ �������
  bool ReadClientProgrammAndLoaderInArray(char *ptr,size_t &offset,size_t max_length);//������� � �������� ��������� �� ������ �������
 protected:
  bool SaveFileAndCompareCRC(char *ptr,size_t size,const CSafeString &file_name,unsigned long original_crc16);//��������� ���� � �������� ��� CRC

};

#endif
