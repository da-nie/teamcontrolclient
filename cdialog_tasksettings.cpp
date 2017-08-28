#include "cdialog_tasksettings.h"

//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_TaskSettings,CDialog)
 ON_WM_DESTROY()
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_OK,OnCommand_Button_Ok)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED,OnCommand_Button_TaskFinished)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_CANCEL,OnCommand_Button_Cancel)
 ON_CBN_SELCHANGE(IDC_COMBO_DIALOG_TASK_SETTINGS_USER,OnSelChange_ComboBox_User)
END_MESSAGE_MAP()

//====================================================================================================
//конструктор класса
//====================================================================================================
CDialog_TaskSettings::CDialog_TaskSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
 hBitmap_TaskFinished=NULL;
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CDialog_TaskSettings::~CDialog_TaskSettings()
{ 
}
//====================================================================================================
//функции класса
//====================================================================================================

//---------------------------------------------------------------------------
//нажали Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnOK(void)
{
}
//----------------------------------------------------------------------------------------------------
//нажали ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCancel(void)
{
}
//----------------------------------------------------------------------------------------------------
//инициализаци€ диалога
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_TaskSettings::OnInitDialog(void)
{
 vector_CUser_Local.clear();
 vector_CProject_Local.clear();

 CRect cRect;
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED))->GetClientRect(cRect);
 hBitmap_TaskFinished=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_TASK_FINISHED_BIG),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 

 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_TASK_FINISHED))->SetBitmap(hBitmap_TaskFinished);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TELEPHONE))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TASK))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_ANSWER))->SetLimitText(254);
 //заполним список данными проектов
 ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->ResetContent();
 //заполн€ем список данными пользователей
 ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->ResetContent();
 ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->SetCurSel(0);
 if (cDocument_Main_Local_Ptr!=NULL)
 {
  size_t n;
  size_t size;
  long selected_index=0;
  CVectorUser cVector_User=cDocument_Main_Local_Ptr->GetCVectorUser();
  vector<CUser> &vector_CUser=cVector_User.GetVectorCUser();
  vector_CUser_Local=vector_CUser;
  size=vector_CUser_Local.size();
  for(n=0;n<size;n++)
  {
   CUser cUser=vector_CUser_Local[n];
   ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->AddString(cUser.GetName());   
   if (cUser.IsUserGUID(cTask_Local.GetForUserGUID())==true) selected_index=n;
  }
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->SetCurSel(selected_index);

  CVectorProject cVector_Project=cDocument_Main_Local_Ptr->GetCVectorProject();
  vector<CProject> &vector_CProject=cVector_Project.GetVectorCProject();
  vector_CProject_Local=vector_CProject;
  size=vector_CProject_Local.size();
  selected_index=0;   
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->AddString("Ѕез проекта");
  for(n=0;n<size;n++)
  {
   CProject cProject=vector_CProject_Local[n];
   ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->AddString(cProject.GetProjectName());
   if (cProject.IsProjectGUID(cTask_Local.GetProjectGUID())==true) selected_index=n+1;
  }
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->SetCurSel(selected_index);
 }
 CTime cTime(cTask_Local.GetDate().GetYear(),cTask_Local.GetDate().GetMonth(),cTask_Local.GetDate().GetDay(),0,0,0); 
 ((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_TASK_SETTINGS_TERM))->SetTime(&cTime); 
 SYSTEMTIME system_time;
 GetLocalTime(&system_time);
 CTime cTime_Min(system_time.wYear,system_time.wMonth,system_time.wDay,0,0,0);
 CTime cTime_Max(2037,12,31,0,0,0);
 ((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_TASK_SETTINGS_TERM))->SetRange(&cTime_Min,&cTime_Max);

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TASK))->SetWindowText(cTask_Local.GetTask());
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_ANSWER))->SetWindowText(cTask_Local.GetAnswer());

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
//запуск диалога
//----------------------------------------------------------------------------------------------------
bool CDialog_TaskSettings::Activate(CTask &cTask,CDocument_Main *cDocument_Main_Ptr,bool new_task)
{
 cTask_Local=cTask;
 cDocument_Main_Local_Ptr=cDocument_Main_Ptr;
 NewTask=new_task;
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
afx_msg void CDialog_TaskSettings::OnDestroy(void)
{
 if (hBitmap_TaskFinished!=NULL) DeleteObject(hBitmap_TaskFinished);
 CDialog::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//применить настройки
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_Ok(void)
{ 
 char task[255];
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TASK))->GetWindowText(task,255); 
 CTime cTime; 
 unsigned  long ret=((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DIALOG_TASK_SETTINGS_TERM))->GetTime(cTime);
 if (ret!=GDT_VALID)
 {
  MessageBox("Ќеверна€ дата!","ќшибка",MB_OK);
  return;
 } 
 size_t size;
 cTask_Local.SetDate(CDate(cTime.GetYear(),cTime.GetMonth(),cTime.GetDay()));
 cTask_Local.SetTask(task);
 if (NewTask==true) cTask_Local.SetIndex(0);//номер вернЄт сервер
 cTask_Local.SetState(TASK_STATE_NO_READ);
 //считываем пользовател€, которому предназначена задача
 size=vector_CUser_Local.size();
 long user_index=((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->GetCurSel();
 if (user_index<size)
 {
  CUser &cUser=vector_CUser_Local[user_index];
  cTask_Local.SetForUserGUID(cUser.GetUserGUID());
 }
 //считываем проект, которому предназначена задача
 size=vector_CProject_Local.size();
 long project_index=((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->GetCurSel();
 if (project_index==0)//без проекта
 {
  cTask_Local.SetProjectGUID("");
 }
 else
 {
  project_index--;
  if (project_index<size)
  {
   CProject cProject=vector_CProject_Local[project_index];
   cTask_Local.SetProjectGUID(cProject.GetProjectGUID());
  }
 }
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//отменить настройки
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_Cancel(void)
{
 EndDialog(-1);
}
//----------------------------------------------------------------------------------------------------
//подтверждение, что задание выполнено
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_TaskFinished(void)
{
 cTask_Local.SetState(TASK_STATE_FINISHED);
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//изменилс€ пользователь
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnSelChange_ComboBox_User(void)
{
 //считываем пользовател€, которому предназначена задача
 size_t size=vector_CUser_Local.size();
 long user_index=((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_USER))->GetCurSel();
 if (user_index<size)
 {
  CUser &cUser=vector_CUser_Local[user_index];
  ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TELEPHONE))->SetWindowText(cUser.GetTelephone());
 }
 else 
 {
  ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_TASK_SETTINGS_TELEPHONE))->SetWindowText("");
 }
}
