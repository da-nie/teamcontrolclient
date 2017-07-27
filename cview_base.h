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
  vector<STask> vector_STask;//������������ ������ �����
  bool FlashState;//��������� �������
  CString SelectedTaskGUID;//GUID ���������� �������
  vector<SCell> vector_SCell_Task;//������ ��������� �������

  CBitmap cBitmap_TaskNotReadFrameOne;//����������� "������� �� ���������"
  CBitmap cBitmap_TaskNotReadFrameOneFlash;//��������� ����������� "������� �� ���������"
  CBitmap cBitmap_TaskDone;//����������� "������� ���������"
  CBitmap cBitmap_TaskReaded;//����������� "������� ���������"
  CBitmap cBitmap_TaskIsRunning;//����������� "������� �����������"
  CBitmap cBitmap_TaskCanceled;//����������� "������� ���������"
  CBitmap cBitmap_TaskFinished;//����������� "������� ���������"

  CScrollBar cScrollBar_ShiftItem;//������ ��������� ������ �����

  CFillCell cFillCell;//����������� ������
  CFrameCell cFrameCell;//����� ������
  CTextCell cTextCell_TaskDate;//����� � ������
  CTextCell cTextCell_Task;//����� � ������
  CTextCell cTextCell_ForUser;//����� � ������
  CTextCell cTextCell_FromUser;//����� � ������
  CBitmapCell cBitmapCell_TaskState;//����������� � ������
  CFrameCell cFrameCell_TaskState;//����� ������ � ���������� ������

  LOGFONT Logfont_Task;//����� ��� ������ �������� ������
  LOGFONT Logfont_TaskDate;//����� ��� ������ ����� ������
  LOGFONT Logfont_FromUser;//����� ��� ������ �� ����
  LOGFONT Logfont_ForUser;//����� ��� ������ ��� ����

  bool VisibleFromUser;//�������� �� �� ����
  bool VisibleForUser;//�������� �� ��� ����

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
 public:
  //-������� ������----------------------------------------------------------
 protected:
  //-������� ������----------------------------------------------------------
  CDocument_Main* GetDocument(void);//�������� ��������
  virtual bool TaskIsVisible(const SShowState &sShowState,const long &state)=0;//��������� �� ���������� �������
  void UpdateTask(vector<STask> &vector_STask_Local);//�������� ������� � ������
  void DrawTasks(CDC *pDC);//���������� ������ �����
  //��������� ������
  const long & GetScrollBarWidth(void){static const long ret=16;return(ret);}//�������� ������ ������ ���������
  const long & GetTastStateVerticalOffset(void){static const long ret=4;return(ret);}//�������� ������ �� ��������� ��� ����������� ������� �������
  const long & GetTastStateHorizontalOffset(void){static const long ret=4;return(ret);}//�������� ������ �� ����������� ��� ����������� ������� �������
  //-������------------------------------------------------------------------
};
#endif