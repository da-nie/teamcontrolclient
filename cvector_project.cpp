#include <fstream>

#include "cvector_project.h"
#include "crc.h"
#include "craiifilein.h"
#include "craiifileout.h"

//====================================================================================================
//конструктор
//====================================================================================================
CVectorProject::CVectorProject()
{
 Version=2;
}
//====================================================================================================
//деструктор
//====================================================================================================
CVectorProject::~CVectorProject()
{
}
//====================================================================================================
//функции
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//сохранить
//----------------------------------------------------------------------------------------------------
bool CVectorProject::Save(char *filename)
{
 CRAIIFileOut cRAIIFileOut(filename,std::ios_base::out|std::ios_base::binary);
 {
  if (cRAIIFileOut.IsOpened()==false) return(false);

  //пишем сигнатуру и номер версии структуры данных
  unsigned short crc16=0;
  if (cRAIIFileOut.GetHandle().write((char *)"PLV",sizeof(unsigned char)*3)==false) return(false);
  if (cRAIIFileOut.GetHandle().write((char *)&Version,sizeof(unsigned long)*1)==false) return(false);
  CreateCRC16(crc16,&Version,sizeof(unsigned long)*1);
 
  size_t size=vector_CProject.size();
  if (cRAIIFileOut.GetHandle().write((char *)&size,sizeof(size_t)*1)==false) return(false);
  CreateCRC16(crc16,&size,sizeof(size_t)*1);
  //записываем CRC
  if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);
 
  for(size_t n=0;n<size;n++)
  {
   const CProject &cProject=vector_CProject[n]; 
   if (cProject.Save(cRAIIFileOut)==false) break;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorProject::Load(char *filename)
{
 vector_CProject.clear();

 CRAIIFileIn cRAIIFileIn(filename,std::ios_base::in|std::ios_base::binary);
 {
  if (cRAIIFileIn.IsOpened()==false) return(false);
  unsigned char signature[3];
  unsigned long version;
  unsigned short crc16_file;
  if (cRAIIFileIn.GetHandle().read((char*)signature,sizeof(unsigned char)*3)==false) return(false);
  if (cRAIIFileIn.GetHandle().read((char*)&version,sizeof(unsigned long)*1)==false) return(false);
  if (signature[0]!='P' || signature[1]!='L' || signature[2]!='V' || version!=Version) return(false);
  size_t size;
  if (cRAIIFileIn.GetHandle().read((char*)&size,sizeof(size_t)*1)==false) return(false);
  if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);
  unsigned short crc16=0;
  CreateCRC16(crc16,&version,sizeof(unsigned long)*1);
  CreateCRC16(crc16,&size,sizeof(size_t)*1);
 
  if (crc16_file!=crc16) return(false);

  for(size_t n=0;n<size;n++)
  {
   CProject cProject;
   if (cProject.Load(cRAIIFileIn)==false) break;
   vector_CProject.push_back(cProject);
  }
 }
 return(true);
}

//----------------------------------------------------------------------------------------------------
//добавить новый элемент
//----------------------------------------------------------------------------------------------------
bool CVectorProject::AddNew(const CProject &cProject)
{
 vector_CProject.push_back(cProject);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//очистить список
//----------------------------------------------------------------------------------------------------
void CVectorProject::Clear(void)
{
 vector_CProject.clear();
}
//----------------------------------------------------------------------------------------------------
//найти по GUID проекта
//----------------------------------------------------------------------------------------------------
bool CVectorProject::FindByProjectGUID(const CSafeString &guid,CProject &cProject)
{
 size_t size=vector_CProject.size();
 for(size_t n=0;n<size;n++)
 {
  cProject=vector_CProject[n];
  if (cProject.IsProjectGUID(guid)==true) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID проекта и отметить, что данные не изменены
//----------------------------------------------------------------------------------------------------
bool CVectorProject::FindByProjectGUIDAndResetChangeData(const CSafeString &guid,CProject &cProject)
{
 size_t size=vector_CProject.size();
 for(size_t n=0;n<size;n++)
 {
  cProject=vector_CProject[n];
  if (cProject.IsProjectGUID(guid)==true)
  {
   vector_CProject[n].SetChangeData(false);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//удалить по GUID проекта
//----------------------------------------------------------------------------------------------------
bool CVectorProject::DeleteByProjectGUID(const CSafeString &guid)
{
 size_t size=vector_CProject.size();
 for(size_t n=0;n<size;n++)
 {
  CProject &cProject_Local=vector_CProject[n];
  if (cProject_Local.IsProjectGUID(guid)==true)
  { 
   vector_CProject.erase(vector_CProject.begin()+n);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//заменить по GUID проекта
//----------------------------------------------------------------------------------------------------
bool CVectorProject::ChangeByProjectGUID(const CSafeString &guid,const CProject &cProject)
{
 size_t size=vector_CProject.size();
 for(size_t n=0;n<size;n++)
 {
  CProject &cProject_Local=vector_CProject[n];
  if (cProject_Local.IsProjectGUID(guid)==true)
  { 
   cProject_Local=cProject;
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//получить количество проектов
//----------------------------------------------------------------------------------------------------
size_t CVectorProject::Size(void)
{
 return(vector_CProject.size());
}
//----------------------------------------------------------------------------------------------------
//получить последний проект и удалить его
//----------------------------------------------------------------------------------------------------
bool CVectorProject::PopBack(CProject &cProject)
{
 size_t size=vector_CProject.size();
 if (size==0) return(false);
 cProject=vector_CProject[size-1];
 vector_CProject.pop_back();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить проект в конец
//----------------------------------------------------------------------------------------------------
bool CVectorProject::PushBack(const CProject &cProject)
{
 vector_CProject.push_back(cProject);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на вектор проектов
//----------------------------------------------------------------------------------------------------
std::vector<CProject>& CVectorProject::GetVectorCProject(void)
{
 return(vector_CProject);
}
