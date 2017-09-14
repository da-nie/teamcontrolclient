#include "ctransceiver.h"

//====================================================================================================
//����������������
//====================================================================================================

//====================================================================================================
//����������� ������
//====================================================================================================
CTransceiver::CTransceiver(void)
{
}
//====================================================================================================
//���������� ������
//====================================================================================================
CTransceiver::~CTransceiver()
{ 
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//��������� ��� ������ ������
//----------------------------------------------------------------------------------------------------
bool CTransceiver::SendBeginPackage(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 char code=static_cast<unsigned char>(PROTOCOL_BEGIN_PACKAGE);
 return(SendData(socket_server,&code,1,cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//��������� ��� ����� ������
//----------------------------------------------------------------------------------------------------
bool CTransceiver::SendEndPackage(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 char code=static_cast<unsigned char>(PROTOCOL_END_PACKAGE);
 return(SendData(socket_server,&code,1,cEvent_Exit,on_exit));
}

//----------------------------------------------------------------------------------------------------
//��������� ������ �������
//----------------------------------------------------------------------------------------------------
bool CTransceiver::SendQuestion(SOCKET socket_server,SERVER_ANSWER answer,const char *data,unsigned long size,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 //���������� ������ ������
 if (SendBeginPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 //���������� ���������
 SServerAnswer::SHeader sServerAnswer_sHeader;
 sServerAnswer_sHeader.AnswerID=answer;
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerAnswer_sHeader),sizeof(sServerAnswer_sHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 //���������� ������
 if (data!=NULL)
 {
  if (SendPart(socket_server,data,size,cEvent_Exit,on_exit)==false) return(false);
  if (on_exit==true) return(true);
 }
 //��������� ��������
 return(SendEndPackage(socket_server,cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//��������� ������ ������� � ����������� �������������
//----------------------------------------------------------------------------------------------------
bool CTransceiver::SendPart(SOCKET socket_server,const char *data,unsigned long size,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 vector<unsigned char> vector_answer;
 vector_answer.reserve(size*2);
 //��������� ������ ������ � ������ �������������
 for(long n=0;n<size;n++)
 {
  unsigned char byte=data[n];
  if (byte==0x00)
  {
   vector_answer.push_back(static_cast<unsigned char>(PROTOCOL_STUFFING));
   vector_answer.push_back(static_cast<unsigned char>(PROTOCOL_STUFFING_00));
   continue;
  }
  if (byte==0xFE)
  {
   vector_answer.push_back(static_cast<unsigned char>(PROTOCOL_STUFFING));
   vector_answer.push_back(static_cast<unsigned char>(PROTOCOL_STUFFING_FE));
   continue;
  }
  if (byte==0xFF)
  {
   vector_answer.push_back(static_cast<unsigned char>(PROTOCOL_STUFFING));
   vector_answer.push_back(static_cast<unsigned char>(PROTOCOL_STUFFING_FF));
   continue;
  }
  vector_answer.push_back(byte);
 }
 const char *ptr=reinterpret_cast<char*>(&vector_answer[0]);
 return(SendData(socket_server,ptr,vector_answer.size(),cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//��������� ������ �������
//----------------------------------------------------------------------------------------------------
bool CTransceiver::SendData(SOCKET socket_server,const char *package,long size,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 long offset=0;
 while(size>0)
 {
  if (WaitForSingleObject(cEvent_Exit.m_hObject,0)==WAIT_OBJECT_0)
  {
   on_exit=true;
   return(true);
  }
  //������ ��� ���� � ����� �������
  fd_set Writen;
  FD_ZERO(&Writen);//�������� ������
  FD_SET(socket_server,&Writen);//��������� �����
  fd_set Exeption;
  FD_ZERO(&Exeption);//�������� ������
  FD_SET(socket_server,&Exeption);//��������� �����
  timeval timeout;
  timeout.tv_sec=0;
  timeout.tv_usec=5000;
  //����������, �� ����� �� ����� ���������� ������
  if (select(0,0,&Writen,&Exeption,&timeout)>0)
  {
   if (FD_ISSET(socket_server,&Exeption))
   {
    on_exit=true;
	return(false);
   }
   if (FD_ISSET(socket_server,&Writen))
   {
    long ret=send(socket_server,package+offset,size,0);
	if (ret==SOCKET_ERROR)
	{
     int error_code=WSAGetLastError();
     if (error_code==WSAEWOULDBLOCK)//���� ���������
     {
      Pause(1);
      continue;
     }
     on_exit=true;
     return(false);
	}
    size-=ret;
    offset+=ret;	
   }
  }
  else
  {
   continue;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//����� � �������������
//----------------------------------------------------------------------------------------------------
void CTransceiver::Pause(long time_ms)
{
 CEvent cEvent;
 cEvent.ResetEvent();
 WaitForSingleObject(cEvent.m_hObject,time_ms); 
}
//----------------------------------------------------------------------------------------------------
//������ ������ �� �������
//----------------------------------------------------------------------------------------------------
void CTransceiver::SetString(CSafeString &text,char *buffer,long length)
{
 text="";
 for(long n=0;n<length;n++) text+=buffer[n];
}