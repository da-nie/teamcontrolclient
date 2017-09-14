#include "cdialog_clientsettings.h"

//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

BEGIN_MESSAGE_MAP(CDialog_ClientSettings,CDialog)
 ON_WM_DESTROY()
 ON_COMMAND(IDC_BUTTON_DIALOG_CLIENT_SETTINGS_OK,OnCommand_Button_Ok)
 ON_COMMAND(IDC_BUTTON_DIALOG_CLIENT_SETTINGS_CANCEL,OnCommand_Button_Cancel)
END_MESSAGE_MAP()

//====================================================================================================
//конструктор класса
//====================================================================================================
CDialog_ClientSettings::CDialog_ClientSettings(LPCTSTR lpszTemplateName,CWnd* pParentWnd):CDialog(lpszTemplateName,pParentWnd)
{
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CDialog_ClientSettings::~CDialog_ClientSettings()
{
}
//====================================================================================================
//функции класса
//====================================================================================================

//---------------------------------------------------------------------------
//нажали Enter
//---------------------------------------------------------------------------
afx_msg void CDialog_ClientSettings::OnOK(void)
{
}
//----------------------------------------------------------------------------------------------------
//нажали ESC
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_ClientSettings::OnCancel(void)
{
}
//----------------------------------------------------------------------------------------------------
//инициализация диалога
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CDialog_ClientSettings::OnInitDialog(void)
{
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_SERVER_PORT))->SetLimitText(5);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_LOGIN))->SetLimitText(100);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_PASSWORD))->SetLimitText(100);

 char port_name[255];
 sprintf(port_name,"%i",sClientSettings_Local.ServerPort);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_SERVER_PORT))->SetWindowText(port_name);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_LOGIN))->SetWindowText(sClientSettings_Local.Login);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_PASSWORD))->SetWindowText(sClientSettings_Local.Password);

 ((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_DIALOG_CLIENT_SETTINGS_SERVER_IP))->SetAddress(sClientSettings_Local.ServerIP[0],sClientSettings_Local.ServerIP[1],sClientSettings_Local.ServerIP[2],sClientSettings_Local.ServerIP[3]);

  //определим, записана ли программа в автозагрузку
  bool AutoLoad=false;
  char KeyName[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
  HKEY hKey;
  if (RegOpenKey(HKEY_LOCAL_MACHINE,KeyName,&hKey)==ERROR_SUCCESS)
  {
   unsigned char str_buffer[MAX_PATH];
   DWORD dwType=REG_SZ;
   DWORD dwLength=MAX_PATH; 
   if (RegQueryValueEx(hKey,"Team Control Client",NULL,&dwType,str_buffer,&dwLength)==ERROR_SUCCESS) AutoLoad=true;
   RegCloseKey(hKey);
  }
  if (AutoLoad==true) ((CButton *)GetDlgItem(IDC_CHECK_DIALOG_CLIENT_SETTINGS_RUN_ON_WINDOWS))->SetCheck(1);
                else ((CButton *)GetDlgItem(IDC_CHECK_DIALOG_CLIENT_SETTINGS_RUN_ON_WINDOWS))->SetCheck(0);
 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//запуск диалога
//----------------------------------------------------------------------------------------------------
bool CDialog_ClientSettings::Activate(SClientSettings &sClientSettings)
{
 sClientSettings_Local=sClientSettings;
 long ret=DoModal();
 if (ret==0)
 {
  sClientSettings=sClientSettings_Local;
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
afx_msg void CDialog_ClientSettings::OnDestroy(void)
{
 CDialog::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//применить настройки
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_ClientSettings::OnCommand_Button_Ok(void)
{ 
 char port[255];
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_SERVER_PORT))->GetWindowText(port,255);
 sClientSettings_Local.ServerPort=atoi(port);

 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_LOGIN))->GetWindowText(sClientSettings_Local.Login,255);
 ((CEdit *)GetDlgItem(IDC_EDIT_DIALOG_CLIENT_SETTINGS_PASSWORD))->GetWindowText(sClientSettings_Local.Password,255);
 ((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_DIALOG_CLIENT_SETTINGS_SERVER_IP))->GetAddress(sClientSettings_Local.ServerIP[0],sClientSettings_Local.ServerIP[1],sClientSettings_Local.ServerIP[2],sClientSettings_Local.ServerIP[3]); 


 if (((CButton *)GetDlgItem(IDC_CHECK_DIALOG_CLIENT_SETTINGS_RUN_ON_WINDOWS))->GetCheck())//нужно установить в автозагрузку
 {
  //записываемся в реестр
  char *Patch=new char[MAX_PATH];
  char KeyName[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
  GetModuleFileName(NULL,Patch,MAX_PATH);
  HKEY hKey;
  DWORD lRetVal;
  if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,KeyName,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&hKey,&lRetVal)!=ERROR_SUCCESS) return;
  RegSetValueEx(hKey,"Team Control Client",0,REG_SZ,(unsigned char*)Patch,strlen(Patch));
  RegCloseKey(hKey);
  delete[](Patch);
 }
 else//нужно убрать из автозагрузки
 {
  //удаляем значение ключа из реестра
  char KeyName[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
  HKEY hKey;
  if (RegOpenKey(HKEY_LOCAL_MACHINE,KeyName,&hKey)!=ERROR_SUCCESS) return;
  RegDeleteValue(hKey,"Team Control Client");
  RegCloseKey(hKey);
 }
 EndDialog(0);
}
//----------------------------------------------------------------------------------------------------
//отменить настройки
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_ClientSettings::OnCommand_Button_Cancel(void)
{
 EndDialog(-1);
}


