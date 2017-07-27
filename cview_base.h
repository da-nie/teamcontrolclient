#ifndef CVIEW_BASE_H
#define CVIEW_BASE_H

//====================================================================================================
//описание
//====================================================================================================

// ласс отображаемого списка заданий

//====================================================================================================
//подключаемые библиотеки
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
//класс представлени€
//====================================================================================================

class CView_Base:public CView
{
 protected: 
  //-ѕеременные класса-------------------------------------------------------
  vector<STask> vector_STask;//отображаемый список задач
  bool FlashState;//состо€ние мигани€
  CString SelectedTaskGUID;//GUID выбранного задани€
  vector<SCell> vector_SCell_Task;//список координат заданий

  CBitmap cBitmap_TaskNotReadFrameOne;//пиктограмма "задание не прочитано"
  CBitmap cBitmap_TaskNotReadFrameOneFlash;//инверсна€ пиктограмма "задание не прочитано"
  CBitmap cBitmap_TaskDone;//пиктограмма "задание выполнено"
  CBitmap cBitmap_TaskReaded;//пиктограмма "задание прочитано"
  CBitmap cBitmap_TaskIsRunning;//пиктограмма "задание выполн€етс€"
  CBitmap cBitmap_TaskCanceled;//пиктограмма "задание отклонено"
  CBitmap cBitmap_TaskFinished;//пиктограмма "задание завершено"

  CScrollBar cScrollBar_ShiftItem;//полоса прокрутки списка задач

  CFillCell cFillCell;//закрашенна€ €чейка
  CFrameCell cFrameCell;//рамка €чейки
  CTextCell cTextCell_TaskDate;//текст в €чейке
  CTextCell cTextCell_Task;//текст в €чейке
  CTextCell cTextCell_ForUser;//текст в €чейке
  CTextCell cTextCell_FromUser;//текст в €чейке
  CBitmapCell cBitmapCell_TaskState;//изображение в €чейке
  CFrameCell cFrameCell_TaskState;//рамка €чейки с состо€нием задачи

  LOGFONT Logfont_Task;//шрифт дл€ вывода названи€ задачи
  LOGFONT Logfont_TaskDate;//шрифт дл€ вывода срока задачи
  LOGFONT Logfont_FromUser;//шрифт дл€ вывода от кого
  LOGFONT Logfont_ForUser;//шрифт дл€ вывода дл€ кого

  bool VisibleFromUser;//выводить ли от кого
  bool VisibleForUser;//выводить ли дл€ кого

  //-ѕрочее------------------------------------------------------------------
 public:
  //- онструктор класса------------------------------------------------------
  CView_Base();
  //-ƒеструктор класса-------------------------------------------------------
  ~CView_Base();
  //-ѕеременные класса-------------------------------------------------------
  //-‘ункции класса----------------------------------------------------------
  afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);//предсоздание окна
  afx_msg void OnInitialUpdate(void);//создание окна
  afx_msg void OnDraw(CDC* pDC);//прорисовка вида
  //-‘ункции обработки сообщений класса--------------------------------------
  afx_msg void OnSize(UINT nType,int cx,int cy);//изменение размеров окна
  afx_msg BOOL OnEraseBkgnd(CDC *pDC);//событие перерисовки фона
  afx_msg void OnTimer(UINT nIDEvent);//событие таймера
  afx_msg void OnDestroy(void);//уничтожение окна
  afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//вертикальна€ полоса прокрутки
 public:
  //-‘ункции класса----------------------------------------------------------
 protected:
  //-‘ункции класса----------------------------------------------------------
  CDocument_Main* GetDocument(void);//получить документ
  virtual bool TaskIsVisible(const SShowState &sShowState,const long &state)=0;//разрешено ли отображать задание
  void UpdateTask(vector<STask> &vector_STask_Local);//обновить задани€ в списке
  void DrawTasks(CDC *pDC);//нарисовать список задач
  //константы класса
  const long & GetScrollBarWidth(void){static const long ret=16;return(ret);}//получить ширину полосы прокрутки
  const long & GetTastStateVerticalOffset(void){static const long ret=4;return(ret);}//получить отступ по вертикали дл€ изображени€ статуса задани€
  const long & GetTastStateHorizontalOffset(void){static const long ret=4;return(ret);}//получить отступ по горизонтали дл€ изображени€ статуса задани€
  //-ѕрочее------------------------------------------------------------------
};
#endif