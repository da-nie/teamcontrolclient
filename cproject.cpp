#include "cproject.h"
#include "crc.h"
#include "cuniquearrayptr.h"

//====================================================================================================
//конструктор класса
//====================================================================================================
CProject::CProject(void)
{
 ProjectName="";
 ProjectGUID="";
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CProject::~CProject()
{		
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//получить название
//----------------------------------------------------------------------------------------------------
const CSafeString& CProject::GetProjectName(void) const
{
 return(ProjectName);
}
//----------------------------------------------------------------------------------------------------
//получить уникальный идентификатор
//----------------------------------------------------------------------------------------------------
const CSafeString& CProject::GetProjectGUID(void) const
{
 return(ProjectGUID);
}
//----------------------------------------------------------------------------------------------------
//получить, изменились ли данные проекта
//----------------------------------------------------------------------------------------------------
const bool& CProject::GetChangeData(void) const
{
 return(ChangeData);
}
//----------------------------------------------------------------------------------------------------
//задать название
//----------------------------------------------------------------------------------------------------
void CProject::SetProjectName(const char *project_name)
{
 ProjectName=project_name;
}
//----------------------------------------------------------------------------------------------------
//задать уникальный идентификатор
//----------------------------------------------------------------------------------------------------
void CProject::SetProjectGUID(const char *guid)
{
 ProjectGUID=guid;
}
//----------------------------------------------------------------------------------------------------
//задать изменились ли данные проекта
//----------------------------------------------------------------------------------------------------
void CProject::SetChangeData(const bool& change_data)
{
 ChangeData=change_data;
}
//----------------------------------------------------------------------------------------------------
//отметить дл€ работы
//----------------------------------------------------------------------------------------------------
void CProject::MarkForWork(void)
{
 ProjectType=PROJECT_TYPE_NONE;
}
//----------------------------------------------------------------------------------------------------
//отметить дл€ удалени€
//----------------------------------------------------------------------------------------------------
void CProject::MarkForDelete(void)
{
 ProjectType=PROJECT_TYPE_DELETED;
}
//----------------------------------------------------------------------------------------------------
//отметить дл€ замены
//----------------------------------------------------------------------------------------------------
void CProject::MarkForChange(void)
{
 ProjectType=PROJECT_TYPE_CHANGED;
}
//----------------------------------------------------------------------------------------------------
//отметить дл€ добавлени€
//----------------------------------------------------------------------------------------------------
void CProject::MarkForAdd(void)
{
 ProjectType=PROJECT_TYPE_ADDED;
}

//----------------------------------------------------------------------------------------------------
//отмечено ли дл€ работы
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForWork(void) const
{
 if (ProjectType==PROJECT_TYPE_NONE) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//отмечено ли дл€ удалени€
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForDelete(void) const
{
 if (ProjectType==PROJECT_TYPE_DELETED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//отмечено ли дл€ замены
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForChange(void) const
{
 if (ProjectType==PROJECT_TYPE_CHANGED) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//отмечено ли дл€ добавлени€
//----------------------------------------------------------------------------------------------------
bool CProject::IsMarkForAdd(void) const
{
 if (ProjectType==PROJECT_TYPE_ADDED) return(true);
 return(false);
}

//----------------------------------------------------------------------------------------------------
//верный ли ProjectGUID
//----------------------------------------------------------------------------------------------------
bool CProject::IsProjectGUID(const char *guid) const
{
 if (ProjectGUID.Compare(const_cast<char*>(guid))==0) return(true);    
 return(false);
}
//----------------------------------------------------------------------------------------------------
//сохранить данные
//----------------------------------------------------------------------------------------------------
bool CProject::Save(FILE *file) const
{
 const char *s_ptr;
 //заполн€ем заголовок
 SHeader sHeader;
 sHeader.ProjectNameSize=ProjectName.GetLength();
 sHeader.ProjectGUIDSize=ProjectGUID.GetLength();
 sHeader.ProjectType=ProjectType;

 fwrite(reinterpret_cast<const char*>(&sHeader),sizeof(SHeader),1,file);

//считаем crc
 unsigned short crc16=0;
 CreateCRC16(crc16,&sHeader,sizeof(SHeader)*1);
 //записываем crc
 fwrite(&crc16,sizeof(unsigned short),1,file);

 s_ptr=ProjectName;
 CreateCRC16(crc16,s_ptr,ProjectName.GetLength());
 s_ptr=ProjectGUID;
 CreateCRC16(crc16,s_ptr,ProjectGUID.GetLength());

 //записываем crc
 fwrite(&crc16,sizeof(unsigned short),1,file);

 //записываем данные  
 s_ptr=ProjectName;
 fwrite(s_ptr,ProjectName.GetLength(),1,file);
 s_ptr=ProjectGUID;
 fwrite(s_ptr,ProjectGUID.GetLength(),1,file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить данные
//----------------------------------------------------------------------------------------------------
bool CProject::Load(FILE *file)
{
 unsigned short crc16_file;
 unsigned short crc16=0;

 SHeader sHeader;
 if (fread(&sHeader,sizeof(SHeader),1,file)<1) return(false);
 if (fread(&crc16_file,sizeof(unsigned short),1,file)<1) return(false);
 CreateCRC16(crc16,&sHeader,sizeof(SHeader));
 if (crc16!=crc16_file) return(false);
 if (fread(&crc16_file,sizeof(unsigned short),1,file)<1) return(false);

 CUniqueArrayPtr<char> project_guid;
 CUniqueArrayPtr<char> project_name;

 project_guid.Set(new char[sHeader.ProjectGUIDSize+1]);
 project_name.Set(new char[sHeader.ProjectNameSize+1]);
 
 if (fread(project_name.Get(),sizeof(char),sHeader.ProjectNameSize,file)<sHeader.ProjectNameSize) return(false);
 if (fread(project_guid.Get(),sizeof(char),sHeader.ProjectGUIDSize,file)<sHeader.ProjectGUIDSize) return(false); 

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
