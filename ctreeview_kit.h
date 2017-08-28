#ifndef CTREEVIEW_MYTASKS_H
#define CTREEVIEW_MYTASKS_H

//====================================================================================================
//описание
//====================================================================================================

//Класс отображаемого дерева комплектов

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include <list>
#include "stdafx.h"
#include "cdocument_main.h"
#include "cdialog_tasksettings.h"
#include "cdialog_projectsettings.h"
#include "cdialog_usersettings.h"
#include "cdialog_clientsettings.h"

using namespace std;

//====================================================================================================
//макроопределения
//====================================================================================================
//масштабный коэффициент
#define KIT_WIDTH_SCALE (3.0f/10.0f)

//====================================================================================================
//структуры
//====================================================================================================

//представление сотрудников в дереве представлений
struct SColleagueInTreeView
{
 HTREEITEM hTREEITEM_Parent;//родитель
 HTREEITEM hTREEITEM_Colleague;//сам сотрудник
 CSafeString ColleagueGUID;//идентификатор
};

//представление проектов в дереве представлений
struct CProjectInTreeView
{
 HTREEITEM hTREEITEM_Parent;//родитель
 HTREEITEM hTREEITEM_Project;//сам проект
 CSafeString ProjectGUID;//идентификатор
};

//====================================================================================================
//класс представления
//====================================================================================================

class CTreeView_Kit:public CTreeView
{
 protected: 
  //-Переменные класса-------------------------------------------------------
  CMenu cMenu_List_User;//выпадающее меню в списке пользователей
  CMenu cMenu_List_Project;//выпадающее меню в списке проектов
  CImageList cImageList;//список изображений

  HTREEITEM hTREEITEM_Colleague;//ветка "сотрудники"
  HTREEITEM hTREEITEM_Projects;//ветка "проекты"

  list<SColleagueInTreeView> list_SColleagueInTreeView;//список сотрудников в дереве представлений
  list<CProjectInTreeView> list_CProjectInTreeView;//список проектов в дереве представлений

  CBitmap cBitmap_MenuList_AddTask;//создать задание
  CBitmap cBitmap_MenuList_UserInfo;//посмотреть информацию о пользователе

  CBitmap cBitmap_MenuList_AddProject;//создать проект
  CBitmap cBitmap_MenuList_DeleteProject;//удалить проект
  CBitmap cBitmap_MenuList_EditProject;//изменить проект

  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CTreeView_Kit();
  //-Деструктор класса-------------------------------------------------------
  ~CTreeView_Kit();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);//предсоздание окна
  afx_msg void OnInitialUpdate(void);//создание окна
  afx_msg void OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint);//обновление вида
  //-Функции обработки сообщений класса--------------------------------------
  afx_msg void OnDestroy(void);//уничтожение окна
  afx_msg void OnSize(UINT nType,int cx,int cy);//изменение размеров окна
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//нажатие правой кнопкой мышки
  afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);//двойное нажатие левой кнопкой мышки
  afx_msg void OnSelchanged(NMHDR* pNMHDR,LRESULT* pResult);//выбран элемент дерева
  afx_msg void OnCommand_Menu_List_AddTask(void);//добавить задание
  afx_msg void OnCommand_Menu_List_UserInfo(void);//посмотреть данные пользователя
  afx_msg void OnCommand_Menu_List_AddProject(void);//добавить проект
  afx_msg void OnCommand_Menu_List_EditProject(void);//изменить проект
  afx_msg void OnCommand_Menu_List_DeleteProject(void);//удалить проект
  DECLARE_MESSAGE_MAP()
 public:
  //-Функции класса----------------------------------------------------------
  void UpdateTree(void);//обновить дерево
 protected:
  //-Функции класса----------------------------------------------------------
  CDocument_Main* GetDocument(void);//получить документ
  HTREEITEM InsertItem(HTREEITEM hParent,const CSafeString& text,long image,long selected_image,bool sort);//добавить элемент в дерево  

  bool FindColleagueByGUID(const CSafeString &guid,SColleagueInTreeView &sColleagueInTreeView);//найти сотрудника по GUID
  bool FindProjectByGUID(const CSafeString &guid,CProjectInTreeView &cProjectInTreeView);//найти проект по GUID
  //функции констант
  static const long& GetTreeImageSize(void) {static const long img=16; return(img);}//получить размер изображений
  static const long& GetRootColleagueImageIndex(void) {static const long img=0; return(img);}//получить индекс корневого изображения сотрудника
  static const long& GetSelectedRootColleagueImageIndex(void) {static const long img=0; return(img);}//получить индекс выбранного корневого изображения сотрудника
  static const long& GetColleagueImageIndex(void) {static const long img=2; return(img);}//получить индекс изображения сотрудника

  static const long& GetSelectedColleagueLeaderImageIndex(void) {static const long img=5; return(img);}//получить индекс выбранного изображения сотрудника, который является начальником
  static const long& GetColleagueLeaderImageIndex(void) {static const long img=6; return(img);}//получить индекс изображения сотрудника, который является начальником

  static const long& GetSelectedColleagueImageIndex(void) {static const long img=1; return(img);}//получить индекс выбранного изображения сотрудника

  static const long& GetRootProjectImageIndex(void) {static const long img=3; return(img);}//получить индекс корневого изображения проектов
  static const long& GetSelectedRootProjectImageIndex(void) {static const long img=3; return(img);}//получить индекс выбранного корневого изображения проектов

  static const long& GetProjectImageIndex(void) {static const long img=4; return(img);}//получить индекс изображения проектов
  static const long& GetSelectedProjectImageIndex(void) {static const long img=4; return(img);}//получить индекс выбранного изображения проектов
  //-Прочее------------------------------------------------------------------
  DECLARE_DYNCREATE(CTreeView_Kit)
  
};
#endif