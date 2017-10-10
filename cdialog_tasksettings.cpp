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
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_SET_TASK_REFERENCE,OnCommand_Button_SetTaskReference)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_RESET_TASK_REFERENCE,OnCommand_Button_ResetTaskReference)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_TASK_REFERENCE,OnCommand_Button_OpenTaskReference)
 ON_COMMAND(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_ANSWER_REFERENCE,OnCommand_Button_OpenAnswerReference)
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
//инициализация диалога
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
 //заполняем список данными пользователей
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
  ((CComboBox *)GetDlgItem(IDC_COMBO_DIALOG_TASK_SETTINGS_PROJECT))->AddString("Без проекта");
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
 if (cTask_Local.IsPlannedPosition()==true) ((CButton *)GetDlgItem(IDC_DIALOG_TASK_SETTINGS_PLANNED_POSITION))->SetCheck(1);
                                       else ((CButton *)GetDlgItem(IDC_DIALOG_TASK_SETTINGS_PLANNED_POSITION))->SetCheck(0);

 if (cTask_Local.IsCommon()==true) ((CButton *)GetDlgItem(IDC_DIALOG_TASK_SETTINGS_COMMON))->SetCheck(1);
                              else ((CButton *)GetDlgItem(IDC_DIALOG_TASK_SETTINGS_COMMON))->SetCheck(0);

 if (cTask_Local.IsAnswerReferenceExist()==true) ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_ANSWER_REFERENCE))->EnableWindow(TRUE);
                                            else ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_ANSWER_REFERENCE))->EnableWindow(FALSE);

 if (cTask_Local.IsTaskReferenceExist()==true)
 {
  ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_RESET_TASK_REFERENCE))->EnableWindow(TRUE);
  ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_TASK_REFERENCE))->EnableWindow(TRUE);
 }
 else 
 {
  ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_RESET_TASK_REFERENCE))->EnableWindow(FALSE);
  ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_TASK_REFERENCE))->EnableWindow(FALSE);
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
  MessageBox("Неверная дата!","Ошибка",MB_OK);
  return;
 }
 size_t size;
 cTask_Local.SetDate(CDate(cTime.GetYear(),cTime.GetMonth(),cTime.GetDay()));
 cTask_Local.SetTask(task);
 if (NewTask==true) cTask_Local.SetIndex(0);//номер вернёт сервер
 cTask_Local.SetStateNoRead();
 cTask_Local.SetAnswerNotRead(false);
 //считываем пользователя, которому предназначена задача
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

 if (((CButton *)GetDlgItem(IDC_DIALOG_TASK_SETTINGS_PLANNED_POSITION))->GetCheck()) cTask_Local.SetPlannedPosition(true);
                                                                                else cTask_Local.SetPlannedPosition(false);

 if (((CButton *)GetDlgItem(IDC_DIALOG_TASK_SETTINGS_COMMON))->GetCheck()) cTask_Local.SetCommon(true);
                                                                      else cTask_Local.SetCommon(false);
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//отменить настройки
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_Cancel(void)
{ 
 cTask_Local.SetAnswerNotRead(false);
 if (NewTask==true)
 {
  EndDialog(-1);
  return;
 }
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//подтверждение, что задание выполнено
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_TaskFinished(void)
{
 cTask_Local.SetAnswerNotRead(false);
 cTask_Local.SetStateFinished();
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//задать ссылку в задании
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_SetTaskReference(void)
{
 char Path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,Path);
 CFileDialog cFileDialog(TRUE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.*|*.*||",this);
 cFileDialog.m_ofn.lpstrInitialDir=Path;
 char Title[256];
 strcpy(Title,"Выберите файл");
 cFileDialog.m_ofn.lpstrTitle=Title;
 if (cFileDialog.DoModal()!=IDOK) return;
 char FilePath[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,FilePath); 
 SetCurrentDirectory(Path);
 //char name[MAX_PATH];
 //DWORD size=MAX_PATH;
 //GetComputerNameA(name,&size);
 CString cString_FilePath=FilePath;
 cString_FilePath+="\\"+cFileDialog.GetFileName();
 const char *str_ptr=cString_FilePath;
 cTask_Local.SetTaskReference(str_ptr);
 cTask_Local.SetTaskReferenceExist(true);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_RESET_TASK_REFERENCE))->EnableWindow(TRUE);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_TASK_REFERENCE))->EnableWindow(TRUE);
}
//----------------------------------------------------------------------------------------------------
//удалить ссылку в задании
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_ResetTaskReference(void)
{
 cTask_Local.SetTaskReferenceExist(false);
 cTask_Local.SetTaskReference("");
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_RESET_TASK_REFERENCE))->EnableWindow(FALSE);
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_TASK_SETTINGS_OPEN_TASK_REFERENCE))->EnableWindow(FALSE);
}
//----------------------------------------------------------------------------------------------------
//открыть ссылку в задании
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_OpenTaskReference(void)
{
 //открываем документ
 CSafeString str="/select, ";
 str+=cTask_Local.GetTaskReference();
 ShellExecute(NULL,"OPEN","EXPLORER",str,NULL,SW_NORMAL);
}
//----------------------------------------------------------------------------------------------------
//открыть ссылку из ответа
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnCommand_Button_OpenAnswerReference(void)
{
 //открываем документ
 CSafeString str="/select, ";
 str+=cTask_Local.GetAnswerReference();
 ShellExecute(NULL,"OPEN","EXPLORER",str,NULL,SW_NORMAL);
}

//----------------------------------------------------------------------------------------------------
//изменился пользователь
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_TaskSettings::OnSelChange_ComboBox_User(void)
{
 //считываем пользователя, которому предназначена задача
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
