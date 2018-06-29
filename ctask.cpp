#include "ctask.h"
#include "crc.h"
#include "cuniquearrayptr.h"

//====================================================================================================
//����������� ������
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
//���������� ������
//====================================================================================================
CTask::~CTask()
{		
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//������� ������
//----------------------------------------------------------------------------------------------------
const long& CTask::GetIndex(void) const
{
 return(Index);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������� �� ������ ������������ �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetFromUserGUID(void) const
{
 return(FromUserGUID);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������� ��� ������ ������������ �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetForUserGUID(void) const
{
 return(ForUserGUID);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetProjectGUID(void) const
{
 return(ProjectGUID);
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetTask(void) const
{
 return(Task);
}
//----------------------------------------------------------------------------------------------------
//�������� ���� �������
//----------------------------------------------------------------------------------------------------
const CDate& CTask::GetDate(void) const
{
 return(cDate);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetTaskGUID(void) const
{
 return(TaskGUID);
}
//----------------------------------------------------------------------------------------------------
//�������� ����� �� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetAnswer(void) const
{
 return(Answer);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ �� ���� � ������ �����������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetAnswerReference(void) const
{
 return(AnswerReference);
}
//----------------------------------------------------------------------------------------------------
//������ ������ �� ���� � �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetTaskReference(void) const
{
 return(TaskReference);
}

//----------------------------------------------------------------------------------------------------
//��������, ���������� �� ������ �������
//----------------------------------------------------------------------------------------------------
const bool& CTask::GetChangeData(void) const
{
 return(ChangeData);
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ������������ ��� �������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetForUser(void) const
{
 return(ForUser);
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ������������ �� �������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetFromUser(void) const
{
 return(FromUser);
}
//----------------------------------------------------------------------------------------------------
//�������� �������� ������� �� �������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CTask::GetProject(void) const
{
 return(Project);
}
//----------------------------------------------------------------------------------------------------
//��������, �������� �� ����� �� �������
//----------------------------------------------------------------------------------------------------
bool CTask::GetAnswerNotRead(void) const
{
 return(AnswerNotRead);
}
//----------------------------------------------------------------------------------------------------
//��������, �������� �� ������� �������� ��������
//----------------------------------------------------------------------------------------------------
bool CTask::GetPlannedPosition(void) const
{
 return(PlannedPosition);
}
//----------------------------------------------------------------------------------------------------
//��������, ���� �� ������ � ������ �����������
//----------------------------------------------------------------------------------------------------
bool CTask::GetAnswerReferenceExist(void) const
{
 return(AnswerReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//��������, ���� �� ������ � �������
//----------------------------------------------------------------------------------------------------
bool CTask::GetTaskReferenceExist(void) const
{
 return(TaskReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//��������, �������� �� ������� �����
//----------------------------------------------------------------------------------------------------
bool CTask::GetCommon(void) const
{
 return(Common);
}
//----------------------------------------------------------------------------------------------------
//������ ������
//----------------------------------------------------------------------------------------------------
void CTask::SetIndex(const long& index)
{
 Index=index;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� ������������� �� ������ ������������ �������
//----------------------------------------------------------------------------------------------------
void CTask::SetFromUserGUID(const char *from_user_guid)
{
 FromUserGUID=from_user_guid;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� ������������� ��� ������ ������������ �������
//----------------------------------------------------------------------------------------------------
void CTask::SetForUserGUID(const char *for_user_guid)
{
 ForUserGUID=for_user_guid;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� ������������� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetProjectGUID(const char *project_guid)
{
 ProjectGUID=project_guid;
}
//----------------------------------------------------------------------------------------------------
//������ �������
//----------------------------------------------------------------------------------------------------
void CTask::SetTask(const char *task)
{
 Task=task;
}
//----------------------------------------------------------------------------------------------------
//������ ���� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetDate(const CDate &cDate_Set)
{
 cDate=cDate_Set;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� ������������� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetTaskGUID(const char *task_guid)
{
 TaskGUID=task_guid;
}
//----------------------------------------------------------------------------------------------------
//������ ����� �� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswer(const char *answer)
{
 Answer=answer;
}
//----------------------------------------------------------------------------------------------------
//������ ������ �� ���� � ������ �����������
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswerReference(const char *reference)
{
 AnswerReference=reference;
}
//----------------------------------------------------------------------------------------------------
//������ ������ �� ���� � �������
//----------------------------------------------------------------------------------------------------
void CTask::SetTaskReference(const char *reference)
{
 TaskReference=reference;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� �� ������ �������
//----------------------------------------------------------------------------------------------------
void CTask::SetChangeData(const bool& change_data)
{
 ChangeData=change_data;
}
//----------------------------------------------------------------------------------------------------
//������ ��� ������������ ��� �������� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetForUser(const char *for_user)
{
 ForUser=for_user;
}
//----------------------------------------------------------------------------------------------------
//������ ��� ������������ �� �������� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetFromUser(const char *from_user)
{
 FromUser=from_user;
}
//----------------------------------------------------------------------------------------------------
//������ �������� ������� �� �������� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetProject(const char *project)
{
 Project=project;
}
//----------------------------------------------------------------------------------------------------
//����������, �������� �� ����� �� �������
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswerNotRead(bool state)
{
 AnswerNotRead=state;
}
//----------------------------------------------------------------------------------------------------
//����������, �������� �� ������� �������� ��������
//----------------------------------------------------------------------------------------------------
void CTask::SetPlannedPosition(bool state)
{
 PlannedPosition=state;
}
//----------------------------------------------------------------------------------------------------
//������, ���� �� ������ � ������ �����������
//----------------------------------------------------------------------------------------------------
void CTask::SetAnswerReferenceExist(bool state)
{
 AnswerReferenceExist=state;
}
//----------------------------------------------------------------------------------------------------
//������, ���� �� ������ � �������
//----------------------------------------------------------------------------------------------------
void CTask::SetTaskReferenceExist(bool state)
{
 TaskReferenceExist=state;
}
//----------------------------------------------------------------------------------------------------
//������, �������� �� ������� �����
//----------------------------------------------------------------------------------------------------
void CTask::SetCommon(bool state)
{
 Common=state;
}
//----------------------------------------------------------------------------------------------------
//����������, ��� ������� �� ���������
//----------------------------------------------------------------------------------------------------
void CTask::SetStateNoRead(void)
{
 State=TASK_STATE_NO_READ;
}
//----------------------------------------------------------------------------------------------------
//����������, ��� ������� ��������� � ������� ����������
//----------------------------------------------------------------------------------------------------
void CTask::SetStateReaded(void)
{
 State=TASK_STATE_READED;
}
//----------------------------------------------------------------------------------------------------
//����������, ��� ������� �����������
//----------------------------------------------------------------------------------------------------
void CTask::SetStateIsRunning(void)
{
 State=TASK_STATE_IS_RUNNING;
}
//----------------------------------------------------------------------------------------------------
//����������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
void CTask::SetStateDone(void)
{
 State=TASK_STATE_DONE;
}
//----------------------------------------------------------------------------------------------------
//����������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
void CTask::SetStateCancelled(void)
{
 State=TASK_STATE_CANCELED; 
}
//----------------------------------------------------------------------------------------------------
//����������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
void CTask::SetStateFinished(void)
{
 State=TASK_STATE_FINISHED;
}

//----------------------------------------------------------------------------------------------------
//�������� ��� ������
//----------------------------------------------------------------------------------------------------
void CTask::MarkForWork(void)
{
 TaskType=TASK_TYPE_NONE;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ��������
//----------------------------------------------------------------------------------------------------
void CTask::MarkForDelete(void)
{
 TaskType=TASK_TYPE_DELETED;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ������
//----------------------------------------------------------------------------------------------------
void CTask::MarkForChange(void)
{
 TaskType=TASK_TYPE_CHANGED;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ����������
//----------------------------------------------------------------------------------------------------
void CTask::MarkForAdd(void)
{
 TaskType=TASK_TYPE_ADDED;
}

//----------------------------------------------------------------------------------------------------
//�������� �� ��� ������
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForWork(void) const
{
 if (TaskType==TASK_TYPE_NONE) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��� ��������
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForDelete(void) const
{
 if (TaskType==TASK_TYPE_DELETED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��� ������
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForChange(void) const
{
 if (TaskType==TASK_TYPE_CHANGED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��� ����������
//----------------------------------------------------------------------------------------------------
bool CTask::IsMarkForAdd(void) const
{
 if (TaskType==TASK_TYPE_ADDED) return(true);
 return(false);
}


//----------------------------------------------------------------------------------------------------
//���������, ��� ������� �� ���������
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateNoRead(void) const
{
 if (State==TASK_STATE_NO_READ) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ������� ��������� � ������� ����������
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateReaded(void) const
{
 if (State==TASK_STATE_READED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ������� �����������
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateIsRunning(void) const
{
 if (State==TASK_STATE_IS_RUNNING) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateDone(void) const
{
 if (State==TASK_STATE_DONE) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateCancelled(void) const
{
 if (State==TASK_STATE_CANCELED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
bool CTask::IsStateFinished(void) const
{
 if (State==TASK_STATE_FINISHED) return(true);
 return(false);
}

//----------------------------------------------------------------------------------------------------
//��� ������� �� ��� ��� ������������ � ���������� ���������������
//----------------------------------------------------------------------------------------------------
bool CTask::IsFromOrForUserGUID(const char *guid) const
{
 if (ForUserGUID.Compare(const_cast<char*>(guid))==0 || FromUserGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��� ������� ��� ������������ � ���������� ���������������
//----------------------------------------------------------------------------------------------------
bool CTask::IsForUserGUID(const char *guid) const
{
 if (ForUserGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��� ������� �� ������������ � ���������� ���������������
//----------------------------------------------------------------------------------------------------
bool CTask::IsFromUserGUID(const char *guid) const
{
 if (FromUserGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��� ������� �� ������� � ���������� ���������������
//----------------------------------------------------------------------------------------------------
bool CTask::IsProjectGUID(const char *guid) const
{
 if (ProjectGUID.Compare(const_cast<char*>(guid))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//������ �� TaskGUID
//----------------------------------------------------------------------------------------------------
bool CTask::IsTaskGUID(const char *guid) const
{
 if (TaskGUID.Compare(const_cast<char*>(guid))==0) return(true);    
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ����� �� �������
//----------------------------------------------------------------------------------------------------
bool CTask::IsAnswerNotRead(void) const
{
 return(AnswerNotRead); 
}
//----------------------------------------------------------------------------------------------------
//�������� �� ������� �������� ��������
//----------------------------------------------------------------------------------------------------
bool CTask::IsPlannedPosition(void) const
{
 return(PlannedPosition);
}
//----------------------------------------------------------------------------------------------------
//���� �� ������ � ������ �����������
//----------------------------------------------------------------------------------------------------
bool CTask::IsAnswerReferenceExist(void) const
{
 return(AnswerReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//���� �� ������ � �������
//----------------------------------------------------------------------------------------------------
bool CTask::IsTaskReferenceExist(void) const
{
 return(TaskReferenceExist);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ������� �����
//----------------------------------------------------------------------------------------------------
bool CTask::IsCommon(void) const
{
 return(Common);
}

//----------------------------------------------------------------------------------------------------
//������������ �� �������
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
//��������� ������
//----------------------------------------------------------------------------------------------------
bool CTask::Save(FILE *file) const
{
 const char *s_ptr;
 //��������� ���������
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

//������� crc
 unsigned short crc16=0;
 CreateCRC16(crc16,&sHeader,sizeof(SHeader)*1);
 //���������� crc
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

 //���������� crc
 fwrite(&crc16,sizeof(unsigned short),1,file);

 //���������� ������ 
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
//��������� ������
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
