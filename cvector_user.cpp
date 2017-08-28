#include "cvector_user.h"

//====================================================================================================
//�����������
//====================================================================================================
CVectorUser::CVectorUser()
{
 Version=1;
}
//====================================================================================================
//����������
//====================================================================================================
CVectorUser::~CVectorUser()
{
}
//====================================================================================================
//�������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
bool CVectorUser::Save(char *filename)
{
 FILE *file=fopen(filename,"wb");
 if (file==NULL) return(false);
 //����� ��������� � ����� ������ ��������� ������
 fwrite("ULV",sizeof(unsigned char),3,file);
 fwrite(&Version,sizeof(unsigned long),1,file);
 //����� ����
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
//���������
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
//�������� ����� �������
//----------------------------------------------------------------------------------------------------
bool CVectorUser::AddNew(const CUser &cUser)
{
 vector_CUser.push_back(cUser);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
void CVectorUser::Clear(void)
{
 vector_CUser.clear();
}
//----------------------------------------------------------------------------------------------------
//����� �� GUID ������������
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
//����� �� GUID ������������ � ��������, ��� ������ �� ��������
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
//������� �� GUID ������������
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
//�������� �� GUID ������������
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
//�������� ���������� �������������
//----------------------------------------------------------------------------------------------------
size_t CVectorUser::Size(void)
{
 return(vector_CUser.size());
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������ � ������� ���
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
//�������� ������������ � �����
//----------------------------------------------------------------------------------------------------
bool CVectorUser::PushBack(const CUser &cUser)
{
 vector_CUser.push_back(cUser);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ �� ������ �������������
//----------------------------------------------------------------------------------------------------
vector<CUser>& CVectorUser::GetVectorCUser(void)
{
 return(vector_CUser);
}
