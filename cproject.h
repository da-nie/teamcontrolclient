#ifndef CPROJECT_H
#define CPROJECT_H

//====================================================================================================
//��������
//====================================================================================================

//����� ��������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "craiifilein.h"
#include "craiifileout.h"

#include "stdafx.h"
#include "csafestring.h"
//====================================================================================================
//����������������
//====================================================================================================

//��� �������
enum PROJECT_TYPE
{
 //��� ����
 PROJECT_TYPE_NONE,
 //������ �� ��������
 PROJECT_TYPE_DELETED,
 //������ �� ���������
 PROJECT_TYPE_CHANGED,
 //������ �� ����������
 PROJECT_TYPE_ADDED
};


//====================================================================================================
//����� ��������
//====================================================================================================
class CProject
{
 private:
  //��������� ��� �������� � ���������� ������
  #pragma pack(1)
  struct SHeader
  {
   unsigned long ProjectNameSize;//�������
   unsigned long ProjectGUIDSize;//������������� �������
   PROJECT_TYPE ProjectType;//��� �������
  };
  #pragma pack()

  CSafeString ProjectName;//�������� �������
  CSafeString ProjectGUID;//���������� �������������  
  //�������������� ������
  PROJECT_TYPE ProjectType;//��� �������
  bool ChangeData;//���������� ������ �������
  //-���������� ������-------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CProject(void);
  //-���������� ������-------------------------------------------------------
  ~CProject();
  //-������� ������----------------------------------------------------------
  const CSafeString& GetProjectName(void) const;//�������� ��������
  const CSafeString& GetProjectGUID(void) const;//�������� ���������� �������������
  const bool& GetChangeData(void) const;//��������, ���������� �� ������ �������

  void SetProjectName(const char *project_name);//������ ��������
  void SetProjectGUID(const char *guid);//������ ���������� �������������
  void SetChangeData(const bool& change_data);//������ ���������� �� ������ �������

  void MarkForWork(void);//�������� ��� ������
  void MarkForDelete(void);//�������� ��� ��������
  void MarkForChange(void);//�������� ��� ������
  void MarkForAdd(void);//�������� ��� ����������

  bool IsMarkForWork(void) const;//�������� �� ��� ������
  bool IsMarkForDelete(void) const;//�������� �� ��� ��������
  bool IsMarkForChange(void) const;//�������� �� ��� ������
  bool IsMarkForAdd(void) const;//�������� �� ��� ����������

  bool IsProjectGUID(const char *guid) const;//������ �� ProjectGUID

  bool Save(CRAIIFileOut &cRAIIFileOut) const;//��������� ������
  bool Load(CRAIIFileIn &cRAIIFileIn);//��������� ������
};
#endif
