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
 if (offset+sizeof(SServerAnswer::STaskDataHeader)>max_length) return(false);
 SServerAnswer::STaskDataHeader *sServerAnswer_sTaskDataHeader_Ptr=reinterpret_cast<SServerAnswer::STaskDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::STaskDataHeader);
 long length=offset;
 length+=sServerAnswer_sTaskDataHeader_Ptr->ForUserGUIDSize;
 length+=sServerAnswer_sTaskDataHeader_Ptr->FromUserGUIDSize;
 length+=sServerAnswer_sTaskDataHeader_Ptr->ProjectGUIDSize;
 length+=sServerAnswer_sTaskDataHeader_Ptr->TaskGUIDSize;
 length+=sServerAnswer_sTaskDataHeader_Ptr->TaskSize;
 length+=sServerAnswer_sTaskDataHeader_Ptr->AnswerSize;
 if (length>max_length) return(false);

 sTask.Year=sServerAnswer_sTaskDataHeader_Ptr->Year;
 sTask.Month=sServerAnswer_sTaskDataHeader_Ptr->Month;
 sTask.Day=sServerAnswer_sTaskDataHeader_Ptr->Day;
 sTask.State=sServerAnswer_sTaskDataHeader_Ptr->State;
 sTask.Index=sServerAnswer_sTaskDataHeader_Ptr->Index;

 SetString(sTask.FromUserGUID,ptr+offset,sServerAnswer_sTaskDataHeader_Ptr->FromUserGUIDSize);
 offset+=sServerAnswer_sTaskDataHeader_Ptr->FromUserGUIDSize;

 SetString(sTask.ForUserGUID,ptr+offset,sServerAnswer_sTaskDataHeader_Ptr->ForUserGUIDSize);
 offset+=sServerAnswer_sTaskDataHeader_Ptr->ForUserGUIDSize;

 SetString(sTask.ProjectGUID,ptr+offset,sServerAnswer_sTaskDataHeader_Ptr->ProjectGUIDSize);
 offset+=sServerAnswer_sTaskDataHeader_Ptr->ProjectGUIDSize;

 SetString(sTask.Task,ptr+offset,sServerAnswer_sTaskDataHeader_Ptr->TaskSize);
 offset+=sServerAnswer_sTaskDataHeader_Ptr->TaskSize;

 SetString(sTask.TaskGUID,ptr+offset,sServerAnswer_sTaskDataHeader_Ptr->TaskGUIDSize);
 offset+=sServerAnswer_sTaskDataHeader_Ptr->TaskGUIDSize;

 SetString(sTask.Answer,ptr+offset,sServerAnswer_sTaskDataHeader_Ptr->AnswerSize);
 offset+=sServerAnswer_sTaskDataHeader_Ptr->AnswerSize;
 return(true); 
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные задания
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::SendTaskDataToServer(SOCKET socket_server,const STask &sTask,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::STaskDataHeader sServerCommand_sTaskDataHeader;
 sServerCommand_sTaskDataHeader.FromUserGUIDSize=sTask.FromUserGUID.GetLength();
 sServerCommand_sTaskDataHeader.ForUserGUIDSize=sTask.ForUserGUID.GetLength();
 sServerCommand_sTaskDataHeader.ProjectGUIDSize=sTask.ProjectGUID.GetLength();
 sServerCommand_sTaskDataHeader.TaskSize=sTask.Task.GetLength();
 sServerCommand_sTaskDataHeader.TaskGUIDSize=sTask.TaskGUID.GetLength();
 sServerCommand_sTaskDataHeader.AnswerSize=sTask.Answer.GetLength();
 sServerCommand_sTaskDataHeader.Year=sTask.Year;
 sServerCommand_sTaskDataHeader.Month=sTask.Month;
 sServerCommand_sTaskDataHeader.Day=sTask.Day;
 sServerCommand_sTaskDataHeader.State=sTask.State;
 sServerCommand_sTaskDataHeader.Index=sTask.Index;
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_sTaskDataHeader),sizeof(SServerCommand::STaskDataHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.FromUserGUID,sTask.FromUserGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.ForUserGUID,sTask.ForUserGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.ProjectGUID,sTask.ProjectGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.Task,sTask.Task.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,sTask.TaskGUID,sTask.TaskGUID.GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendPart(socket_server,sTask.Answer,sTask.Answer.GetLength(),cEvent_Exit,on_exit));
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
