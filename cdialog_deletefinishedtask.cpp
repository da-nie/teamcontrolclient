#include "cdialog_deletefinishedtask.h"

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_DeleteFinishedTask,CDialog)
 ON_WM_DESTROY()
 ON_COMMAND(IDC_BUTTON_DIALOG_DELETE_FINISHED_TASK_DELETE,OnCommand_Button_Delete)
 ON_COMMAND(IDC_BUTTON_DIALOG_DELETE_FINISHED_TASK_CANCEL,OnCommand_Button_Cancel)
END_MESSAGE_MAP()

//====================================================================================================
//����������� ������
//====================================================================================================
CDialog_DeleteFinishedTask::CDialog_DeleteFinishedTask(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
}
//====================================================================================================
//���������� ������
//====================================================================================================
CDialog_DeleteFinishedTask::~CDialog_DeleteFinishedTask()
{
}
//====================================================================================================
//������� ������
//====================================================================================================

//---------------------------------------------------------------------------
//������ Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_DeleteFinishedTask::OnOK(void)
{
}
//----------------------------------------------------------------------------------------------------
//������ ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_DeleteFinishedTask::OnCancel(void)
{
}
//----------------------------------------------------------------------------------------------------
//������������� �������
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_DeleteFinishedTask::OnInitDialog(void)
{
 SYSTEMTIME system_time;
 GetLocalTime(&system_time);
 CTime cTime(system_time.wYear,system_time.wMonth,system_time.wDay,0,0,0); 
 ((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_DELETE_FINISHED_TASK_DATE))->SetTime(&cTime); 
 CTime cTime_Min(2016,12,31,0,0,0);
 ((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_DELETE_FINISHED_TASK_DATE))->SetRange(&cTime_Min,&cTime);
 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//������ �������
//----------------------------------------------------------------------------------------------------
bool CDialog_DeleteFinishedTask::Activate(long &Year,long &Month,long &Day)
{
 Deleted_Year=Year;
 Deleted_Month=Month;
 Deleted_Day=Day;
 long ret=DoModal();
 if (ret==0)
 {
  Year=Deleted_Year;
  Month=Deleted_Month;
  Day=Deleted_Day;
  return(true);
 }
 return(false);
}

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//����������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_DeleteFinishedTask::OnDestroy(void)
{
 CDialog::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_DeleteFinishedTask::OnCommand_Button_Delete(void)
{ 
 if (MessageBox("������� ����������� �������?","�������������",MB_YESNO|MB_DEFBUTTON2)!=IDYES) return;
 CTime cTime; 
 unsigned  long ret=((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_DELETE_FINISHED_TASK_DATE))->GetTime(cTime);
 if (ret!=GDT_VALID)
 {
  MessageBox("�������� ����!","������",MB_OK);
  return;
 } 
 Deleted_Year=cTime.GetYear();
 Deleted_Month=cTime.GetMonth();
 Deleted_Day=cTime.GetDay();
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//������
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_DeleteFinishedTask::OnCommand_Button_Cancel(void)
{
 EndDialog(-1);
}
