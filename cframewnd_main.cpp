#include "cframewnd_main.h"

//====================================================================================================
//карта сообщений класса
//====================================================================================================
BEGIN_MESSAGE_MAP(CFrameWnd_Main,CFrameWnd)
 ON_WM_CREATE()
 ON_WM_TIMER()
 ON_WM_SIZE()
 ON_WM_DESTROY()
 ON_WM_SYSCOMMAND()
 ON_COMMAND(IDC_MENU_MAIN_SETTINGS,OnCommand_Menu_Main_Settings)
 ON_COMMAND(IDC_MENU_MAIN_DELETE_FINISHED_TASK,OnCommand_Menu_Main_DeleteFinishedTask)

 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_CANCELLED,OnCommand_ToolBar_Main_OutTaskShowCancelled)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_DONE,OnCommand_ToolBar_Main_OutTaskShowDone)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_NOT_READ,OnCommand_ToolBar_Main_OutTaskShowNotRead)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_FINISHED,OnCommand_ToolBar_Main_OutTaskShowFinished)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_IS_RUNNING,OnCommand_ToolBar_Main_OutTaskShowIsRunning)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_READED,OnCommand_ToolBar_Main_OutTaskShowReaded)

 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_CANCELLED,OnCommand_ToolBar_Main_MyTaskShowCancelled)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_DONE,OnCommand_ToolBar_Main_MyTaskShowDone)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_NOT_READ,OnCommand_ToolBar_Main_MyTaskShowNotRead)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_FINISHED,OnCommand_ToolBar_Main_MyTaskShowFinished)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_IS_RUNNING,OnCommand_ToolBar_Main_MyTaskShowIsRunning)
 ON_COMMAND(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_READED,OnCommand_ToolBar_Main_MyTaskShowReaded)

 ON_COMMAND(IDC_TOOLBAR_MAIN_SHOW_COMMON_TASK,OnCommand_ToolBar_Main_ShowCommonTask) 

 ON_MESSAGE(WM_SYSTEM_TRAY_ICON,OnSystemTrayIconMessage)
 ON_COMMAND(IDC_MENU_SYSTRAY_EXIT,OnCommand_Menu_SysTray_Exit)
