#include "cfillcell.h"

//====================================================================================================
//����������� ������
//====================================================================================================
CFillCell::CFillCell(void)
{ 
 BackgroundColor=RGB(255,255,255);
}
//====================================================================================================
//���������� ������
//====================================================================================================
CFillCell::~CFillCell() 
{
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
void CFillCell::Draw(CDC *pDC,const CRect &cRect_DrawArea)
{ 
 if (pDC==NULL) return;
 CBrush cBrush;
 cBrush.CreateSolidBrush(BackgroundColor);
 pDC->FillRect(&cRect_DrawArea,&cBrush);
 cBrush.DeleteObject();
}
//----------------------------------------------------------------------------------------------------
//������ ���� ����
//----------------------------------------------------------------------------------------------------
void CFillCell::SetBackgroundColor(const COLORREF &color)
{
 BackgroundColor=color;
}
//----------------------------------------------------------------------------------------------------
//�������� ������� ��������
//----------------------------------------------------------------------------------------------------
void CFillCell::GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize)
{
 cSize.cx=0;
 cSize.cy=0;
}