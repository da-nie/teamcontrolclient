#ifndef CVIEW_BASE_H
#define CVIEW_BASE_H

//====================================================================================================
//описание
//====================================================================================================

//Класс отображаемого списка заданий

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
#include "clinetextcell.h"
#include "cframecell.h"
#include "cbitmapcell.h"

using namespace std;

//====================================================================================================
//класс представления
//====================================================================================================

class CView_Base:public CView
{
 protected: 
  //-Переменные класса-------------------------------------------------------
  vector<CTask> vector_CTask;//отображаемый список задач
  bool FlashState;//состояние мигания
  CSafeString SelectedTaskGUID;//GUID выбранного задания
  vector<SCell> vector_SCell_Task;//список координат заданий

  CBitmap cBitmap_TaskNotReadFrameOne;//пиктограмма "задание не прочитано"
  CBitmap cBitmap_TaskNotReadFrameOneFlash;//инверсная пиктограмма "задание не прочитано"
  CBitmap cBitmap_TaskDoneFrameOne;//пиктограмма "задание выполнено"
  CBitmap cBitmap_TaskDoneFrameTwo;//пиктограмма "задание выполнено"
  CBitmap cBitmap_TaskReadedFrameOne;//пиктограмма "задание прочитано"
  CBitmap cBitmap_TaskReadedFrameTwo;//пиктограмма "задание прочитано"
  CBitmap cBitmap_TaskIsRunningFrameOne;//пиктограмма "задание выполняется"
  CBitmap cBitmap_TaskIsRunningFrameTwo;//пиктограмма "задание выполняется"
  CBitmap cBitmap_TaskCanceledFrameOne;//пиктограмма "задание отклонено"
  CBitmap cBitmap_TaskCanceledFrameTwo;//пиктограмма "задание отклонено"

  CBitmap cBitmap_TaskFinished;//пиктограмма "задание завершено"

  CScrollBar cScrollBar_ShiftItem;//полоса прокрутки списка задач

  CFillCell cFillCell;//закрашенная ячейка
  CFrameCell cFrameCell;//рамка ячейки
  CTextCell cTextCell_TaskDate;//текст в ячейке
  CTextCell cTextCell_Task;//текст в ячейке
  CTextCell cTextCell_ForUser;//текст в ячейке
  CTextCell cTextCell_FromUser;//текст в ячейке
  CTextCell cTextCell_PlannedPosition;//текст в ячейке
  CTextCell cTextCell_Project;//текст в ячейке
  CBitmapCell cBitmapCell_TaskState;//изображение в ячейке
  CFrameCell cFrameCell_TaskState;//рамка ячейки с состоянием задачи
  CLineTextCell cLineTextCell_ColumnName;//текст назначения столбца

  LOGFONT Logfont_Task;//шрифт для вывода названия задачи
  LOGFONT Logfont_TaskDate;//шрифт для вывода срока задачи
  LOGFONT Logfont_FromUser;//шрифт для вывода от кого
  LOGFONT Logfont_ForUser;//шрифт для вывода для кого
  LOGFONT Logfont_PlannedPosition;//шрифт для вывода плановая ли позиция
  LOGFONT Logfont_ColumnName;//шрифт для вывода назначения столбца

  bool VisibleFromUser;//выводить ли от кого
  bool VisibleForUser;//выводить ли для кого  

  CSafeString ColumnName;//название стобца для вида

  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CView_Base();
  //-Деструктор класса-------------------------------------------------------
  ~CView_Base();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);//предсоздание окна
  afx_msg void OnInitialUpdate(void);//создание окна
  afx_msg void OnDraw(CDC* pDC);//прорисовка вида
  //-Функции обработки сообщений класса--------------------------------------
  afx_msg void OnSize(UINT nType,int cx,int cy);//изменение размеров окна
  afx_msg BOOL OnEraseBkgnd(CDC *pDC);//событие перерисовки фона
  afx_msg void OnTimer(UINT nIDEvent);//событие таймера
  afx_msg void OnDestroy(void);//уничтожение окна
  afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);//вертикальная полоса прокрутки
  afx_msg BOOL OnMouseWheel(UINT nFlags,short zDelta,CPoint pt);//вращение колёсика мышки
 public:
  //-Функции класса----------------------------------------------------------
 protected:
  //-Функции класса----------------------------------------------------------
  CDocument_Main* GetDocument(void);//получить документ
  virtual bool TaskIsVisible(const SShowState &sShowState,const CTask& cTask)=0;//разрешено ли отображать задание
  void UpdateTask(vector<CTask> &vector_CTask_Local);//обновить задания в списке
  void DrawTasks(CDC *pDC);//нарисовать список задач
  //константы класса
  const long & GetScrollBarWidth(void){static const long ret=16;return(ret);}//получить ширину полосы прокрутки
  const long & GetTastStateVerticalOffset(void){static const long ret=4;return(ret);}//получить отступ по вертикали для изображения статуса задания
  const long & GetTastStateHorizontalOffset(void){static const long ret=4;return(ret);}//получить отступ по горизонтали для изображения статуса задания
  const long & GetHeightOffsetColumnName(void){static const long ret=8;return(ret);}//получить отступ по вертикали для изображения названия столбца
  //-Прочее------------------------------------------------------------------
};
#endif