#include "ctransceiver_ping.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_Ping::CTransceiver_Ping(void)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTransceiver_Ping::~CTransceiver_Ping()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//передать серверу сообщение для проверки связи
//----------------------------------------------------------------------------------------------------
void CTransceiver_Ping::SendPingDataToServerInPackage(SOCKET socket_server,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SendBeginPackage(socket_server,cEvent_Exit,on_exit);
 if (on_exit==true) return;
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=command;
 SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sHeader),sizeof(SServerCommand::SHeader),cEvent_Exit,on_exit);
 if (on_exit==true) return;
 SServerCommand::SPingDataHeader sServerCommand_sPingDataHeader;
 sServerCommand_sPingDataHeader.PingData[0]='T';
 sServerCommand_sPingDataHeader.PingData[1]='E';
 sServerCommand_sPingDataHeader.PingData[2]='S';
 sServerCommand_sPingDataHeader.PingData[3]='T';
 sServerCommand_sPingDataHeader.PingData[4]=' ';
 sServerCommand_sPingDataHeader.PingData[5]='T';
 sServerCommand_sPingDataHeader.PingData[6]='E';
 sServerCommand_sPingDataHeader.PingData[7]='S';
 sServerCommand_sPingDataHeader.PingData[8]='T';
 sServerCommand_sPingDataHeader.PingData[9]=0;
 SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sPingDataHeader),sizeof(SServerCommand::SPingDataHeader),cEvent_Exit,on_exit);
 if (on_exit==true) return;
 SendEndPackage(socket_server,cEvent_Exit,on_exit);
}
