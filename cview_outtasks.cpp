#include "cview_outtasks.h"

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

BEGIN_MESSAGE_MAP(CView_OutTasks,CView)
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
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_REPEAT_TASK,OnCommand_Menu_List_TaskRepeat)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_DELETE_TASK,OnCommand_Menu_List_TaskDelete)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_EDIT_TASK,OnCommand_Menu_List_TaskEdit)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_SET_FINISHED,OnCommand_Menu_List_SetTaskFinished)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_SEND_TASK_COPY,OnCommand_Menu_List_SendTaskCopy)
END_MESSAGE_MAP()

//====================================================================================================
//����������� ������
//====================================================================================================
CView_OutTasks::CView_OutTasks() 
{ 
 VisibleFromUser=false;
 VisibleForUser=false;
 ColumnName="�������� �������";
}
//====================================================================================================
//���������� ������
//====================================================================================================
CView_OutTasks::~CView_OutTasks() 
{
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//�������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnInitialUpdate(void)
{ 	
 CView_Base::OnInitialUpdate();
 //�������� ����������� ����
 cMenu_List.LoadMenu(IDR_MENU_LIST_VIEW_OUT_TASK);
 //��������� �����������
 cBitmap_MenuList_DeleteTask.LoadBitmap(IDB_BITMAP_MENU_DELETE_TASK);
 cBitmap_MenuList_EditTask.LoadBitmap(IDB_BITMAP_MENU_EDIT_TASK);
 cBitmap_MenuList_RepeatTask.LoadBitmap(IDB_BITMAP_MENU_REPEAT_TASK);
 cBitmap_MenuList_SetTaskFinished.LoadBitmap(IDB_BITMAP_MENU_TASK_FINISHED);
 cBitmap_MenuList_SendTaskCopy.LoadBitmap(IDB_BITMAP_MENU_ADD_TASK);
}
//----------------------------------------------------------------------------------------------------
//�������� ���
//----------------------------------------------------------------------------------------------------
void CView_OutTasks::OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 vector<CTask> vector_CTask_Local;

 CUser cUser;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser)==false)
 {
  CView_Base::OnUpdate(pSender,lHint,pHint);	
  UpdateTask(vector_CTask_Local);
  return;
 }
 CSafeString my_guid;
 CSafeString my_name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,my_guid,my_name,leader);
 if (cUser.IsUserGUID(ALL_USER_GUID)==true)//������� ����� ��� ������������
 {
  if (cDocument_Main_Ptr->IsShowCommonTask()==true) vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskCommon(); 
                                               else vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskByFromUserGUID(my_guid); 
  VisibleFromUser=false;
  VisibleForUser=true;
 }
 else 
 {
  //��������, �� ������ �� ������, � �� ������������
  CUser cUser_Out;
  if (cDocument_Main_Ptr->GetCVectorUser().FindByUserGUID(cUser.GetUserGUID(),cUser_Out)==false)//������ ������������ ��� � ����, ������, ��� ������ ������
  {
   if (cDocument_Main_Ptr->IsShowCommonTask()==true) vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskCommonByProjectGUID(cUser.GetUserGUID());
                                                else vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskByProjectGUIDFromUserGUID(cUser.GetUserGUID(),my_guid);
   VisibleFromUser=true;
   VisibleForUser=true;
  }
  else//��� ������ ������������
  {
   if (cDocument_Main_Ptr->IsShowCommonTask()==true) vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskCommonByForUserGUID(cUser.GetUserGUID()); 
	                                            else vector_CTask_Local=cDocument_Main_Ptr->CreateVectorCTaskByForUserOneGUIDAndFromUserTwoGUID(cUser.GetUserGUID(),my_guid);
   VisibleFromUser=false;
   VisibleForUser=false;
  }
 }
 if (cDocument_Main_Ptr->IsShowCommonTask()==true) VisibleFromUser=true;
 CView_Base::OnUpdate(pSender,lHint,pHint);	
 UpdateTask(vector_CTask_Local);
}
//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================



