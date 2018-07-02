#include "cproject.h"
#include "crc.h"
#include "cuniquearrayptr.h"

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
bool CProject::Save(CRAIIFileOut &cRAIIFileOut) const
{
 const char *s_ptr;
 //��������� ���������
 SHeader sHeader;
 sHeader.ProjectNameSize=ProjectName.GetLength();
 sHeader.ProjectGUIDSize=ProjectGUID.GetLength();
 sHeader.ProjectType=ProjectType;

 if (cRAIIFileOut.GetHandle().write((char *)&sHeader,sizeof(SHeader)*1)==false) return(false);

 //������� crc
 unsigned short crc16=0;
 CreateCRC16(crc16,&sHeader,sizeof(SHeader)*1);
 //���������� crc
 if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);

 s_ptr=ProjectName;
 CreateCRC16(crc16,s_ptr,ProjectName.GetLength());
 s_ptr=ProjectGUID;
 CreateCRC16(crc16,s_ptr,ProjectGUID.GetLength());

 //���������� crc
 if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);

 //���������� ������  
 s_ptr=ProjectName;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(unsigned char)*ProjectName.GetLength())==false) return(false);
 s_ptr=ProjectGUID;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(unsigned char)*ProjectGUID.GetLength())==false) return(false);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� ������
//----------------------------------------------------------------------------------------------------
bool CProject::Load(CRAIIFileIn &cRAIIFileIn)
{
 unsigned short crc16_file;
 unsigned short crc16=0;

 SHeader sHeader;
 if (cRAIIFileIn.GetHandle().read((char*)&sHeader,sizeof(SHeader)*1)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);
 CreateCRC16(crc16,&sHeader,sizeof(SHeader));
 if (crc16!=crc16_file) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);

 CUniqueArrayPtr<char> project_guid;
 CUniqueArrayPtr<char> project_name;

 project_guid.Set(new char[sHeader.ProjectGUIDSize+1]);
 project_name.Set(new char[sHeader.ProjectNameSize+1]);
 
 if (cRAIIFileIn.GetHandle().read((char*)project_name.Get(),sizeof(char)*sHeader.ProjectNameSize)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)project_guid.Get(),sizeof(char)*sHeader.ProjectGUIDSize)==false) return(false);

 CreateCRC16(crc16,project_name.Get(),sizeof(char)*sHeader.ProjectNameSize);
 CreateCRC16(crc16,project_guid.Get(),sizeof(char)*sHeader.ProjectGUIDSize);

 if (crc16!=crc16_file) return(false);

 project_name.Get()[sHeader.ProjectNameSize]=0;
 project_guid.Get()[sHeader.ProjectGUIDSize]=0;

 ProjectName=project_name.Get();
 ProjectGUID=project_guid.Get();
 ProjectType=sHeader.ProjectType;

 return(true);
}
