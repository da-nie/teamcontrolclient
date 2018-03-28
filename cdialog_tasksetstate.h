#ifndef CDIALOG_TASK_SET_STATE_H
#define CDIALOG_TASK_SET_STATE_H

//====================================================================================================
//описание
//====================================================================================================

//Класс диалога установки состояния задания

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "protocol.h"

//====================================================================================================
//класс диалога установки состояния задания
//====================================================================================================
class CDialog_TaskSetState:public CDialog
{
 protected:
  //-Переменные класса-------------------------------------------------------
  CTask cTask_Local;//редактируемое задание
  //пиктограммы
  HBITMAP hBitmap_TaskDone;
  HBITMAP hBitmap_TaskIsRunning;
  HBITMAP hBitmap_TaskRead;
  HBITMAP hBitmap_TaskCancel;
 public:
  //-Конструктор класса------------------------------------------------------
  CDialog_TaskSetState(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-Деструктор класса-------------------------------------------------------
  ~CDialog_TaskSetState();
  //-Функции-----------------------------------------------------------------
  afx_msg void OnOK(void);//нажали Enter
  afx_msg void OnCancel(void);//нажали ESC
  afx_msg BOOL OnInitDialog(void);//инициализация диалога
  //-Функции класса----------------------------------------------------------
  bool Activate(CTask& cTask);//запустить диалог
  //-Функции обработки сообщений класса--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//уничтожение окна
  afx_msg void OnCommand_Button_Cancel(void);//отменить настройки
  afx_msg void OnCommand_Button_TaskDone(void);//задание выполнено
  afx_msg void OnCommand_Button_TaskCancel(void);//задание отклонено
  afx_msg void OnCommand_Button_TaskRead(void);//задание прочитано
  afx_msg void OnCommand_Button_TaskIsRunning(void);//задание выполняется
  afx_msg void OnCommand_Button_OpenTaskReference(void);//открыть ссылку в задании
  afx_msg void OnCommand_Button_SetAnswerReference(void);//задать ссылку в ответе
  afx_msg void OnCommand_Button_ResetAnswerReference(void);//удалить ссылку в ответе
  afx_msg void OnCommand_Button_OpenAnswerReference(void);//открыть ссылку в ответе
 protected:
  //-Новые функции класса (защищённые)---------------------------------------
  void ReadAnswer(void);//считать ответ
  //-Прочее------------------------------------------------------------------  
};
//---------------------------------------------------------------------------
#endif