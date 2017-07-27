#include "ctransceiver_task.h"

//====================================================================================================
//макроопределения
//====================================================================================================

//====================================================================================================
//конструктор класса
//====================================================================================================
CTransceiver_Task::CTransceiver_Task(void)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTransceiver_Task::~CTransceiver_Task()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//получение задания из массива принятых данных
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::ReadSTaskInArray(char *ptr,size_t &offset,size_t max_length,STask &sTask)
{
 if (offset+sizeof(SServerCommand::STaskDataHeader)>max_length) return(false);
 SServerCommand::STaskDataHeader *sServerCommand_sTaskDataHeader_Ptr=reinterpret_cast<SServerCommand::STaskDataHeader*>(ptr+offset);
 offset+=sizeof(SServerCommand::STaskDataHeader);
 long length=offset;
 length+=sServerCommand_sTaskDataHeader_Ptr->ForUserGUIDSize;
 length+=sServerCommand_sTaskDataHeader_Ptr->FromUserGUIDSize;
 length+=sServerCommand_sTaskDataHeader_Ptr->ProjectGUIDSize;
 length+=sServerCommand_sTaskDataHeader_Ptr->TaskGUIDSize;
 length+=sServerCommand_sTaskDataHeader_Ptr->TaskSize;
 if (length>max_length) return(false);

 sTask.Year=sServerCommand_sTaskDataHeader_Ptr->Year;
 sTask.Month=sServerCommand_sTaskDataHeader_Ptr->Month;
 sTask.Day=sServerCommand_sTaskDataHeader_Ptr->Day;
 sTask.State=sServerCommand_sTaskDataHeader_Ptr->State;

 SetString(sTask.FromUserGUID,ptr+offset,sServerCommand_sTaskDataHeader_Ptr->FromUserGUIDSize);
 offset+=sServerCommand_sTaskDataHeader_Ptr->FromUserGUIDSize;

 SetString(sTask.ForUserGUID,ptr+offset,sServerCommand_sTaskDataHeader_Ptr->ForUserGUIDSize);
 offset+=sServerCommand_sTaskDataHeader_Ptr->ForUserGUIDSize;

 SetString(sTask.ProjectGUID,ptr+offset,sServerCommand_sTaskDataHeader_Ptr->ProjectGUIDSize);
 offset+=sServerCommand_sTaskDataHeader_Ptr->ProjectGUIDSize;

 SetString(sTask.Task,ptr+offset,sServerCommand_sTaskDataHeader_Ptr->TaskSize);
 offset+=sServerCommand_sTaskDataHeader_Ptr->TaskSize;

 SetString(sTask.TaskGUID,ptr+offset,sServerCommand_sTaskDataHeader_Ptr->TaskGUIDSize);
 offset+=sServerCommand_sTaskDataHeader_Ptr->TaskGUIDSize;
 return(true); 
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные задания
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::SendTaskDataToServer(SOCKET socket_server,const STask &sTask,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerAnswer::STaskDataHeader sServerAnswer_sTaskDataHeader;
 sServerAnswer_sTaskDataHeader.FromUserGUIDSize=sTask.FromUserGUID.GetLength();
 sServerAnswer_sTaskDataHeader.ForUserGUIDSize=sTask.ForUserGUID.GetLength();
 sServerAnswer_sTaskDataHeader.ProjectGUIDSize=sTask.ProjectGUID.GetLength();
 sServerAnswer_sTaskDataHeader.TaskSize=sTask.Task.GetLength();
 sServerAnswer_sTaskDataHeader.TaskGUIDSize=sTask.TaskGUID.GetLength();
 sServerAnswer_sTaskDataHeader.Year=sTask.Year;
 sServerAnswer_sTaskDataHeader.Month=sTask.Month;
 sServerAnswer_sTaskDataHeader.Day=sTask.Day;
 sServerAnswer_sTaskDataHeader.State=sTask.State;
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerAnswer_sTaskDataHeader),sizeof(SServerAnswer::STaskDataHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.FromUserGUID,sTask.FromUserGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.ForUserGUID,sTask.ForUserGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.ProjectGUID,sTask.ProjectGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.Task,sTask.Task.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendPart(socket_server,sTask.TaskGUID,sTask.TaskGUID.GetLength(),cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные задания в виде полного пакета
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::SendTaskDataToServerInPackage(SOCKET socket_server,const STask &sTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit)
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
 if (SendTaskDataToServer(socket_server,sTask,cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendEndPackage(socket_server,cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//запрос базы данных заданий
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::GetTaskBook(SOCKET socket_server,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::SHeader sServerCommand_sHeader;
 sServerCommand_sHeader.CommandID=SERVER_COMMAND_GET_TASK_BOOK;
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
//считать задачу из ответа сервера
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::GetTaskAnswer(char *ptr,size_t size,STask &sTask)
{
 size_t offset=0;
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 if (ReadSTaskInArray(ptr,offset,size,sTask)==false) return(false);;
 return(true);
}
