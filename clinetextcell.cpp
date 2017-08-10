#include "clinetextcell.h"

//====================================================================================================
//конструктор класса
//====================================================================================================
CLineTextCell::CLineTextCell(void)
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
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CLineTextCell::~CLineTextCell() 
{
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//отрисовка
//----------------------------------------------------------------------------------------------------
void CLineTextCell::Draw(CDC *pDC,const CRect &cRect_DrawArea)
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
void CLineTextCell::GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize)
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
void CLineTextCell::SetText(const CSafeString &text)
{
 Text=text;
}
//----------------------------------------------------------------------------------------------------
//задать цвет текста
//----------------------------------------------------------------------------------------------------
void CLineTextCell::SetTextColor(const COLORREF &color)
{
 TextColor=color;
}
//----------------------------------------------------------------------------------------------------
//задать цвет зачёркивания
//----------------------------------------------------------------------------------------------------
void CLineTextCell::SetStrikeOutColor(const COLORREF &color)
{
 StrikeOutColor=color;
}
//----------------------------------------------------------------------------------------------------
//задать шрифт текста
//----------------------------------------------------------------------------------------------------
void CLineTextCell::SetTextFont(const LOGFONT &lf)
{
 cFont_Text.CreateFontIndirect(&lf);
}
//----------------------------------------------------------------------------------------------------
//задать зачёркивание текста
//----------------------------------------------------------------------------------------------------
void CLineTextCell::SetStrikeOut(const bool &state)
{
 StrikeOut=state;
}

//----------------------------------------------------------------------------------------------------
//вывести текст в одну строку
//----------------------------------------------------------------------------------------------------
void CLineTextCell::OutText(CDC *pDC,const CRect &cRect_DrawArea,CRect &cRect_Cell,const bool &draw)
{
 cRect_Cell=cRect_DrawArea;
 if (pDC==NULL) return; 
 CPen cPen_StrikeOut;
 cPen_StrikeOut.CreatePen(PS_SOLID,1,StrikeOutColor);
 CPen *cPen_Old_Ptr=pDC->SelectObject(&cPen_StrikeOut);
 //выводим текст
 SIZE Size;
 GetTextExtentPoint32(pDC->m_hDC,Text,Text.GetLength(),&Size);
 cRect_Cell.left=cRect_DrawArea.left;
 cRect_Cell.right=cRect_DrawArea.right;
 cRect_Cell.top=cRect_DrawArea.top;
 cRect_Cell.bottom=cRect_DrawArea.top+Size.cy;
 if (draw==false) return;
 long x_left=(cRect_DrawArea.right-cRect_DrawArea.left)/2-Size.cx/2+cRect_DrawArea.left;
 long y_top=(cRect_DrawArea.bottom-cRect_DrawArea.top)/2-Size.cy/2+cRect_DrawArea.top;
 TextOut(pDC->m_hDC,x_left,y_top,Text,Text.GetLength());
 if (StrikeOut==true)//вычёркиваем строку 
 {
  pDC->MoveTo(CPoint(cRect_DrawArea.left,y_top+(cRect_DrawArea.bottom-cRect_DrawArea.top)/2));
  pDC->LineTo(cRect_DrawArea.right,y_top+(cRect_DrawArea.bottom-cRect_DrawArea.top)/2);
 }
 pDC->SelectObject(cPen_Old_Ptr);
}
