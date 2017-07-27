#include "cdialog_about.h"


//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CDialog_About,CDialog)
 ON_WM_DESTROY()
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CDialog_About::CDialog_About(void)
{
}
//-Деструктор класса---------------------------------------------------------
CDialog_About::~CDialog_About()
{
}
//-Замещённые функции предка-------------------------------------------------
afx_msg void CDialog_About::OnOK(void)
{
}
afx_msg void CDialog_About::OnClose(void)
{
 //ShowWindow(SW_HIDE);
}
afx_msg void CDialog_About::OnCancel(void)
{
 //ShowWindow(SW_HIDE);
}
afx_msg BOOL CDialog_About::OnInitDialog(void)
{
 return(CDialog::OnInitDialog());
}
