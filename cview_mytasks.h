#ifndef CVIEW_MYTASKS_H
#define CVIEW_MYTASKS_H

//====================================================================================================
//описание
//====================================================================================================

//Класс отображаемого списка для списка принятых заданий

//====================================================================================================
//подключаемые библиотеки
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
//макроопределения
//====================================================================================================
//масштабный коэффициент
#define MY_TASK_WIDTH_SCALE (3.55f/10.0f)

//====================================================================================================
//класс представления
//====================================================================================================

class CView_MyTasks:public CView_Base
{
 protected: 
  //-Переменные класса-------------------------------------------------------
  CMenu cMenu_List;//выпадающее меню в списке заданий пользователю

  CBitmap cBitmap_MenuList_TaskDone;//пиктограмма "задание выполнено"
  CBitmap cBitmap_MenuList_SetTaskReaded;//пиктограмма "задание прочитано"
  CBitmap cBitmap_MenuList_SetTaskIsRunning;//пиктограмма "задание выполняется"
  CBitmap cBitmap_MenuList_SetTaskCanceled;//пиктограмма "задание отклонено"
  CBitmap cBitmap_MenuList_SendTask;//пиктограмма "поручить копию задания"
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CView_MyTasks();
  //-Деструктор класса-------------------------------------------------------
  ~CView_MyTasks();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  afx_msg void OnInitialUpdate(void);//создание окна
  afx_msg void OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint);//обновление вида
  //-Функции обработки сообщений класса--------------------------------------
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//нажатие правой кнопкой мышки
  afx_msg void OnLButtonDown(UINT nFlags,CPoint point);//нажатие левой кнопкой мышки
  afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);//двойное нажатие левой кнопкой мышки
  afx_msg void OnCommand_Menu_List_SetTaskDone(void);//установить, что задание завершено
  afx_msg void OnCommand_Menu_List_SetTaskReaded(void);//установить, что задание прочитано
  afx_msg void OnCommand_Menu_List_SetTaskIsRunning(void);//установить, что задание выполняется
  afx_msg void OnCommand_Menu_List_SetTaskCanceled(void);//установить, что задание отклонено
  afx_msg void OnCommand_Menu_List_SendTask(void);//поручить копию задания
  DECLARE_MESSAGE_MAP()
 public:
  //-Функции класса----------------------------------------------------------
 protected:
  //-Функции класса----------------------------------------------------------
  bool TaskIsVisible(const SShowState &sShowState,const CTask& cTask);//разрешено ли отображать задание
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CView_MyTasks)  
};
#endif