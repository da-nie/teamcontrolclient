#include "cdialog_tasksetstate.h"

//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_TaskSetState,CDialog)
 ON_WM_DESTROY()
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SET_STATE_CANCEL,OnCommand_Button_Cancel)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_DONE,OnCommand_Button_TaskDone)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_IS_RUNNING,OnCommand_Button_TaskIsRunning)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_CANCEL,OnCommand_Button_TaskCancel)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_READ,OnCommand_Button_TaskRead)
END_MESSAGE_MAP()

//====================================================================================================
//конструктор класса
//====================================================================================================
CDialog_TaskSetState::CDialog_TaskSetState(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
 hBitmap_TaskDone=NULL;
 hBitmap_TaskIsRunning=NULL;
 hBitmap_TaskRead=NULL;
 hBitmap_TaskCancel=NULL;
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CDialog_TaskSetState::~CDialog_TaskSetState()
{
}
//====================================================================================================
//функции класса
//====================================================================================================

//---------------------------------------------------------------------------
//нажали Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnOK(void)
{
}
//----------------------------------------------------------------------------------------------------
//нажали ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCancel(void)
{
}
//----------------------------------------------------------------------------------------------------
//инициализация диалога
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_TaskSetState::OnInitDialog(void)
{
 CRect cRect;
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_DONE))->GetClientRect(cRect);
 hBitmap_TaskDone=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_DONE_FRAME_ONE),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 

 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_CANCEL))->GetClientRect(cRect);
 hBitmap_TaskIsRunning=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_IS_RUNNING_FRAME_ONE),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 

 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_IS_RUNNING))->GetClientRect(cRect);
 hBitmap_TaskRead=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_READED_FRAME_ONE),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 

 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_READ))->GetClientRect(cRect);
 hBitmap_TaskCancel=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_CANCELED_FRAME_ONE),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 

 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_DONE))->SetBitmap(hBitmap_TaskDone);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_CANCEL))->SetBitmap(hBitmap_TaskCancel);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_IS_RUNNING))->SetBitmap(hBitmap_TaskIsRunning);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_READ))->SetBitmap(hBitmap_TaskRead);

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SET_STATE_TASK))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SET_STATE_TASK))->SetWindowText(cTask_Local.GetTask());

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SET_STATE_ANSWER))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SET_STATE_ANSWER))->SetWindowText(cTask_Local.GetAnswer());

 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//запуск диалога
//----------------------------------------------------------------------------------------------------
bool CDialog_TaskSetState::Activate(CTask &cTask)
{
 cTask_Local=cTask;
 long ret=DoModal();
 if (ret==0)
 {
  cTask=cTask_Local;
  return(true);
 }
 return(false);
}

//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//уничтожение окна
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnDestroy(void)
{
 if (hBitmap_TaskDone!=NULL) DeleteObject(hBitmap_TaskDone);
 if (hBitmap_TaskIsRunning!=NULL) DeleteObject(hBitmap_TaskIsRunning);
 if (hBitmap_TaskRead!=NULL) DeleteObject(hBitmap_TaskRead);
 if (hBitmap_TaskCancel!=NULL) DeleteObject(hBitmap_TaskCancel);
 CDialog::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//отменить настройки
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_Cancel(void)
{
 EndDialog(-1);
}
//----------------------------------------------------------------------------------------------------
//задание выполнено
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskDone(void)
{
 cTask_Local.SetStateDone();
 ReadAnswer();
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задание отклонено
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskCancel(void)
{
 ReadAnswer();
 if (cTask_Local.GetAnswer().GetLength()==0)
 {
  MessageBox("Требуется указать в комментарии причину отклонения задания!","Ошибка",MB_OK);
  return;
 }
 cTask_Local.SetStateCancelled(); 
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задание прочитано
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskRead(void)
{
 cTask_Local.SetStateReaded();
 ReadAnswer();
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задание выполняется
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskIsRunning(void)
{
 cTask_Local.SetStateIsRunning();
 ReadAnswer();
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//считать ответ
//----------------------------------------------------------------------------------------------------
void CDialog_TaskSetState::ReadAnswer(void)
{
 char answer[255];
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SET_STATE_ANSWER))->GetWindowText(answer,255);
 if (cTask_Local.GetAnswer().Compare(answer)!=0) cTask_Local.SetAnswerNotRead(true);
 cTask_Local.SetAnswer(answer);
}