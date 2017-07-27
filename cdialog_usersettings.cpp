#include "cdialog_usersettings.h"

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_UserSettings,CDialog)
 ON_WM_DESTROY()
END_MESSAGE_MAP()

//====================================================================================================
//����������� ������
//====================================================================================================
CDialog_UserSettings::CDialog_UserSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
}
//====================================================================================================
//���������� ������
//====================================================================================================
CDialog_UserSettings::~CDialog_UserSettings()
{
}
//====================================================================================================
//������� ������
//====================================================================================================

//---------------------------------------------------------------------------
//������ Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_UserSettings::OnOK(void)
{
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//������ ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_UserSettings::OnCancel(void)
{
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//������������� �������
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_UserSettings::OnInitDialog(void)
{
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_NAME))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_JOB_TITLE))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_DESCRIPTION))->SetLimitText(254);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_TELEPHONE))->SetLimitText(254);

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_NAME))->SetWindowText(sUser_Local.Name);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_JOB_TITLE))->SetWindowText(sUser_Local.JobTitle);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_DESCRIPTION))->SetWindowText(sUser_Local.Description);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_USER_SETTINGS_TELEPHONE))->SetWindowText(sUser_Local.Telephone);

 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//������ �������
//----------------------------------------------------------------------------------------------------
bool CDialog_UserSettings::Activate(SUser &sUser)
{
 sUser_Local=sUser;
 long ret=DoModal();
 if (ret==0)
 {
  sUser=sUser_Local;
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
afx_msg void CDialog_UserSettings::OnDestroy(void)
{
 CDialog::OnDestroy();
}
