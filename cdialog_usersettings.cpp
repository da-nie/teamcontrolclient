#include "cdialog_usersettings.h"

//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_UserSettings,CDialog)
 ON_WM_DESTROY()
END_MESSAGE_MAP()

//====================================================================================================
//конструктор класса
//====================================================================================================
CDialog_UserSettings::CDialog_UserSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CDialog_UserSettings::~CDialog_UserSettings()
{
}
//====================================================================================================
//функции класса
//====================================================================================================

//---------------------------------------------------------------------------
//нажали Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_UserSettings::OnOK(void)
{
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//нажали ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_UserSettings::OnCancel(void)
{
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//инициализация диалога
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_UserSettings::OnInitDialog(void)
{
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_NAME))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_JOB_TITLE))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_DESCRIPTION))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_TELEPHONE))->SetLimitText(254);

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_NAME))->SetWindowText(cUser_Local.GetName());
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_JOB_TITLE))->SetWindowText(cUser_Local.GetJobTitle());
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_DESCRIPTION))->SetWindowText(cUser_Local.GetDescription());
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_TELEPHONE))->SetWindowText(cUser_Local.GetTelephone());

 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//запуск диалога
//----------------------------------------------------------------------------------------------------
bool CDialog_UserSettings::Activate(CUser &cUser)
{
 cUser_Local=cUser;
 long ret=DoModal();
 if (ret==0)
 {
  cUser=cUser_Local;
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
afx_msg void CDialog_UserSettings::OnDestroy(void)
{
 CDialog::OnDestroy();
}
