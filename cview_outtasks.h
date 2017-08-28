#ifndef CVIEW_OUTTASKS_H
#define CVIEW_OUTTASKS_H

//====================================================================================================
//описание
//====================================================================================================

//Класс отображаемого списка для списка выданных заданий

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
#include "cview_base.h"

using namespace std;

//====================================================================================================
//макроопределения
//====================================================================================================
//масштабный коэффициент
#define OUT_TASK_WIDTH_SCALE (3.5f/10.0f)

//====================================================================================================
//класс представления
//====================================================================================================

class CView_OutTasks:public CView_Base
{
 protected: 
  //-Переменные класса-------------------------------------------------------
  CMenu cMenu_List;//выпадающее меню в списке заданий пользователю

  CBitmap cBitmap_MenuList_DeleteTask;//пиктограмма "удалить задачу"
  CBitmap cBitmap_MenuList_RepeatTask;//пиктограмма "повторить задачу"
  CBitmap cBitmap_MenuList_EditTask;//пиктограмма "редактировать задачу"
  CBitmap cBitmap_MenuList_SetTaskFinished;//пиктограмма "завершить задание"
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CView_OutTasks();
  //-Деструктор класса-------------------------------------------------------
  ~CView_OutTasks();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  afx_msg void OnInitialUpdate(void);//создание окна
  afx_msg void OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint);//обновление вида
  //-Функции обработки сообщений класса--------------------------------------
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//нажатие правой кнопкой мышки
  afx_msg void OnLButtonDown(UINT nFlags,CPoint point);//нажатие левой кнопкой мышки
  afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);//двойное нажатие левой кнопкой мышки
  afx_msg void OnCommand_Menu_List_TaskRepeat(void);//повторить выполнение задания
  afx_msg void OnCommand_Menu_List_TaskDelete(void);//удалить задание
  afx_msg void OnCommand_Menu_List_TaskEdit(void);//изменить задание
  afx_msg void OnCommand_Menu_List_SetTaskFinished(void);//завершить задание
  DECLARE_MESSAGE_MAP()
 public:
  //-Функции класса----------------------------------------------------------
 protected:
  //-Функции класса----------------------------------------------------------
  bool TaskIsVisible(const SShowState &sShowState,const CTask& cTask);//разрешено ли отображать задание
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CView_OutTasks)
  
};
#endif
