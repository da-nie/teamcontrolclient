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
 hBitmap_TaskDone=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_DONE),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
 hBitmap_TaskIsRunning=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_IS_RUNNING),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
 hBitmap_TaskRead=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_READED),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
 hBitmap_TaskCancel=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_CANCELED),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CDialog_TaskSetState::~CDialog_TaskSetState()
{
 DeleteObject(hBitmap_TaskDone);
 DeleteObject(hBitmap_TaskIsRunning);
 DeleteObject(hBitmap_TaskRead);
 DeleteObject(hBitmap_TaskCancel);
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
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_DONE))->SetBitmap(hBitmap_TaskDone);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_CANCEL))->SetBitmap(hBitmap_TaskCancel);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_IS_RUNNING))->SetBitmap(hBitmap_TaskIsRunning);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SET_STATE_TASK_READ))->SetBitmap(hBitmap_TaskRead);
 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//запуск диалога
//----------------------------------------------------------------------------------------------------
bool CDialog_TaskSetState::Activate(STask &sTask)
{
 sTask_Local=sTask;
 long ret=DoModal();
 if (ret==0)
 {
  sTask=sTask_Local;
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
 sTask_Local.State=TASK_STATE_DONE;
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задание отклонено
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskCancel(void)
{
 sTask_Local.State=TASK_STATE_CANCELED;
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задание прочитано
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskRead(void)
{
 sTask_Local.State=TASK_STATE_READED;
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задание выполняется
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSetState::OnCommand_Button_TaskIsRunning(void)
{
 sTask_Local.State=TASK_STATE_IS_RUNNING;
 EndDialog(0);
}

