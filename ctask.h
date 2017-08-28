#ifndef CTASK_H
#define CTASK_H

//====================================================================================================
//��������
//====================================================================================================

//����� �������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include "csafestring.h"
#include "cdate.h"
#include "protocol.h"

//====================================================================================================
//����������������
//====================================================================================================

//��� �������
enum TASK_TYPE
{
 //��� ����
 TASK_TYPE_NONE,
 //������� �� ��������
 TASK_TYPE_DELETED,
 //������� �� ���������
 TASK_TYPE_CHANGED,
 //������� �� ����������
 TASK_TYPE_ADDED
};

//====================================================================================================
//����� �������
//====================================================================================================
class CTask
{
 private:
  //��������� ��� �������� � ���������� ������
  #pragma pack(1)
  struct SHeader
  {
   long Index;//������ �������
   unsigned long FromUserGUIDSize;//�� ������������
   unsigned long ForUserGUIDSize;//��� ������������
   unsigned long ProjectGUIDSize;//�� �������
   unsigned long TaskSize;//�������
   unsigned long TaskGUIDSize;//������������� �������
   unsigned long AnswerSize;//�����
   long State;//���������
   long Year;//���
   long Month;//�����
   long Day;//�����    
   TASK_TYPE TaskType;//��� �������
  };
  #pragma pack()

  long Index;//������ �������
  CSafeString FromUserGUID;//�� ������������
  CSafeString ForUserGUID;//��� ������������
  CSafeString ProjectGUID;//�� �������
  CSafeString Task;//�������
  long State;//���������
  CDate cDate;//����
  CSafeString TaskGUID;//������������� �������
  CSafeString Answer;//����� �� �������
  //�������������� ������
  bool ChangeData;//���������� ������ �������
  TASK_TYPE TaskType;//��� �������
  CSafeString ForUser;//��� ������������
  CSafeString FromUser;//�� ������������
  //-���������� ������-------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CTask(void);
  //-���������� ������-------------------------------------------------------
  ~CTask();
  //-������� ������----------------------------------------------------------
  //�������� ��������� �������
  bool operator<(const CTask &cTask) const
  {
   if (cTask==*(this)) return(false);
   if (cTask>*(this)) return(false);
   return(true);
  }
  bool operator>(const CTask &cTask) const
  {
   if (cDate>cTask.cDate) return(true);
   if (cDate==cTask.cDate) 
   {
    if (Index>cTask.Index) return(true);
    return(false);
   }
   return(false);
  }
  bool operator==(const CTask &cTask) const
  {
   if (cDate==cTask.cDate && Index==cTask.Index) return(true);
   return(false);
  }

  const long& GetIndex(void) const;//������� ������
  const CSafeString& GetFromUserGUID(void) const;//�������� ���������� ������������� �� ������ ������������ �������
  const CSafeString& GetForUserGUID(void) const;//�������� ���������� ������������� ��� ������ ������������ �������
  const CSafeString& GetProjectGUID(void) const;//�������� ���������� ������������� �������
  const CSafeString& GetTask(void) const;//�������� �������
  //const long& GetState(void) const;//������� ��������� �������
  const CDate& GetDate(void) const;//�������� ���� �������
  const CSafeString& GetTaskGUID(void) const;//�������� ���������� ������������� �������
  const CSafeString& GetAnswer(void) const;//�������� ����� �� �������
  const bool& GetChangeData(void) const;//��������, ���������� �� ������ �������
  const CSafeString& GetForUser(void) const;//�������� ��� ������������ ��� �������� �������
  const CSafeString& GetFromUser(void) const;//�������� ��� ������������ �� �������� �������

  void SetIndex(const long& index);//������ ������
  void SetFromUserGUID(const char *from_user_guid);//������ ���������� ������������� �� ������ ������������ �������
  void SetForUserGUID(const char *for_user_guid);//������ ���������� ������������� ��� ������ ������������ �������
  void SetProjectGUID(const char *project_guid);//������ ���������� ������������� �������
  void SetTask(const char *task);//������ �������
  //void SetState(const long &state);//������� ��������� �������
  void SetDate(const CDate &cDate_Set);//������ ���� �������
  void SetTaskGUID(const char *task_guid);//������ ���������� ������������� �������
  void SetAnswer(const char *answer);//������ ����� �� �������
  void SetChangeData(const bool& change_data);//������ ���������� �� ������ �������
  void SetForUser(const char *for_user);//������ ��� ������������ ��� �������� �������
  void SetFromUser(const char *from_user);//������ ��� ������������ �� �������� �������

  void SetStateNoRead(void);//����������, ��� ������� �� ���������
  void SetStateReaded(void);//����������, ��� ������� ��������� � ������� ����������
  void SetStateIsRunning(void);//����������, ��� ������� �����������
  void SetStateDone(void);//����������, ��� ������� ���������
  void SetStateCancelled(void);//����������, ��� ������� ���������
  void SetStateFinished(void);//����������, ��� ������� ���������

  void MarkForWork(void);//�������� ��� ������
  void MarkForDelete(void);//�������� ��� ��������
  void MarkForChange(void);//�������� ��� ������
  void MarkForAdd(void);//�������� ��� ����������

  bool IsMarkForWork(void) const;//�������� �� ��� ������
  bool IsMarkForDelete(void) const;//�������� �� ��� ��������
  bool IsMarkForChange(void) const;//�������� �� ��� ������
  bool IsMarkForAdd(void) const;//�������� �� ��� ����������

  bool IsStateNoRead(void) const;//���������, ��� ������� �� ���������
  bool IsStateReaded(void) const;//���������, ��� ������� ��������� � ������� ����������
  bool IsStateIsRunning(void) const;//���������, ��� ������� �����������
  bool IsStateDone(void) const;//���������, ��� ������� ���������
  bool IsStateCancelled(void) const;//���������, ��� ������� ���������
  bool IsStateFinished(void) const;//���������, ��� ������� ���������

  bool IsFromOrForUserGUID(const char *guid) const;//��� ������� �� ��� ��� ������������ � ���������� ���������������
  bool IsForUserGUID(const char *guid) const;//��� ������� ��� ������������ � ���������� ���������������
  bool IsFromUserGUID(const char *guid) const;//��� ������� �� ������������ � ���������� ���������������
  bool IsProjectGUID(const char *guid) const;//��� ������� �� ������� � ���������� ���������������
  bool IsTaskGUID(const char *guid) const;//������ �� TaskGUID

  bool Save(FILE *file) const;//��������� ������
  bool Load(FILE *file);//��������� ������
};
#endif