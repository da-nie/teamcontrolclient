#ifndef CVIEW_MYTASKS_H
#define CVIEW_MYTASKS_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������������� ������ ��� ������ �������� �������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include <list>
#include "stdafx.h"
#include "protocol.h"
#include "cdocument_main.h"
#include "cdialog_tasksetstate.h"

#include "cicell.h"
#include "cfillcell.h"
#include "ctextcell.h"
#include "cframecell.h"
#include "cbitmapcell.h"
#include "cview_base.h"



//====================================================================================================
//����������������
//====================================================================================================
//���������� �����������
#define MY_TASK_WIDTH_SCALE (3.55f/10.0f)

//====================================================================================================
//����� �������������
//====================================================================================================

class CView_MyTasks:public CView_Base
{
 protected: 
  //-���������� ������-------------------------------------------------------
  CMenu cMenu_List;//���������� ���� � ������ ������� ������������

  CBitmap cBitmap_MenuList_TaskDone;//����������� "������� ���������"
  CBitmap cBitmap_MenuList_SetTaskReaded;//����������� "������� ���������"
  CBitmap cBitmap_MenuList_SetTaskIsRunning;//����������� "������� �����������"
  CBitmap cBitmap_MenuList_SetTaskCanceled;//����������� "������� ���������"
  CBitmap cBitmap_MenuList_SendTask;//����������� "�������� ����� �������"
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CView_MyTasks();
  //-���������� ������-------------------------------------------------------
  ~CView_MyTasks();
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  afx_msg void OnInitialUpdate(void);//�������� ����
  afx_msg void OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint);//���������� ����
  //-������� ��������� ��������� ������--------------------------------------
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//������� ������ ������� �����
  afx_msg void OnLButtonDown(UINT nFlags,CPoint point);//������� ����� ������� �����
  afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);//������� ������� ����� ������� �����
  afx_msg void OnCommand_Menu_List_SetTaskDone(void);//����������, ��� ������� ���������
  afx_msg void OnCommand_Menu_List_SetTaskReaded(void);//����������, ��� ������� ���������
  afx_msg void OnCommand_Menu_List_SetTaskIsRunning(void);//����������, ��� ������� �����������
  afx_msg void OnCommand_Menu_List_SetTaskCanceled(void);//����������, ��� ������� ���������
  afx_msg void OnCommand_Menu_List_SendTask(void);//�������� ����� �������
  DECLARE_MESSAGE_MAP()
 public:
  //-������� ������----------------------------------------------------------
 protected:
  //-������� ������----------------------------------------------------------
  bool TaskIsVisible(const SShowState &sShowState,const CTask& cTask);//��������� �� ���������� �������
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CView_MyTasks)  
};
#endif