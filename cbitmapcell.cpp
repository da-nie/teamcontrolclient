#include "cbitmapcell.h"

//====================================================================================================
//конструктор класса
//====================================================================================================
CBitmapCell::CBitmapCell(void)
{ 
 cBitmap_Ptr=NULL;
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CBitmapCell::~CBitmapCell() 
{
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//отрисовка
//----------------------------------------------------------------------------------------------------
void CBitmapCell::Draw(CDC *pDC,const CRect &cRect_DrawArea)
{ 
 if (pDC==NULL) return;
 if (cBitmap_Ptr==NULL) return;
 BITMAP bitmap;
 cBitmap_Ptr->GetObject(sizeof(BITMAP),&bitmap);
 CDC cDC;
 cDC.CreateCompatibleDC(pDC);
 cDC.SelectObject(*cBitmap_Ptr);
 long width=cRect_DrawArea.right-cRect_DrawArea.left;
 long height=cRect_DrawArea.bottom-cRect_DrawArea.top;
 long x=cRect_DrawArea.left+(width-bitmap.bmWidth)/2;
 long y=cRect_DrawArea.top+(height-bitmap.bmHeight)/2;
 pDC->StretchBlt(x,y,bitmap.bmWidth,bitmap.bmHeight,&cDC,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
}
//----------------------------------------------------------------------------------------------------
//получить размеры элемента
//----------------------------------------------------------------------------------------------------
void CBitmapCell::GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize)
{
 cSize.cx=0;
 cSize.cy=0;
 if (cBitmap_Ptr==NULL) return;
 BITMAP bitmap;
 cBitmap_Ptr->GetObject(sizeof(BITMAP),&bitmap);
 cSize.cx=bitmap.bmWidth;
 cSize.cy=bitmap.bmHeight;
}
//----------------------------------------------------------------------------------------------------
//задать изображение
//----------------------------------------------------------------------------------------------------
void CBitmapCell::SetBitmap(CBitmap *cBitmap_Ptr_Set)
{
 cBitmap_Ptr=cBitmap_Ptr_Set;
}
