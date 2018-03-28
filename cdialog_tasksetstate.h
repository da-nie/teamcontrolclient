#ifndef CDIALOG_TASK_SET_STATE_H
#define CDIALOG_TASK_SET_STATE_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������� ��������� ��������� �������

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "protocol.h"

//====================================================================================================
//����� ������� ��������� ��������� �������
//====================================================================================================
class CDialog_TaskSetState:public CDialog
{
 protected:
  //-���������� ������-------------------------------------------------------
  CTask cTask_Local;//������������� �������
  //�����������
  HBITMAP hBitmap_TaskDone;
  HBITMAP hBitmap_TaskIsRunning;
  HBITMAP hBitmap_TaskRead;
  HBITMAP hBitmap_TaskCancel;
 public:
  //-����������� ������------------------------------------------------------
  CDialog_TaskSetState(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-���������� ������-------------------------------------------------------
  ~CDialog_TaskSetState();
  //-�������-----------------------------------------------------------------
  afx_msg void OnOK(void);//������ Enter
  afx_msg void OnCancel(void);//������ ESC
  afx_msg BOOL OnInitDialog(void);//������������� �������
  //-������� ������----------------------------------------------------------
  bool Activate(CTask& cTask);//��������� ������
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//����������� ����
  afx_msg void OnCommand_Button_Cancel(void);//�������� ���������
  afx_msg void OnCommand_Button_TaskDone(void);//������� ���������
  afx_msg void OnCommand_Button_TaskCancel(void);//������� ���������
  afx_msg void OnCommand_Button_TaskRead(void);//������� ���������
  afx_msg void OnCommand_Button_TaskIsRunning(void);//������� �����������
  afx_msg void OnCommand_Button_OpenTaskReference(void);//������� ������ � �������
  afx_msg void OnCommand_Button_SetAnswerReference(void);//������ ������ � ������
  afx_msg void OnCommand_Button_ResetAnswerReference(void);//������� ������ � ������
  afx_msg void OnCommand_Button_OpenAnswerReference(void);//������� ������ � ������
 protected:
  //-����� ������� ������ (����������)---------------------------------------
  void ReadAnswer(void);//������� �����
  //-������------------------------------------------------------------------  
};
//---------------------------------------------------------------------------
#endif