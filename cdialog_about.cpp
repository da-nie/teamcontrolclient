#include "cdialog_about.h"


//-Функции обработки сообщений класса----------------------------------------
BEGIN_MESSAGE_MAP(CDialog_About,CDialog)
 ON_WM_DESTROY()
END_MESSAGE_MAP()
//-Конструктор класса--------------------------------------------------------
CDialog_About::CDialog_About(void)
{
 hBitmap_About=NULL;
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
 
}
afx_msg void CDialog_About::OnCancel(void)
{
 
}
//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================
afx_msg BOOL CDialog_About::OnInitDialog(void)
{
 CRect cRect;
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_ABOUT_IMAGE))->GetClientRect(cRect);
 hBitmap_About=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ABOUT),IMAGE_BITMAP,cRect.right-cRect.left,cRect.bottom-cRect.top,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
 ((CButton *)GetDlgItem(IDC_BUTTON_DIALOG_ABOUT_IMAGE))->SetBitmap(hBitmap_About);
 return(CDialog::OnInitDialog());
}
//----------------------------------------------------------------------------------------------------
//уничтожение окна
//----------------------------------------------------------------------------------------------------
afx_msg void CDialog_About::OnDestroy(void)
{
 if (hBitmap_About!=NULL) DeleteObject(hBitmap_About);
 hBitmap_About=NULL;
 CDialog::OnDestroy();
}