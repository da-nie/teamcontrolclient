#include "cvector_project.h"
#include "crc.h"

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
 FILE *file=fopen(filename,"wb");
 if (file==NULL) return(false);
 //пишем сигнатуру и номер версии структуры данных
 unsigned short crc16=0;
 fwrite("PLV",sizeof(unsigned char),3,file);
 fwrite(&Version,sizeof(unsigned long),1,file);
 CreateCRC16(crc16,&Version,sizeof(unsigned long)*1);

 size_t size=vector_CProject.size();
 fwrite(&size,sizeof(size_t),1,file);
 CreateCRC16(crc16,&size,sizeof(size_t)*1);
 //записываем CRC
 fwrite(&crc16,sizeof(unsigned short),1,file);

 for(size_t n=0;n<size;n++)
 {
  const CProject &cProject=vector_CProject[n]; 
  if (cProject.Save(file)==false) break;
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorProject::Load(char *filename)
{
 vector_CProject.clear();

 FILE *file=fopen(filename,"rb");
 if (file==NULL) return(false);
 unsigned char signature[3];
 unsigned long version;
 unsigned short crc16_file;
 if (fread(signature,sizeof(unsigned char),3,file)<3)
 {
  fclose(file);
  return(false);
 }
 if (fread(&version,sizeof(unsigned long),1,file)<1)
 {
  fclose(file);
  return(false);
 }
 if (signature[0]!='P' || signature[1]!='L' || signature[2]!='V' || version!=Version)
 {
  fclose(file);
  return(false);
 }
 size_t size;
 if (fread(&size,sizeof(size_t),1,file)<1)
 {
  fclose(file);
  return(false);
 }  
 if (fread(&crc16_file,sizeof(unsigned short),1,file)<1)
 {
  fclose(file);
  return(false);
 }

 unsigned short crc16=0;
 CreateCRC16(crc16,&version,sizeof(unsigned long)*1);
 CreateCRC16(crc16,&size,sizeof(size_t)*1);
 
 if (crc16_file!=crc16)
 {
  fclose(file);
  return(false);
 }

 for(size_t n=0;n<size;n++)
 {
  CProject cProject;
  if (cProject.Load(file)==false) break;
  vector_CProject.push_back(cProject);
 }
 fclose(file);
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
vector<CProject>& CVectorProject::GetVectorCProject(void)
{
 return(vector_CProject);
}
