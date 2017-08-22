#include "ctreeview_kit.h"

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

BEGIN_MESSAGE_MAP(CTreeView_Kit,CTreeView)
 ON_WM_SIZE()
 ON_WM_PAINT()//��� ON_WM_PAINT ������ ������ �� ��������������!!! ���� ������ ��.
 ON_WM_RBUTTONDOWN() 
 ON_WM_LBUTTONDBLCLK()
 ON_WM_TIMER()
 ON_WM_DESTROY()
 ON_NOTIFY_REFLECT(TVN_SELCHANGED,OnSelchanged)
 ON_COMMAND(IDC_MENU_LIST_TREE_VIEW_ADD_TASK,OnCommand_Menu_List_AddTask) 
 ON_COMMAND(IDC_MENU_LIST_TREE_VIEW_USER_INFO,OnCommand_Menu_List_UserInfo)
 ON_COMMAND(IDC_MENU_LIST_TREE_VIEW_ADD_PROJECT,OnCommand_Menu_List_AddProject) 
 ON_COMMAND(IDC_MENU_LIST_TREE_VIEW_DELETE_PROJECT,OnCommand_Menu_List_DeleteProject) 
 ON_COMMAND(IDC_MENU_LIST_TREE_VIEW_EDIT_PROJECT,OnCommand_Menu_List_EditProject) 
END_MESSAGE_MAP()

//====================================================================================================
//����������� ������
//====================================================================================================
CTreeView_Kit::CTreeView_Kit() 
{ 
 hTREEITEM_Colleague=NULL;
 hTREEITEM_Projects=NULL;
}
//====================================================================================================
//���������� ������
//====================================================================================================
CTreeView_Kit::~CTreeView_Kit() 
{ 
	
}
//====================================================================================================
//������� ������
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//������������ ����
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CTreeView_Kit::PreCreateWindow(CREATESTRUCT& cs)
{
 return(CTreeView::PreCreateWindow(cs));
}
//----------------------------------------------------------------------------------------------------
//�������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnInitialUpdate(void)
{
 CTreeView::OnInitialUpdate();	
 cBitmap_MenuList_AddTask.LoadBitmap(IDB_BITMAP_MENU_ADD_TASK);
 cBitmap_MenuList_UserInfo.LoadBitmap(IDB_BITMAP_MENU_USER_INFO);

 cBitmap_MenuList_AddProject.LoadBitmap(IDB_BITMAP_MENU_ADD_TASK);
 cBitmap_MenuList_DeleteProject.LoadBitmap(IDB_BITMAP_MENU_DELETE_TASK);
 cBitmap_MenuList_EditProject.LoadBitmap(IDB_BITMAP_MENU_EDIT_TASK);

 //���������� BITMAP, ����� ������� 24 ���� RGB � ������, ������ 16 ������ ��� ������� �������� CImageList �� �������
 HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_USER),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS); 
 CBitmap cBitmap; 
 cBitmap.Attach(hBitmap);
 cImageList.Create(GetTreeImageSize(),GetTreeImageSize(),ILC_COLOR24,0,0);
 cImageList.Add(&cBitmap,reinterpret_cast<CBitmap*>(NULL));

 //������ ������
 CTreeCtrl &cTreeCtrl=GetTreeCtrl(); 
 cTreeCtrl.ModifyStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|WS_CHILD|WS_BORDER);
 cTreeCtrl.DeleteAllItems();
 cTreeCtrl.SetImageList(&cImageList,TVSIL_NORMAL);
 //������ �����
 
 //������ ������� �����
 hTREEITEM_Colleague=InsertItem(NULL,"�������� ����������� �������",GetRootColleagueImageIndex(),GetSelectedRootColleagueImageIndex(),false);
 hTREEITEM_Projects=InsertItem(NULL,"�������� �� �������� �������",GetRootProjectImageIndex(),GetSelectedRootProjectImageIndex(),false);

 SUser sUser;
 sUser.UserGUID=ALL_USER_GUID;
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 cDocument_Main_Ptr->SetSelectedUser(sUser);

 UpdateTree();

 //�������� ����������� ����
 cMenu_List_User.LoadMenu(IDR_MENU_LIST_TREE_VIEW_USER);
 cMenu_List_Project.LoadMenu(IDR_MENU_LIST_TREE_VIEW_PROJECT);
}
//----------------------------------------------------------------------------------------------------
//���������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnUpdate(CView *pSender,LPARAM lHint,CObject *pHint)
{
 UpdateTree();
 CTreeView::OnUpdate(pSender,lHint,pHint);
}