//----------------------------------------------------------------------------------------------------
//������� ������ ������� �����
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnRButtonDown(UINT nFlags,CPoint point)
{
 OnLButtonDown(nFlags,point);

 //������ ���������� ����
 CPoint mpoint;
 GetCursorPos(&mpoint);
 //���� �� � ������ ������ ��� �������
 size_t size=vector_SCell_Task.size();
 for(size_t n=0;n<size;n++)
 {
  SCell &sCell=vector_SCell_Task[n];
  if (SelectedTaskGUID.Compare(sCell.GUID)==0)//��������� ������� ��������� � ������ �����������
  {
   if (IsMyTask(SelectedTaskGUID)==false) return;
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_DELETE_TASK,MF_BYCOMMAND,&cBitmap_MenuList_DeleteTask,&cBitmap_MenuList_DeleteTask);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_EDIT_TASK,MF_BYCOMMAND,&cBitmap_MenuList_EditTask,&cBitmap_MenuList_EditTask);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_REPEAT_TASK,MF_BYCOMMAND,&cBitmap_MenuList_RepeatTask,&cBitmap_MenuList_RepeatTask);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_SET_FINISHED,MF_BYCOMMAND,&cBitmap_MenuList_SetTaskFinished,&cBitmap_MenuList_SetTaskFinished);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_SEND_TASK_COPY,MF_BYCOMMAND,&cBitmap_MenuList_SendTaskCopy,&cBitmap_MenuList_SendTaskCopy);
   cMenu_List.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,mpoint.x,mpoint.y,this); 	
   return;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������� ����� ������� �����
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnLButtonDown(UINT nFlags,CPoint point)
{
 SelectedTaskGUID="";
 //����, ��� �� ���� ������� ������
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
//������� ������� ����� ������� �����
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnLButtonDblClk(UINT nFlags,CPoint point)
{
 OnCommand_Menu_List_TaskEdit();
}
//----------------------------------------------------------------------------------------------------
//��������� ���������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnCommand_Menu_List_TaskRepeat(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 if (IsMyTask(SelectedTaskGUID)==false) return;
 //������ �������� �������
 cTask.SetStateNoRead();
 if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
 {
  MessageBox("�� ������� �������� �������!","������",MB_OK);
 }
}
//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnCommand_Menu_List_TaskDelete(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;

 if (IsMyTask(SelectedTaskGUID)==false) return;
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 if (MessageBox("������� ��������� �������?","�������������",MB_YESNO|MB_DEFBUTTON2)!=IDYES) return;
 cDocument_Main_Ptr->DeleteTask(cTask); 
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnCommand_Menu_List_TaskEdit(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;

 if (IsMyTask(SelectedTaskGUID)==false) return;

 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 CSafeString for_user_guid=cTask.GetForUserGUID();
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(cTask,cDocument_Main_Ptr,false)==true)
  {   
   if (cTask.IsForUserGUID(for_user_guid)==false)//� ������� ��������� �������
   {
    cTask.SetAnswer("");//������� ����������� ������� ��������
   }
   //������ �������� �������
   if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
   {
    MessageBox("�� ������� �������� �������!","������",MB_OK);
   }
   else break;
  }
  else break;
 } 
}
//----------------------------------------------------------------------------------------------------
//��������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnCommand_Menu_List_SetTaskFinished(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 if (IsMyTask(SelectedTaskGUID)==false) return;
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 //������ �������� �������
 cTask.SetStateFinished();
 if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
 {
  MessageBox("�� ������� �������� �������!","������",MB_OK);
 }
}

//----------------------------------------------------------------------------------------------------
//��������� ����� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnCommand_Menu_List_SendTaskCopy(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 cTask.SetAnswer("");
 CSafeString for_user_guid=cTask.GetForUserGUID();
 //��������� ������ �������� ������ �������
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(cTask,cDocument_Main_Ptr,true)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   if (cTask.IsForUserGUID(for_user_guid)==true)
   {
    MessageBox("��������� �������� ������������, ��� �������� �������� �������!","������",MB_OK);
	continue;
   }
   //������ �������� �������
   if (cDocument_Main_Ptr->AddTask(cTask)==false)
   {
    MessageBox("�� ������� ������� �������!","������",MB_OK);
   }
   else break;
  }
  else break;
 }

/* CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;

 if (IsMyTask(SelectedTaskGUID)==false) return;

 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,cTask)==false) return;
 CSafeString for_user_guid=cTask.GetForUserGUID();
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(cTask,cDocument_Main_Ptr,false)==true)
  {   
   if (cTask.IsForUserGUID(for_user_guid)==false)//� ������� ��������� �������
   {
    cTask.SetAnswer("");//������� ����������� ������� ��������
   }
   //������ �������� �������
   if (cDocument_Main_Ptr->ChangeTask(cTask)==false)
   {
    MessageBox("�� ������� �������� �������!","������",MB_OK);
   }
   else break;
  }
  else break;
 } 
 */
}

//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//��������� �� ���������� �������
//----------------------------------------------------------------------------------------------------
bool CView_OutTasks::TaskIsVisible(const SShowState &sShowState,const CTask &cTask)
{
 if (cTask.IsStateNoRead()==true && sShowState.OutTask_Show_NotRead==false) return(false);
 if (cTask.IsStateReaded()==true && sShowState.OutTask_Show_Readed==false) return(false);
 if (cTask.IsStateIsRunning()==true && sShowState.OutTask_Show_IsRunning==false) return(false);
 if (cTask.IsStateDone()==true && sShowState.OutTask_Show_Done==false) return(false);
 if (cTask.IsStateCancelled()==true && sShowState.OutTask_Show_Cancelled==false) return(false);
 if (cTask.IsStateFinished()==true && sShowState.OutTask_Show_Finished==false) return(false);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ������� � ��������������� ������ ����
//----------------------------------------------------------------------------------------------------
bool CView_OutTasks::IsMyTask(const CSafeString &task_guid)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return(false);
 CSafeString my_guid;
 CSafeString my_name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,my_guid,my_name,leader);

 //��������, ��� ������� ������� �� ���
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 CTask cTask;
 if (cVectorTask.FindByTaskGUID(task_guid,cTask)==false) return(false);
 if (cTask.IsFromUserGUID(my_guid)==false) return(false);//��� �� ���� �������
 return(true);
}

//====================================================================================================
//������
//====================================================================================================
IMPLEMENT_DYNCREATE(CView_OutTasks,CView)
