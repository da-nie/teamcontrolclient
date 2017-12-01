#ifndef CVIEW_BASE_H
#define CVIEW_BASE_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������������� ������ �������

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
#include "clinetextcell.h"
#include "cframecell.h"
#include "cbitmapcell.h"

using namespace std;

//====================================================================================================
//����� �������������
//====================================================================================================

class CView_Base:public CView
{
 protected: 
  //-���������� ������-------------------------------------------------------
  vector<CTask> vector_CTask;//������������ ������ �����
  bool FlashState;//��������� �������
  CSafeString SelectedTaskGUID;//GUID ���������� �������
  vector<SCell> vector_SCell_Task;//������ ��������� �������

  CBitmap cBitmap_TaskNotReadFrameOne;//����������� "������� �� ���������"
  CBitmap cBitmap_TaskNotReadFrameOneFlash;//��������� ����������� "������� �� ���������"
  CBitmap cBitmap_TaskDoneFrameOne;//����������� "������� ���������"
  CBitmap cBitmap_TaskDoneFrameTwo;//����������� "������� ���������"
  CBitmap cBitmap_TaskReadedFrameOne;//����������� "������� ���������"
  CBitmap cBitmap_TaskReadedFrameTwo;//����������� "������� ���������"
  CBitmap cBitmap_TaskIsRunningFrameOne;//����������� "������� �����������"
  CBitmap cBitmap_TaskIsRunningFrameTwo;//����������� "������� �����������"
  CBitmap cBitmap_TaskCanceledFrameOne;//����������� "������� ���������"
  CBitmap cBitmap_TaskCanceledFrameTwo;//����������� "������� ���������"

  CBitmap cBitmap_TaskFinished;//����������� "������� ���������"

  CScrollBar cScrollBar_ShiftItem;//������ ��������� ������ �����

  CFillCell cFillCell;//����������� ������
  CFrameCell cFrameCell;//����� ������
  CTextCell cTextCell_TaskDate;//����� � ������
  CTextCell cTextCell_Task;//����� � ������
  CTextCell cTextCell_ForUser;//����� � ������
  CTextCell cTextCell_FromUser;//����� � ������
  CTextCell cTextCell_PlannedPosition;//����� � ������
  CTextCell cTextCell_Project;//����� � ������
  CBitmapCell cBitmapCell_TaskState;//����������� � ������
  CFrameCell cFrameCell_TaskState;//����� ������ � ���������� ������
  CLineTextCell cLineTextCell_ColumnName;//����� ���������� �������

  LOGFONT Logfont_Task;//����� ��� ������ �������� ������
  LOGFONT Logfont_TaskDate;//����� ��� ������ ����� ������
  LOGFONT Logfont_FromUser;//����� ��� ������ �� ����
  LOGFONT Logfont_ForUser;//����� ��� ������ ��� ����
  LOGFONT Logfont_PlannedPosition;//����� ��� ������ �������� �� �������
  LOGFONT Logfont_ColumnName;//����� ��� ������ ���������� �������

  bool VisibleFromUser;//�������� �� �� ����
  bool VisibleForUser;//�������� �� ��� ����  

  CSafeString ColumnName;//�������� ������ ��� ����

  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CView_Base();
  //-���������� ������-------------------------------------------------------
  ~CView_Base();
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);//������������ ����
  afx_msg void OnInitialUpdate(void);//�������� ����
  afx_msg void OnDraw(CDC* pDC);//���������� ����
  //-������� ��������� ��������� ������--------------------------------------
  afx_msg void OnSize(UINT nType,int cx,int cy);//��������� �������� ����
  afx_msg BOOL OnEraseBkgnd(CDC *pDC);//������� ����������� ����
  afx_msg void OnTimer(UINT nIDEvent);//������� �������
  afx_msg void OnDestroy(void);//����������� ����
  afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//������������ ������ ���������
  afx_msg BOOL OnMouseWheel(UINT nFlags,short zDelta,CPoint pt);//�������� ������� �����
 public:
  //-������� ������----------------------------------------------------------
 protected:
  //-������� ������----------------------------------------------------------
  CDocument_Main* GetDocument(void);//�������� ��������
  virtual bool TaskIsVisible(const SShowState &sShowState,const CTask& cTask)=0;//��������� �� ���������� �������
  void UpdateTask(vector<CTask> &vector_CTask_Local);//�������� ������� � ������
  void DrawTasks(CDC *pDC);//���������� ������ �����
  //��������� ������
  const long & GetScrollBarWidth(void){static const long ret=16;return(ret);}//�������� ������ ������ ���������
  const long & GetTastStateVerticalOffset(void){static const long ret=4;return(ret);}//�������� ������ �� ��������� ��� ����������� ������� �������
  const long & GetTastStateHorizontalOffset(void){static const long ret=4;return(ret);}//�������� ������ �� ����������� ��� ����������� ������� �������
  const long & GetHeightOffsetColumnName(void){static const long ret=8;return(ret);}//�������� ������ �� ��������� ��� ����������� �������� �������
  //-������------------------------------------------------------------------
};
#endif