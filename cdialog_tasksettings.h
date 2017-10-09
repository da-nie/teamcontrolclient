#ifndef CDIALOG_TASK_SETTINGS_H
#define CDIALOG_TASK_SETTINGS_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������� ��������� �������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "protocol.h"

//====================================================================================================
//����� ������� ��������� �������
//====================================================================================================
class CDialog_TaskSettings:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  CTask cTask_Local;//������������� �������
  CDocument_Main *cDocument_Main_Local_Ptr;//��������� �� ��������
  vector<CUser> vector_CUser_Local;//������ ������������� �� ����� �������������� ������� (�� ���� ����� �������� ���������� � ���������)
  vector<CProject> vector_CProject_Local;//������ �������� �� ����� �������������� ������� (�� ���� ����� �������� ���������� � ���������)
  bool NewTask;//�������� �� ����� �������

  HBITMAP hBitmap_TaskFinished;//����������� ���������� �������
 public:
  //-����������� ������------------------------------------------------------
  CDialog_TaskSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_TaskSettings();
  //-�������-----------------------------------------------------------------
  afx_msg void OnOK(void);//������ Enter
  afx_msg void OnCancel(void);//������ ESC
  afx_msg BOOL OnInitDialog(void);//������������� �������
  //-������� ������----------------------------------------------------------
  bool Activate(CTask& cTask,CDocument_Main *cDocument_Main_Ptr,bool new_task);//��������� ������
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//����������� ����
  afx_msg void OnCommand_Button_Ok(void);//��������� ���������
  afx_msg void OnCommand_Button_Cancel(void);//�������� ���������
  afx_msg void OnCommand_Button_TaskFinished(void);//�������������, ��� ������� ���������
  afx_msg void OnCommand_Button_SetTaskReference(void);//������ ������ � �������
  afx_msg void OnCommand_Button_ResetTaskReference(void);//������� ������ � �������
  afx_msg void OnCommand_Button_OpenTaskReference(void);//������� ������ � �������
  afx_msg void OnCommand_Button_OpenAnswerReference(void);//������� ������ �� ������
  afx_msg void OnSelChange_ComboBox_User(void);//��������� ������������
 protected:
  //-����� ������� ������ (����������)---------------------------------------
  //-������------------------------------------------------------------------  
};
//---------------------------------------------------------------------------
#endif