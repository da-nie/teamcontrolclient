#ifndef CVIEW_OUTTASKS_H
#define CVIEW_OUTTASKS_H

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
#include "cdialog_tasksettings.h"

#include "cicell.h"
#include "cfillcell.h"
#include "ctextcell.h"
#include "cframecell.h"
#include "cbitmapcell.h"
#include "cview_base.h"

using namespace std;

//====================================================================================================
//����������������
//====================================================================================================
//���������� �����������
#define OUT_TASK_WIDTH_SCALE (3.5f/10.0f)

//====================================================================================================
//����� �������������
//====================================================================================================

class CView_OutTasks:public CView_Base
{
 protected: 
  //-���������� ������-------------------------------------------------------
  CMenu cMenu_List;//���������� ���� � ������ ������� ������������

  CBitmap cBitmap_MenuList_DeleteTask;//����������� "������� ������"
  CBitmap cBitmap_MenuList_RepeatTask;//����������� "��������� ������"
  CBitmap cBitmap_MenuList_EditTask;//����������� "������������� ������"
  CBitmap cBitmap_MenuList_SetTaskFinished;//����������� "��������� �������"
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CView_OutTasks();
  //-���������� ������-------------------------------------------------------
  ~CView_OutTasks();
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  afx_msg void OnInitialUpdate(void);//�������� ����
  afx_msg void OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint);//���������� ����
  //-������� ��������� ��������� ������--------------------------------------
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//������� ������ ������� �����
  afx_msg void OnLButtonDown(UINT nFlags,CPoint point);//������� ����� ������� �����
  afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);//������� ������� ����� ������� �����
  afx_msg void OnCommand_Menu_List_TaskRepeat(void);//��������� ���������� �������
  afx_msg void OnCommand_Menu_List_TaskDelete(void);//������� �������
  afx_msg void OnCommand_Menu_List_TaskEdit(void);//�������� �������
  afx_msg void OnCommand_Menu_List_SetTaskFinished(void);//��������� �������
  DECLARE_MESSAGE_MAP()
 public:
  //-������� ������----------------------------------------------------------
 protected:
  //-������� ������----------------------------------------------------------
  bool TaskIsVisible(const SShowState &sShowState,const CTask& cTask);//��������� �� ���������� �������
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CView_OutTasks)
  
};
#endif
