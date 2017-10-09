#ifndef CDIALOG_TASK_SETTINGS_H
#define CDIALOG_TASK_SETTINGS_H

//====================================================================================================
//описание
//====================================================================================================

//Класс диалога настройки задания

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "protocol.h"

//====================================================================================================
//класс диалога настройки задания
//====================================================================================================
class CDialog_TaskSettings:public CDialog
{
 protected:
  //-Переменные класса-------------------------------------------------------
  CTask cTask_Local;//редактируемое задание
  CDocument_Main *cDocument_Main_Local_Ptr;//указатель на документ
  vector<CUser> vector_CUser_Local;//список пользователей на время редактирования заданий (он ведь может внезапно измениться в документе)
  vector<CProject> vector_CProject_Local;//список проектов на время редактирования заданий (он ведь может внезапно измениться в документе)
  bool NewTask;//создаётся ли новое задание

  HBITMAP hBitmap_TaskFinished;//пиктограмма завершения задания
 public:
  //-Конструктор класса------------------------------------------------------
  CDialog_TaskSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd);
  //-Деструктор класса-------------------------------------------------------
  ~CDialog_TaskSettings();
  //-Функции-----------------------------------------------------------------
  afx_msg void OnOK(void);//нажали Enter
  afx_msg void OnCancel(void);//нажали ESC
  afx_msg BOOL OnInitDialog(void);//инициализация диалога
  //-Функции класса----------------------------------------------------------
  bool Activate(CTask& cTask,CDocument_Main *cDocument_Main_Ptr,bool new_task);//запустить диалог
  //-Функции обработки сообщений класса--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnDestroy(void);//уничтожение окна
  afx_msg void OnCommand_Button_Ok(void);//применить настройки
  afx_msg void OnCommand_Button_Cancel(void);//отменить настройки
  afx_msg void OnCommand_Button_TaskFinished(void);//подтверждение, что задание выполнено
  afx_msg void OnCommand_Button_SetTaskReference(void);//задать ссылку в задании
  afx_msg void OnCommand_Button_ResetTaskReference(void);//удалить ссылку в задании
  afx_msg void OnCommand_Button_OpenTaskReference(void);//открыть ссылку в задании
  afx_msg void OnCommand_Button_OpenAnswerReference(void);//открыть ссылку из ответа
  afx_msg void OnSelChange_ComboBox_User(void);//изменился пользователь
 protected:
  //-Новые функции класса (защищённые)---------------------------------------
  //-Прочее------------------------------------------------------------------  
};
//---------------------------------------------------------------------------
#endif