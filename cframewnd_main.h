#ifndef CFRAMEWND_MAIN_H
#define CFRAMEWND_MAIN_H

//====================================================================================================
//��������
//====================================================================================================

//����� ����� ����

//====================================================================================================
//������������ ����������
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "cview_mytasks.h"
#include "cview_outtasks.h"
#include "ctreeview_kit.h"
#include "cdialog_about.h"
#include "cdialog_deletefinishedtask.h"

//====================================================================================================
//����������������
//====================================================================================================

//���������� ������ � ������ ������������
#define TOOLBAR_MAIN_BUTTON_AMOUNT 17

//������ ������� ����� ����
#define FRAME_WND_TIMER_PERIOD 100
//������������ ����� ������ �������� ��� ���������
#define ABOUT_TIMER_MAX_CONTER (3000/FRAME_WND_TIMER_PERIOD)
//����� �� ����� ������ � ����
#define SYSTRAY_CHANGE_ICON_COUNTER (500/FRAME_WND_TIMER_PERIOD)
//������������� �������� �����
#define PING_COUNTER_MAX_VALUE (60000/FRAME_WND_TIMER_PERIOD)

//====================================================================================================
//����� ����� ����
//====================================================================================================
class CFrameWnd_Main:public CFrameWnd
{
 protected:
  //-���������� ������-------------------------------------------------------
  CStatusBar cStatusBar_Main;
  CToolBar cToolBar_Main;
  CSplitterWnd cSplitterWnd_Main;

  NOTIFYICONDATA NotifyIconData;//������
  HICON hIcon_SysTray;//����������� ������ � ����
  HICON hIcon_SysTray_NotRead;//������ � ���� ��� ������� ������������� ���������
  HICON hIcon_SysTray_NotReadInverse;//��������� ������ � ���� ��� ������� ������������� ���������

  CDialog_About cDialog_About;//������ "� ���������"
  long AboutCounter;//������� ������ ���� � ���������

  long ChangeSysTrayIconCounter;//������� ��� ����� ������ � ����

  long PingCounter;//������� ��� �������� �����
 public:
  //-����������� ������------------------------------------------------------
  CFrameWnd_Main(void);
  //-���������� ������-------------------------------------------------------
  ~CFrameWnd_Main();
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  afx_msg BOOL OnCreateClient(LPCREATESTRUCT lpcs,CCreateContext* pContext);//���������� ���������� ����
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//�������� �����
  afx_msg void OnDestroy(void);//����������� �����
  afx_msg void OnTimer(UINT nIDEvent);//������� �������
  afx_msg void OnSize(UINT nType,int cx,int cy);//��������� �������� ����
  afx_msg void OnSysCommand(UINT nID,LPARAM lParam);//��������� ���������� ����
  //-������� ��������� ��������� ������--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnCommand_Menu_Main_Settings(void);//��������� �������
  afx_msg void OnCommand_Menu_Main_DeleteFinishedTask(void);//�������� ����������� �������

  afx_msg void OnCommand_ToolBar_Main_OutTaskShowCancelled(void);//������ ������ "�������� ��������� ������� �� ������ ��������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowDone(void);//������ ������ "�������� ����������� ������� �� ������ ��������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowNotRead(void);//������ ������ "�������� �� ����������� ������� �� ������ ��������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowFinished(void);//������ ������ "�������� ����������� ������� �� ������ ��������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowIsRunning(void);//������ ������ "�������� ������������� ������� �� ������ ��������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowReaded(void);//������ ������ "�������� ����������� ������� �� ������ ��������" ������� ������ ������������ 

  afx_msg void OnCommand_ToolBar_Main_MyTaskShowCancelled(void);//������ ������ "�������� ��������� ������� �� ������ ����������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowDone(void);//������ ������ "�������� ����������� ������� �� ������ ����������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowNotRead(void);//������ ������ "�������� �� ����������� ������� �� ������ ����������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowFinished(void);//������ ������ "�������� ����������� ������� �� ������ ����������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowIsRunning(void);//������ ������ "�������� ������������� ������� �� ������ ����������" ������� ������ ������������ 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowReaded(void);//������ ������ "�������� ����������� ������� �� ������ ����������" ������� ������ ������������ 

  afx_msg void OnCommand_ToolBar_Main_ShowCommonTask(void);//������ ������ "���������� ����� ������� ������ ��������" ������� ������ ������������ 

  afx_msg void OnSystemTrayIconMessage(WPARAM wParam,LPARAM lParam);//��������� ��������� ����
  afx_msg void OnCommand_Menu_SysTray_Exit(void);//��������� ������� ������ �� ���������

 protected:
  //������� ������
  void CheckToolBarMainButtonAndSetShowStateInDocument(void);//��������� ������ ������� ������ ������������ � ������ �� ��������� � ���������  
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CFrameWnd_Main) 
};
#endif