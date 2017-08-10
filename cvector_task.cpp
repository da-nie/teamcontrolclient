#include "cvector_task.h"

//====================================================================================================
//конструктор
//====================================================================================================
CVectorTask::CVectorTask()
{
}
//====================================================================================================
//деструктор
//====================================================================================================
CVectorTask::~CVectorTask()
{
}
//====================================================================================================
//функции
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//сохранить
//----------------------------------------------------------------------------------------------------
bool CVectorTask::Save(char *filename)
{
 FILE *file=fopen(filename,"wb");
 if (file==NULL) return(false);
 size_t size=vector_STask.size();
 fwrite(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  const STask &sTask=vector_STask[n]; 
  //заполняем заголовок
  SHeader sHeader;
  sHeader.FromUserGUIDSize=sTask.FromUserGUID.GetLength();
  sHeader.ForUserGUIDSize=sTask.ForUserGUID.GetLength();
  sHeader.ProjectGUIDSize=sTask.ProjectGUID.GetLength();
  sHeader.TaskSize=sTask.Task.GetLength();
  sHeader.TaskGUIDSize=sTask.TaskGUID.GetLength();
  sHeader.Year=sTask.Year;
  sHeader.Month=sTask.Month;
  sHeader.Day=sTask.Day;
  sHeader.State=sTask.State;
  sHeader.TaskType=sTask.TaskType;
  sHeader.Index=sTask.Index;
  fwrite(reinterpret_cast<const char*>(&sHeader),sizeof(SHeader),1,file);
  const char *s_ptr;
  s_ptr=sTask.FromUserGUID;
  fwrite(s_ptr,sTask.FromUserGUID.GetLength(),1,file);
  s_ptr=sTask.ForUserGUID;
  fwrite(s_ptr,sTask.ForUserGUID.GetLength(),1,file);
  s_ptr=sTask.ProjectGUID;
  fwrite(s_ptr,sTask.ProjectGUID.GetLength(),1,file);
  s_ptr=sTask.Task;
  fwrite(s_ptr,sTask.Task.GetLength(),1,file);
  s_ptr=sTask.TaskGUID;
  fwrite(s_ptr,sTask.TaskGUID.GetLength(),1,file);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorTask::Load(char *filename)
{
 vector_STask.clear();

 FILE *file=fopen(filename,"rb");
 if (file==NULL) return(false);
 size_t size;
 fread(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  SHeader sHeader;
  fread(&sHeader,sizeof(SHeader),1,file);
  char *from_user_guid=new char[sHeader.FromUserGUIDSize+1];
  char *for_user_guid=new char[sHeader.ForUserGUIDSize+1];
  char *project_guid=new char[sHeader.ProjectGUIDSize+1];
  char *task=new char[sHeader.TaskSize+1];
  char *task_guid=new char[sHeader.TaskGUIDSize+1];
 
  fread(from_user_guid,sizeof(char),sHeader.FromUserGUIDSize,file);
  fread(for_user_guid,sizeof(char),sHeader.ForUserGUIDSize,file);
  fread(project_guid,sizeof(char),sHeader.ProjectGUIDSize,file);
  fread(task,sizeof(char),sHeader.TaskSize,file);
  fread(task_guid,sizeof(char),sHeader.TaskGUIDSize,file);  
 
  from_user_guid[sHeader.FromUserGUIDSize]=0;
  for_user_guid[sHeader.ForUserGUIDSize]=0;
  project_guid[sHeader.ProjectGUIDSize]=0;
  task[sHeader.TaskSize]=0;
  task_guid[sHeader.TaskGUIDSize]=0;

  STask sTask;
  sTask.FromUserGUID=from_user_guid;
  sTask.ForUserGUID=for_user_guid;
  sTask.ProjectGUID=project_guid;
  sTask.Task=task;
  sTask.TaskGUID=task_guid;

  sTask.State=sHeader.State;
  sTask.Year=sHeader.Year;
  sTask.Month=sHeader.Month;
  sTask.Day=sHeader.Day;
  sTask.TaskType=sHeader.TaskType;
  sTask.Index=sHeader.Index;

  delete[](from_user_guid);
  delete[](for_user_guid);
  delete[](project_guid);
  delete[](task);
  delete[](task_guid);

  vector_STask.push_back(sTask);
 }

 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить новый элемент
//----------------------------------------------------------------------------------------------------
bool CVectorTask::AddNew(const STask &sTask)
{
 vector_STask.push_back(sTask);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//очистить список
//----------------------------------------------------------------------------------------------------
void CVectorTask::Clear(void)
{
 vector_STask.clear();
}
//----------------------------------------------------------------------------------------------------
//сортировка заданий по дате по возрастанию
//----------------------------------------------------------------------------------------------------
void CVectorTask::SortByDate(void)
{
 sort(vector_STask.begin(),vector_STask.end());
}
//----------------------------------------------------------------------------------------------------
//найти по GUID задания
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByTaskGUID(const CSafeString &guid,STask &sTask)
{
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  sTask=vector_STask[n];
  if (sTask.TaskGUID.Compare(guid)==0) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя от которого задание
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByFromUserGUID(const CSafeString &guid,STask &sTask)
{
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  sTask=vector_STask[n];
  if (sTask.FromUserGUID.Compare(guid)==0) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя для которого задание
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByForUserGUID(const CSafeString &guid,STask &sTask)
{
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  sTask=vector_STask[n];
  if (sTask.ForUserGUID.Compare(guid)==0) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID проекта
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByProjectGUID(const CSafeString &guid,STask &sTask)
{
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  sTask=vector_STask[n];
  if (sTask.ProjectGUID.Compare(guid)==0) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//удалить по GUID задания
//----------------------------------------------------------------------------------------------------
bool CVectorTask::DeleteByTaskGUID(const CSafeString &guid)
{
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  STask &sTask_Local=vector_STask[n];
  if (sTask_Local.TaskGUID.Compare(guid)==0)
  { 
   vector_STask.erase(vector_STask.begin()+n);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//заменить по GUID задания
//----------------------------------------------------------------------------------------------------
bool CVectorTask::ChangeByTaskGUID(const CSafeString &guid,const STask &sTask)
{
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  STask &sTask_Local=vector_STask[n];
  if (sTask_Local.TaskGUID.Compare(guid)==0)
  { 
   sTask_Local=sTask;
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//получить количество заданий
//----------------------------------------------------------------------------------------------------
size_t CVectorTask::Size(void)
{
 return(vector_STask.size());
}
//----------------------------------------------------------------------------------------------------
//получить последнее задание и удалить его
//----------------------------------------------------------------------------------------------------
bool CVectorTask::PopBack(STask &sTask)
{
 size_t size=vector_STask.size();
 if (size==0) return(false);
 sTask=vector_STask[size-1];
 vector_STask.pop_back();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить задание в конец
//----------------------------------------------------------------------------------------------------
bool CVectorTask::PushBack(const STask &sTask)
{
 vector_STask.push_back(sTask);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на вектор задач
//----------------------------------------------------------------------------------------------------
vector<STask>& CVectorTask::GetVectorSTask(void)
{
 return(vector_STask);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по GUID пользователя для которого задание
//----------------------------------------------------------------------------------------------------
vector<STask> CVectorTask::CreateVectorSTaskByForUserGUID(const CSafeString &guid)
{
 vector<STask> vector_STask_Out;
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  STask sTask=vector_STask[n];
  if (sTask.ForUserGUID.Compare(guid)==0) vector_STask_Out.push_back(sTask);
 }
 return(vector_STask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по GUID пользователя от которого задание
//----------------------------------------------------------------------------------------------------
vector<STask> CVectorTask::CreateVectorSTaskByFromUserGUID(const CSafeString &guid)
{
 vector<STask> vector_STask_Out;
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  STask sTask=vector_STask[n];
  if (sTask.FromUserGUID.Compare(guid)==0) vector_STask_Out.push_back(sTask);
 }
 return(vector_STask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по GUID пользователя один для которого задание от пользователя два
//----------------------------------------------------------------------------------------------------
vector<STask> CVectorTask::CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two)
{
 vector<STask> vector_STask_Out;
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  STask sTask=vector_STask[n];
  if (sTask.ForUserGUID.Compare(guid_one)==0 && sTask.FromUserGUID.Compare(guid_two)==0) vector_STask_Out.push_back(sTask);
 }
 return(vector_STask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по проекту от пользователя
//----------------------------------------------------------------------------------------------------
vector<STask> CVectorTask::CreateVectorSTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user)
{
 vector<STask> vector_STask_Out;
 size_t size=vector_STask.size();
 for(size_t n=0;n<size;n++)
 {
  STask sTask=vector_STask[n];
  if (sTask.FromUserGUID.Compare(guid_from_user)==0)
  {
   if (sTask.ProjectGUID.Compare(guid_project)==0) vector_STask_Out.push_back(sTask);
  }
 }
 return(vector_STask_Out);
}