//====================================================================================================
//������� ��������� ��������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//����������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnDestroy(void)
{
 CTreeView::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//��������� �������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnSize(UINT nType,int cx,int cy)
{ 
 CTreeView::OnSize(nType,cx,cy); 
}
//----------------------------------------------------------------------------------------------------
//������� ������ ������� �����
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnRButtonDown(UINT nFlags,CPoint point)
{
 //������ ���������� ����
 CPoint mpoint;
 GetCursorPos(&mpoint);
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SUser sUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser_Selected)==false) return;//��� ���������� ��������
 //�������, ��� ���� �������
 CSafeString guid;
 CSafeString name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,guid,name,leader);

 CTreeCtrl& cTreeCtrl=GetTreeCtrl();
 HTREEITEM hTREEITEM_item=cTreeCtrl.GetSelectedItem();
 if (sUser_Selected.UserGUID.Compare(ALL_USER_GUID)==0 && hTREEITEM_item==hTREEITEM_Colleague) return;//������� ����� �������������
 if (sUser_Selected.UserGUID.Compare(ALL_USER_GUID)==0 && hTREEITEM_item==hTREEITEM_Projects)//������� ����� ��������
 {  
  if (leader==false) return;//������ ������������ ����� ��������� ���������

  cMenu_List_Project.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_ADD_PROJECT,MF_BYCOMMAND,&cBitmap_MenuList_AddProject,&cBitmap_MenuList_AddProject);
  cMenu_List_Project.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_DELETE_PROJECT,MF_BYCOMMAND,&cBitmap_MenuList_DeleteProject,&cBitmap_MenuList_DeleteProject);
  cMenu_List_Project.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_EDIT_PROJECT,MF_BYCOMMAND,&cBitmap_MenuList_EditProject,&cBitmap_MenuList_EditProject);
  cMenu_List_Project.EnableMenuItem(IDC_MENU_LIST_TREE_VIEW_DELETE_PROJECT,TRUE);
  cMenu_List_Project.EnableMenuItem(IDC_MENU_LIST_TREE_VIEW_EDIT_PROJECT,TRUE);  
  cMenu_List_Project.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,mpoint.x,mpoint.y,this); 	
  return;
 }
 
 SProject sProject;
 if (cDocument_Main_Ptr->FindByProjectGUID(sUser_Selected.UserGUID,sProject)==true)//������ ������
 {
  if (leader==false) return;//������ ������������ ����� ��������� ���������

  cMenu_List_Project.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_ADD_PROJECT,MF_BYCOMMAND,&cBitmap_MenuList_AddProject,&cBitmap_MenuList_AddProject);
  cMenu_List_Project.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_DELETE_PROJECT,MF_BYCOMMAND,&cBitmap_MenuList_DeleteProject,&cBitmap_MenuList_DeleteProject);
  cMenu_List_Project.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_EDIT_PROJECT,MF_BYCOMMAND,&cBitmap_MenuList_EditProject,&cBitmap_MenuList_EditProject);
  cMenu_List_Project.EnableMenuItem(IDC_MENU_LIST_TREE_VIEW_DELETE_PROJECT,FALSE);
  cMenu_List_Project.EnableMenuItem(IDC_MENU_LIST_TREE_VIEW_EDIT_PROJECT,FALSE);  
  cMenu_List_Project.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,mpoint.x,mpoint.y,this); 	
  return;
 }
 SUser sUser;
 if (cDocument_Main_Ptr->FindByUserGUID(sUser_Selected.UserGUID,sUser)==true)//������ ������������
 {
  cMenu_List_User.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_ADD_TASK,MF_BYCOMMAND,&cBitmap_MenuList_AddTask,&cBitmap_MenuList_AddTask);
  cMenu_List_User.SetMenuItemBitmaps(IDC_MENU_LIST_TREE_VIEW_USER_INFO,MF_BYCOMMAND,&cBitmap_MenuList_UserInfo,&cBitmap_MenuList_UserInfo);
  cMenu_List_User.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,mpoint.x,mpoint.y,this); 	
 }
}
//----------------------------------------------------------------------------------------------------
//������� ������� ����� ������� �����
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnLButtonDblClk(UINT nFlags,CPoint point)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SUser sUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser_Selected)==false) return;//��� ���������� ��������
 if (sUser_Selected.UserGUID.Compare(ALL_USER_GUID)==0) return;
 OnCommand_Menu_List_AddTask();
}
//----------------------------------------------------------------------------------------------------
//������ ������� ������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnSelchanged(NMHDR* pNMHDR,LRESULT* pResult) 
{
 //�������, ��� ���� �������
 CTreeCtrl& cTreeCtrl=GetTreeCtrl();
 HTREEITEM hTREEITEM_item=cTreeCtrl.GetSelectedItem();
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 //���������, �� ������ �� �������� ������� "����������" ��� "�������"
 if (hTREEITEM_item==hTREEITEM_Colleague || hTREEITEM_item==hTREEITEM_Projects)
 {
  SUser sUser;
  sUser.UserGUID=ALL_USER_GUID;
  cDocument_Main_Ptr->SetSelectedUser(sUser);
  return;
 }
 //���� ��������� ������� ����� �����������
 list<SColleagueInTreeView>::iterator iterator=list_SColleagueInTreeView.begin();
 list<SColleagueInTreeView>::iterator iterator_end=list_SColleagueInTreeView.end();  
 while(iterator!=iterator_end)
 {
  SColleagueInTreeView &sColleagueInTreeView=*iterator;
  if (sColleagueInTreeView.hTREEITEM_Colleague==hTREEITEM_item)
  {
   SUser sUser;
   bool is_finded=cDocument_Main_Ptr->FindByUserGUIDAndResetChangeData(sColleagueInTreeView.ColleagueGUID,sUser);
   if (is_finded==true) cDocument_Main_Ptr->SetSelectedUser(sUser);//���������, ��� ��� ������ ������ ������������
   return;
  }
  iterator++;
 }

 //���� ��������� ������� ����� ��������
 list<SProjectInTreeView>::iterator iterator_project=list_SProjectInTreeView.begin();
 list<SProjectInTreeView>::iterator iterator_project_end=list_SProjectInTreeView.end();  
 while(iterator_project!=iterator_project_end)
 {
  SProjectInTreeView &sProjectInTreeView=*iterator_project;
  if (sProjectInTreeView.hTREEITEM_Project==hTREEITEM_item)
  {
   SProject sProject;
   bool is_finded=cDocument_Main_Ptr->FindByProjectGUIDAndResetChangeData(sProjectInTreeView.ProjectGUID,sProject);
   if (is_finded==true)
   {      
    //������������� ��������� ������������ � ��������������� ������� (�������������� ������� �� ������������)
    SUser sUser;
    sUser.UserGUID=sProject.ProjectGUID;
    cDocument_Main_Ptr->SetSelectedUser(sUser);
   }
   return;
  }
  iterator_project++;
 }

 cDocument_Main_Ptr->ResetSelectedUser();
}

