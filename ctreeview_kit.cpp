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

 CUser cUser;
 cUser.SetUserGUID(ALL_USER_GUID);
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 cDocument_Main_Ptr->SetSelectedUser(cUser);

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
 CUser cUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser_Selected)==false) return;//��� ���������� ��������
 //�������, ��� ���� �������
 CSafeString guid;
 CSafeString name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,guid,name,leader);

 CTreeCtrl& cTreeCtrl=GetTreeCtrl();
 HTREEITEM hTREEITEM_item=cTreeCtrl.GetSelectedItem();
 if (cUser_Selected.IsUserGUID(ALL_USER_GUID)==true && hTREEITEM_item==hTREEITEM_Colleague) return;//������� ����� �������������
 if (cUser_Selected.IsUserGUID(ALL_USER_GUID)==true && hTREEITEM_item==hTREEITEM_Projects)//������� ����� ��������
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
 
 CProject cProject;
 if (cDocument_Main_Ptr->FindByProjectGUID(cUser_Selected.GetUserGUID(),cProject)==true)//������ ������
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
 CUser cUser;
 if (cDocument_Main_Ptr->FindByUserGUID(cUser_Selected.GetUserGUID(),cUser)==true)//������ ������������
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
 CUser cUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser_Selected)==false) return;//��� ���������� ��������
 if (cUser_Selected.IsUserGUID(ALL_USER_GUID)==true) return;
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
  CUser cUser;
  cUser.SetUserGUID(ALL_USER_GUID);
  cDocument_Main_Ptr->SetSelectedUser(cUser);
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
   CUser cUser;
   bool is_finded=cDocument_Main_Ptr->FindByUserGUIDAndResetChangeData(sColleagueInTreeView.ColleagueGUID,cUser);
   if (is_finded==true) cDocument_Main_Ptr->SetSelectedUser(cUser);//���������, ��� ��� ������ ������ ������������
   return;
  }
  iterator++;
 }

 //���� ��������� ������� ����� ��������
 list<CProjectInTreeView>::iterator iterator_project=list_CProjectInTreeView.begin();
 list<CProjectInTreeView>::iterator iterator_project_end=list_CProjectInTreeView.end();  
 while(iterator_project!=iterator_project_end)
 {
  CProjectInTreeView &cProjectInTreeView=*iterator_project;
  if (cProjectInTreeView.hTREEITEM_Project==hTREEITEM_item)
  {
   CProject cProject;
   bool is_finded=cDocument_Main_Ptr->FindByProjectGUIDAndResetChangeData(cProjectInTreeView.ProjectGUID,cProject);
   if (is_finded==true)
   {      
    //������������� ��������� ������������ � ��������������� ������� (�������������� ������� �� ������������)
    CUser cUser;
    cUser.SetUserGUID(cProject.GetProjectGUID());
    cDocument_Main_Ptr->SetSelectedUser(cUser);
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
 CUser cUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser_Selected)==false) return;//��� ���������� ��������
 CUser cUser;
 if (cDocument_Main_Ptr->FindByUserGUID(cUser_Selected.GetUserGUID(),cUser)==false) return;//������ ������������ ��� � ����

 CTask cTask;
 SYSTEMTIME system_time;
 GetLocalTime(&system_time);
 cTask.SetPlannedPosition(false);
 cTask.SetAnswerNotRead(false);
 cTask.SetDate(CDate(system_time.wYear,system_time.wMonth,system_time.wDay));
 cTask.SetForUserGUID(cUser_Selected.GetUserGUID());
 while(1)
 {
  CDialog_TaskSettings cDialog_TaskSettings((LPCSTR)IDD_DIALOG_TASK_SETTINGS,this);
  if (cDialog_TaskSettings.Activate(cTask,cDocument_Main_Ptr,true)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //������ �������� �������
   if (cDocument_Main_Ptr->AddTask(cTask)==false)
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
 CUser cUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser_Selected)==false) return;//��� ���������� ��������
 CUser cUser;
 if (cDocument_Main_Ptr->FindByUserGUID(cUser_Selected.GetUserGUID(),cUser)==false) return;//������ ������������ ��� � ����

 CDialog_UserSettings cDialog_UserSettings((LPCSTR)IDD_DIALOG_USER_SETTINGS,this);
 cDialog_UserSettings.Activate(cUser_Selected);	
}

