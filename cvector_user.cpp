#include "cvector_user.h"

//====================================================================================================
//конструктор
//====================================================================================================
CVectorUser::CVectorUser()
{
 Version=1;
}
//====================================================================================================
//деструктор
//====================================================================================================
CVectorUser::~CVectorUser()
{
}
//====================================================================================================
//функции
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//сохранить
//----------------------------------------------------------------------------------------------------
bool CVectorUser::Save(char *filename)
{
 FILE *file=fopen(filename,"wb");
 if (file==NULL) return(false);
 //пишем сигнатуру и номер версии структуры данных
 fwrite("ULV",sizeof(unsigned char),3,file);
 fwrite(&Version,sizeof(unsigned long),1,file);
 //пишем файл
 size_t size=vector_SUser.size();
 fwrite(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  const SUser &sUser=vector_SUser[n]; 
  //заполняем заголовок
  SHeader sHeader;
  sHeader.NameSize=sUser.Name.GetLength();
  sHeader.JobTitleSize=sUser.JobTitle.GetLength();
  sHeader.TelephoneSize=sUser.Telephone.GetLength();
  sHeader.DescriptionSize=sUser.Description.GetLength();
  sHeader.UserGUIDSize=sUser.UserGUID.GetLength();
  sHeader.Leader=sUser.Leader;
  fwrite(reinterpret_cast<const char*>(&sHeader),sizeof(SHeader),1,file);
  const char *s_ptr;
  s_ptr=sUser.Name;
  fwrite(s_ptr,sUser.Name.GetLength(),1,file);
  s_ptr=sUser.JobTitle;
  fwrite(s_ptr,sUser.JobTitle.GetLength(),1,file);
  s_ptr=sUser.Telephone;
  fwrite(s_ptr,sUser.Telephone.GetLength(),1,file);
  s_ptr=sUser.Description;
  fwrite(s_ptr,sUser.Description.GetLength(),1,file);
  s_ptr=sUser.UserGUID;
  fwrite(s_ptr,sUser.UserGUID.GetLength(),1,file);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorUser::Load(char *filename)
{
 vector_SUser.clear();

 FILE *file=fopen(filename,"rb");
 if (file==NULL) return(false);
 unsigned char signature[3];
 unsigned char version;
 fread(&signature,sizeof(unsigned char),3,file);
 fread(&version,sizeof(unsigned long),1,file);
 if (signature[0]!='U' || signature[1]!='L' || signature[2]!='V' || version!=Version)
 {
  fclose(file);
  return(false);
 }
 size_t size;
 fread(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  SHeader sHeader;
  fread(&sHeader,sizeof(SHeader),1,file);
  char *name=new char[sHeader.NameSize+1];
  char *job_title=new char[sHeader.JobTitleSize+1];
  char *telephone=new char[sHeader.TelephoneSize+1];
  char *description=new char[sHeader.DescriptionSize+1];
  char *user_guid=new char[sHeader.UserGUIDSize+1];
 
  fread(name,sizeof(char),sHeader.NameSize,file);
  fread(job_title,sizeof(char),sHeader.JobTitleSize,file);
  fread(telephone,sizeof(char),sHeader.TelephoneSize,file);
  fread(description,sizeof(char),sHeader.DescriptionSize,file);
  fread(user_guid,sizeof(char),sHeader.UserGUIDSize,file);  
 
  name[sHeader.NameSize]=0;
  job_title[sHeader.JobTitleSize]=0;
  telephone[sHeader.TelephoneSize]=0;
  description[sHeader.DescriptionSize]=0;
  user_guid[sHeader.UserGUIDSize]=0;

  SUser sUser;
  sUser.Name=name;
  sUser.JobTitle=job_title;
  sUser.Telephone=telephone;
  sUser.Description=description;
  sUser.UserGUID=user_guid;
  sUser.Leader=sHeader.Leader;

  delete[](name);
  delete[](job_title);
  delete[](telephone);
  delete[](description);
  delete[](user_guid);

  vector_SUser.push_back(sUser);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить новый элемент
//----------------------------------------------------------------------------------------------------
bool CVectorUser::AddNew(const SUser &sUser)
{
 vector_SUser.push_back(sUser);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//очистить список
//----------------------------------------------------------------------------------------------------
void CVectorUser::Clear(void)
{
 vector_SUser.clear();
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя
//----------------------------------------------------------------------------------------------------
bool CVectorUser::FindByUserGUID(const CSafeString &guid,SUser &sUser)
{
 size_t size=vector_SUser.size();
 for(size_t n=0;n<size;n++)
 {
  sUser=vector_SUser[n];
  if (sUser.UserGUID.Compare(guid)==0) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя и отметить, что данные не изменены
//----------------------------------------------------------------------------------------------------
bool CVectorUser::FindByUserGUIDAndResetChangeData(const CSafeString &guid,SUser &sUser)
{
 size_t size=vector_SUser.size();
 for(size_t n=0;n<size;n++)
 {
  sUser=vector_SUser[n];
  if (sUser.UserGUID.Compare(guid)==0)
  {
   vector_SUser[n].ChangeData=false;
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//удалить по GUID пользователя
//----------------------------------------------------------------------------------------------------
bool CVectorUser::DeleteByUserGUID(const CSafeString &guid)
{
 size_t size=vector_SUser.size();
 for(size_t n=0;n<size;n++)
 {
  SUser &sUser_Local=vector_SUser[n];
  if (sUser_Local.UserGUID.Compare(guid)==0)
  { 
   vector_SUser.erase(vector_SUser.begin()+n);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//заменить по GUID пользователя
//----------------------------------------------------------------------------------------------------
bool CVectorUser::ChangeByUserGUID(const CSafeString &guid,const SUser &sUser)
{
 size_t size=vector_SUser.size();
 for(size_t n=0;n<size;n++)
 {
  SUser &sUser_Local=vector_SUser[n];
  if (sUser_Local.UserGUID.Compare(guid)==0)
  { 
   sUser_Local=sUser;
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//получить количество пользователей
//----------------------------------------------------------------------------------------------------
size_t CVectorUser::Size(void)
{
 return(vector_SUser.size());
}
//----------------------------------------------------------------------------------------------------
//получить последнего пользователя и удалить его
//----------------------------------------------------------------------------------------------------
bool CVectorUser::PopBack(SUser &sUser)
{
 size_t size=vector_SUser.size();
 if (size==0) return(false);
 sUser=vector_SUser[size-1];
 vector_SUser.pop_back();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить пользователя в конец
//----------------------------------------------------------------------------------------------------
bool CVectorUser::PushBack(const SUser &sUser)
{
 vector_SUser.push_back(sUser);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на вектор пользователей
//----------------------------------------------------------------------------------------------------
vector<SUser>& CVectorUser::GetVectorSUser(void)
{
 return(vector_SUser);
}
