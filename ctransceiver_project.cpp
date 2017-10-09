#include "ctransceiver_project.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_Project::CTransceiver_Project(void)
{
 Version=1;
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
bool CTransceiver_Project::ReadCProjectInArray(char *ptr,size_t &offset,size_t max_length,CProject &cProject)
{
 if (offset+sizeof(SServerAnswer::CProjectDataHeader)>max_length) return(false);
 SServerAnswer::CProjectDataHeader *sServerAnswer_cProjectDataHeader_Ptr=reinterpret_cast<SServerAnswer::CProjectDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::CProjectDataHeader);

 if (sServerAnswer_cProjectDataHeader_Ptr->Signature[0]!='P' || sServerAnswer_cProjectDataHeader_Ptr->Signature[1]!='L' || sServerAnswer_cProjectDataHeader_Ptr->Signature[2]!='V') return(false);
 if (sServerAnswer_cProjectDataHeader_Ptr->Version!=Version) return(false);

 long length=offset;
 length+=sServerAnswer_cProjectDataHeader_Ptr->ProjectNameSize;
 length+=sServerAnswer_cProjectDataHeader_Ptr->ProjectGUIDSize;
 if (length>max_length) return(false);

 CSafeString str;
 SetString(str,ptr+offset,sServerAnswer_cProjectDataHeader_Ptr->ProjectNameSize);
 cProject.SetProjectName(str);
 offset+=sServerAnswer_cProjectDataHeader_Ptr->ProjectNameSize;

 SetString(str,ptr+offset,sServerAnswer_cProjectDataHeader_Ptr->ProjectGUIDSize);
 cProject.SetProjectGUID(str);
 offset+=sServerAnswer_cProjectDataHeader_Ptr->ProjectGUIDSize;
 return(true); 
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные проекта
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::SendProjectDataToServer(SOCKET socket_server,const CProject &cProject,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::CProjectDataHeader sServerCommand_cProjectDataHeader;
 sServerCommand_cProjectDataHeader.ProjectNameSize=cProject.GetProjectName().GetLength();
 sServerCommand_cProjectDataHeader.ProjectGUIDSize=cProject.GetProjectGUID().GetLength();
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_cProjectDataHeader),sizeof(SServerCommand::CProjectDataHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,cProject.GetProjectName(),cProject.GetProjectName().GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendPart(socket_server,cProject.GetProjectGUID(),cProject.GetProjectGUID().GetLength(),cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные проекта в виде полного пакета
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Project::SendProjectDataToServerInPackage(SOCKET socket_server,const CProject &cProject,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit)
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
 if (SendProjectDataToServer(socket_server,cProject,cEvent_Exit,on_exit)==false) return(false);
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
bool CTransceiver_Project::GetProjectAnswer(char *ptr,size_t size,CProject &cProject)
{
 size_t offset=0;
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 if (ReadCProjectInArray(ptr,offset,size,cProject)==false) return(false);;
 return(true);
}
