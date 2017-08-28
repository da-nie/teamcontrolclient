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
 size_t size=vector_CUser.size();
 fwrite(&size,sizeof(size_t),1,file);
 for(size_t n=0;n<size;n++)
 {
  const CUser &cUser=vector_CUser[n]; 
  if (cUser.Save(file)==false) break;
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorUser::Load(char *filename)
{
 vector_CUser.clear();

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
  CUser cUser;
  if (cUser.Load(file)==false) break;
  vector_CUser.push_back(cUser);
 }
 fclose(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить новый элемент
//----------------------------------------------------------------------------------------------------
bool CVectorUser::AddNew(const CUser &cUser)
{
 vector_CUser.push_back(cUser);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//очистить список
//----------------------------------------------------------------------------------------------------
void CVectorUser::Clear(void)
{
 vector_CUser.clear();
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя
//----------------------------------------------------------------------------------------------------
bool CVectorUser::FindByUserGUID(const CSafeString &guid,CUser &cUser)
{
 size_t size=vector_CUser.size();
 for(size_t n=0;n<size;n++)
 {
  cUser=vector_CUser[n];
  if (cUser.IsUserGUID(guid)==true) return(true);
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//найти по GUID пользователя и отметить, что данные не изменены
//----------------------------------------------------------------------------------------------------
bool CVectorUser::FindByUserGUIDAndResetChangeData(const CSafeString &guid,CUser &cUser)
{
 size_t size=vector_CUser.size();
 for(size_t n=0;n<size;n++)
 {
  cUser=vector_CUser[n];
  if (cUser.IsUserGUID(guid)==true)
  {
   vector_CUser[n].SetChangeData(false);
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
 size_t size=vector_CUser.size();
 for(size_t n=0;n<size;n++)
 {
  CUser &cUser_Local=vector_CUser[n];
  if (cUser_Local.IsUserGUID(guid)==true)
  { 
   vector_CUser.erase(vector_CUser.begin()+n);
   return(true);
  }
 }
 return(false);
}
//----------------------------------------------------------------------------------------------------
//заменить по GUID пользователя
//----------------------------------------------------------------------------------------------------
bool CVectorUser::ChangeByUserGUID(const CSafeString &guid,const CUser &cUser)
{
 size_t size=vector_CUser.size();
 for(size_t n=0;n<size;n++)
 {
  CUser &cUser_Local=vector_CUser[n];
  if (cUser_Local.IsUserGUID(guid)==true)
  { 
   cUser_Local=cUser;
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
 return(vector_CUser.size());
}
//----------------------------------------------------------------------------------------------------
//получить последнего пользователя и удалить его
//----------------------------------------------------------------------------------------------------
bool CVectorUser::PopBack(CUser &cUser)
{
 size_t size=vector_CUser.size();
 if (size==0) return(false);
 cUser=vector_CUser[size-1];
 vector_CUser.pop_back();
 return(true);
}
//----------------------------------------------------------------------------------------------------
//добавить пользователя в конец
//----------------------------------------------------------------------------------------------------
bool CVectorUser::PushBack(const CUser &cUser)
{
 vector_CUser.push_back(cUser);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на вектор пользователей
//----------------------------------------------------------------------------------------------------
vector<CUser>& CVectorUser::GetVectorCUser(void)
{
 return(vector_CUser);
}
