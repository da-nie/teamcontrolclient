#include "cuser.h"
#include "crc.h"
#include "cuniquearrayptr.h"

//====================================================================================================
//����������� ������
//====================================================================================================
CUser::CUser(void)
{
 Name="";
 JobTitle="";
 Login="";
 Password="";
 Description="";
 Telephone="";
 UserGUID="";
 Leader=false;
 ChangeData=false;
}
//====================================================================================================
//���������� ������
//====================================================================================================
CUser::~CUser()
{		
}
//====================================================================================================
//������� ������
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//�������� ���
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetName(void) const
{
 return(Name);
}
//----------------------------------------------------------------------------------------------------
//�������� �����
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetLogin(void) const
{
 return(Login);
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetPassword(void) const
{
 return(Password);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetJobTitle(void) const
{
 return(JobTitle);
}
//----------------------------------------------------------------------------------------------------
//�������� ��������
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetDescription(void) const
{
 return(Description);
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetTelephone(void) const
{
 return(Telephone);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� ������������� ������������
//----------------------------------------------------------------------------------------------------
const CSafeString& CUser::GetUserGUID(void) const
{
 return(UserGUID);
}
//----------------------------------------------------------------------------------------------------
//��������, �������� �� �������������
//----------------------------------------------------------------------------------------------------
const bool& CUser::GetLeader(void) const
{
 return(Leader);
}
//----------------------------------------------------------------------------------------------------
//��������, ���������� �� ������ ����������
//----------------------------------------------------------------------------------------------------
const bool& CUser::GetChangeData(void) const
{
 return(ChangeData);
}

//----------------------------------------------------------------------------------------------------
//������ ���
//----------------------------------------------------------------------------------------------------
void CUser::SetName(const char *name)
{
 Name=name;
}
//----------------------------------------------------------------------------------------------------
//������ �����
//----------------------------------------------------------------------------------------------------
void CUser::SetLogin(const char *login)
{
 Login=login;
}
//----------------------------------------------------------------------------------------------------
//������ ������
//----------------------------------------------------------------------------------------------------
void CUser::SetPassword(const char *password)
{
 Password=password;
}
//----------------------------------------------------------------------------------------------------
//������ ���������
//----------------------------------------------------------------------------------------------------
void CUser::SetJobTitle(const char *job_title)
{
 JobTitle=job_title;
}
//----------------------------------------------------------------------------------------------------
//������ ��������
//----------------------------------------------------------------------------------------------------
void CUser::SetDescription(const char *description)
{
 Description=description;
}
//----------------------------------------------------------------------------------------------------
//������ �������
//----------------------------------------------------------------------------------------------------
void CUser::SetTelephone(const char *telephone)
{
 Telephone=telephone;
}
//----------------------------------------------------------------------------------------------------
//������ ���������� ������������� ������������
//----------------------------------------------------------------------------------------------------
void CUser::SetUserGUID(const char *user_guid)
{
 UserGUID=user_guid;
}
//----------------------------------------------------------------------------------------------------
//������, �������� �� �������������
//----------------------------------------------------------------------------------------------------
void CUser::SetLeader(bool leader)
{
 Leader=leader;
}
//----------------------------------------------------------------------------------------------------
//������, ���������� �� ������ ����������
//----------------------------------------------------------------------------------------------------
void CUser::SetChangeData(bool change_data)
{
 ChangeData=change_data;
}

//----------------------------------------------------------------------------------------------------
//������ �� ����� � ������
//----------------------------------------------------------------------------------------------------
bool CUser::IsLoginAndPassword(const char *login,const char *password) const
{
 if (Login.Compare(CSafeString(const_cast<char*>(login)))==0 && Password.Compare(CSafeString(const_cast<char*>(password)))==0) return(true);
 return(false);
}
//----------------------------------------------------------------------------------------------------
//������ �� UserGUID
//----------------------------------------------------------------------------------------------------
bool CUser::IsUserGUID(const char *guid) const
{
 if (UserGUID.Compare(const_cast<char*>(guid))==0) return(true);    
 return(false);
}

//----------------------------------------------------------------------------------------------------
//��������� ������
//----------------------------------------------------------------------------------------------------
bool CUser::Save(CRAIIFileOut &cRAIIFileOut) const
{
 const char *s_ptr;
 //��������� ���������
 SHeader sHeader;
 sHeader.NameSize=Name.GetLength();
 sHeader.JobTitleSize=JobTitle.GetLength();
 sHeader.TelephoneSize=Telephone.GetLength();
 sHeader.DescriptionSize=Description.GetLength();
 sHeader.UserGUIDSize=UserGUID.GetLength();
 sHeader.Leader=Leader;

 if (cRAIIFileOut.GetHandle().write((char *)&sHeader,sizeof(SHeader)*1)==false) return(false);

 //������� crc
 unsigned short crc16=0;
 CreateCRC16(crc16,&sHeader,sizeof(SHeader)*1);
 //���������� crc

 if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);

 s_ptr=Name;
 CreateCRC16(crc16,s_ptr,Name.GetLength());
 s_ptr=JobTitle;
 CreateCRC16(crc16,s_ptr,JobTitle.GetLength());
 s_ptr=Telephone;
 CreateCRC16(crc16,s_ptr,Telephone.GetLength());
 s_ptr=Description;
 CreateCRC16(crc16,s_ptr,Description.GetLength());
 s_ptr=UserGUID;
 CreateCRC16(crc16,s_ptr,UserGUID.GetLength());

 //���������� crc
 if (cRAIIFileOut.GetHandle().write((char *)&crc16,sizeof(unsigned short)*1)==false) return(false);
 
 //���������� ������
 s_ptr=Name;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(char)*Name.GetLength())==false) return(false);
 s_ptr=JobTitle;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(char)*JobTitle.GetLength())==false) return(false);
 s_ptr=Telephone;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(char)*Telephone.GetLength())==false) return(false);
 s_ptr=Description;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(char)*Description.GetLength())==false) return(false);
 s_ptr=UserGUID;
 if (cRAIIFileOut.GetHandle().write((char *)s_ptr,sizeof(char)*UserGUID.GetLength())==false) return(false);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� ������
