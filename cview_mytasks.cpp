#include "cview_mytasks.h"

//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

BEGIN_MESSAGE_MAP(CView_MyTasks,CView)
 ON_WM_SIZE()
 ON_WM_ERASEBKGND()
 ON_WM_RBUTTONDOWN()
 ON_WM_LBUTTONDOWN()
 ON_WM_LBUTTONDBLCLK()
 ON_WM_MOUSEWHEEL()
 ON_WM_CREATE()
 ON_WM_TIMER()
 ON_WM_DESTROY()
 ON_WM_VSCROLL()
 ON_COMMAND(IDC_MENU_LIST_VIEW_MY_TASK_SET_DONE,OnCommand_Menu_List_SetTaskDone)
 ON_COMMAND(IDC_MENU_LIST_VIEW_MY_TASK_SET_READED,OnCommand_Menu_List_SetTaskReaded)
 ON_COMMAND(IDC_MENU_LIST_VIEW_MY_TASK_SET_IS_RUNNING,OnCommand_Menu_List_SetTaskIsRunning)
 ON_COMMAND(IDC_MENU_LIST_VIEW_MY_TASK_SET_CANCELED,OnCommand_Menu_List_SetTaskCanceled)
 ON_COMMAND(IDC_MENU_LIST_VIEW_MY_TASK_SEND,OnCommand_Menu_List_SendTask)
END_MESSAGE_MAP()