//----------------------------------------------------------------------------------------------------
//�������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnCommand_Menu_List_AddTask(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SUser sUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser_Selected)==false) return;//��� ���������� ��������
 SUser sUser;
 if (cDocument_Main_Ptr->FindByUserGUID(sUser_Selected.UserGUID,sUser)==false) return;//������ ������������ ��� � ����

 STask sTask;
 SYSTEMTIME system_time;
 GetLocalTime(&system_time);
 sTask.cDate.SetDate(system_time.wYear,system_time.wMonth,system_time.wDay);
 sTask.ForUserGUID=sUser_Selected.UserGUID;
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(sTask,cDocument_Main_Ptr,true)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //������ �������� �������
   if (cDocument_Main_Ptr->AddTask(sTask)==false)
   {
    MessageBox("�� ������� ������� �������!","������",MB_OK);
   }
   else break;
  }
  else break;
 }
}
//----------------------------------------------------------------------------------------------------
//���������� ������ ������������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnCommand_Menu_List_UserInfo(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SUser sUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser_Selected)==false) return;//��� ���������� ��������
 SUser sUser;
 if (cDocument_Main_Ptr->FindByUserGUID(sUser_Selected.UserGUID,sUser)==false) return;//������ ������������ ��� � ����

 CDialog_UserSettings cDialog_UserSettings((LPCSTR)IDD_DIALOG_USER_SETTINGS,this);
 cDialog_UserSettings.Activate(sUser_Selected);	
}

