#include "cvector_task.h"
#include "crc.h"

//====================================================================================================
//конструктор
//====================================================================================================
CVectorTask::CVectorTask()
{
 Version=6;
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
 CRAIIFileOut cRAIIFileOut(filename,std::ios_base::out|std::ios_base::binary);
 {
  if (cRAIIFileOut.IsOpened()==false) return(false);
  //пишем сигнатуру и номер версии структуры данных
  unsigned short crc16=0;
  if (cRAIIFileOut.GetHandle().write((char *)"TLV",sizeof(unsigned char)*3)==false) return(false);
  if (cRAIIFileOut.GetHandle().write((char *)&Version,sizeof(unsigned long)*1)==false) return(false);
  CreateCRC16(crc16,&Version,sizeof(unsigned long)*1);

  size_t size=vector_CTask.size();
if (cRAIIFileOut.GetHandle().write((char *)&size,sizeof(size_t)*1)==false) return(false);
  CreateCRC16(crc16,&size,sizeof(size_t)*1);
  //записываем CRC
  if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);
 
  for(size_t n=0;n<size;n++)
  {
   const CTask &cTask=vector_CTask[n]; 
   if (cTask.Save(cRAIIFileOut)==false) break;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorTask::Load(char *filename)
{
 vector_CTask.clear();

 CRAIIFileIn cRAIIFileIn(filename,std::ios_base::in|std::ios_base::binary);
 {
  if (cRAIIFileIn.IsOpened()==false) return(false);
  unsigned char signature[3];
  unsigned long version;
  unsigned short crc16_file;
  if (cRAIIFileIn.GetHandle().read((char*)signature,sizeof(unsigned char)*3)==false) return(false);
  if (cRAIIFileIn.GetHandle().read((char*)&version,sizeof(unsigned long)*1)==false) return(false);
  if (signature[0]!='T' || signature[1]!='L' || signature[2]!='V' || version!=Version) return(false);
  size_t size;
  if (cRAIIFileIn.GetHandle().read((char*)&size,sizeof(size_t)*1)==false) return(false);
  if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);
  unsigned short crc16=0;
  CreateCRC16(crc16,&version,sizeof(unsigned long)*1);
  CreateCRC16(crc16,&size,sizeof(size_t)*1);
 
  if (crc16_file!=crc16) return(false);

  for(size_t n=0;n<size;n++)
  {
   CTask cTask;
   if (cTask.Load(cRAIIFileIn)==false) break;
   vector_CTask.push_back(cTask);
  } 
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить новый элемент
//----------------------------------------------------------------------------------------------------
bool CVectorTask::AddNew(const CTask &cTask)
{
 vector_CTask.push_back(cTask);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//очистить список
//----------------------------------------------------------------------------------------------------
void CVectorTask::Clear(void)
{
 vector_CTask.clear();
}
//----------------------------------------------------------------------------------------------------
//сортировка заданий по дате по возрастанию
//----------------------------------------------------------------------------------------------------
void CVectorTask::SortByDate(void)
{
 sort(vector_CTask.begin(),vector_CTask.end());
}
//----------------------------------------------------------------------------------------------------
//найти по GUID задания
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByTaskGUID(const CSafeString &guid,CTask &cTask)
{
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  cTask=vector_CTask[n];
  if (cTask.IsTaskGUID(guid)==true) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя от которого задание
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByFromUserGUID(const CSafeString &guid,CTask &cTask)
{
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  cTask=vector_CTask[n];
  if (cTask.IsFromUserGUID(guid)==true) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя для которого задание
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByForUserGUID(const CSafeString &guid,CTask &cTask)
{
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  cTask=vector_CTask[n];
  if (cTask.IsForUserGUID(guid)==true) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID проекта
//----------------------------------------------------------------------------------------------------
bool CVectorTask::FindByProjectGUID(const CSafeString &guid,CTask &cTask)
{
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  cTask=vector_CTask[n];
  if (cTask.IsProjectGUID(guid)==true) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//удалить по GUID задания
//----------------------------------------------------------------------------------------------------
bool CVectorTask::DeleteByTaskGUID(const CSafeString &guid)
{
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask &cTask_Local=vector_CTask[n];
  if (cTask_Local.IsTaskGUID(guid)==true)
  { 
   vector_CTask.erase(vector_CTask.begin()+n);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//заменить по GUID задания
//----------------------------------------------------------------------------------------------------
bool CVectorTask::ChangeByTaskGUID(const CSafeString &guid,const CTask &cTask)
{
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask &cTask_Local=vector_CTask[n];
  if (cTask_Local.IsTaskGUID(guid)==true)
  { 
   cTask_Local=cTask;
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
 return(vector_CTask.size());
}
//----------------------------------------------------------------------------------------------------
//получить последнее задание и удалить его
//----------------------------------------------------------------------------------------------------
bool CVectorTask::PopBack(CTask &cTask)
{
 size_t size=vector_CTask.size();
 if (size==0) return(false);
 cTask=vector_CTask[size-1];
 vector_CTask.pop_back();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить задание в конец
//----------------------------------------------------------------------------------------------------
bool CVectorTask::PushBack(const CTask &cTask)
{
 vector_CTask.push_back(cTask);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на вектор задач
//----------------------------------------------------------------------------------------------------
std::vector<CTask>& CVectorTask::GetVectorCTask(void)
{
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по GUID пользователя для которого задание
//----------------------------------------------------------------------------------------------------
std::vector<CTask> CVectorTask::CreateVectorCTaskByForUserGUID(const CSafeString &guid)
{
 std::vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsForUserGUID(guid)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по GUID пользователя от которого задание
//----------------------------------------------------------------------------------------------------
std::vector<CTask> CVectorTask::CreateVectorCTaskByFromUserGUID(const CSafeString &guid)
{
 std::vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsFromUserGUID(guid)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по GUID пользователя один для которого задание от пользователя два
//----------------------------------------------------------------------------------------------------
std::vector<CTask> CVectorTask::CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two)
{
 std::vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsForUserGUID(guid_one)==true && cTask.IsFromUserGUID(guid_two)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по проекту от пользователя
//----------------------------------------------------------------------------------------------------
std::vector<CTask> CVectorTask::CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user)
{
 std::vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsFromUserGUID(guid_from_user)==true)
  {
   if (cTask.IsProjectGUID(guid_project)==true) vector_CTask_Out.push_back(cTask);
  }
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//создать вектор задач по проекту
//----------------------------------------------------------------------------------------------------
std::vector<CTask> CVectorTask::CreateVectorCTaskByProjectGUID(const CSafeString &guid_project)
{
 std::vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsProjectGUID(guid_project)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}