//----------------------------------------------------------------------------------------------------
bool CUser::Load(CRAIIFileIn &cRAIIFileIn)
{
 unsigned short crc16_file;
 unsigned short crc16=0;

 SHeader sHeader;
 if (cRAIIFileIn.GetHandle().read((char*)&sHeader,sizeof(SHeader)*1)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);
 CreateCRC16(crc16,&sHeader,sizeof(SHeader)); 
 if (crc16!=crc16_file) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)&crc16_file,sizeof(unsigned short)*1)==false) return(false);

 CUniqueArrayPtr<char> name;
 CUniqueArrayPtr<char> job_title;
 CUniqueArrayPtr<char> telephone;
 CUniqueArrayPtr<char> description;
 CUniqueArrayPtr<char> user_guid;

 name.Set(new char[sHeader.NameSize+1]);
 job_title.Set(new char[sHeader.JobTitleSize+1]);
 telephone.Set(new char[sHeader.TelephoneSize+1]);
 description.Set(new char[sHeader.DescriptionSize+1]);
 user_guid.Set(new char[sHeader.UserGUIDSize+1]);
 
 if (cRAIIFileIn.GetHandle().read((char*)name.Get(),sizeof(char)*sHeader.NameSize)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)job_title.Get(),sizeof(char)*sHeader.JobTitleSize)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)telephone.Get(),sizeof(char)*sHeader.TelephoneSize)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)description.Get(),sizeof(char)*sHeader.DescriptionSize)==false) return(false);
 if (cRAIIFileIn.GetHandle().read((char*)user_guid.Get(),sizeof(char)*sHeader.UserGUIDSize)==false) return(false);

 CreateCRC16(crc16,name.Get(),sizeof(char)*sHeader.NameSize); 
 CreateCRC16(crc16,job_title.Get(),sizeof(char)*sHeader.JobTitleSize);
 CreateCRC16(crc16,telephone.Get(),sizeof(char)*sHeader.TelephoneSize);
 CreateCRC16(crc16,description.Get(),sizeof(char)*sHeader.DescriptionSize);
 CreateCRC16(crc16,user_guid.Get(),sizeof(char)*sHeader.UserGUIDSize);

 if (crc16!=crc16_file) return(false); 

 name.Get()[sHeader.NameSize]=0;
 job_title.Get()[sHeader.JobTitleSize]=0;
 telephone.Get()[sHeader.TelephoneSize]=0;
 description.Get()[sHeader.DescriptionSize]=0;
 user_guid.Get()[sHeader.UserGUIDSize]=0;

 Name=name.Get();
 JobTitle=job_title.Get();
 Telephone=telephone.Get();
 Description=description.Get();
 UserGUID=user_guid.Get();
 Leader=sHeader.Leader;

 return(true);
}