END_MESSAGE_MAP()
//====================================================================================================
//конструктор класса
//====================================================================================================
CFrameWnd_Main::CFrameWnd_Main(void)
{
 hIcon_SysTray=NULL;
 hIcon_SysTray_NotRead=NULL;
 hIcon_SysTray_NotReadInverse=NULL;
 PingCounter=PING_COUNTER_MAX_VALUE;
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CFrameWnd_Main::~CFrameWnd_Main()
{
}

//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//добавление клиенского окна
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CFrameWnd_Main::OnCreateClient(LPCREATESTRUCT lpcs,CCreateContext* pContext)
{ 
 //создадим панель инструментов
 cToolBar_Main.Create(this,WS_CHILD|WS_VISIBLE|CBRS_SIZE_FIXED|CBRS_TOP|CBRS_TOOLTIPS);
 //загрузим картинки для панели

 //используем BITMAP, чтобы сделать 24 бита RGB в панели инструментов, вместо 16 цветов при обычном создании из ресурса
 HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TOOLBAR_MAIN),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
 cToolBar_Main.SetBitmap(hBitmap);

 UINT ButtonIndex[TOOLBAR_MAIN_BUTTON_AMOUNT];
 ButtonIndex[0]=IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_CANCELLED;
 ButtonIndex[1]=IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_DONE;
 ButtonIndex[2]=IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_NOT_READ;
 ButtonIndex[3]=IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_FINISHED;
 ButtonIndex[4]=IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_IS_RUNNING;
 ButtonIndex[5]=IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_READED;
 ButtonIndex[6]=0;
 ButtonIndex[7]=IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_CANCELLED;
 ButtonIndex[8]=IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_DONE;
 ButtonIndex[9]=IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_NOT_READ;
 ButtonIndex[10]=IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_FINISHED;
 ButtonIndex[11]=IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_IS_RUNNING;
 ButtonIndex[12]=IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_READED;
 ButtonIndex[13]=0;
 ButtonIndex[14]=0;
 ButtonIndex[15]=0;
 ButtonIndex[16]=IDC_TOOLBAR_MAIN_SHOW_COMMON_TASK;

 
 cToolBar_Main.SetButtons(ButtonIndex,TOOLBAR_MAIN_BUTTON_AMOUNT);

 //настроим кнопки панели
 cToolBar_Main.SetButtonStyle(0,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(1,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(2,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(3,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(4,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(5,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonInfo(6,ID_SEPARATOR,TBBS_SEPARATOR,24);
 cToolBar_Main.SetButtonStyle(7,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(8,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(9,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(10,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(11,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonStyle(12,TBBS_CHECKBOX);
 cToolBar_Main.SetButtonInfo(13,ID_SEPARATOR,TBBS_SEPARATOR,24);
 cToolBar_Main.SetButtonInfo(14,ID_SEPARATOR,TBBS_SEPARATOR,24);
 cToolBar_Main.SetButtonInfo(15,ID_SEPARATOR,TBBS_SEPARATOR,24);
 cToolBar_Main.SetButtonStyle(16,TBBS_CHECKBOX);
 //название панели
 cToolBar_Main.SetWindowText("Настройка вида");
 //устанавливаем новые размеры кнопок
 SIZE Size_Button;
 Size_Button.cx=40;
 Size_Button.cy=40;
 SIZE Size_Image;
 Size_Image.cx=32;
 Size_Image.cy=32;
 cToolBar_Main.SetSizes(Size_Button,Size_Image);
 cToolBar_Main.EnableDocking(CBRS_ALIGN_ANY);
 DockControlBar(&cToolBar_Main,AFX_IDW_DOCKBAR_TOP);
 //включим все кнопки
 for(long n=0;n<TOOLBAR_MAIN_BUTTON_AMOUNT;n++)
 {
  if (ButtonIndex[n]==0) continue;
  if (ButtonIndex[n]==IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_FINISHED) continue;
  if (ButtonIndex[n]==IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_CANCELLED) continue;
  if (ButtonIndex[n]==IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_DONE) continue;
  if (ButtonIndex[n]==IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_FINISHED) continue;
  if (ButtonIndex[n]==IDC_TOOLBAR_MAIN_SHOW_COMMON_TASK) continue;
  cToolBar_Main.GetToolBarCtrl().SetState(ButtonIndex[n],TBSTATE_CHECKED);
 } 

 //создаём разделитель
 RECT Rect;
 GetClientRect(&Rect);
 long width=Rect.right-Rect.left;
 long kit_width=width*KIT_WIDTH_SCALE;
 long out_tasks_width=width*OUT_TASK_WIDTH_SCALE;
 long my_tasks_width=width*MY_TASK_WIDTH_SCALE;

 cSplitterWnd_Main.CreateStatic(this,1,3); 
 cSplitterWnd_Main.CreateView(0,0,RUNTIME_CLASS(CTreeView_Kit),CSize(kit_width,0),pContext);//создаём первый вид
 cSplitterWnd_Main.CreateView(0,1,RUNTIME_CLASS(CView_OutTasks),CSize(out_tasks_width,0),pContext);//создаём второй вид
 cSplitterWnd_Main.CreateView(0,2,RUNTIME_CLASS(CView_MyTasks),CSize(my_tasks_width,0),pContext);//создаём третий вид
 SetActiveView((CView*)cSplitterWnd_Main.GetPane(0,1));//устанавливаем активный вид
 return(TRUE);
}
//----------------------------------------------------------------------------------------------------
//создание рамки
//----------------------------------------------------------------------------------------------------
afx_msg int CFrameWnd_Main::OnCreate(LPCREATESTRUCT lpCreateStruct)
{ 
 //запускаем таймер
 SetTimer(ID_TIMER_FRAMEWND_MAIN,FRAME_WND_TIMER_PERIOD,NULL); 
 //создаём иконку в трее
 hIcon_SysTray=(HICON)LoadImage(AfxGetInstanceHandle(),(char*)IDI_ICON_SYSTRAY,IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
 hIcon_SysTray_NotRead=(HICON)LoadImage(AfxGetInstanceHandle(),(char*)IDI_ICON_SYSTRAY_NOT_READ,IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
 hIcon_SysTray_NotReadInverse=(HICON)LoadImage(AfxGetInstanceHandle(),(char*)IDI_ICON_SYSTRAY_NOT_READ_INVERSE,IMAGE_ICON,32,32,LR_DEFAULTCOLOR);

 NotifyIconData.cbSize=sizeof(NOTIFYICONDATA);
 NotifyIconData.hWnd=m_hWnd;
 NotifyIconData.uID=IDI_ICON_SYSTRAY;
 NotifyIconData.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
 NotifyIconData.uCallbackMessage=WM_SYSTEM_TRAY_ICON;
 NotifyIconData.hIcon=hIcon_SysTray;
 strcpy(NotifyIconData.szTip,"Team Control клиент");
 Shell_NotifyIcon(NIM_ADD,&NotifyIconData);
 SetIcon(NotifyIconData.hIcon,TRUE); 

 cDialog_About.Create((LPSTR)IDD_DIALOG_ABOUT,this);
 
 CRect cRect_Window;
 GetWindowRect(&cRect_Window);

 CRect cRect_About;
 cDialog_About.GetWindowRect(&cRect_About);

 long window_width=(cRect_Window.right-cRect_Window.left);
 long window_height=(cRect_Window.bottom-cRect_Window.top);

 long about_width=(cRect_About.right-cRect_About.left);
 long about_height=(cRect_About.bottom-cRect_About.top);

 long x=cRect_Window.left+(window_width-about_width)/2;
 long y=cRect_Window.top+(window_height-about_height)/2;
 cDialog_About.MoveWindow(x,y,about_width,about_height,TRUE);
 cDialog_About.ShowWindow(SW_SHOW);

 AboutCounter=ABOUT_TIMER_MAX_CONTER;
 ChangeSysTrayIconCounter=SYSTRAY_CHANGE_ICON_COUNTER;

 return(CFrameWnd::OnCreate(lpCreateStruct));
}
//----------------------------------------------------------------------------------------------------
//уничтожение рамки
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnDestroy(void)
{
 KillTimer(ID_TIMER_FRAMEWND_MAIN);
 Shell_NotifyIcon(NIM_DELETE,&NotifyIconData);
 if (hIcon_SysTray!=NULL) DeleteObject(hIcon_SysTray);
 if (hIcon_SysTray_NotRead!=NULL) DeleteObject(hIcon_SysTray_NotRead);
 if (hIcon_SysTray_NotReadInverse!=NULL) DeleteObject(hIcon_SysTray_NotReadInverse);
 hIcon_SysTray=NULL;
 hIcon_SysTray_NotRead=NULL;
 hIcon_SysTray_NotReadInverse=NULL;
}
//----------------------------------------------------------------------------------------------------
//событие таймера
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnTimer(UINT nIDEvent)
{
 if (nIDEvent==ID_TIMER_FRAMEWND_MAIN)
 { 
  CDocument_Main *cDocument_Main_Ptr=(CDocument_Main*)GetActiveDocument();
  if (PingCounter>0) PingCounter--;
  else
  {
   if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetSendPing(true);
   PingCounter=PING_COUNTER_MAX_VALUE;
  }
  bool not_read_task=false;
  if (cDocument_Main_Ptr!=NULL)
  {
   not_read_task=cDocument_Main_Ptr->GetNotReadTaskState();
   if (cDocument_Main_Ptr->GetRestartWithLoaderState()==true)//перезапускаемся через загрузчик
   {
    //запускаем загрузчик
    ShellExecute(NULL,NULL,"TeamControlLoader.exe",NULL,NULL,SW_SHOWNORMAL); 
    DestroyWindow();
	return;
   }
  }

  if (ChangeSysTrayIconCounter>0)
  {
   ChangeSysTrayIconCounter--;
  }
  else
  {
   //меняем иконку
   HICON hIcon_Old=NotifyIconData.hIcon;
   if (not_read_task==false)
   {
    NotifyIconData.hIcon=hIcon_SysTray;
   }
   else
   {
    if (hIcon_Old==hIcon_SysTray_NotRead || hIcon_Old==hIcon_SysTray)
    {
     NotifyIconData.hIcon=hIcon_SysTray_NotReadInverse;
    }
    if (hIcon_Old==hIcon_SysTray_NotReadInverse)
    {
     NotifyIconData.hIcon=hIcon_SysTray_NotRead;
    }
   }
   Shell_NotifyIcon(NIM_MODIFY,&NotifyIconData);
   ChangeSysTrayIconCounter=SYSTRAY_CHANGE_ICON_COUNTER;
  }

  if (AboutCounter>0)
  {
   AboutCounter--;
   if (AboutCounter==0) cDialog_About.ShowWindow(SW_HIDE);
  }
  if (cDocument_Main_Ptr!=NULL) 
  {
   cDocument_Main_Ptr->Processing();
   bool on_line;
   CSafeString guid;
   CSafeString name;
   bool leader;
   cDocument_Main_Ptr->GetMyParam(on_line,guid,name,leader);
   CSafeString out="Клиент Team Control: "+name+"    ";
   if (on_line==true) out+="В сети";
                 else out+="НЕ В СЕТИ";
   SetWindowText(out);
   if (cDocument_Main_Ptr->GetOnShowAndResetOnShow()==true) ShowWindow(SW_SHOW);
  }
 }
 CFrameWnd::OnTimer(nIDEvent);
}
//----------------------------------------------------------------------------------------------------
//изменение размеров окна
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnSize(UINT nType,int cx,int cy)
{
 //выполняем изменение размеров окна
 CFrameWnd::OnSize(nType,cx,cy);
 /*
 //почему-то не работает
 long n;
 //определим пропорции видов
 long pane_width[3];
 long all_pane_width=0;
 for(n=0;n<3;n++)
 {
  CWnd *cWnd_Pane_Ptr;
  RECT Rect;
  cWnd_Pane_Ptr=cSplitterWnd_Main.GetPane(0,n);
  if (cWnd_Pane_Ptr==NULL)
  {
   CFrameWnd::OnSize(nType,cx,cy);
   return;
  }
  cWnd_Pane_Ptr->GetWindowRect(&Rect);
  pane_width[n]=Rect.right-Rect.left;
  all_pane_width+=pane_width[n];
 }
 if (all_pane_width==0) all_pane_width=1;
 //выполняем изменение размеров окна
 CFrameWnd::OnSize(nType,cx,cy);
 //задаём новые пропорции видов
 for(n=0;n<3;n++)
 {
  CWnd *cWnd_Pane_Ptr;
  RECT Rect;
  cWnd_Pane_Ptr=cSplitterWnd_Main.GetPane(0,n);
  cWnd_Pane_Ptr->GetWindowRect(&Rect);  
  long new_width=(pane_width[n]*cx)/all_pane_width;
  long height=Rect.bottom-Rect.top;
  cWnd_Pane_Ptr->MoveWindow(Rect.left,Rect.top,new_width,height,TRUE);
 } 
 
 CDocument *cDocument_Ptr=GetActiveDocument();
 cDocument_Ptr->UpdateAllViews(NULL);
 */
}
//----------------------------------------------------------------------------------------------------
//изменение параметров окна
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnSysCommand(UINT nID,LPARAM lParam)
{
 if (nID==SC_MINIMIZE || nID==SC_CLOSE)//свернём окно в системный лоток
 {
  ShowWindow(SW_HIDE);
  return;
 }
 CFrameWnd::OnSysCommand(nID,lParam);
}

//====================================================================================================
//функции обработки сообщений
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//настройка клиента
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_Menu_Main_Settings(void)
{
 CDocument_Main *cDocument_Main_Ptr=reinterpret_cast<CDocument_Main*>(GetActiveDocument());
 if (cDocument_Main_Ptr==NULL) return;
 SClientSettings sClientSettings;
 cDocument_Main_Ptr->GetClientSettings(sClientSettings);
 CDialog_ClientSettings cDialog_ClientSettings((LPCSTR)IDD_DIALOG_CLIENT_SETTINGS,this);
 if (cDialog_ClientSettings.Activate(sClientSettings)==true) cDocument_Main_Ptr->SetClientSettings(sClientSettings);
}

//----------------------------------------------------------------------------------------------------
//удаление завершённых заданий
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_Menu_Main_DeleteFinishedTask(void)
{
 CDocument_Main *cDocument_Main_Ptr=reinterpret_cast<CDocument_Main*>(GetActiveDocument());
 if (cDocument_Main_Ptr==NULL) return;
 CDialog_DeleteFinishedTask cDialog_DeleteFinishedTask((LPCSTR)IDD_DIALOG_DELETE_FINISHED_TASK,this);
 long year=0;
 long month=0;
 long day=0;
 if (cDialog_DeleteFinishedTask.Activate(year,month,day)==true) cDocument_Main_Ptr->DeleteFinishedTask(year,month,day);
}

//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка выданных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_OutTaskShowCancelled(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка выполненных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_OutTaskShowDone(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка не прочитанных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_OutTaskShowNotRead(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка завершённых" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_OutTaskShowFinished(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка выполняющихся" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_OutTaskShowIsRunning(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка прочитанных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_OutTaskShowReaded(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка полученных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_MyTaskShowCancelled(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка выполненных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_MyTaskShowDone(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка не прочитанных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_MyTaskShowNotRead(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка завершённых" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_MyTaskShowFinished(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка выполняющихся" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_MyTaskShowIsRunning(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показать отменённые задания из списка прочитанных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_MyTaskShowReaded(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//нажата кнопка "показывать общие задания вместо выданных" главной панели инструментов 
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_ToolBar_Main_ShowCommonTask(void)
{
 CheckToolBarMainButtonAndSetShowStateInDocument();
}
//----------------------------------------------------------------------------------------------------
//обработка сообщений трея
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnSystemTrayIconMessage(WPARAM wParam,LPARAM lParam)
{
 if (wParam!=IDI_ICON_SYSTRAY) return;//это не наша иконка в лотке 
 if (lParam==WM_LBUTTONUP)//нажали и отпустили левую кнопку мыши
 {  
  SetForegroundWindow();
  ShowWindow(SW_SHOW);
 }
 if (lParam==WM_RBUTTONUP)//нажали и отпустили правую кнопку мыши
 {  
  SetForegroundWindow();
  //отображаем меню
  CMenu *cMenu=new CMenu;
  cMenu->CreatePopupMenu();
  cMenu->AppendMenu(MF_STRING,IDC_MENU_SYSTRAY_EXIT,"Завершить работу программы");
  CPoint cPoint;
  GetCursorPos(&cPoint);
  cMenu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON,cPoint.x,cPoint.y,this);
  delete(cMenu);
 }
}
//----------------------------------------------------------------------------------------------------
//обработка команды выхода из программы
//----------------------------------------------------------------------------------------------------
afx_msg void CFrameWnd_Main::OnCommand_Menu_SysTray_Exit(void)
{
 if (MessageBox("Завершить работу программы?","Подтверждение",MB_YESNO|MB_DEFBUTTON2)!=IDYES) return;
 DestroyWindow();
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//проверить кнопки главной панели инструментов и задать их состояние в документе
//----------------------------------------------------------------------------------------------------
void CFrameWnd_Main::CheckToolBarMainButtonAndSetShowStateInDocument(void)
{
 SShowState sShowState;
 CDocument_Main *cDocument_Main_Ptr=(CDocument_Main*)GetActiveDocument();
 if (cDocument_Main_Ptr==NULL) return;//ошибка
 cDocument_Main_Ptr->GetShowState(sShowState);

 sShowState.OutTask_Show_Cancelled=false;
 sShowState.OutTask_Show_Done=false;
 sShowState.OutTask_Show_NotRead=false;
 sShowState.OutTask_Show_Finished=false;
 sShowState.OutTask_Show_IsRunning=false;
 sShowState.OutTask_Show_Readed=false;

 sShowState.MyTask_Show_Cancelled=false;
 sShowState.MyTask_Show_Done=false;
 sShowState.MyTask_Show_NotRead=false;
 sShowState.MyTask_Show_Finished=false;
 sShowState.MyTask_Show_IsRunning=false;
 sShowState.MyTask_Show_Readed=false;

 sShowState.ShowCommonTask=false;

 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_CANCELLED)) sShowState.OutTask_Show_Cancelled=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_DONE)) sShowState.OutTask_Show_Done=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_NOT_READ)) sShowState.OutTask_Show_NotRead=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_FINISHED)) sShowState.OutTask_Show_Finished=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_IS_RUNNING)) sShowState.OutTask_Show_IsRunning=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_OUT_TASK_SHOW_READED)) sShowState.OutTask_Show_Readed=true;

 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_CANCELLED)) sShowState.MyTask_Show_Cancelled=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_DONE)) sShowState.MyTask_Show_Done=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_NOT_READ)) sShowState.MyTask_Show_NotRead=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_FINISHED)) sShowState.MyTask_Show_Finished=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_IS_RUNNING)) sShowState.MyTask_Show_IsRunning=true;
 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_IN_MY_TASK_SHOW_READED)) sShowState.MyTask_Show_Readed=true;

 if (cToolBar_Main.GetToolBarCtrl().IsButtonChecked(IDC_TOOLBAR_MAIN_SHOW_COMMON_TASK)) sShowState.ShowCommonTask=true;

 cDocument_Main_Ptr->SetShowState(sShowState);
 cDocument_Main_Ptr->UpdateAllViews(NULL,0,NULL);
}


//====================================================================================================
//Прочее
//====================================================================================================
IMPLEMENT_DYNCREATE(CFrameWnd_Main,CFrameWnd)

