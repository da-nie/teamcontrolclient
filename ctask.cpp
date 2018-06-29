#include "ctask.h"
#include "crc.h"
#include "cuniquearrayptr.h"

//====================================================================================================
//конструктор класса
//====================================================================================================
CTask::CTask(void)
{
 Index=0;
 ForUserGUID="";
 FromUserGUID="";
 ProjectGUID="";
 TaskGUID="";
 Task="";
 State=TASK_STATE_NO_READ;
 cDate.SetDate(0,0,0);
 Answer="";
 AnswerNotRead=false;
 PlannedPosition=false;
 AnswerReferenceExist=false;
 TaskReferenceExist=false;
 Common=true;
 AnswerReference="";
 TaskReference="";
 Project="";
 FromUser="";
 ForUser="";
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTask::~CTask()
{		
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//получиь индекс
//----------------------------------------------------------------------------------------------------
const long& CTask::GetIndex(void) const
{
 return(Index);
}
//----------------------------------------------------------------------------------------------------
//получить уникальный идентификатор от какого пользователя задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetFromUserGUID(void) const
{
 return(FromUserGUID);
}
//----------------------------------------------------------------------------------------------------
//получить уникальный идентификатор для какого пользователя задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetForUserGUID(void) const
{
 return(ForUserGUID);
}
//----------------------------------------------------------------------------------------------------
//получить уникальный идентификатор проекта
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetProjectGUID(void) const
{
 return(ProjectGUID);
}
//----------------------------------------------------------------------------------------------------
//получить задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetTask(void) const
{
 return(Task);
}
//----------------------------------------------------------------------------------------------------
//получить срок задания
//----------------------------------------------------------------------------------------------------
const CDate& CTask::GetDate(void) const
{
 return(cDate);
}
//----------------------------------------------------------------------------------------------------
//получить уникальный идентификатор задания
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetTaskGUID(void) const
{
 return(TaskGUID);
}
//----------------------------------------------------------------------------------------------------
//получить ответ на задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetAnswer(void) const
{
 return(Answer);
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на файл в ответе исполнителя
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetAnswerReference(void) const
{
 return(AnswerReference);
}
//----------------------------------------------------------------------------------------------------
//задать ссылку на файл в задании
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetTaskReference(void) const
{
 return(TaskReference);
}

//----------------------------------------------------------------------------------------------------
//получить, изменились ли данные задания
//----------------------------------------------------------------------------------------------------
const bool& CTask::GetChangeData(void) const
{
 return(ChangeData);
}
//----------------------------------------------------------------------------------------------------
//получить имя пользователя для которого задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetForUser(void) const
{
 return(ForUser);
}
//----------------------------------------------------------------------------------------------------
//получить имя пользователя от которого задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetFromUser(void) const
{
 return(FromUser);
}
//----------------------------------------------------------------------------------------------------
//получить название проекта по которому задание
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetProject(void) const
{
 return(Project);
}
//----------------------------------------------------------------------------------------------------
//получить, прочитан ли ответ на задание
//----------------------------------------------------------------------------------------------------
bool CTask::GetAnswerNotRead(void) const
{
 return(AnswerNotRead);
}
//----------------------------------------------------------------------------------------------------
//получить, является ли задание плановой позицией
//----------------------------------------------------------------------------------------------------
bool CTask::GetPlannedPosition(void) const
{
 return(PlannedPosition);
}
//----------------------------------------------------------------------------------------------------
//получить, есть ли ссылка в ответе исполнителя
//----------------------------------------------------------------------------------------------------
bool CTask::GetAnswerReferenceExist(void) const
{
 return(AnswerReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//получить, есть ли ссылка в задании
//----------------------------------------------------------------------------------------------------
bool CTask::GetTaskReferenceExist(void) const
{
 return(TaskReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//получить, является ли задание обшим
//----------------------------------------------------------------------------------------------------
bool CTask::GetCommon(void) const
{
 return(Common);
}
//----------------------------------------------------------------------------------------------------
//задать индекс
//----------------------------------------------------------------------------------------------------
void CTask::SetIndex(const long& index)
{
 Index=index;
}
//----------------------------------------------------------------------------------------------------
//задать уникальный идентификатор от какого пользователя задание
//----------------------------------------------------------------------------------------------------
void CTask::SetFromUserGUID(const char *from_user_guid)
{
 FromUserGUID=from_user_guid;
}
//----------------------------------------------------------------------------------------------------
//задать уникальный идентификатор для какого пользователя задание
//----------------------------------------------------------------------------------------------------
void CTask::SetForUserGUID(const char *for_user_guid)
{
 ForUserGUID=for_user_guid;
}
//----------------------------------------------------------------------------------------------------
//задать уникальный идентификатор проекта
//----------------------------------------------------------------------------------------------------
void CTask::SetProjectGUID(const char *project_guid)
{
 ProjectGUID=project_guid;
}
//----------------------------------------------------------------------------------------------------
//задать задание
//----------------------------------------------------------------------------------------------------
void CTask::SetTask(const char *task)
{
 Task=task;
}
//----------------------------------------------------------------------------------------------------
//задать срок задания
//----------------------------------------------------------------------------------------------------
void CTask::SetDate(const CDate &cDate_Set)
{
 cDate=cDate_Set;
}
//----------------------------------------------------------------------------------------------------
//задать уникальный идентификатор задания
//----------------------------------------------------------------------------------------------------
void CTask::SetTaskGUID(const char *task_guid)
{
 TaskGUID=task_guid;
}
//----------------------------------------------------------------------------------------------------
//задать ответ на задание
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswer(const char *answer)
{
 Answer=answer;
}
//----------------------------------------------------------------------------------------------------
//задать ссылку на файл в ответе исполнителя
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswerReference(const char *reference)
{
 AnswerReference=reference;
}
//----------------------------------------------------------------------------------------------------
//задать ссылку на файл в задании
//----------------------------------------------------------------------------------------------------
void CTask::SetTaskReference(const char *reference)
{
 TaskReference=reference;
}
//----------------------------------------------------------------------------------------------------
//задать изменились ли данные задания
//----------------------------------------------------------------------------------------------------
void CTask::SetChangeData(const bool& change_data)
{
 ChangeData=change_data;
}
//----------------------------------------------------------------------------------------------------
//задать имя пользователя для которого задание
//----------------------------------------------------------------------------------------------------
void CTask::SetForUser(const char *for_user)
{
 ForUser=for_user;
}
//----------------------------------------------------------------------------------------------------
//задать имя пользователя от которого задание
//----------------------------------------------------------------------------------------------------
void CTask::SetFromUser(const char *from_user)
{
 FromUser=from_user;
}
//----------------------------------------------------------------------------------------------------
//задать название проекта по которому задание
//----------------------------------------------------------------------------------------------------
void CTask::SetProject(const char *project)
{
 Project=project;
}
//----------------------------------------------------------------------------------------------------
//установить, прочитан ли ответ на задание
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswerNotRead(bool state)
{
 AnswerNotRead=state;
}
//----------------------------------------------------------------------------------------------------
//установить, является ли задание плановой позицией
//----------------------------------------------------------------------------------------------------
void CTask::SetPlannedPosition(bool state)
{
 PlannedPosition=state;
}
//----------------------------------------------------------------------------------------------------
//задать, есть ли ссылка в ответе исполнителя
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswerReferenceExist(bool state)
{
 AnswerReferenceExist=state;
}
//----------------------------------------------------------------------------------------------------
//задать, есть ли ссылка в задании
//----------------------------------------------------------------------------------------------------
void CTask::SetTaskReferenceExist(bool state)
{
 TaskReferenceExist=state;
}
//----------------------------------------------------------------------------------------------------
//задать, является ли задание общим
//----------------------------------------------------------------------------------------------------
void CTask::SetCommon(bool state)
{
 Common=state;
}
//----------------------------------------------------------------------------------------------------
//установить, что задание не прочитано
//----------------------------------------------------------------------------------------------------
void CTask::SetStateNoRead(void)
{
 State=TASK_STATE_NO_READ;
}
//----------------------------------------------------------------------------------------------------
//установить, что задание прочитано и ожидает выполнения
//----------------------------------------------------------------------------------------------------
void CTask::SetStateReaded(void)
{
 State=TASK_STATE_READED;
}
//----------------------------------------------------------------------------------------------------
//установить, что задание выполняется
//----------------------------------------------------------------------------------------------------
void CTask::SetStateIsRunning(void)
{
 State=TASK_STATE_IS_RUNNING;
}
//----------------------------------------------------------------------------------------------------
//установить, что задание выполнено
//----------------------------------------------------------------------------------------------------
void CTask::SetStateDone(void)
{
 State=TASK_STATE_DONE;
}
//----------------------------------------------------------------------------------------------------
//установить, что задание отклонено
//----------------------------------------------------------------------------------------------------
void CTask::SetStateCancelled(void)
{
 State=TASK_STATE_CANCELED; 
}
//----------------------------------------------------------------------------------------------------
//установить, что задание завершено
//----------------------------------------------------------------------------------------------------
void CTask::SetStateFinished(void)
{
 State=TASK_STATE_FINISHED;
}

//----------------------------------------------------------------------------------------------------
//отметить для работы
//----------------------------------------------------------------------------------------------------
void CTask::MarkForWork(void)
{
 TaskType=TASK_TYPE_NONE;
}
//----------------------------------------------------------------------------------------------------
//отметить для удаления
//----------------------------------------------------------------------------------------------------
void CTask::MarkForDelete(void)
{
 TaskType=TASK_TYPE_DELETED;
}
//----------------------------------------------------------------------------------------------------
//отметить для замены
//----------------------------------------------------------------------------------------------------
void CTask::MarkForChange(void)
{
 TaskType=TASK_TYPE_CHANGED;
}
//----------------------------------------------------------------------------------------------------
//отметить для добавления
//----------------------------------------------------------------------------------------------------
void CTask::MarkForAdd(void)
{
 TaskType=TASK_TYPE_ADDED;
}

//----------------------------------------------------------------------------------------------------
//отмечено ли для работы
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForWork(void) const
{
 if (TaskType==TASK_TYPE_NONE) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//отмечено ли для удаления
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForDelete(void) const
{
 if (TaskType==TASK_TYPE_DELETED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//отмечено ли для замены
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForChange(void) const
{
 if (TaskType==TASK_TYPE_CHANGED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//отмечено ли для добавления
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForAdd(void) const
{
 if (TaskType==TASK_TYPE_ADDED) return(true);
 return(false);
}


//----------------------------------------------------------------------------------------------------
//проверить, что задание не прочитано
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateNoRead(void) const
{
 if (State==TASK_STATE_NO_READ) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//проверить, что задание прочитано и ожидает выполнения
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateReaded(void) const
{
 if (State==TASK_STATE_READED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//проверить, что задание выполняется
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateIsRunning(void) const
{
 if (State==TASK_STATE_IS_RUNNING) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//проверить, что задание выполнено
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateDone(void) const
{
 if (State==TASK_STATE_DONE) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//проверить, что задание отклонено
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateCancelled(void) const
{
 if (State==TASK_STATE_CANCELED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//проверить, что задание завершено
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateFinished(void) const
{
 if (State==TASK_STATE_FINISHED) return(true);
 return(false);
}

//----------------------------------------------------------------------------------------------------
//это задание от или для пользователя с уникальным идентификатором
//----------------------------------------------------------------------------------------------------
bool CTask::IsFromOrForUserGUID(const char *guid) const
{
 if (ForUserGUID.Compare(const_cast<char*>(guid))==0 || FromUserGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//это задание для пользователя с уникальным идентификатором
//----------------------------------------------------------------------------------------------------
bool CTask::IsForUserGUID(const char *guid) const
{
 if (ForUserGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//это задание от пользователя с уникальным идентификатором
//----------------------------------------------------------------------------------------------------
bool CTask::IsFromUserGUID(const char *guid) const
{
 if (FromUserGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//это задание по проекту с уникальным идентификатором
//----------------------------------------------------------------------------------------------------
bool CTask::IsProjectGUID(const char *guid) const
{
 if (ProjectGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//верный ли TaskGUID
//----------------------------------------------------------------------------------------------------
bool CTask::IsTaskGUID(const char *guid) const
{
 if (TaskGUID.Compare(const_cast<char*>(guid))==0) return(true);    
 return(false);
}
//----------------------------------------------------------------------------------------------------
//прочитан ли ответ на задание
//----------------------------------------------------------------------------------------------------
bool CTask::IsAnswerNotRead(void) const
{
 return(AnswerNotRead); 
}
//----------------------------------------------------------------------------------------------------
//является ли задание плановой позицией
//----------------------------------------------------------------------------------------------------
bool CTask::IsPlannedPosition(void) const
{
 return(PlannedPosition);
}
//----------------------------------------------------------------------------------------------------
//есть ли ссылка в ответе исполнителя
//----------------------------------------------------------------------------------------------------
bool CTask::IsAnswerReferenceExist(void) const
{
 return(AnswerReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//есть ли ссылка в задании
//----------------------------------------------------------------------------------------------------
bool CTask::IsTaskReferenceExist(void) const
{
 return(TaskReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//является ли задание общим
//----------------------------------------------------------------------------------------------------
bool CTask::IsCommon(void) const
{
 return(Common);
}

//----------------------------------------------------------------------------------------------------
//эквивалентны ли задания
//----------------------------------------------------------------------------------------------------
bool CTask::IsEquivalent(const CTask &cTask)
{
 if (Index!=cTask.Index) return(false);
 if (State!=cTask.State) return(false);
 
 if (FromUserGUID.Compare(cTask.FromUserGUID)!=0) return(false);
 if (ForUserGUID.Compare(cTask.ForUserGUID)!=0) return(false);
 if (ProjectGUID.Compare(cTask.ProjectGUID)!=0) return(false);
 if (Task.Compare(cTask.Task)!=0) return(false);
 if (AnswerNotRead!=cTask.AnswerNotRead) return(false);
 if (PlannedPosition!=cTask.PlannedPosition) return(false);
 if (AnswerReferenceExist!=cTask.AnswerReferenceExist) return(false);
 if (TaskReferenceExist!=cTask.TaskReferenceExist) return(false);
 if (Common!=cTask.Common) return(false);
 if (!(cDate==cTask.cDate)) return(false);
 if (TaskGUID.Compare(cTask.TaskGUID)!=0) return(false);
 if (Answer.Compare(cTask.Answer)!=0) return(false);
 if (AnswerReference.Compare(cTask.AnswerReference)!=0) return(false);
 if (TaskReference.Compare(cTask.TaskReference)!=0) return(false);
 
 return(true);
}

//----------------------------------------------------------------------------------------------------
//сохранить данные
//----------------------------------------------------------------------------------------------------
bool CTask::Save(FILE *file) const
{
 const char *s_ptr;
 //заполняем заголовок
 SHeader sHeader;
 sHeader.FromUserGUIDSize=FromUserGUID.GetLength();
 sHeader.ForUserGUIDSize=ForUserGUID.GetLength();
 sHeader.ProjectGUIDSize=ProjectGUID.GetLength();
 sHeader.TaskSize=Task.GetLength();
 sHeader.TaskGUIDSize=TaskGUID.GetLength();
 sHeader.AnswerSize=Answer.GetLength();
 sHeader.AnswerReferenceSize=AnswerReference.GetLength();
 sHeader.TaskReferenceSize=TaskReference.GetLength();
 sHeader.Year=cDate.GetYear();
 sHeader.Month=cDate.GetMonth();
 sHeader.Day=cDate.GetDay();
 sHeader.State=State;
 sHeader.TaskType=TaskType;
 sHeader.Index=Index;
 sHeader.AnswerNotRead=AnswerNotRead;
 sHeader.PlannedPosition=PlannedPosition;
 sHeader.AnswerReferenceExist=AnswerReferenceExist;
 sHeader.TaskReferenceExist=TaskReferenceExist;
 sHeader.Common=Common;

 fwrite(reinterpret_cast<const char*>(&sHeader),sizeof(SHeader),1,file); 

//считаем crc
 unsigned short crc16=0;
 CreateCRC16(crc16,&sHeader,sizeof(SHeader)*1);
 //записываем crc
 fwrite(&crc16,sizeof(unsigned short),1,file);

 s_ptr=FromUserGUID;
 CreateCRC16(crc16,s_ptr,FromUserGUID.GetLength());
 s_ptr=ForUserGUID;
 CreateCRC16(crc16,s_ptr,ForUserGUID.GetLength());
 s_ptr=ProjectGUID;
 CreateCRC16(crc16,s_ptr,ProjectGUID.GetLength());
 s_ptr=Task;
 CreateCRC16(crc16,s_ptr,Task.GetLength());
 s_ptr=TaskGUID;
 CreateCRC16(crc16,s_ptr,TaskGUID.GetLength());
 s_ptr=Answer;
 CreateCRC16(crc16,s_ptr,Answer.GetLength());
 s_ptr=AnswerReference;
 CreateCRC16(crc16,s_ptr,AnswerReference.GetLength());
 s_ptr=TaskReference;
 CreateCRC16(crc16,s_ptr,TaskReference.GetLength());

 //записываем crc
 fwrite(&crc16,sizeof(unsigned short),1,file);

 //записываем данные 
 s_ptr=FromUserGUID;
 fwrite(s_ptr,FromUserGUID.GetLength(),1,file);
 s_ptr=ForUserGUID;
 fwrite(s_ptr,ForUserGUID.GetLength(),1,file);
 s_ptr=ProjectGUID;
 fwrite(s_ptr,ProjectGUID.GetLength(),1,file);
 s_ptr=Task;
 fwrite(s_ptr,Task.GetLength(),1,file);
 s_ptr=TaskGUID;
 fwrite(s_ptr,TaskGUID.GetLength(),1,file);
 s_ptr=Answer;
 fwrite(s_ptr,Answer.GetLength(),1,file);
 s_ptr=AnswerReference;
 fwrite(s_ptr,AnswerReference.GetLength(),1,file);
 s_ptr=TaskReference;
 fwrite(s_ptr,TaskReference.GetLength(),1,file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить данные
//----------------------------------------------------------------------------------------------------
bool CTask::Load(FILE *file)
{
 unsigned short crc16_file;
 unsigned short crc16=0;

 SHeader sHeader;
 if (fread(&sHeader,sizeof(SHeader),1,file)<1) return(false);
 if (fread(&crc16_file,sizeof(unsigned short),1,file)<1) return(false);
 CreateCRC16(crc16,&sHeader,sizeof(SHeader));
 if (crc16!=crc16_file) return(false);
 if (fread(&crc16_file,sizeof(unsigned short),1,file)<1) return(false);

 CUniqueArrayPtr<char> from_user_guid;
 CUniqueArrayPtr<char> for_user_guid;
 CUniqueArrayPtr<char> project_guid;
 CUniqueArrayPtr<char> task;
 CUniqueArrayPtr<char> task_guid;
 CUniqueArrayPtr<char> answer;
 CUniqueArrayPtr<char> answer_reference;
 CUniqueArrayPtr<char> task_reference;

 from_user_guid.Set(new char[sHeader.FromUserGUIDSize+1]);
 for_user_guid.Set(new char[sHeader.ForUserGUIDSize+1]);
 project_guid.Set(new char[sHeader.ProjectGUIDSize+1]);
 task.Set(new char[sHeader.TaskSize+1]);
 task_guid.Set(new char[sHeader.TaskGUIDSize+1]);
 answer.Set(new char[sHeader.AnswerSize+1]);
 answer_reference.Set(new char[sHeader.AnswerReferenceSize+1]);
 task_reference.Set(new char[sHeader.TaskReferenceSize+1]);
 
 if (fread(from_user_guid.Get(),sizeof(char),sHeader.FromUserGUIDSize,file)<sHeader.FromUserGUIDSize) return(false);
 if (fread(for_user_guid.Get(),sizeof(char),sHeader.ForUserGUIDSize,file)<sHeader.ForUserGUIDSize) return(false);
 if (fread(project_guid.Get(),sizeof(char),sHeader.ProjectGUIDSize,file)<sHeader.ProjectGUIDSize) return(false);
 if (fread(task.Get(),sizeof(char),sHeader.TaskSize,file)<sHeader.TaskSize) return(false);
 if (fread(task_guid.Get(),sizeof(char),sHeader.TaskGUIDSize,file)<sHeader.TaskGUIDSize) return(false);
 if (fread(answer.Get(),sizeof(char),sHeader.AnswerSize,file)<sHeader.AnswerSize) return(false);
 if (fread(answer_reference.Get(),sizeof(char),sHeader.AnswerReferenceSize,file)<sHeader.AnswerReferenceSize) return(false);
 if (fread(task_reference.Get(),sizeof(char),sHeader.TaskReferenceSize,file)<sHeader.TaskReferenceSize) return(false);

 CreateCRC16(crc16,from_user_guid.Get(),sizeof(char)*sHeader.FromUserGUIDSize);
 CreateCRC16(crc16,for_user_guid.Get(),sizeof(char)*sHeader.ForUserGUIDSize);
 CreateCRC16(crc16,project_guid.Get(),sizeof(char)*sHeader.ProjectGUIDSize);
 CreateCRC16(crc16,task.Get(),sizeof(char)*sHeader.TaskSize);
 CreateCRC16(crc16,task_guid.Get(),sizeof(char)*sHeader.TaskGUIDSize);
 CreateCRC16(crc16,answer.Get(),sizeof(char)*sHeader.AnswerSize);
 CreateCRC16(crc16,answer_reference.Get(),sizeof(char)*sHeader.AnswerReferenceSize);
 CreateCRC16(crc16,task_reference.Get(),sizeof(char)*sHeader.TaskReferenceSize);

 if (crc16!=crc16_file) return(false);

 from_user_guid.Get()[sHeader.FromUserGUIDSize]=0;
 for_user_guid.Get()[sHeader.ForUserGUIDSize]=0;
 project_guid.Get()[sHeader.ProjectGUIDSize]=0;
 task.Get()[sHeader.TaskSize]=0;
 task_guid.Get()[sHeader.TaskGUIDSize]=0;
 answer.Get()[sHeader.AnswerSize]=0;
 answer_reference.Get()[sHeader.AnswerReferenceSize]=0;
 task_reference.Get()[sHeader.TaskReferenceSize]=0;

 FromUserGUID=from_user_guid.Get();
 ForUserGUID=for_user_guid.Get();
 ProjectGUID=project_guid.Get();
 Task=task.Get();
 TaskGUID=task_guid.Get();
 Answer=answer.Get();
 AnswerReference=answer_reference.Get();
 TaskReference=task_reference.Get(); 

 State=sHeader.State;
 cDate.SetDate(sHeader.Year,sHeader.Month,sHeader.Day);
 TaskType=sHeader.TaskType;
 Index=sHeader.Index;
 AnswerNotRead=sHeader.AnswerNotRead;
 PlannedPosition=sHeader.PlannedPosition;
 Common=sHeader.Common;
 TaskReferenceExist=sHeader.TaskReferenceExist;
 AnswerReferenceExist=sHeader.AnswerReferenceExist;

 return(true);
}
