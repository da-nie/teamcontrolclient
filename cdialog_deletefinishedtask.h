#ifndef CDIALOG_DELETE_FINISHED_TASK_H
#define CDIALOG_DELETE_FINISHED_TASK_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������� �������� �������� ���� � ����������� �������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "protocol.h"

//====================================================================================================
//����� ������� �������� �������� ���� � ����������� �������
//====================================================================================================
class CDialog_DeleteFinishedTask:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  //����, �� ������� ������������ ����� ������� ����������� �������
  long Deleted_Year;//���
  long Deleted_Month;//�����
  long Deleted_Day;//�����
 public:
  //-����������� ������------------------------------------------------------
  CDialog_DeleteFinishedTask(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_DeleteFinishedTask();
  //-�������-----------------------------------------------------------------
  afx_msg void OnOK(void);//������ Enter
  afx_msg void OnCancel(void);//������ ESC
  afx_msg BOOL OnInitDialog(void);//������������� �������
  //-������� ������----------------------------------------------------------
  bool Activate(long &Year,long &Month,long &Day);//��������� ������
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//����������� ����
  afx_msg void OnCommand_Button_Delete(void);//�������
  afx_msg void OnCommand_Button_Cancel(void);//������
 protected:
  //-����� ������� ������ (����������)---------------------------------------
  //-������------------------------------------------------------------------  
};
//---------------------------------------------------------------------------
#endif