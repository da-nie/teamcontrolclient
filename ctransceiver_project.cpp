#include "ctransceiver_project.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_Project::CTransceiver_Project(void)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTransceiver_Project::~CTransceiver_Project()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//получение проекта из массива принятых данных
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::ReadSProjectInArray(char *ptr,size_t &offset,size_t max_length,SProject &sProject)
{
 if (offset+sizeof(SServerCommand::SProjectDataHeader)>max_length) return(false);
 SServerCommand::SProjectDataHeader *sServerCommand_sProjectDataHeader_Ptr=reinterpret_cast<SServerCommand::SProjectDataHeader*>(ptr+offset);
 offset+=sizeof(SServerCommand::SProjectDataHeader);
 long length=offset;
 length+=sServerCommand_sProjectDataHeader_Ptr->ProjectNameSize;
 length+=sServerCommand_sProjectDataHeader_Ptr->ProjectGUIDSize;
 if (length>max_length) return(false);

 SetString(sProject.ProjectName,ptr+offset,sServerCommand_sProjectDataHeader_Ptr->ProjectNameSize);
 offset+=sServerCommand_sProjectDataHeader_Ptr->ProjectNameSize;

 SetString(sProject.ProjectGUID,ptr+offset,sServerCommand_sProjectDataHeader_Ptr->ProjectGUIDSize);
 offset+=sServerCommand_sProjectDataHeader_Ptr->ProjectGUIDSize;
 return(true); 
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные проекта
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::SendProjectDataToServer(SOCKET socket_server,const SProject &sProject,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerAnswer::SProjectDataHeader sServerAnswer_sProjectDataHeader;
 sServerAnswer_sProjectDataHeader.ProjectNameSize=sProject.ProjectName.GetLength();
 sServerAnswer_sProjectDataHeader.ProjectGUIDSize=sProject.ProjectGUID.GetLength();
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerAnswer_sProjectDataHeader),sizeof(SServerAnswer::SProjectDataHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sProject.ProjectName,sProject.ProjectName.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendPart(socket_server,sProject.ProjectGUID,sProject.ProjectGUID.GetLength(),cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные проекта в виде полного пакета
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::SendProjectDataToServerInPackage(SOCKET socket_server,const SProject &sProject,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 //передаём данные
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=command;
 //начинаем передачу пакета
 if (SendBeginPackage(socket_server,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sHeader),sizeof(SServerCommand::SHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendProjectDataToServer(socket_server,sProject,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendEndPackage(socket_server,cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//запрос базы данных заданий
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::GetProjectBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=SERVER_COMMAND_GET_PROJECT_BOOK;
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
//считать проект из ответа сервера
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::GetProjectAnswer(char *ptr,size_t size,SProject &sProject)
{
 size_t offset=0;
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 if (ReadSProjectInArray(ptr,offset,size,sProject)==false) return(false);;
 return(true);
}