//====================================================================================================
//конструктор класса
//====================================================================================================
CView_MyTasks::CView_MyTasks() 
{
 VisibleFromUser=true;
 VisibleForUser=false;	
 ColumnName="ѕолученные задани€";
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CView_MyTasks::~CView_MyTasks() 
{
}

//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//создание окна
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnInitialUpdate(void)
{ 
 //создадим контекстное меню
 cMenu_List.LoadMenu(IDR_MENU_LIST_VIEW_MY_TASK);
 //загружаем изображени€
 cBitmap_MenuList_TaskDone.LoadBitmap(IDB_BITMAP_MENU_TASK_DONE);
 cBitmap_MenuList_SetTaskReaded.LoadBitmap(IDB_BITMAP_MENU_TASK_READED);
 cBitmap_MenuList_SetTaskIsRunning.LoadBitmap(IDB_BITMAP_MENU_TASK_IS_RUNNING);
 cBitmap_MenuList_SetTaskCanceled.LoadBitmap(IDB_BITMAP_MENU_DELETE_TASK);
 cBitmap_MenuList_SendTask.LoadBitmap(IDB_BITMAP_MENU_ADD_TASK);

 CView_Base::OnInitialUpdate();
}
//----------------------------------------------------------------------------------------------------
//обновить вид
//----------------------------------------------------------------------------------------------------
void CView_MyTasks::OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 CSafeString guid;
 CSafeString name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,guid,name,leader);
 
 vector<CTask> vector_CTask_Local;
 vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskByForUserGUID(guid); 
 
 size_t size=vector_CTask_Local.size();
 bool not_read_task_state=false;
 for(size_t n=0;n<size;n++)
 {
  if (vector_CTask_Local[n].IsStateNoRead()==true)
  {
   not_read_task_state=true;
   break;
  }
 }
 cDocument_Main_Ptr->SetNotReadTaskState(not_read_task_state);
 CView_Base::OnUpdate(pSender,lHint,pHint);	
 UpdateTask(vector_CTask_Local); 
 return;
}
//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//нажатие правой кнопкой мышки
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnRButtonDown(UINT nFlags,CPoint point)
{
 OnLButtonDown(nFlags,point);
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 if (cTask.IsStateFinished()==true) return;//завершЄнные задани€ измен€ть нельз€
 //создаЄм выпадающее меню
 CPoint mpoint;
 GetCursorPos(&mpoint);
 //есть ли в списке нужное нам задание
 size_t size=vector_SCell_Task.size();
 for(size_t n=0;n<size;n++)
 {
  SCell &sCell=vector_SCell_Task[n];
  if (SelectedTaskGUID.Compare(sCell.GUID)==0)//выбранное задание находитс€ в списке отображени€
  {
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_MY_TASK_SET_DONE,MF_BYCOMMAND,&cBitmap_MenuList_TaskDone,&cBitmap_MenuList_TaskDone);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_MY_TASK_SET_READED,MF_BYCOMMAND,&cBitmap_MenuList_SetTaskReaded,&cBitmap_MenuList_SetTaskReaded);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_MY_TASK_SET_IS_RUNNING,MF_BYCOMMAND,&cBitmap_MenuList_SetTaskIsRunning,&cBitmap_MenuList_SetTaskIsRunning);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_MY_TASK_SET_CANCELED,MF_BYCOMMAND,&cBitmap_MenuList_SetTaskCanceled,&cBitmap_MenuList_SetTaskCanceled);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_MY_TASK_SEND,MF_BYCOMMAND,&cBitmap_MenuList_SendTask,&cBitmap_MenuList_SendTask);
   cMenu_List.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,mpoint.x,mpoint.y,this); 	
   return;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//нажатие левой кнопкой мышки
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnLButtonDown(UINT nFlags,CPoint point)
{
 SelectedTaskGUID="";
 //ищем, что же было выбрано мышкой
 size_t size=vector_SCell_Task.size();
 for(size_t n=0;n<size;n++)
 {
  SCell &sCell=vector_SCell_Task[n];
  if (point.x>=sCell.cRect.left && point.x<=sCell.cRect.right && point.y>=sCell.cRect.top && point.y<=sCell.cRect.bottom)
  {
   SelectedTaskGUID=sCell.GUID;
   InvalidateRect(NULL,FALSE);
   return;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//двойное нажатие левой кнопкой мышки
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnLButtonDblClk(UINT nFlags,CPoint point)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 if (cTask.IsStateFinished()==true) return;//завершЄнные задани€ измен€ть нельз€
 //просим изменить задание
 while(1)
 {
  CDialog_TaskSetState cDialog_TaskSetState((LPCSTR)IDD_DIALOG_TASK_SET_STATE,this);
  if (cDialog_TaskSetState.Activate(cTask)==true)
  {
   //просим изменить задание
   if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
   {
    MessageBox("Ќе удалось изменить задание!","ќшибка",MB_OK);
   }
   else break;
  }
  else break;
 } 
}

//----------------------------------------------------------------------------------------------------
//установить, что задание завершено
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnCommand_Menu_List_SetTaskDone(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 //просим изменить задание
 cTask.SetStateDone();
 if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
 {
  MessageBox("Ќе удалось изменить задание!","ќшибка",MB_OK);
 }
}
//----------------------------------------------------------------------------------------------------
//установить, что задание прочитано
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnCommand_Menu_List_SetTaskReaded(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 //просим изменить задание
 cTask.SetStateReaded();
 if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
 {
  MessageBox("Ќе удалось изменить задание!","ќшибка",MB_OK);
 }
}
//----------------------------------------------------------------------------------------------------
//установить, что задание выполн€етс€
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnCommand_Menu_List_SetTaskIsRunning(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 //просим изменить задание
 cTask.SetStateIsRunning();
 if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
 {
  MessageBox("Ќе удалось изменить задание!","ќшибка",MB_OK);
 }
}
//----------------------------------------------------------------------------------------------------
//установить, что задание отклонено
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnCommand_Menu_List_SetTaskCanceled(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 //просим изменить задание
 cTask.SetStateCancelled();
 if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
 {
  MessageBox("Ќе удалось изменить задание!","ќшибка",MB_OK);
 }
}
//----------------------------------------------------------------------------------------------------
//поручить копию задани€
//----------------------------------------------------------------------------------------------------
afx_msg void CView_MyTasks::OnCommand_Menu_List_SendTask(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //получаем выбранное задание
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 cTask.SetAnswer("");
 //запускаем диалог создани€ нового задани€
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(cTask,cDocument_Main_Ptr,true)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //просим добавить задание
   if (cDocument_Main_Ptr->AddTask(cTask)==false)
   {
    MessageBox("Ќе удалось создать задание!","ќшибка",MB_OK);
   }
   else break;
  }
  else break;
 }
}

//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//разрешено ли отображать задание
//----------------------------------------------------------------------------------------------------
bool CView_MyTasks::TaskIsVisible(const SShowState &sShowState,const CTask& cTask)
{
 if (cTask.IsStateNoRead()==true && sShowState.MyTask_Show_NotRead==false) return(false);
 if (cTask.IsStateReaded()==true && sShowState.MyTask_Show_Readed==false) return(false);
 if (cTask.IsStateIsRunning()==true && sShowState.MyTask_Show_IsRunning==false) return(false);
 if (cTask.IsStateDone()==true && sShowState.MyTask_Show_Done==false) return(false);
 if (cTask.IsStateCancelled()==true && sShowState.MyTask_Show_Cancelled==false) return(false);
 if (cTask.IsStateFinished()==true && sShowState.MyTask_Show_Finished==false) return(false);
 return(true);
}

//====================================================================================================
//прочее
//====================================================================================================
IMPLEMENT_DYNCREATE(CView_MyTasks,CView)
