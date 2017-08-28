#ifndef CTREEVIEW_MYTASKS_H
#define CTREEVIEW_MYTASKS_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������������� ������ ����������

//====================================================================================================
//������������ ����������
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
//����������������
//====================================================================================================
//���������� �����������
#define KIT_WIDTH_SCALE (3.0f/10.0f)

//====================================================================================================
//���������
//====================================================================================================

//������������� ����������� � ������ �������������
struct SColleagueInTreeView
{
 HTREEITEM hTREEITEM_Parent;//��������
 HTREEITEM hTREEITEM_Colleague;//��� ���������
 CSafeString ColleagueGUID;//�������������
};

//������������� �������� � ������ �������������
struct CProjectInTreeView
{
 HTREEITEM hTREEITEM_Parent;//��������
 HTREEITEM hTREEITEM_Project;//��� ������
 CSafeString ProjectGUID;//�������������
};

//====================================================================================================
//����� �������������
//====================================================================================================

class CTreeView_Kit:public CTreeView
{
 protected: 
  //-���������� ������-------------------------------------------------------
  CMenu cMenu_List_User;//���������� ���� � ������ �������������
  CMenu cMenu_List_Project;//���������� ���� � ������ ��������
  CImageList cImageList;//������ �����������

  HTREEITEM hTREEITEM_Colleague;//����� "����������"
  HTREEITEM hTREEITEM_Projects;//����� "�������"

  list<SColleagueInTreeView> list_SColleagueInTreeView;//������ ����������� � ������ �������������
  list<CProjectInTreeView> list_CProjectInTreeView;//������ �������� � ������ �������������

  CBitmap cBitmap_MenuList_AddTask;//������� �������
  CBitmap cBitmap_MenuList_UserInfo;//���������� ���������� � ������������

  CBitmap cBitmap_MenuList_AddProject;//������� ������
  CBitmap cBitmap_MenuList_DeleteProject;//������� ������
  CBitmap cBitmap_MenuList_EditProject;//�������� ������

  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CTreeView_Kit();
  //-���������� ������-------------------------------------------------------
  ~CTreeView_Kit();
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);//������������ ����
  afx_msg void OnInitialUpdate(void);//�������� ����
  afx_msg void OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint);//���������� ����
  //-������� ��������� ��������� ������--------------------------------------
  afx_msg void OnDestroy(void);//����������� ����
  afx_msg void OnSize(UINT nType,int cx,int cy);//��������� �������� ����
  afx_msg void OnRButtonDown(UINT nFlags,CPoint point);//������� ������ ������� �����
  afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);//������� ������� ����� ������� �����
  afx_msg void OnSelchanged(NMHDR* pNMHDR,LRESULT* pResult);//������ ������� ������
  afx_msg void OnCommand_Menu_List_AddTask(void);//�������� �������
  afx_msg void OnCommand_Menu_List_UserInfo(void);//���������� ������ ������������
  afx_msg void OnCommand_Menu_List_AddProject(void);//�������� ������
  afx_msg void OnCommand_Menu_List_EditProject(void);//�������� ������
  afx_msg void OnCommand_Menu_List_DeleteProject(void);//������� ������
  DECLARE_MESSAGE_MAP()
 public:
  //-������� ������----------------------------------------------------------
  void UpdateTree(void);//�������� ������
 protected:
  //-������� ������----------------------------------------------------------
  CDocument_Main* GetDocument(void);//�������� ��������
  HTREEITEM InsertItem(HTREEITEM hParent,const CSafeString& text,long image,long selected_image,bool sort);//�������� ������� � ������  

  bool FindColleagueByGUID(const CSafeString &guid,SColleagueInTreeView &sColleagueInTreeView);//����� ���������� �� GUID
  bool FindProjectByGUID(const CSafeString &guid,CProjectInTreeView &cProjectInTreeView);//����� ������ �� GUID
  //������� ��������
  static const long& GetTreeImageSize(void) {static const long img=16; return(img);}//�������� ������ �����������
  static const long& GetRootColleagueImageIndex(void) {static const long img=0; return(img);}//�������� ������ ��������� ����������� ����������
  static const long& GetSelectedRootColleagueImageIndex(void) {static const long img=0; return(img);}//�������� ������ ���������� ��������� ����������� ����������
  static const long& GetColleagueImageIndex(void) {static const long img=2; return(img);}//�������� ������ ����������� ����������

  static const long& GetSelectedColleagueLeaderImageIndex(void) {static const long img=5; return(img);}//�������� ������ ���������� ����������� ����������, ������� �������� �����������
  static const long& GetColleagueLeaderImageIndex(void) {static const long img=6; return(img);}//�������� ������ ����������� ����������, ������� �������� �����������

  static const long& GetSelectedColleagueImageIndex(void) {static const long img=1; return(img);}//�������� ������ ���������� ����������� ����������

  static const long& GetRootProjectImageIndex(void) {static const long img=3; return(img);}//�������� ������ ��������� ����������� ��������
  static const long& GetSelectedRootProjectImageIndex(void) {static const long img=3; return(img);}//�������� ������ ���������� ��������� ����������� ��������

  static const long& GetProjectImageIndex(void) {static const long img=4; return(img);}//�������� ������ ����������� ��������
  static const long& GetSelectedProjectImageIndex(void) {static const long img=4; return(img);}//�������� ������ ���������� ����������� ��������
  //-������------------------------------------------------------------------
  DECLARE_DYNCREATE(CTreeView_Kit)
  
};
#endif