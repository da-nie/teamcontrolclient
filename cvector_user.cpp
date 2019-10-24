#include "cvector_user.h"
#include "crc.h"

//====================================================================================================
//конструктор
//====================================================================================================
CVectorUser::CVectorUser()
{
 Version=2;
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
 CRAIIFileOut cRAIIFileOut(filename,std::ios_base::out|std::ios_base::binary);
 {
  if (cRAIIFileOut.IsOpened()==false) return(false);

  //пишем сигнатуру и номер версии структуры данных
  unsigned short crc16=0;
  if (cRAIIFileOut.GetHandle().write((char *)"ULV",sizeof(unsigned char)*3)==false) return(false);
  if (cRAIIFileOut.GetHandle().write((char *)&Version,sizeof(unsigned long)*1)==false) return(false);
  CreateCRC16(crc16,&Version,sizeof(unsigned long)*1);
  //пишем файл
  size_t size=vector_CUser.size();
  if (cRAIIFileOut.GetHandle().write((char *)&size,sizeof(size_t)*1)==false) return(false);  
  CreateCRC16(crc16,&size,sizeof(size_t)*1);
  //записываем CRC
  if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);
 
  for(size_t n=0;n<size;n++)
  {
   const CUser &cUser=vector_CUser[n]; 
   if (cUser.Save(cRAIIFileOut)==false) break;
  }
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CVectorUser::Load(char *filename)
{
 vector_CUser.clear();

 CRAIIFileIn cRAIIFileIn(filename,std::ios_base::in|std::ios_base::binary);
 {
  if (cRAIIFileIn.IsOpened()==false) return(false);
  unsigned char signature[3];
  unsigned long version;
  unsigned short crc16_file;
  if (cRAIIFileIn.GetHandle().read((char*)signature,sizeof(unsigned char)*3)==false) return(false);
  if (cRAIIFileIn.GetHandle().read((char*)&version,sizeof(unsigned long)*1)==false) return(false);
  if (signature[0]!='U' || signature[1]!='L' || signature[2]!='V' || version!=Version) return(false);
  size_t size;
  if (cRAIIFileIn.GetHandle().read((char*)&size,sizeof(size_t)*1)==false) return(false);
  if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);
  unsigned short crc16=0;
  CreateCRC16(crc16,&version,sizeof(unsigned long)*1);
  CreateCRC16(crc16,&size,sizeof(size_t)*1);
  if (crc16_file!=crc16) return(false);
  for(size_t n=0;n<size;n++)
  {
   CUser cUser;
   if (cUser.Load(cRAIIFileIn)==false) break;
   vector_CUser.push_back(cUser);
  }
 }
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
std::vector<CUser>& CVectorUser::GetVectorCUser(void)
{
 return(vector_CUser);
}
