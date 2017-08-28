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
bool CTransceiver_Task::ReadCTaskInArray(char *ptr,size_t &offset,size_t max_length,CTask &cTask)
{
 if (offset+sizeof(SServerAnswer::CTaskDataHeader)>max_length) return(false);
 SServerAnswer::CTaskDataHeader *sServerAnswer_cTaskDataHeader_Ptr=reinterpret_cast<SServerAnswer::CTaskDataHeader*>(ptr+offset);
 offset+=sizeof(SServerAnswer::CTaskDataHeader);
 long length=offset;
 length+=sServerAnswer_cTaskDataHeader_Ptr->ForUserGUIDSize;
 length+=sServerAnswer_cTaskDataHeader_Ptr->FromUserGUIDSize;
 length+=sServerAnswer_cTaskDataHeader_Ptr->ProjectGUIDSize;
 length+=sServerAnswer_cTaskDataHeader_Ptr->TaskGUIDSize;
 length+=sServerAnswer_cTaskDataHeader_Ptr->TaskSize;
 length+=sServerAnswer_cTaskDataHeader_Ptr->AnswerSize;
 if (length>max_length) return(false);

 cTask.SetDate(CDate(sServerAnswer_cTaskDataHeader_Ptr->Year,sServerAnswer_cTaskDataHeader_Ptr->Month,sServerAnswer_cTaskDataHeader_Ptr->Day)); 
 cTask.SetState(sServerAnswer_cTaskDataHeader_Ptr->State);
 cTask.SetIndex(sServerAnswer_cTaskDataHeader_Ptr->Index);

 CSafeString str;
 SetString(str,ptr+offset,sServerAnswer_cTaskDataHeader_Ptr->FromUserGUIDSize);
 cTask.SetFromUserGUID(str);
 offset+=sServerAnswer_cTaskDataHeader_Ptr->FromUserGUIDSize;

 SetString(str,ptr+offset,sServerAnswer_cTaskDataHeader_Ptr->ForUserGUIDSize);
 cTask.SetForUserGUID(str);
 offset+=sServerAnswer_cTaskDataHeader_Ptr->ForUserGUIDSize;

 SetString(str,ptr+offset,sServerAnswer_cTaskDataHeader_Ptr->ProjectGUIDSize);
 cTask.SetProjectGUID(str);
 offset+=sServerAnswer_cTaskDataHeader_Ptr->ProjectGUIDSize;

 SetString(str,ptr+offset,sServerAnswer_cTaskDataHeader_Ptr->TaskSize);
 cTask.SetTask(str);
 offset+=sServerAnswer_cTaskDataHeader_Ptr->TaskSize;

 SetString(str,ptr+offset,sServerAnswer_cTaskDataHeader_Ptr->TaskGUIDSize);
 cTask.SetTaskGUID(str);
 offset+=sServerAnswer_cTaskDataHeader_Ptr->TaskGUIDSize;

 SetString(str,ptr+offset,sServerAnswer_cTaskDataHeader_Ptr->AnswerSize);
 cTask.SetAnswer(str);
 offset+=sServerAnswer_cTaskDataHeader_Ptr->AnswerSize;

 return(true); 
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные задания
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::SendTaskDataToServer(SOCKET socket_server,const CTask &cTask,CEvent &cEvent_Exit,bool &on_exit)
{
 on_exit=false;
 SServerCommand::CTaskDataHeader sServerCommand_cTaskDataHeader;
 sServerCommand_cTaskDataHeader.FromUserGUIDSize=cTask.GetFromUserGUID().GetLength();
 sServerCommand_cTaskDataHeader.ForUserGUIDSize=cTask.GetForUserGUID().GetLength();
 sServerCommand_cTaskDataHeader.ProjectGUIDSize=cTask.GetProjectGUID().GetLength();
 sServerCommand_cTaskDataHeader.TaskSize=cTask.GetTask().GetLength();
 sServerCommand_cTaskDataHeader.TaskGUIDSize=cTask.GetTaskGUID().GetLength();
 sServerCommand_cTaskDataHeader.AnswerSize=cTask.GetAnswer().GetLength();
 const CDate& cDate=cTask.GetDate();
 sServerCommand_cTaskDataHeader.Year=cDate.GetYear();
 sServerCommand_cTaskDataHeader.Month=cDate.GetMonth();
 sServerCommand_cTaskDataHeader.Day=cDate.GetDay();
 sServerCommand_cTaskDataHeader.State=cTask.GetState();
 sServerCommand_cTaskDataHeader.Index=cTask.GetIndex();
 if (SendPart(socket_server,reinterpret_cast<char*>(&sServerCommand_cTaskDataHeader),sizeof(SServerCommand::CTaskDataHeader),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,cTask.GetFromUserGUID(),cTask.GetFromUserGUID().GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,cTask.GetForUserGUID(),cTask.GetForUserGUID().GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,cTask.GetProjectGUID(),cTask.GetProjectGUID().GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,cTask.GetTask(),cTask.GetTask().GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 if (SendPart(socket_server,cTask.GetTaskGUID(),cTask.GetTaskGUID().GetLength(),cEvent_Exit,on_exit)==false) return(false);
 if (on_exit==true) return(true);
 return(SendPart(socket_server,cTask.GetAnswer(),cTask.GetAnswer().GetLength(),cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//передать серверу данные задания в виде полного пакета
//----------------------------------------------------------------------------------------------------
bool CTransceiver_Task::SendTaskDataToServerInPackage(SOCKET socket_server,const CTask &cTask,SERVER_COMMAND command,CEvent &cEvent_Exit,bool &on_exit)
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
 if (SendTaskDataToServer(socket_server,cTask,cEvent_Exit,on_exit)==false) return(false);
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
bool CTransceiver_Task::GetTaskAnswer(char *ptr,size_t size,CTask &cTask)
{
 size_t offset=0;
 if (sizeof(SServerAnswer::SHeader)>size) return(false);
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 if (ReadCTaskInArray(ptr,offset,size,cTask)==false) return(false);;
 return(true);
}
