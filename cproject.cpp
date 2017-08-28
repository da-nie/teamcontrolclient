#include "cproject.h"

//====================================================================================================
//����������� ������
//====================================================================================================
CProject::CProject(void)
{
 ProjectName="";
 ProjectGUID="";
}
//====================================================================================================
//���������� ������
//====================================================================================================
CProject::~CProject()
{		
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//�������� ��������
//----------------------------------------------------------------------------------------------------
const CSafeString& CProject::GetProjectName(void) const
{
 return(ProjectName);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� �������������
//----------------------------------------------------------------------------------------------------
const CSafeString& CProject::GetProjectGUID(void) const
{
 return(ProjectGUID);
}
//----------------------------------------------------------------------------------------------------
//��������, ���������� �� ������ �������
//----------------------------------------------------------------------------------------------------
const bool& CProject::GetChangeData(void) const
{
 return(ChangeData);
}
//----------------------------------------------------------------------------------------------------
//������ ��������
//----------------------------------------------------------------------------------------------------
void CProject::SetProjectName(const char *project_name)
{
 ProjectName=project_name;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� �������������
//----------------------------------------------------------------------------------------------------
void CProject::SetProjectGUID(const char *guid)
{
 ProjectGUID=guid;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� �� ������ �������
//----------------------------------------------------------------------------------------------------
void CProject::SetChangeData(const bool& change_data)
{
 ChangeData=change_data;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ������
//----------------------------------------------------------------------------------------------------
void CProject::MarkForWork(void)
{
 ProjectType=PROJECT_TYPE_NONE;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ��������
//----------------------------------------------------------------------------------------------------
void CProject::MarkForDelete(void)
{
 ProjectType=PROJECT_TYPE_DELETED;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ������
//----------------------------------------------------------------------------------------------------
void CProject::MarkForChange(void)
{
 ProjectType=PROJECT_TYPE_CHANGED;
}
//----------------------------------------------------------------------------------------------------
//�������� ��� ����������
//----------------------------------------------------------------------------------------------------
void CProject::MarkForAdd(void)
{
 ProjectType=PROJECT_TYPE_ADDED;
}

//----------------------------------------------------------------------------------------------------
//�������� �� ��� ������
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForWork(void) const
{
 if (ProjectType==PROJECT_TYPE_NONE) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��� ��������
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForDelete(void) const
{
 if (ProjectType==PROJECT_TYPE_DELETED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��� ������
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForChange(void) const
{
 if (ProjectType==PROJECT_TYPE_CHANGED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��� ����������
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForAdd(void) const
{
 if (ProjectType==PROJECT_TYPE_ADDED) return(true);
 return(false);
}

//----------------------------------------------------------------------------------------------------
//������ �� ProjectGUID
//----------------------------------------------------------------------------------------------------
bool CProject::IsProjectGUID(const char *guid) const
{
 if (ProjectGUID.Compare(const_cast<char*>(guid))==0) return(true);    
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��������� ������
//----------------------------------------------------------------------------------------------------
bool CProject::Save(FILE *file) const
{
 //��������� ���������
 SHeader sHeader;
 sHeader.ProjectNameSize=ProjectName.GetLength();
 sHeader.ProjectGUIDSize=ProjectGUID.GetLength();
 sHeader.ProjectType=ProjectType;
 fwrite(reinterpret_cast<const char*>(&sHeader),sizeof(SHeader),1,file);
 const char *s_ptr;
 s_ptr=ProjectName;
 fwrite(s_ptr,ProjectName.GetLength(),1,file);
 s_ptr=ProjectGUID;
 fwrite(s_ptr,ProjectGUID.GetLength(),1,file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� ������
//----------------------------------------------------------------------------------------------------
bool CProject::Load(FILE *file)
{
 SHeader sHeader;
 fread(&sHeader,sizeof(SHeader),1,file);
 char *project_guid=new char[sHeader.ProjectGUIDSize+1];
 char *project_name=new char[sHeader.ProjectNameSize+1];
 
 fread(project_name,sizeof(char),sHeader.ProjectNameSize,file);
 fread(project_guid,sizeof(char),sHeader.ProjectGUIDSize,file);  
 
 project_name[sHeader.ProjectNameSize]=0;
 project_guid[sHeader.ProjectGUIDSize]=0;

 ProjectName=project_name;
 ProjectGUID=project_guid;
 ProjectType=sHeader.ProjectType;

 delete[](project_name);
 delete[](project_guid);
 return(true);
}