//----------------------------------------------------------------------------------------------------
//�������� ������
//----------------------------------------------------------------------------------------------------
afx_msg void CTreeView_Kit::OnCommand_Menu_List_AddProject(void)
{
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 CProject cProject;
 cProject.SetProjectName("");
 cProject.SetProjectGUID("");
 cProject.SetChangeData(false);
 cProject.MarkForWork();
 while(1)
 {  
  CDialog_ProjectSettings cDialog_ProjectSettings((LPCSTR)IDD_DIALOG_PROJECT_SETTINGS,this);
  if (cDialog_ProjectSettings.Activate(cProject)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //������ �������� ������
   if (cDocument_Main_Ptr->AddProject(cProject)==false)
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
 CUser cUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser_Selected)==false) return;//��� ���������� ��������
 CProject cProject;
 if (cDocument_Main_Ptr->FindByProjectGUID(cUser_Selected.GetUserGUID(),cProject)==false) return;//������ ������� ��� � ����

 while(1)
 {
  CDialog_ProjectSettings cDialog_ProjectSettings((LPCSTR)IDD_DIALOG_PROJECT_SETTINGS,this);
  if (cDialog_ProjectSettings.Activate(cProject)==true)
  {
   CDocument_Main *cDocument_Main_Ptr=GetDocument();
   //������ �������� ������
   if (cDocument_Main_Ptr->ChangeProject(cProject)==false)
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
 CUser cUser_Selected;
 if (cDocument_Main_Ptr->GetSelectedUser(cUser_Selected)==false) return;//��� ���������� ��������
 CProject cProject;
 if (cDocument_Main_Ptr->FindByProjectGUID(cUser_Selected.GetUserGUID(),cProject)==false) return;//������ ������� ��� � ����
 if (MessageBox("������� ��������� ������?","�������������",MB_YESNO|MB_DEFBUTTON2)!=IDYES) return;
 cDocument_Main_Ptr->DeleteProject(cProject); 
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
   CUser cUser;  
   bool is_finded=cDocument_Main_Ptr->FindByUserGUIDAndResetChangeData(sColleagueInTreeView.ColleagueGUID,cUser);
   if (is_finded==false || cUser.GetChangeData()==true)//���������� ��� � ���� ��� ��� ������ ������ ���� ��������
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
  vector<CUser> &vector_CUser=cVectorUser.GetVectorCUser();
  size_t size=vector_CUser.size();
  for(size_t n=0;n<size;n++)
  {
   CUser &cUser=vector_CUser[n];
   SColleagueInTreeView sColleagueInTreeView;
   //���� ����������
   bool is_finded=FindColleagueByGUID(cUser.GetUserGUID(),sColleagueInTreeView);
   if (is_finded==false)//��������� � ������
   {
    sColleagueInTreeView.ColleagueGUID=cUser.GetUserGUID();
	if (cUser.GetLeader()==true) sColleagueInTreeView.hTREEITEM_Colleague=InsertItem(hTREEITEM_Colleague,cUser.GetName(),GetColleagueLeaderImageIndex(),GetSelectedColleagueLeaderImageIndex(),true);
	                        else sColleagueInTreeView.hTREEITEM_Colleague=InsertItem(hTREEITEM_Colleague,cUser.GetName(),GetColleagueImageIndex(),GetSelectedColleagueImageIndex(),true);
	sColleagueInTreeView.hTREEITEM_Parent=hTREEITEM_Colleague;
    list_SColleagueInTreeView.push_back(sColleagueInTreeView);
   }
  }
 }
 if (hTREEITEM_Projects!=NULL)
 {
  //��������� ������ �������� � ��������� ��� ������� �������
  list<CProjectInTreeView>::iterator iterator=list_CProjectInTreeView.begin();
  list<CProjectInTreeView>::iterator iterator_end=list_CProjectInTreeView.end();  
  //�������� ��������
  while(iterator!=iterator_end)
  {
   CProjectInTreeView &cProjectInTreeView=*iterator;
   CProject cProject;  
   bool is_finded=cDocument_Main_Ptr->FindByProjectGUIDAndResetChangeData(cProjectInTreeView.ProjectGUID,cProject);
   if (is_finded==false || cProject.GetChangeData()==true)//������� ��� � ���� ��� ��� ������ ������ ���� ��������
   {
    //������� ������
	cTreeCtrl.DeleteItem(cProjectInTreeView.hTREEITEM_Project);
    list_CProjectInTreeView.erase(iterator);
    iterator=list_CProjectInTreeView.begin();
    iterator_end=list_CProjectInTreeView.end();
	continue;
   }
   iterator++;
  }
   //���������� ��������
  CVectorProject cVectorProject=cDocument_Main_Ptr->GetCVectorProject();
  vector<CProject> &vector_CProject=cVectorProject.GetVectorCProject();
  size_t size=vector_CProject.size();
  for(size_t n=0;n<size;n++)
  {
   CProject &cProject=vector_CProject[n];
   CProjectInTreeView cProjectInTreeView;
   //����������
   bool is_finded=FindProjectByGUID(cProject.GetProjectGUID(),cProjectInTreeView);
   if (is_finded==false)//��������� � ������
   {
    cProjectInTreeView.ProjectGUID=cProject.GetProjectGUID();
	cProjectInTreeView.hTREEITEM_Project=InsertItem(hTREEITEM_Projects,cProject.GetProjectName(),GetProjectImageIndex(),GetSelectedProjectImageIndex(),true);
	cProjectInTreeView.hTREEITEM_Parent=hTREEITEM_Projects;
    list_CProjectInTreeView.push_back(cProjectInTreeView);
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
bool CTreeView_Kit::FindProjectByGUID(const CSafeString &guid,CProjectInTreeView &cProjectInTreeView)
{
 list<CProjectInTreeView>::iterator iterator=list_CProjectInTreeView.begin();
 list<CProjectInTreeView>::iterator iterator_end=list_CProjectInTreeView.end();
 while(iterator!=iterator_end)
 {
  cProjectInTreeView=*iterator;
  if (cProjectInTreeView.ProjectGUID.Compare(guid)==0) return(true);
  iterator++;
 }
 return(false); 
}

//====================================================================================================
//������
//====================================================================================================
IMPLEMENT_DYNCREATE(CTreeView_Kit,CTreeView)
