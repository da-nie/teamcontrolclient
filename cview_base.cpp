#include "cview_base.h"

//====================================================================================================
//конструктор класса
//====================================================================================================
CView_Base::CView_Base() 
{ 
 Logfont_Task.lfHeight=8; 
 Logfont_Task.lfWidth=0; 
 Logfont_Task.lfEscapement=0;
 Logfont_Task.lfOrientation=0; 
 Logfont_Task.lfWeight=FW_NORMAL; 
 Logfont_Task.lfItalic=0;
 Logfont_Task.lfUnderline=0; 
 Logfont_Task.lfStrikeOut=0; 
 Logfont_Task.lfCharSet=DEFAULT_CHARSET; 
 Logfont_Task.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 Logfont_Task.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 Logfont_Task.lfQuality=DEFAULT_QUALITY; 
 Logfont_Task.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(Logfont_Task.lfFaceName,"system"); 

 Logfont_TaskDate.lfHeight=20; 
 Logfont_TaskDate.lfWidth=0; 
 Logfont_TaskDate.lfEscapement=0;
 Logfont_TaskDate.lfOrientation=0; 
 Logfont_TaskDate.lfWeight=FW_BOLD; 
 Logfont_TaskDate.lfItalic=0;
 Logfont_TaskDate.lfUnderline=0; 
 Logfont_TaskDate.lfStrikeOut=0; 
 Logfont_TaskDate.lfCharSet=DEFAULT_CHARSET; 
 Logfont_TaskDate.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 Logfont_TaskDate.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 Logfont_TaskDate.lfQuality=DEFAULT_QUALITY; 
 Logfont_TaskDate.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(Logfont_TaskDate.lfFaceName,"Courier New"); 

 Logfont_FromUser.lfHeight=16; 
 Logfont_FromUser.lfWidth=0; 
 Logfont_FromUser.lfEscapement=0;
 Logfont_FromUser.lfOrientation=0; 
 Logfont_FromUser.lfWeight=FW_NORMAL; 
 Logfont_FromUser.lfItalic=0;
 Logfont_FromUser.lfUnderline=0; 
 Logfont_FromUser.lfStrikeOut=0; 
 Logfont_FromUser.lfCharSet=DEFAULT_CHARSET; 
 Logfont_FromUser.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 Logfont_FromUser.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 Logfont_FromUser.lfQuality=DEFAULT_QUALITY; 
 Logfont_FromUser.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(Logfont_FromUser.lfFaceName,"Times New Roman"); 

 Logfont_ForUser.lfHeight=16; 
 Logfont_ForUser.lfWidth=0; 
 Logfont_ForUser.lfEscapement=0;
 Logfont_ForUser.lfOrientation=0; 
 Logfont_ForUser.lfWeight=FW_NORMAL; 
 Logfont_ForUser.lfItalic=0;
 Logfont_ForUser.lfUnderline=0; 
 Logfont_ForUser.lfStrikeOut=0; 
 Logfont_ForUser.lfCharSet=DEFAULT_CHARSET; 
 Logfont_ForUser.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 Logfont_ForUser.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 Logfont_ForUser.lfQuality=DEFAULT_QUALITY; 
 Logfont_ForUser.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(Logfont_ForUser.lfFaceName,"Times New Roman"); 

 Logfont_ColumnName.lfHeight=20; 
 Logfont_ColumnName.lfWidth=0; 
 Logfont_ColumnName.lfEscapement=0;
 Logfont_ColumnName.lfOrientation=0; 
 Logfont_ColumnName.lfWeight=FW_BOLD; 
 Logfont_ColumnName.lfItalic=0;
 Logfont_ColumnName.lfUnderline=0; 
 Logfont_ColumnName.lfStrikeOut=0; 
 Logfont_ColumnName.lfCharSet=DEFAULT_CHARSET; 
 Logfont_ColumnName.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 Logfont_ColumnName.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 Logfont_ColumnName.lfQuality=DEFAULT_QUALITY; 
 Logfont_ColumnName.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(Logfont_ColumnName.lfFaceName,"Arial"); 

 FlashState=false;
 SelectedTaskGUID="";

 cTextCell_TaskDate.SetTextFont(Logfont_TaskDate);
 cTextCell_TaskDate.SetTextColor(RGB(0,0,255));

 cTextCell_Task.SetTextFont(Logfont_Task);
 cTextCell_Task.SetTextColor(RGB(0,0,0)); 

 cTextCell_ForUser.SetTextFont(Logfont_ForUser);
 cTextCell_ForUser.SetTextColor(RGB(0,127,255));

 cTextCell_FromUser.SetTextFont(Logfont_FromUser);
 cTextCell_FromUser.SetTextColor(RGB(127,0,255));

 cLineTextCell_ColumnName.SetTextFont(Logfont_ColumnName);
 cLineTextCell_ColumnName.SetTextColor(RGB(0,0,0));

 cFrameCell_TaskState.SetBorderColor(RGB(0,0,0));
 cFrameCell.SetBorderColor(RGB(0,0,0));

 cTextCell_Task.SetStrikeOutColor(RGB(192,192,192));

 VisibleFromUser=true;
 VisibleForUser=true;
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CView_Base::~CView_Base() 
{
}

//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//предсоздание окна
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CView_Base::PreCreateWindow(CREATESTRUCT& cs)
{
 return(CView::PreCreateWindow(cs));
}
//----------------------------------------------------------------------------------------------------
//создание окна
//----------------------------------------------------------------------------------------------------
afx_msg void CView_Base::OnInitialUpdate(void)
{ 	
 //создаЄм полосу прокрутки
 CRect cRect;
 GetClientRect(&cRect);
 cRect.left=cRect.right-GetScrollBarWidth(); 
 cScrollBar_ShiftItem.Create(WS_CHILD|WS_VISIBLE|SBS_VERT,cRect,this,IDC_SCROLLBAR_LIST_VIEW_OUT_TASK_SHIFT_ITEM);
 cScrollBar_ShiftItem.SetScrollRange(0,0,TRUE);
 cScrollBar_ShiftItem.EnableWindow(FALSE);

 cBitmap_TaskNotReadFrameOne.LoadBitmap(IDB_BITMAP_TASK_NOT_READ_FRAME_ONE);
 cBitmap_TaskNotReadFrameOneFlash.LoadBitmap(IDB_BITMAP_TASK_NOT_READ_FRAME_TWO);
 cBitmap_TaskDone.LoadBitmap(IDB_BITMAP_TASK_DONE);
 cBitmap_TaskReaded.LoadBitmap(IDB_BITMAP_TASK_READED);
 cBitmap_TaskIsRunning.LoadBitmap(IDB_BITMAP_TASK_IS_RUNNING);
 cBitmap_TaskCanceled.LoadBitmap(IDB_BITMAP_TASK_CANCELED);
 cBitmap_TaskFinished.LoadBitmap(IDB_BITMAP_TASK_FINISHED);

 CView::OnInitialUpdate();
 //запускаем таймер
 SetTimer(ID_TIMER_VIEW,500,NULL);
}
//----------------------------------------------------------------------------------------------------
//прорисовка вида
//----------------------------------------------------------------------------------------------------
afx_msg void CView_Base::OnDraw(CDC* pDC)
{
 CView::OnDraw(pDC);
 //готовим поле
 CDC cDC_Mem;
 cDC_Mem.CreateCompatibleDC(pDC);
 CRect cRect;
 GetClientRect(&cRect);
 cRect.right-=GetScrollBarWidth();

 CBitmap cBitmap;
 cDC_Mem.SetMapMode(MM_TEXT);
 cBitmap.CreateCompatibleBitmap(pDC,cRect.right,cRect.bottom);
 cDC_Mem.SelectObject(&cBitmap);
 //очистим область
 CBrush cBrush;
 cBrush.CreateSolidBrush(RGB(250,250,220));
 cDC_Mem.FillRect(&cRect,&cBrush);
 cBrush.DeleteObject();
 //теперь можно рисовать
 DrawTasks(&cDC_Mem);
 //выводим область
 pDC->BitBlt(0,0,cRect.right,cRect.bottom,&cDC_Mem,0,0,SRCCOPY);
 cDC_Mem.DeleteDC(); 
}
//====================================================================================================
//функции обработки сообщений класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//изменение размеров окна
//----------------------------------------------------------------------------------------------------
afx_msg void CView_Base::OnSize(UINT nType,int cx,int cy)
{ 
 CView::OnSize(nType,cx,cy); 
 CRect cRect;
 GetClientRect(&cRect);
 cRect.left=cRect.right-GetScrollBarWidth();
 cScrollBar_ShiftItem.MoveWindow(cRect,TRUE);
}
//----------------------------------------------------------------------------------------------------
//событие перерисовки фона
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CView_Base::OnEraseBkgnd(CDC *pDC)
{
 return(TRUE);
}
//----------------------------------------------------------------------------------------------------
//событие таймера
//----------------------------------------------------------------------------------------------------
afx_msg void CView_Base::OnTimer(UINT nIDEvent)
{
 CView::OnTimer(nIDEvent);
 if (nIDEvent!=ID_TIMER_VIEW) return;
 if (FlashState==true) FlashState=false;
                  else FlashState=true;
 InvalidateRect(NULL,FALSE);
}
//----------------------------------------------------------------------------------------------------
//уничтожение окна
//----------------------------------------------------------------------------------------------------
afx_msg void CView_Base::OnDestroy(void)
{
 KillTimer(ID_TIMER_VIEW);
}
//---------------------------------------------------------------------------
//вертикальна€ полоса прокрутки
//---------------------------------------------------------------------------
afx_msg void CView_Base::OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
 if (pScrollBar!=&cScrollBar_ShiftItem) return;//не наша полоса прокрутки
 long hpos=pScrollBar->GetScrollPos();
 if (nSBCode==SB_LINERIGHT) hpos++;
 if (nSBCode==SB_LINELEFT) hpos--;
 int min,max;
 pScrollBar->GetScrollRange(&min,&max);
 long delta=(max-min);
 long step=delta*0.05;
 if (step<1 && delta>0) step=1;
 if (nSBCode==SB_PAGERIGHT) hpos+=step;
 if (nSBCode==SB_PAGELEFT) hpos-=step;
 if (nSBCode==SB_RIGHT) hpos=max;
 if (nSBCode==SB_LEFT) hpos=min;
 if (nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK) hpos=nPos;
 if (hpos<min) hpos=min;
 if (hpos>max) hpos=max;
 pScrollBar->SetScrollPos(hpos,TRUE);
 InvalidateRect(NULL,FALSE);
}
//----------------------------------------------------------------------------------------------------
//вращение колЄсика мышки
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CView_Base::OnMouseWheel(UINT nFlags,short zDelta,CPoint pt)
{
 zDelta/=WHEEL_DELTA;
 if (zDelta>-1 && zDelta<1) return(TRUE);
 long hpos=cScrollBar_ShiftItem.GetScrollPos();
 int min,max;
 cScrollBar_ShiftItem.GetScrollRange(&min,&max);
 hpos-=zDelta;
 if (hpos<min) hpos=min;
 if (hpos>max) hpos=max;
 cScrollBar_ShiftItem.SetScrollPos(hpos,TRUE);
 InvalidateRect(NULL,FALSE);
 return(TRUE);
}

