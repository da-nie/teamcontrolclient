#include "ctransceiver_user.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_User::CTransceiver_User(void)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTransceiver_User::~CTransceiver_User()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//получение сотрудника из массива принятых данных
//----------------------------------------------------------------------------------------------------
bool CTransceiver_User::ReadSUserInArray(char *ptr,size_t &offset,size_t max_length,SUser &sUser)
{
 if (offset+sizeof(SServerAnswer::SUserDataHeader)>max_length) return(false);
 SServerAnswer::SUserDataHeader *sServerAnswer_sUserDataHeader_Ptr=reinterpret_cast<SServerAnswer::SUserDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::SUserDataHeader);
 long length=offset;
 length+=sServerAnswer_sUserDataHeader_Ptr->NameSize;
 length+=sServerAnswer_sUserDataHeader_Ptr->DescriptionSize;
 length+=sServerAnswer_sUserDataHeader_Ptr->JobTitleSize;
 length+=sServerAnswer_sUserDataHeader_Ptr->GUIDSize;
 length+=sServerAnswer_sUserDataHeader_Ptr->TelephoneSize;
 if (length>max_length) return(false);

 SetString(sUser.Name,ptr+offset,sServerAnswer_sUserDataHeader_Ptr->NameSize);
 offset+=sServerAnswer_sUserDataHeader_Ptr->NameSize;

 SetString(sUser.JobTitle,ptr+offset,sServerAnswer_sUserDataHeader_Ptr->JobTitleSize);
 offset+=sServerAnswer_sUserDataHeader_Ptr->JobTitleSize;

 SetString(sUser.Telephone,ptr+offset,sServerAnswer_sUserDataHeader_Ptr->TelephoneSize);
 offset+=sServerAnswer_sUserDataHeader_Ptr->TelephoneSize;

 SetString(sUser.Description,ptr+offset,sServerAnswer_sUserDataHeader_Ptr->DescriptionSize);
 offset+=sServerAnswer_sUserDataHeader_Ptr->DescriptionSize;

 SetString(sUser.UserGUID,ptr+offset,sServerAnswer_sUserDataHeader_Ptr->GUIDSize);
 offset+=sServerAnswer_sUserDataHeader_Ptr->GUIDSize;

 sUser.Leader=sServerAnswer_sUserDataHeader_Ptr->Leader;

 return(true); 
}
//----------------------------------------------------------------------------------------------------
//запрос базы данных пользователей
//----------------------------------------------------------------------------------------------------
bool CTransceiver_User::GetUserBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=SERVER_COMMAND_GET_USER_BOOK;
 //начинаем передачу пакета
 if (SendBeginPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sHeader),sizeof(SServerCommand::SHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendEndPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//считать пользователя из ответа сервера
//----------------------------------------------------------------------------------------------------
bool CTransceiver_User::GetUserAnswer(char *ptr,size_t size,SUser &sUser)
{
 size_t offset=0;
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 if (ReadSUserInArray(ptr,offset,size,sUser)==false) return(false);;
 return(true);
}