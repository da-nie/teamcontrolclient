#include "cdialog_tasksettings.h"

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_TaskSettings,CDialog)
 ON_WM_DESTROY()
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_OK,OnCommand_Button_Ok)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED,OnCommand_Button_TaskFinished)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_CANCEL,OnCommand_Button_Cancel)
 ON_CBN_SELCHANGE(IDC_COMBO_DIALOG_TASK_SETTINGS_USER,OnSelChange_ComboBox_User)
END_MESSAGE_MAP()

//====================================================================================================
//����������� ������
//====================================================================================================
CDialog_TaskSettings::CDialog_TaskSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
 hBitmap_TaskFinished=NULL;
}
//====================================================================================================
//���������� ������
//====================================================================================================
CDialog_TaskSettings::~CDialog_TaskSettings()
{ 
}
//====================================================================================================
//������� ������
//====================================================================================================

//---------------------------------------------------------------------------
//������ Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnOK(void)
{
}
//----------------------------------------------------------------------------------------------------
//������ ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCancel(void)
{
}
//----------------------------------------------------------------------------------------------------
//������������� �������
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_TaskSettings::OnInitDialog(void)
{
 vector_SUser_Local.clear();
 vector_SProject_Local.clear();

 CRect cRect;
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED))->GetClientRect(cRect);
 hBitmap_TaskFinished=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_FINISHED_BIG),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 


 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED))->SetBitmap(hBitmap_TaskFinished);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TELEPHONE))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TASK))->SetLimitText(254);
 //�������� ������ ������� ��������
 ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->ResetContent();
 //��������� ������ ������� �������������
 ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->ResetContent();
 ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->SetCurSel(0);
 if (cDocument_Main_Local_Ptr!=NULL)
 {
  size_t n;
  size_t size;
  long selected_index=0;
  CVectorUser cVector_User=cDocument_Main_Local_Ptr->GetCVectorUser();
  vector<SUser> &vector_SUser=cVector_User.GetVectorSUser();
  vector_SUser_Local=vector_SUser;
  size=vector_SUser_Local.size();
  for(n=0;n<size;n++)
  {
   SUser sUser=vector_SUser_Local[n];
   ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->AddString(sUser.Name);
   if (sUser.UserGUID.Compare(sTask_Local.ForUserGUID)==0) selected_index=n;
  }
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->SetCurSel(selected_index);

  CVectorProject cVector_Project=cDocument_Main_Local_Ptr->GetCVectorProject();
  vector<SProject> &vector_SProject=cVector_Project.GetVectorSProject();
  vector_SProject_Local=vector_SProject;
  size=vector_SProject_Local.size();
  selected_index=0;   
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->AddString("��� �������");
  for(n=0;n<size;n++)
  {
   SProject sProject=vector_SProject_Local[n];
   ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->AddString(sProject.ProjectName);
   if (sProject.ProjectGUID.Compare(sTask_Local.ProjectGUID)==0) selected_index=n+1;
  }
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->SetCurSel(selected_index);
 }
 CTime cTime(sTask_Local.Year,sTask_Local.Month,sTask_Local.Day,0,0,0); 
 ((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_TASK_SETTINGS_TERM))->SetTime(&cTime); 
 SYSTEMTIME system_time;
 GetLocalTime(&system_time);
 CTime cTime_Min(system_time.wYear,system_time.wMonth,system_time.wDay,0,0,0);
 CTime cTime_Max(2037,12,31,0,0,0);
 ((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_TASK_SETTINGS_TERM))->SetRange(&cTime_Min,&cTime_Max);

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TASK))->SetWindowText(sTask_Local.Task);

 if (NewTask==true) 
 {
  ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED))->ShowWindow(SW_HIDE);
  ((CStatic *)GetDlgItem(IDC_STATIC_DIALOG_TASK_SETTINGS_TASK_FINISHED))->ShowWindow(SW_HIDE);
 }
 else
 {
  ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED))->ShowWindow(SW_SHOW);
  ((CStatic *)GetDlgItem(IDC_STATIC_DIALOG_TASK_SETTINGS_TASK_FINISHED))->ShowWindow(SW_SHOW);
 }

 OnSelChange_ComboBox_User();

 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//������ �������
//----------------------------------------------------------------------------------------------------
bool CDialog_TaskSettings::Activate(STask &sTask,CDocument_Main *cDocument_Main_Ptr,bool new_task)
{
 sTask_Local=sTask;
 cDocument_Main_Local_Ptr=cDocument_Main_Ptr;
 NewTask=new_task;
 long ret=DoModal();
 if (ret==0)
 {
  sTask=sTask_Local;
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
afx_msg void CDialog_TaskSettings::OnDestroy(void)
{
 if (hBitmap_TaskFinished!=NULL) DeleteObject(hBitmap_TaskFinished);
 CDialog::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//��������� ���������
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_Ok(void)
{ 
 char task[255];
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TASK))->GetWindowText(task,255); 
 CTime cTime; 
 unsigned  long ret=((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_TASK_SETTINGS_TERM))->GetTime(cTime);
 if (ret!=GDT_VALID)
 {
  MessageBox("�������� ����!","������",MB_OK);
  return;
 } 
 size_t size;
 sTask_Local.Year=cTime.GetYear();
 sTask_Local.Month=cTime.GetMonth();
 sTask_Local.Day=cTime.GetDay();
 sTask_Local.Task=task;
 if (NewTask==true) sTask_Local.Index=0;//����� ����� ������
 sTask_Local.State=TASK_STATE_NO_READ;
 //��������� ������������, �������� ������������� ������
 size=vector_SUser_Local.size();
 long user_index=((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->GetCurSel();
 if (user_index<size)
 {
  SUser &sUser=vector_SUser_Local[user_index];
  sTask_Local.ForUserGUID=sUser.UserGUID;
 }
 //��������� ������, �������� ������������� ������
 size=vector_SProject_Local.size();
 long project_index=((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->GetCurSel();
 if (project_index==0)//��� �������
 {
  sTask_Local.ProjectGUID="";
 }
 else
 {
  project_index--;
  if (project_index<size)
  {
   SProject sProject=vector_SProject_Local[project_index];
   sTask_Local.ProjectGUID=sProject.ProjectGUID;
  }
 }
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_Cancel(void)
{
 EndDialog(-1);
}
//----------------------------------------------------------------------------------------------------
//�������������, ��� ������� ���������
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_TaskFinished(void)
{
 sTask_Local.State=TASK_STATE_FINISHED;
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//��������� ������������
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnSelChange_ComboBox_User(void)
{
 //��������� ������������, �������� ������������� ������
 size_t size=vector_SUser_Local.size();
 long user_index=((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->GetCurSel();
 if (user_index<size)
 {
  SUser &sUser=vector_SUser_Local[user_index];
  ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TELEPHONE))->SetWindowText(sUser.Telephone);  
 }
 else 
 {
  ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TELEPHONE))->SetWindowText("");
 }
}