//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnCommand_Menu_List_AddProject(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SProject sProject;
 sProject.ProjectName="";
 sProject.ProjectGUID="";
 sProject.ChangeData=false;
 sProject.ProjectType=PROJECT_TYPE_NONE;
 while(1)
 {  
  CDialog_ProjectSettings cDialog_ProjectSettings((LPCSTR)IDD_DIALOG_PROJECT_SETTINGS,this);
  if (cDialog_ProjectSettings.Activate(sProject)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //������ �������� ������
   if (cDocument_Main_Ptr->AddProject(sProject)==false)
   {
    MessageBox("�� ������� ������� ������!","������",MB_OK);
   }
   else break;
  }
  else break;
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnCommand_Menu_List_EditProject(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SUser sUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser_Selected)==false) return;//��� ���������� ��������
 SProject sProject;
 if (cDocument_Main_Ptr->FindByProjectGUID(sUser_Selected.UserGUID,sProject)==false) return;//������ ������� ��� � ����

 while(1)
 {
  CDialog_ProjectSettings cDialog_ProjectSettings((LPCSTR)IDD_DIALOG_PROJECT_SETTINGS,this);
  if (cDialog_ProjectSettings.Activate(sProject)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //������ �������� ������
   if (cDocument_Main_Ptr->ChangeProject(sProject)==false)
   {
    MessageBox("�� ������� �������� ������!","������",MB_OK);
   }
   else break;
  }
  else break;
 }
}
//----------------------------------------------------------------------------------------------------
//������� ������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnCommand_Menu_List_DeleteProject(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 SUser sUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(sUser_Selected)==false) return;//��� ���������� ��������
 SProject sProject;
 if (cDocument_Main_Ptr->FindByProjectGUID(sUser_Selected.UserGUID,sProject)==false) return;//������ ������� ��� � ����
 if (MessageBox("������� ��������� ������?","�������������",MB_YESNO|MB_DEFBUTTON2)!=IDYES) return;
 cDocument_Main_Ptr->DeleteProject(sProject); 
}

