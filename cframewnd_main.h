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
//����� ����� ����
//====================================================================================================
class CFrameWnd_Main:public CFrameWnd
{
 protected:
  //-��������� ������--------------------------------------------------------
  static const unsigned long TOOLBAR_MAIN_BUTTON_AMOUNT=17;//���������� ������ � ������ ������������
  static const unsigned long FRAME_WND_TIMER_PERIOD=100;//������ ������� ����� ����
  static const unsigned long ABOUT_TIMER_MAX_CONTER=(3000/FRAME_WND_TIMER_PERIOD);//������������ ����� ������ �������� ��� ���������
  static const unsigned long SYSTRAY_CHANGE_ICON_COUNTER=(500/FRAME_WND_TIMER_PERIOD);//����� �� ����� ������ � ����
  static const unsigned long PING_COUNTER_MAX_VALUE=(60000/FRAME_WND_TIMER_PERIOD);//������������� �������� �����
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
  afx_msg void OnCommand_Menu_Main_ExportTaskFromHTML(void);//������� �������� ������� � html
  afx_msg void OnCommand_Menu_Main_ExportTaskFromCSV(void);//������� �������� ������� � csv
  afx_msg void OnCommand_Menu_Main_ExportTaskForHTML(void);//������� ���������� ������� � html
  afx_msg void OnCommand_Menu_Main_ExportTaskForCSV(void);//������� ���������� ������� � csv

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

  afx_msg LRESULT OnSystemTrayIconMessage(WPARAM wParam,LPARAM lParam);//��������� ��������� ����
  afx_msg void OnCommand_Menu_SysTray_Exit(void);//��������� ������� ������ �� ���������

 protected:
  //������� ������
  void CheckToolBarMainButtonAndSetShowStateInDocument(void);//��������� ������ ������� ������ ������������ � ������ �� ��������� � ���������  
  bool GetFileNameForSave(std::string &file_name,const std::string &caption,const std::string &extension);//�������� ��� ����� ��� ����������
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CFrameWnd_Main) 
};
#endif