//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//получить документ
//----------------------------------------------------------------------------------------------------
CDocument_Main* CView_Base::GetDocument(void)
{
 ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));// проверить есть ли класс документа
 return(reinterpret_cast<CDocument_Main*>(m_pDocument));//возвратить указатель на документ
}
//----------------------------------------------------------------------------------------------------
//обновить задани€ в списке
//----------------------------------------------------------------------------------------------------
void CView_Base::UpdateTask(vector<CTask> &vector_CTask_Local)
{
 vector_CTask.clear();
 CDocument_Main *cDocument_Main_Ptr=GetDocument();
 if (cDocument_Main_Ptr==NULL) return;
 SShowState sShowState;
 cDocument_Main_Ptr->GetShowState(sShowState);

 CSafeString guid;
 CSafeString name;
 bool on_line;
 bool leader;
 cDocument_Main_Ptr->GetMyParam(on_line,guid,name,leader);

 vector_CTask.clear();
 size_t size=vector_CTask_Local.size();
 for(size_t n=0;n<size;n++)
 {  
  if (TaskIsVisible(sShowState,vector_CTask_Local[n])==false) continue;
  CUser cUser;
  cDocument_Main_Ptr->FindByUserGUID(vector_CTask_Local[n].GetFromUserGUID(),cUser);
  vector_CTask_Local[n].SetFromUser(cUser.GetName());
  cDocument_Main_Ptr->FindByUserGUID(vector_CTask_Local[n].GetForUserGUID(),cUser);
  vector_CTask_Local[n].SetForUser(cUser.GetName());
  vector_CTask.push_back(vector_CTask_Local[n]);
 }

 if (vector_CTask.size()==0)
 {
  cScrollBar_ShiftItem.SetScrollRange(0,0,TRUE);
  cScrollBar_ShiftItem.EnableWindow(FALSE);
 }
 else
 {
  cScrollBar_ShiftItem.SetScrollRange(0,vector_CTask.size()-1,TRUE);
  cScrollBar_ShiftItem.EnableWindow(TRUE);
 }
 return;
}
//----------------------------------------------------------------------------------------------------
//нарисовать список задач
//----------------------------------------------------------------------------------------------------
void CView_Base::DrawTasks(CDC *pDC)
{
 CRect cRect;
 GetClientRect(&cRect);
 cRect.right-=GetScrollBarWidth();

 long task_index=cScrollBar_ShiftItem.GetScrollPos();

 vector_SCell_Task.clear();
 //выводим список задач к этому пользователю
 size_t size=vector_CTask.size();
 CRect cRect_DrawArea;
 cRect_DrawArea.left=cRect.left;
 cRect_DrawArea.right=cRect.right;
 cRect_DrawArea.top=cRect.top;
 cRect_DrawArea.bottom=cRect.bottom;

 SYSTEMTIME system_time;
 GetLocalTime(&system_time);

 CDate cDate_Current(system_time.wYear,system_time.wMonth,system_time.wDay);//текущее врем€ дл€ сравнени€ с временем заданий

 //выводим название столбца
 cLineTextCell_ColumnName.SetText(ColumnName);
 CSize cSize_ColumnName;
 cLineTextCell_ColumnName.GetSize(pDC,cRect_DrawArea,cSize_ColumnName);
 CRect cRect_ColumnName=CRect(cRect_DrawArea.left,cRect_DrawArea.top,cRect_DrawArea.right,cRect_DrawArea.top+cSize_ColumnName.cy+GetHeightOffsetColumnName());
 cFillCell.SetBackgroundColor(RGB(220,220,220));
 cFillCell.Draw(pDC,cRect_ColumnName);
 cLineTextCell_ColumnName.Draw(pDC,cRect_ColumnName);
 cRect_DrawArea.top=cRect_ColumnName.bottom;
 cFrameCell.SetBorderColor(RGB(0,0,0));
 cFrameCell.Draw(pDC,cRect_ColumnName);

 for(size_t n=task_index;n<size;n++)
 {
  if (cRect_DrawArea.top>cRect.bottom) break;
  CTask &cTask=vector_CTask[n];
  char str_date[255];
  const CDate& cDate=cTask.GetDate();
  sprintf(str_date,"ƒо %02i.%02i.%04i [є %i]",cDate.GetDay(),cDate.GetMonth(),cDate.GetYear(),cTask.GetIndex());
  cTextCell_TaskDate.SetText(str_date);
  /*if (cTask.State==TASK_STATE_DONE) cTextCell_Task.SetStrikeOut(true);
                               else cTextCell_Task.SetStrikeOut(false);
							   */
  cTextCell_Task.SetStrikeOut(false);
  cTextCell_Task.SetText(cTask.GetTask());
  //кому это задание
  cTextCell_ForUser.SetText("ƒл€: "+cTask.GetForUser());
  //от кого задание
  cTextCell_FromUser.SetText("ќт: "+cTask.GetFromUser());
  //узнаем размеры изображени€
  CBitmap *cBitmap_Ptr=NULL;
  if (cTask.IsStateNoRead()==true)
  {
   if (FlashState==true) cBitmap_Ptr=&cBitmap_TaskNotReadFrameOne;
                    else cBitmap_Ptr=&cBitmap_TaskNotReadFrameOneFlash;
  }
  if (cTask.IsStateReaded()==true) cBitmap_Ptr=&cBitmap_TaskReaded;
  if (cTask.IsStateCancelled()==true) cBitmap_Ptr=&cBitmap_TaskCanceled;
  if (cTask.IsStateIsRunning()==true) cBitmap_Ptr=&cBitmap_TaskIsRunning;
  if (cTask.IsStateDone()==true) cBitmap_Ptr=&cBitmap_TaskDone;
  if (cTask.IsStateFinished()==true) cBitmap_Ptr=&cBitmap_TaskFinished;
  cBitmapCell_TaskState.SetBitmap(cBitmap_Ptr);
  CSize cSize_TaskState;
  cBitmapCell_TaskState.GetSize(pDC,cRect_DrawArea,cSize_TaskState);
  //узнаем размеры текста
  CRect cRect_TextArea=CRect(cRect_DrawArea.left+cSize_TaskState.cx+GetTastStateHorizontalOffset()*2,cRect_DrawArea.top,cRect_DrawArea.right,cRect_DrawArea.bottom);
  CSize cSize_TaskDate;
  cTextCell_TaskDate.GetSize(pDC,cRect_TextArea,cSize_TaskDate);
  CSize cSize_ForUser;
  cTextCell_ForUser.GetSize(pDC,cRect_TextArea,cSize_ForUser);
  CSize cSize_FromUser;
  cTextCell_FromUser.GetSize(pDC,cRect_TextArea,cSize_FromUser);
  CSize cSize_Task;
  cTextCell_Task.GetSize(pDC,cRect_TextArea,cSize_Task);  

  if (VisibleFromUser==false) cSize_FromUser=CSize(0,0);
  if (VisibleForUser==false) cSize_ForUser=CSize(0,0);

  //модифицируем размеры €чейки под изображение
  long cell_height=cSize_TaskDate.cy+cSize_Task.cy+cSize_ForUser.cy+cSize_FromUser.cy;
  if (cell_height<GetTastStateVerticalOffset()*2+cSize_TaskState.cy+cSize_ForUser.cy+cSize_FromUser.cy) cell_height=GetTastStateVerticalOffset()*2+cSize_TaskState.cy+cSize_ForUser.cy+cSize_FromUser.cy;
  cRect_TextArea.bottom=cRect_TextArea.top+cell_height;  
  cRect_DrawArea.bottom=cRect_DrawArea.top+cell_height;
  //модифицируем размеры €чейки изображени€ по ширине
  CRect cRect_TaskState=CRect(cRect_DrawArea.left,cRect_DrawArea.top,cRect_DrawArea.left+GetTastStateHorizontalOffset()*2+cSize_TaskState.cx,cRect_DrawArea.bottom);
  //заменим фон дл€ выбранного задани€
  COLORREF color=RGB(250,250,230);
  if (cTask.IsTaskGUID(SelectedTaskGUID)==true)
  {
   color=RGB(230,230,250);	  
   cFillCell.SetBackgroundColor(color);
   cFillCell.Draw(pDC,cRect_TextArea);
  }
  //закрашиваем срок
  CRect cRect_TextDateArea=CRect(cRect_TextArea.left,cRect_TextArea.top,cRect_TextArea.right,cRect_TextArea.top+cSize_TaskDate.cy);  
  if (cDate_Current>cTask.GetDate()) color=RGB(255,0,0);//просроченное задание
  //if (cTaskGetDate()>cDate_Current) color=RGB(250,250,230);//ещЄ есть врем€
  if (cDate_Current==cTask.GetDate()) color=RGB(255,255,0);//сегодн€шн€€ дата
  if (cTask.IsStateFinished()==true) color=RGB(0,255,0);//задание завершено
   
  cFillCell.SetBackgroundColor(color);
  cFillCell.Draw(pDC,cRect_TextDateArea);

  //выводим статус задани€
  cBitmapCell_TaskState.Draw(pDC,cRect_TaskState);
  cFrameCell_TaskState.Draw(pDC,cRect_TaskState);

  //выведем текст
  CRect cRect_TaskDateArea=CRect(cRect_TextArea.left,cRect_TextArea.top,cRect_TextArea.right,cRect_TextArea.bottom);
  cTextCell_TaskDate.Draw(pDC,cRect_TaskDateArea);

  if (VisibleFromUser==true) 
  {
   CRect cRect_FromUserArea=CRect(cRect_TextArea.left,cRect_TextArea.top+cSize_TaskDate.cy,cRect_TextArea.right,cRect_TextArea.bottom);
   cTextCell_FromUser.Draw(pDC,cRect_FromUserArea);
  }
  if (VisibleForUser==true) 
  {
   CRect cRect_ForUserArea=CRect(cRect_TextArea.left,cRect_TextArea.top+cSize_TaskDate.cy+cSize_FromUser.cy,cRect_TextArea.right,cRect_TextArea.bottom);
   cTextCell_ForUser.Draw(pDC,cRect_ForUserArea);
  }

  CRect cRect_TaskArea=CRect(cRect_TextArea.left,cRect_TextArea.top+cSize_TaskDate.cy+cSize_ForUser.cy+cSize_FromUser.cy,cRect_TextArea.right,cRect_TextArea.bottom);
  cTextCell_Task.Draw(pDC,cRect_TaskArea);
  //выведем рамку  
  cFrameCell.Draw(pDC,cRect_DrawArea);

  SCell sCell;
  sCell.GUID=cTask.GetTaskGUID();
  sCell.cRect=cRect_DrawArea;
  vector_SCell_Task.push_back(sCell);

  cRect_DrawArea.top=cRect_DrawArea.bottom;
 }
}

