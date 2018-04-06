#include "ctextcell.h"

//====================================================================================================
//конструктор класса
//====================================================================================================
CTextCell::CTextCell(void)
{ 
 TextColor=RGB(0,0,0);
 StrikeOutColor=RGB(0,0,0);

 StrikeOut=false;

 LOGFONT lf;
 lf.lfHeight=14; 
 lf.lfWidth=0; 
 lf.lfEscapement=0;
 lf.lfOrientation=0; 
 lf.lfWeight=FW_NORMAL; 
 lf.lfItalic=0;
 lf.lfUnderline=0; 
 lf.lfStrikeOut=0; 
 lf.lfCharSet=DEFAULT_CHARSET; 
 lf.lfOutPrecision=OUT_DEFAULT_PRECIS; 
 lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
 lf.lfQuality=DEFAULT_QUALITY; 
 lf.lfPitchAndFamily=DEFAULT_PITCH;  
 strcpy(lf.lfFaceName,"Times New Roman"); 

 cFont_Text.CreateFontIndirect(&lf);

 Text="";

 MinLineWidth=256;
 TextHeightOffset=2; 
 TextWidthOffset=2; 
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CTextCell::~CTextCell() 
{
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//отрисовка
//----------------------------------------------------------------------------------------------------
void CTextCell::Draw(CDC *pDC,const CRect &cRect_DrawArea)
{ 
 if (pDC==NULL) return;
 CRect cRect_NewDrawArea;
 //рисуем в заданной области
 CFont* cFont_Old=pDC->SelectObject(&cFont_Text);
 pDC->SetTextColor(TextColor);
 long oldbkmode=pDC->SetBkMode(TRANSPARENT);
 CRect cRect_Cell;

 OutText(pDC,cRect_DrawArea,cRect_Cell,true);

 pDC->SelectObject(cFont_Old);
 pDC->SetBkMode(oldbkmode);
}

//----------------------------------------------------------------------------------------------------
//получить размеры элемента
//----------------------------------------------------------------------------------------------------
void CTextCell::GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize)
{ 
 cSize.cx=0;
 cSize.cy=0;
 if (pDC==NULL) return;
 //рисуем в заданной области
 CFont* cFont_Old=pDC->SelectObject(&cFont_Text);
 pDC->SetTextColor(TextColor);
 long oldbkmode=pDC->SetBkMode(TRANSPARENT);
 CRect cRect_Cell;
 OutText(pDC,cRect_DrawArea,cRect_Cell,false);

 pDC->SelectObject(cFont_Old);
 pDC->SetBkMode(oldbkmode);

 cSize.cx=cRect_Cell.right-cRect_Cell.left;
 cSize.cy=cRect_Cell.bottom-cRect_Cell.top;
}

//----------------------------------------------------------------------------------------------------
//задать текст
//----------------------------------------------------------------------------------------------------
void CTextCell::SetText(const CSafeString &text)
{
 Text=text;
}
//----------------------------------------------------------------------------------------------------
//задать цвет текста
//----------------------------------------------------------------------------------------------------
void CTextCell::SetTextColor(const COLORREF &color)
{
 TextColor=color;
}
//----------------------------------------------------------------------------------------------------
//задать цвет зачёркивания
//----------------------------------------------------------------------------------------------------
void CTextCell::SetStrikeOutColor(const COLORREF &color)
{
 StrikeOutColor=color;
}
//----------------------------------------------------------------------------------------------------
//задать шрифт текста
//----------------------------------------------------------------------------------------------------
void CTextCell::SetTextFont(const LOGFONT &lf)
{
 cFont_Text.DeleteObject();
 cFont_Text.CreateFontIndirect(&lf);
}
//----------------------------------------------------------------------------------------------------
//задать зачёркивание текста
//----------------------------------------------------------------------------------------------------
void CTextCell::SetStrikeOut(const bool &state)
{
 StrikeOut=state;
}

//----------------------------------------------------------------------------------------------------
//вывести текст с разбиением на строки
//----------------------------------------------------------------------------------------------------
void CTextCell::OutText(CDC *pDC,const CRect &cRect_DrawArea,CRect &cRect_Cell,const bool &draw)
{
 cRect_Cell=cRect_DrawArea;
 if (pDC==NULL) return; 
 CPen cPen_StrikeOut;
 cPen_StrikeOut.CreatePen(PS_SOLID,1,StrikeOutColor);
 CPen *cPen_Old_Ptr=pDC->SelectObject(&cPen_StrikeOut);
 CSize cSize_Cell(0,TextHeightOffset);
 //выводим текст с разбиением на строки
 SIZE Size;
 GetTextExtentPoint32(pDC->m_hDC," ",1,&Size);
 long min_line_height=Size.cy;
 long length=Text.GetLength();
 const char *s_ptr=Text;
 long pos=0;
 GetTextExtentPoint32(pDC->m_hDC," ",1,&Size);
 long line_height=min_line_height;
 long line_width=TextWidthOffset;
 CString word="";//собираемое слово
 while(pos<=length)
 {
  char symbol=*s_ptr;
  pos++;
  s_ptr++;
  if (symbol=='\t') symbol=' ';
  if (static_cast<unsigned char>(symbol)>=32) 
  {   
   word+=symbol;
   if (static_cast<unsigned char>(symbol)!=32) continue;
  }
  if (word.GetLength()>0) GetTextExtentPoint32(pDC->m_hDC,word,word.GetLength(),&Size);  
                     else GetTextExtentPoint32(pDC->m_hDC," ",1,&Size);
  bool on_enter=false;
  if (line_width+Size.cx>MinLineWidth-TextWidthOffset)//если длина строки превышает минимальную
  {
   if (cRect_DrawArea.left+line_width+Size.cx>cRect_DrawArea.right-TextWidthOffset) on_enter=true;//разрываем строку, так как превысили размер области
   if (line_width==TextWidthOffset) on_enter=false;//если слово столь длинное, что превышает минимальный размер строки, то выводим такое слово целиком
  }
  if (symbol=='\n') on_enter=true;
  //делаем перевод строки, если он нужен
  if (on_enter==true)
  {
   if (StrikeOut==true && draw==true)//вычёркиваем строку 
   {
    pDC->MoveTo(CPoint(cRect_DrawArea.left,cRect_DrawArea.top+cSize_Cell.cy+line_height/2));
    pDC->LineTo(cRect_DrawArea.right,cRect_DrawArea.top+cSize_Cell.cy+line_height/2);     	 
   }
   if (line_width>cSize_Cell.cx) cSize_Cell.cx=line_width;
   line_width=TextWidthOffset;
   cSize_Cell.cy+=line_height;
   line_height=min_line_height;
  }
  //заново считаем размер
  if (Size.cy>line_height) line_height=Size.cy;
  //выводим слово
  if (word.GetLength()>0)
  {
   if (draw==true) pDC->TextOut(cRect_DrawArea.left+line_width,cRect_DrawArea.top+cSize_Cell.cy,word);
   line_width+=Size.cx;
  }
  word="";
  if (symbol==0)//делаем ещё один перевод строки
  {
   if (StrikeOut==true && draw==true)//вычёркиваем строку 
   {
    pDC->MoveTo(CPoint(cRect_DrawArea.left,cRect_DrawArea.top+cSize_Cell.cy+line_height/2));
    pDC->LineTo(cRect_DrawArea.right,cRect_DrawArea.top+cSize_Cell.cy+line_height/2);     	 
   }
   if (line_width>cSize_Cell.cx) cSize_Cell.cx=line_width;
   line_width=TextWidthOffset;
   cSize_Cell.cy+=line_height;
   line_height=min_line_height;
  }
 }
 cSize_Cell.cy+=TextHeightOffset;

 cRect_Cell.right=cRect_Cell.left+cSize_Cell.cx;
 cRect_Cell.bottom=cRect_Cell.top+cSize_Cell.cy;

 pDC->SelectObject(cPen_Old_Ptr);
}
