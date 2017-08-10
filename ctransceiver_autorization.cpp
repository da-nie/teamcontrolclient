#include "ctransceiver_autorization.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_Autorization::CTransceiver_Autorization(void)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTransceiver_Autorization::~CTransceiver_Autorization()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//отправить данные авторизации
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Autorization::SendAutorization(SOCKET socket_server,const CSafeString &login,const CSafeString &password,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::SHeader sServerCommand_sHeader;
 SServerCommand::SAutorizationDataHeader sServerCommand_sAutorizationDataHeader;
 sServerCommand_sHeader.CommandID=SERVER_COMMAND_AUTORIZATION;

 sServerCommand_sAutorizationDataHeader.LoginSize=login.GetLength();
 sServerCommand_sAutorizationDataHeader.PasswordSize=password.GetLength();
 //начинаем передачу пакета
 if (SendBeginPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sHeader),sizeof(SServerCommand::SHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sAutorizationDataHeader),sizeof(SServerCommand::SAutorizationDataHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,login,login.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,password,password.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendEndPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(true); 
}
//----------------------------------------------------------------------------------------------------
//считать результат авторизации
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Autorization::GetAutorizationAnswer(char *ptr,size_t size,CSafeString &guid)
{
 guid="";
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 offset+=sizeof(SServerAnswer::SHeader);
 SServerAnswer::SAutorizationDataHeader *sServerAnswer_sAutorizationDataHeader_Ptr=reinterpret_cast<SServerAnswer::SAutorizationDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::SAutorizationDataHeader);
 if (sServerAnswer_sAutorizationDataHeader_Ptr->UserGUIDSize+offset>size) return(false);
 SetString(guid,ptr+offset,sServerAnswer_sAutorizationDataHeader_Ptr->UserGUIDSize);
 return(true);
}
