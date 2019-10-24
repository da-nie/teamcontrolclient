#ifndef CFRAMEWND_MAIN_H
#define CFRAMEWND_MAIN_H

//====================================================================================================
//описание
//====================================================================================================

//Класс рамки окна

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================
#include "stdafx.h"
#include "cdocument_main.h"
#include "cview_mytasks.h"
#include "cview_outtasks.h"
#include "ctreeview_kit.h"
#include "cdialog_about.h"
#include "cdialog_deletefinishedtask.h"

//====================================================================================================
//класс рамки окна
//====================================================================================================
class CFrameWnd_Main:public CFrameWnd
{
 protected:
  //-Константы класса--------------------------------------------------------
  static const unsigned long TOOLBAR_MAIN_BUTTON_AMOUNT=17;//количество кнопок в панели инструментов
  static const unsigned long FRAME_WND_TIMER_PERIOD=100;//период таймера рамки окна
  static const unsigned long ABOUT_TIMER_MAX_CONTER=(3000/FRAME_WND_TIMER_PERIOD);//максимальное время показа заставки при включении
  static const unsigned long SYSTRAY_CHANGE_ICON_COUNTER=(500/FRAME_WND_TIMER_PERIOD);//время на смену иконки в трее
  static const unsigned long PING_COUNTER_MAX_VALUE=(60000/FRAME_WND_TIMER_PERIOD);//периодичность проверки связи
  //-Переменные класса-------------------------------------------------------
  CStatusBar cStatusBar_Main;
  CToolBar cToolBar_Main;
  CSplitterWnd cSplitterWnd_Main;

  NOTIFYICONDATA NotifyIconData;//иконка
  HICON hIcon_SysTray;//стандартная иконка в трее
  HICON hIcon_SysTray_NotRead;//иконка в трее при наличии непрочитанных сообщений
  HICON hIcon_SysTray_NotReadInverse;//инверсная иконка в трее при наличии непрочитанных сообщений

  CDialog_About cDialog_About;//диалог "о программе"
  long AboutCounter;//счётчик показа окна о программе

  long ChangeSysTrayIconCounter;//счётчик для смены иконки в трее

  long PingCounter;//счётчик для проверки связи
 public:
  //-Конструктор класса------------------------------------------------------
  CFrameWnd_Main(void);
  //-Деструктор класса-------------------------------------------------------
  ~CFrameWnd_Main();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  afx_msg BOOL OnCreateClient(LPCREATESTRUCT lpcs,CCreateContext* pContext);//добавление клиенского окна
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//создание рамки
  afx_msg void OnDestroy(void);//уничтожение рамки
  afx_msg void OnTimer(UINT nIDEvent);//событие таймера
  afx_msg void OnSize(UINT nType,int cx,int cy);//изменение размеров окна
  afx_msg void OnSysCommand(UINT nID,LPARAM lParam);//изменение параметров окна
  //-Функции обработки сообщений класса--------------------------------------
  DECLARE_MESSAGE_MAP()
  afx_msg void OnCommand_Menu_Main_Settings(void);//настройка клиента
  afx_msg void OnCommand_Menu_Main_DeleteFinishedTask(void);//удаление завершённых заданий
  afx_msg void OnCommand_Menu_Main_ExportTaskFromHTML(void);//экспорт выданных заданий в html
  afx_msg void OnCommand_Menu_Main_ExportTaskFromCSV(void);//экспорт выданных заданий в csv
  afx_msg void OnCommand_Menu_Main_ExportTaskForHTML(void);//экспорт полученных заданий в html
  afx_msg void OnCommand_Menu_Main_ExportTaskForCSV(void);//экспорт полученных заданий в csv

  afx_msg void OnCommand_ToolBar_Main_OutTaskShowCancelled(void);//нажата кнопка "показать отменённые задания из списка выданных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowDone(void);//нажата кнопка "показать выполненные задания из списка выданных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowNotRead(void);//нажата кнопка "показать не прочитанные задания из списка выданных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowFinished(void);//нажата кнопка "показать завершённые задания из списка выданных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowIsRunning(void);//нажата кнопка "показать выполняющиеся задания из списка выданных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_OutTaskShowReaded(void);//нажата кнопка "показать прочитанные задания из списка выданных" главной панели инструментов 

  afx_msg void OnCommand_ToolBar_Main_MyTaskShowCancelled(void);//нажата кнопка "показать отменённые задания из списка полученных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowDone(void);//нажата кнопка "показать выполненные задания из списка полученных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowNotRead(void);//нажата кнопка "показать не прочитанные задания из списка полученных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowFinished(void);//нажата кнопка "показать завершённые задания из списка полученных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowIsRunning(void);//нажата кнопка "показать выполняющиеся задания из списка полученных" главной панели инструментов 
  afx_msg void OnCommand_ToolBar_Main_MyTaskShowReaded(void);//нажата кнопка "показать прочитанные задания из списка полученных" главной панели инструментов 

  afx_msg void OnCommand_ToolBar_Main_ShowCommonTask(void);//нажата кнопка "показывать общие задания вместо выданных" главной панели инструментов 

  afx_msg LRESULT OnSystemTrayIconMessage(WPARAM wParam,LPARAM lParam);//обработка сообщений трея
  afx_msg void OnCommand_Menu_SysTray_Exit(void);//обработка команды выхода из программы

 protected:
  //функции класса
  void CheckToolBarMainButtonAndSetShowStateInDocument(void);//проверить кнопки главной панели инструментов и задать их состояние в документе  
  bool GetFileNameForSave(std::string &file_name,const std::string &caption,const std::string &extension);//получить имя файла для сохранения
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CFrameWnd_Main) 
};
#endif