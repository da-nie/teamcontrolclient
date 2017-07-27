#include "cvector_project.h"

//====================================================================================================
//�����������
//====================================================================================================
CVectorProject::CVectorProject()
{
}
//====================================================================================================
//����������
//====================================================================================================
CVectorProject::~CVectorProject()
{
}
//====================================================================================================
//�������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::Save(char *filename)
{
 FILE *file=fopen(filename,"wb");
 if (file==NULL) return(false);
 size_t size=vector_SProject.size();
 fwrite(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  const SProject &sProject=vector_SProject[n]; 
  //��������� ���������
  SHeader sHeader;
  sHeader.ProjectNameSize=sProject.ProjectName.GetLength();
  sHeader.ProjectGUIDSize=sProject.ProjectGUID.GetLength();
  sHeader.ProjectType=sProject.ProjectType;
  fwrite(reinterpret_cast<const char*>(&sHeader),sizeof(SHeader),1,file);
  const char *s_ptr;
  s_ptr=sProject.ProjectName;
  fwrite(s_ptr,sProject.ProjectName.GetLength(),1,file);
  s_ptr=sProject.ProjectGUID;
  fwrite(s_ptr,sProject.ProjectGUID.GetLength(),1,file);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::Load(char *filename)
{
 vector_SProject.clear();

 FILE *file=fopen(filename,"rb");
 if (file==NULL) return(false);
 size_t size;
 fread(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  SHeader sHeader;
  fread(&sHeader,sizeof(SHeader),1,file);
  char *project_guid=new char[sHeader.ProjectGUIDSize+1];
  char *project_name=new char[sHeader.ProjectNameSize+1];
 
  fread(project_name,sizeof(char),sHeader.ProjectNameSize,file);
  fread(project_guid,sizeof(char),sHeader.ProjectGUIDSize,file);  
 
  project_name[sHeader.ProjectNameSize]=0;
  project_guid[sHeader.ProjectGUIDSize]=0;

  SProject sProject;
  sProject.ProjectName=project_name;
  sProject.ProjectGUID=project_guid;
  sProject.ProjectType=sHeader.ProjectType;

  delete[](project_name);
  delete[](project_guid);

  vector_SProject.push_back(sProject);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ����� �������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::AddNew(const SProject &sProject)
{
 vector_SProject.push_back(sProject);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
void CVectorProject::Clear(void)
{
 vector_SProject.clear();
}
//----------------------------------------------------------------------------------------------------
//����� �� GUID �������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::FindByProjectGUID(const CString &guid,SProject &sProject)
{
 size_t size=vector_SProject.size();
 for(size_t n=0;n<size;n++)
 {
  sProject=vector_SProject[n];
  if (sProject.ProjectGUID.Compare(guid)==0) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//����� �� GUID ������� � ��������, ��� ������ �� ��������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::FindByProjectGUIDAndResetChangeData(const CString &guid,SProject &sProject)
{
 size_t size=vector_SProject.size();
 for(size_t n=0;n<size;n++)
 {
  sProject=vector_SProject[n];
  if (sProject.ProjectGUID.Compare(guid)==0)
  {
   vector_SProject[n].ChangeData=false;
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//������� �� GUID �������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::DeleteByProjectGUID(const CString &guid)
{
 size_t size=vector_SProject.size();
 for(size_t n=0;n<size;n++)
 {
  SProject &sProject_Local=vector_SProject[n];
  if (sProject_Local.ProjectGUID.Compare(guid)==0)
  { 
   vector_SProject.erase(vector_SProject.begin()+n);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� GUID �������
//----------------------------------------------------------------------------------------------------
bool CVectorProject::ChangeByProjectGUID(const CString &guid,const SProject &sProject)
{
 size_t size=vector_SProject.size();
 for(size_t n=0;n<size;n++)
 {
  SProject &sProject_Local=vector_SProject[n];
  if (sProject_Local.ProjectGUID.Compare(guid)==0)
  { 
   sProject_Local=sProject;
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ��������
//----------------------------------------------------------------------------------------------------
size_t CVectorProject::Size(void)
{
 return(vector_SProject.size());
}
//----------------------------------------------------------------------------------------------------
//�������� ��������� ������ � ������� ���
//----------------------------------------------------------------------------------------------------
bool CVectorProject::PopBack(SProject &sProject)
{
 size_t size=vector_SProject.size();
 if (size==0) return(false);
 sProject=vector_SProject[size-1];
 vector_SProject.pop_back();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ � �����
//----------------------------------------------------------------------------------------------------
bool CVectorProject::PushBack(const SProject &sProject)
{
 vector_SProject.push_back(sProject);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ �� ������ ��������
//----------------------------------------------------------------------------------------------------
vector<SProject>& CVectorProject::GetVectorSProject(void)
{
 return(vector_SProject);
}
