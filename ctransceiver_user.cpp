#include "ctransceiver_user.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_User::CTransceiver_User(void)
{
 Version=1;
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
bool CTransceiver_User::ReadCUserInArray(char *ptr,size_t &offset,size_t max_length,CUser &cUser)
{
 if (offset+sizeof(SServerAnswer::CUserDataHeader)>max_length) return(false);
 SServerAnswer::CUserDataHeader *sServerAnswer_cUserDataHeader_Ptr=reinterpret_cast<SServerAnswer::CUserDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::CUserDataHeader);

 if (sServerAnswer_cUserDataHeader_Ptr->Signature[0]!='U' || sServerAnswer_cUserDataHeader_Ptr->Signature[1]!='L' || sServerAnswer_cUserDataHeader_Ptr->Signature[2]!='V') return(false);
 if (sServerAnswer_cUserDataHeader_Ptr->Version!=Version) return(false);

 long length=offset;
 length+=sServerAnswer_cUserDataHeader_Ptr->NameSize;
 length+=sServerAnswer_cUserDataHeader_Ptr->DescriptionSize;
 length+=sServerAnswer_cUserDataHeader_Ptr->JobTitleSize;
 length+=sServerAnswer_cUserDataHeader_Ptr->GUIDSize;
 length+=sServerAnswer_cUserDataHeader_Ptr->TelephoneSize;
 if (length>max_length) return(false);

 CSafeString str;
 SetString(str,ptr+offset,sServerAnswer_cUserDataHeader_Ptr->NameSize);
 cUser.SetName(str);
 offset+=sServerAnswer_cUserDataHeader_Ptr->NameSize;

 SetString(str,ptr+offset,sServerAnswer_cUserDataHeader_Ptr->JobTitleSize);
 cUser.SetJobTitle(str);
 offset+=sServerAnswer_cUserDataHeader_Ptr->JobTitleSize;

 SetString(str,ptr+offset,sServerAnswer_cUserDataHeader_Ptr->TelephoneSize);
 cUser.SetTelephone(str);
 offset+=sServerAnswer_cUserDataHeader_Ptr->TelephoneSize;

 SetString(str,ptr+offset,sServerAnswer_cUserDataHeader_Ptr->DescriptionSize);
 cUser.SetDescription(str);
 offset+=sServerAnswer_cUserDataHeader_Ptr->DescriptionSize;

 SetString(str,ptr+offset,sServerAnswer_cUserDataHeader_Ptr->GUIDSize);
 cUser.SetUserGUID(str);
 offset+=sServerAnswer_cUserDataHeader_Ptr->GUIDSize;

 cUser.SetLeader(sServerAnswer_cUserDataHeader_Ptr->Leader);

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
bool CTransceiver_User::GetUserAnswer(char *ptr,size_t size,CUser &cUser)
{
 size_t offset=0;
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 if (ReadCUserInArray(ptr,offset,size,cUser)==false) return(false);;
 return(true);
}