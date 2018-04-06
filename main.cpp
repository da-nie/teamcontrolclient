#include "stdafx.h"
//------------------------------------------------------------------------------
#include "cdocument_main.h"
#include "cview_mytasks.h"
#include "cview_outtasks.h"
#include "ctreeview_kit.h"
#include "cframewnd_main.h"

//------------------------------------------------------------------------------
class CWinApp_Main:public CWinApp
{
 protected:
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CWinApp_Main(void);
  //-Деструктор класса-------------------------------------------------------
  ~CWinApp_Main();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  virtual BOOL InitInstance(void);
  int ExitInstance(void);
  //-Прочее------------------------------------------------------------------
};
//-Конструктор класса--------------------------------------------------------
CWinApp_Main::CWinApp_Main(void)
{
}
//-Деструктор класса---------------------------------------------------------
CWinApp_Main::~CWinApp_Main()
{
}
//-Функции класса------------------------------------------------------------
BOOL CWinApp_Main::InitInstance(void)
{ 
 CWinApp::InitInstance();

 char FileName[MAX_PATH];
 GetModuleFileName(NULL,FileName,MAX_PATH);
 //отматываем до черты
 long size=strlen(FileName);
 if (size>0) size--;
 while(size>0)
 {
  unsigned char s=FileName[size];
  if (s==0 || s=='\\')
  {
   FileName[size+1]=0;
   break;
  }
  size--;
 }
 SetCurrentDirectory(FileName);
 //удаляем загрузчик
 DeleteFile("TeamControlLoader.exe");
 //инициализируем сокеты
 WSADATA wsadata;
 if (WSAStartup(0x0202,&wsadata)!=0) 
 {
  MessageBox(NULL,"Ошибка инициализации сокетов.","Ошибка",MB_OK);
  WSACleanup();
  return(FALSE);
 }
 if (wsadata.wVersion!=0x0202)
 {
  MessageBox(NULL,"Неверная версия библиотеки сокетов.","Ошибка",MB_OK);
  WSACleanup();
  return(FALSE);
 } 
 CSingleDocTemplate* pDocTemplate;//новый шаблон 
 pDocTemplate=new CSingleDocTemplate(IDR_MENU_MAIN,RUNTIME_CLASS(CDocument_Main),RUNTIME_CLASS(CFrameWnd_Main),RUNTIME_CLASS(CTreeView_Kit));
 if (pDocTemplate==NULL)
 {
  MessageBox(NULL,"Не могу создать шаблон!","Ошибка",MB_OK);
  return(false);
 }
 AddDocTemplate(pDocTemplate);//добавить шаблон 
 CCommandLineInfo cmdInfo;//класс команд 
 ParseCommandLine(cmdInfo);//разбор командной строки 
 if (!ProcessShellCommand(cmdInfo)) return(FALSE);//запуск команд на выполнение 
 m_pMainWnd->SetWindowText("Клиент Team Control");
 //m_pMainWnd->SetWindowPos(NULL,0,0,640,480,0);
 m_pMainWnd->ShowWindow(SW_SHOW);//показать окно 
 m_pMainWnd->UpdateWindow();//запустить цикл обработки сообщений 
 return(TRUE);
}
int CWinApp_Main::ExitInstance(void)
{
 //деинициализируем сокеты
 WSACleanup();
 return(CWinApp::ExitInstance());
}

CWinApp_Main cWinApp_Main;


