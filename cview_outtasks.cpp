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
 ON_WM_TIMER()
 ON_WM_DESTROY()
 ON_WM_VSCROLL()
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_REPEAT_TASK,OnCommand_Menu_List_TaskRepeat)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_DELETE_TASK,OnCommand_Menu_List_TaskDelete)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_EDIT_TASK,OnCommand_Menu_List_TaskEdit)
 ON_COMMAND(IDC_MENU_LIST_VIEW_OUT_TASK_SET_FINISHED,OnCommand_Menu_List_SetTaskFinished)
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
 //�������� ����������� ����
 cMenu_List.LoadMenu(IDR_MENU_LIST_VIEW_OUT_TASK);
 //��������� �����������
 cBitmap_MenuList_DeleteTask.LoadBitmap(IDB_BITMAP_MENU_DELETE_TASK);
 cBitmap_MenuList_EditTask.LoadBitmap(IDB_BITMAP_MENU_EDIT_TASK);
 cBitmap_MenuList_RepeatTask.LoadBitmap(IDB_BITMAP_MENU_REPEAT_TASK);
 cBitmap_MenuList_SetTaskFinished.LoadBitmap(IDB_BITMAP_MENU_TASK_FINISHED);
 CView_Base::OnInitialUpdate();
}
//----------------------------------------------------------------------------------------------------
//�������� ���
//----------------------------------------------------------------------------------------------------
void CView_OutTasks::OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 vector<STask> vector_STask_Local;

 SUser sUser;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser)==false)
 {
  CView_Base::OnUpdate(pSender,lHint,pHint);	
  UpdateTask(vector_STask_Local);
  return;
 }
 CString guid;
 CString name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,guid,name,leader);
 if (sUser.UserGUID.Compare(ALL_USER_GUID)==0)//������� ����� ��� ������������
 {
  vector_STask_Local=cDocument_Main_Ptr->CreateVectorSTaskByFromUserGUID(guid); 
  VisibleFromUser=false;
  VisibleForUser=true;
 }
 else 
 {
  //��������, �� ������ �� ������, � �� ������������
  SUser sUser_Out;
  if (cDocument_Main_Ptr->GetCVectorUser().FindByUserGUID(sUser.UserGUID,sUser_Out)==false)//������ ����������� ��� � ����
  {
   vector_STask_Local=cDocument_Main_Ptr->CreateVectorSTaskByProjectGUIDFromUserGUID(sUser.UserGUID,guid);
   VisibleFromUser=true;
   VisibleForUser=true;
  }
  else//��� ������ ������������
  {
   vector_STask_Local=cDocument_Main_Ptr->CreateVectorSTaskByForUserOneGUIDAndFromUserTwoGUID(sUser.UserGUID,guid); 
   VisibleFromUser=false;
   VisibleForUser=false;
  }
 }
 CView_Base::OnUpdate(pSender,lHint,pHint);	
 UpdateTask(vector_STask_Local);
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
 //���� �� � ������ ����� ��� �������
 size_t size=vector_SCell_Task.size();
 for(size_t n=0;n<size;n++)
 {
  SCell &sCell=vector_SCell_Task[n];
  if (SelectedTaskGUID.Compare(sCell.GUID)==0)//��������� ������� ��������� � ������ �����������
  {
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_DELETE_TASK,MF_BYCOMMAND,&cBitmap_MenuList_DeleteTask,&cBitmap_MenuList_DeleteTask);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_EDIT_TASK,MF_BYCOMMAND,&cBitmap_MenuList_EditTask,&cBitmap_MenuList_EditTask);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_REPEAT_TASK,MF_BYCOMMAND,&cBitmap_MenuList_RepeatTask,&cBitmap_MenuList_RepeatTask);
   cMenu_List.SetMenuItemBitmaps(IDC_MENU_LIST_VIEW_OUT_TASK_SET_FINISHED,MF_BYCOMMAND,&cBitmap_MenuList_SetTaskFinished,&cBitmap_MenuList_SetTaskFinished);
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
 STask sTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,sTask)==false) return;
 //������ �������� �������
 sTask.State=TASK_STATE_NO_READ;
 if (cDocument_Main_Ptr->ChangeTask(sTask)==false)
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
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 STask sTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,sTask)==false) return;
 if (MessageBox("������� ��������� �������?","�������������",MB_YESNO|MB_DEFBUTTON2)!=IDYES) return;
 cDocument_Main_Ptr->DeleteTask(sTask); 
}
//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CView_OutTasks::OnCommand_Menu_List_TaskEdit(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 STask sTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,sTask)==false) return;
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(sTask,cDocument_Main_Ptr,false)==true)
  {
   //������ �������� �������
   if (cDocument_Main_Ptr->ChangeTask(sTask)==false)
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
 //�������� ��������� �������
 CVectorTask cVectorTask=cDocument_Main_Ptr->GetCVectorTask();
 STask sTask;
 if (cVectorTask.FindByTaskGUID(SelectedTaskGUID,sTask)==false) return;
 //������ �������� �������
 sTask.State=TASK_STATE_FINISHED;
 if (cDocument_Main_Ptr->ChangeTask(sTask)==false)
 {
  MessageBox("�� ������� �������� �������!","������",MB_OK);
 }
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//��������� �� ���������� �������
//----------------------------------------------------------------------------------------------------
bool CView_OutTasks::TaskIsVisible(const SShowState &sShowState,const long &state)
{
 if (state==TASK_STATE_NO_READ && sShowState.OutTask_Show_NotRead==false) return(false);
 if (state==TASK_STATE_READED && sShowState.OutTask_Show_Readed==false) return(false);
 if (state==TASK_STATE_IS_RUNNING && sShowState.OutTask_Show_IsRunning==false) return(false);
 if (state==TASK_STATE_DONE && sShowState.OutTask_Show_Done==false) return(false);
 if (state==TASK_STATE_CANCELED && sShowState.OutTask_Show_Cancelled==false) return(false);
 if (state==TASK_STATE_FINISHED && sShowState.OutTask_Show_Finished==false) return(false);
 return(true);
}
//====================================================================================================
//������
//====================================================================================================
IMPLEMENT_DYNCREATE(CView_OutTasks,CView)
