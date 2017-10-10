#include "cvector_task.h"

//====================================================================================================
//�����������
//====================================================================================================
CVectorTask::CVectorTask()
{
 Version=5;
}
//====================================================================================================
//����������
//====================================================================================================
CVectorTask::~CVectorTask()
{
}
//====================================================================================================
//�������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
bool CVectorTask::Save(char *filename)
{
 FILE *file=fopen(filename,"wb");
 if (file==NULL) return(false);
 //����� ��������� � ����� ������ ��������� ������
 fwrite("TLV",sizeof(unsigned char),3,file);
 fwrite(&Version,sizeof(unsigned long),1,file);

 size_t size=vector_CTask.size();
 fwrite(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  const CTask &cTask=vector_CTask[n]; 
  if (cTask.Save(file)==false) break;
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
bool CVectorTask::Load(char *filename)
{
 vector_CTask.clear();

 FILE *file=fopen(filename,"rb");
 if (file==NULL) return(false);
 unsigned char signature[3];
 unsigned char version;
 fread(&signature,sizeof(unsigned char),3,file);
 fread(&version,sizeof(unsigned long),1,file);
 if (signature[0]!='T' || signature[1]!='L' || signature[2]!='V' || version!=Version)
 {
  fclose(file);
  return(false);
 }
 size_t size;
 fread(&size,sizeof(size_t),1,file);

 for(size_t n=0;n<size;n++)
 {
  CTask cTask;
  if (cTask.Load(file)==false) break;
  vector_CTask.push_back(cTask);
 } 
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ����� �������
//----------------------------------------------------------------------------------------------------
bool CVectorTask::AddNew(const CTask &cTask)
{
 vector_CTask.push_back(cTask);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
void CVectorTask::Clear(void)
{
 vector_CTask.clear();
}
//----------------------------------------------------------------------------------------------------
//���������� ������� �� ���� �� �����������
//----------------------------------------------------------------------------------------------------
void CVectorTask::SortByDate(void)
{
 sort(vector_CTask.begin(),vector_CTask.end());
}
//----------------------------------------------------------------------------------------------------
//����� �� GUID �������
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
//����� �� GUID ������������ �� �������� �������
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
//����� �� GUID ������������ ��� �������� �������
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
//����� �� GUID �������
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
//������� �� GUID �������
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
//�������� �� GUID �������
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
//�������� ���������� �������
//----------------------------------------------------------------------------------------------------
size_t CVectorTask::Size(void)
{
 return(vector_CTask.size());
}
//----------------------------------------------------------------------------------------------------
//�������� ��������� ������� � ������� ���
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
//�������� ������� � �����
//----------------------------------------------------------------------------------------------------
bool CVectorTask::PushBack(const CTask &cTask)
{
 vector_CTask.push_back(cTask);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ �� ������ �����
//----------------------------------------------------------------------------------------------------
vector<CTask>& CVectorTask::GetVectorCTask(void)
{
 return(vector_CTask);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ ��� �������� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CVectorTask::CreateVectorCTaskByForUserGUID(const CSafeString &guid)
{
 vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsForUserGUID(guid)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ �� �������� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CVectorTask::CreateVectorCTaskByFromUserGUID(const CSafeString &guid)
{
 vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsFromUserGUID(guid)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� GUID ������������ ���� ��� �������� ������� �� ������������ ���
//----------------------------------------------------------------------------------------------------
vector<CTask> CVectorTask::CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(const CSafeString &guid_one,const CSafeString &guid_two)
{
 vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsForUserGUID(guid_one)==true && cTask.IsFromUserGUID(guid_two)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}
//----------------------------------------------------------------------------------------------------
//������� ������ ����� �� ������� �� ������������
//----------------------------------------------------------------------------------------------------
vector<CTask> CVectorTask::CreateVectorCTaskByProjectGUIDFromUserGUID(const CSafeString &guid_project,const CSafeString &guid_from_user)
{
 vector<CTask> vector_CTask_Out;
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
//������� ������ ����� �� �������
//----------------------------------------------------------------------------------------------------
vector<CTask> CVectorTask::CreateVectorCTaskByProjectGUID(const CSafeString &guid_project)
{
 vector<CTask> vector_CTask_Out;
 size_t size=vector_CTask.size();
 for(size_t n=0;n<size;n++)
 {
  CTask cTask=vector_CTask[n];
  if (cTask.IsProjectGUID(guid_project)==true) vector_CTask_Out.push_back(cTask);
 }
 return(vector_CTask_Out);
}