//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
void CTreeView_Kit::UpdateTree(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 CTreeCtrl& cTreeCtrl=GetTreeCtrl();
 if (hTREEITEM_Colleague!=NULL)
 {
  //��������� ������ ����������� � ��������� ��� ������� �����������
  list<SColleagueInTreeView>::iterator iterator=list_SColleagueInTreeView.begin();
  list<SColleagueInTreeView>::iterator iterator_end=list_SColleagueInTreeView.end();  
  //�������� �����������
  while(iterator!=iterator_end)
  {
   SColleagueInTreeView &sColleagueInTreeView=*iterator;
   SUser sUser;  
   bool is_finded=cDocument_Main_Ptr->FindByUserGUIDAndResetChangeData(sColleagueInTreeView.ColleagueGUID,sUser);
   if (is_finded==false || sUser.ChangeData==true)//���������� ��� � ���� ��� ��� ������ ������ ���� ��������
   {
    //������� ����������
	cTreeCtrl.DeleteItem(sColleagueInTreeView.hTREEITEM_Colleague);
    list_SColleagueInTreeView.erase(iterator);
    iterator=list_SColleagueInTreeView.begin();
    iterator_end=list_SColleagueInTreeView.end();
	continue;
   }
   iterator++;
  }
   //���������� �����������
  CVectorUser cVectorUser=cDocument_Main_Ptr->GetCVectorUser();
  vector<SUser> &vector_SUser=cVectorUser.GetVectorSUser();
  size_t size=vector_SUser.size();
  for(size_t n=0;n<size;n++)
  {
   SUser &sUser=vector_SUser[n];
   SColleagueInTreeView sColleagueInTreeView;
   //���� ����������
   bool is_finded=FindColleagueByGUID(sUser.UserGUID,sColleagueInTreeView);
   if (is_finded==false)//��������� � ������
   {
    sColleagueInTreeView.ColleagueGUID=sUser.UserGUID;
	if (sUser.Leader==true) sColleagueInTreeView.hTREEITEM_Colleague=InsertItem(hTREEITEM_Colleague,sUser.Name,GetColleagueLeaderImageIndex(),GetSelectedColleagueLeaderImageIndex(),true);
	                   else sColleagueInTreeView.hTREEITEM_Colleague=InsertItem(hTREEITEM_Colleague,sUser.Name,GetColleagueImageIndex(),GetSelectedColleagueImageIndex(),true);
	sColleagueInTreeView.hTREEITEM_Parent=hTREEITEM_Colleague;
    list_SColleagueInTreeView.push_back(sColleagueInTreeView);
   }
  }
 }
 if (hTREEITEM_Projects!=NULL)
 {
  //��������� ������ �������� � ��������� ��� ������� �������
  list<SProjectInTreeView>::iterator iterator=list_SProjectInTreeView.begin();
  list<SProjectInTreeView>::iterator iterator_end=list_SProjectInTreeView.end();  
  //�������� ��������
  while(iterator!=iterator_end)
  {
   SProjectInTreeView &sProjectInTreeView=*iterator;
   SProject sProject;  
   bool is_finded=cDocument_Main_Ptr->FindByProjectGUIDAndResetChangeData(sProjectInTreeView.ProjectGUID,sProject);
   if (is_finded==false || sProject.ChangeData==true)//������� ��� � ���� ��� ��� ������ ������ ���� ��������
   {
    //������� ������
	cTreeCtrl.DeleteItem(sProjectInTreeView.hTREEITEM_Project);
    list_SProjectInTreeView.erase(iterator);
    iterator=list_SProjectInTreeView.begin();
    iterator_end=list_SProjectInTreeView.end();
	continue;
   }
   iterator++;
  }
   //���������� ��������
  CVectorProject cVectorProject=cDocument_Main_Ptr->GetCVectorProject();
  vector<SProject> &vector_SProject=cVectorProject.GetVectorSProject();
  size_t size=vector_SProject.size();
  for(size_t n=0;n<size;n++)
  {
   SProject &sProject=vector_SProject[n];
   SProjectInTreeView sProjectInTreeView;
   //����������
   bool is_finded=FindProjectByGUID(sProject.ProjectGUID,sProjectInTreeView);
   if (is_finded==false)//��������� � ������
   {
    sProjectInTreeView.ProjectGUID=sProject.ProjectGUID;
	sProjectInTreeView.hTREEITEM_Project=InsertItem(hTREEITEM_Projects,sProject.ProjectName,GetProjectImageIndex(),GetSelectedProjectImageIndex(),true);
	sProjectInTreeView.hTREEITEM_Parent=hTREEITEM_Projects;
    list_SProjectInTreeView.push_back(sProjectInTreeView);
   }
  }
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ��������
//----------------------------------------------------------------------------------------------------
CDocument_Main* CTreeView_Kit::GetDocument(void)
{
 ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));// ��������� ���� �� ����� ���������
 return(reinterpret_cast<CDocument_Main*>(m_pDocument));//���������� ��������� �� ��������
}
//----------------------------------------------------------------------------------------------------
//�������� ������� � ������
//----------------------------------------------------------------------------------------------------
HTREEITEM CTreeView_Kit::InsertItem(HTREEITEM hParent,const CSafeString& text,long image,long selected_image,bool sort)
{
 TV_ITEM TV_Item;
 TV_Item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
 TV_Item.pszText=const_cast<LPSTR>((LPCSTR)text);
 TV_Item.cchTextMax=text.GetLength();
 TV_Item.iImage=image;
 TV_Item.iSelectedImage=selected_image; 

 TV_INSERTSTRUCT TV_InsertStruct;
 TV_InsertStruct.hParent=hParent;
 TV_InsertStruct.hInsertAfter=TVI_LAST;
 if (sort==true) TV_InsertStruct.hInsertAfter=TVI_SORT;
 TV_InsertStruct.item=TV_Item;
 return(GetTreeCtrl().InsertItem(&TV_InsertStruct));
}
//----------------------------------------------------------------------------------------------------
//����� ���������� �� GUID
//----------------------------------------------------------------------------------------------------
bool CTreeView_Kit::FindColleagueByGUID(const CSafeString &guid,SColleagueInTreeView &sColleagueInTreeView)
{
 list<SColleagueInTreeView>::iterator iterator=list_SColleagueInTreeView.begin();
 list<SColleagueInTreeView>::iterator iterator_end=list_SColleagueInTreeView.end();
 while(iterator!=iterator_end)
 {
  sColleagueInTreeView=*iterator;
  if (sColleagueInTreeView.ColleagueGUID.Compare(guid)==0) return(true);
  iterator++;
 }
 return(false); 
}
//----------------------------------------------------------------------------------------------------
//����� ������ �� GUID
//----------------------------------------------------------------------------------------------------
bool CTreeView_Kit::FindProjectByGUID(const CSafeString &guid,SProjectInTreeView &sProjectInTreeView)
{
 list<SProjectInTreeView>::iterator iterator=list_SProjectInTreeView.begin();
 list<SProjectInTreeView>::iterator iterator_end=list_SProjectInTreeView.end();
 while(iterator!=iterator_end)
 {
  sProjectInTreeView=*iterator;
  if (sProjectInTreeView.ProjectGUID.Compare(guid)==0) return(true);
  iterator++;
 }
 return(false); 
}

//====================================================================================================
//������
//====================================================================================================
IMPLEMENT_DYNCREATE(CTreeView_Kit,CTreeView)
