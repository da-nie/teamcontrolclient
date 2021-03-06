#include "cframecell.h"

//====================================================================================================
//����������� ������
//====================================================================================================
CFrameCell::CFrameCell(void)
{ 
 BorderColor=RGB(0,0,0);
}
//====================================================================================================
//���������� ������
//====================================================================================================
CFrameCell::~CFrameCell() 
{
}
//====================================================================================================
//������� ������
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------------------------------
void CFrameCell::Draw(CDC *pDC,const CRect &cRect_DrawArea)
{ 
 if (pDC==NULL) return;
 CPen cPen;
 CPen *cPen_Old_Ptr;
 cPen.CreatePen(PS_SOLID,1,BorderColor);
 cPen_Old_Ptr=pDC->SelectObject(&cPen);
 pDC->MoveTo(CPoint(cRect_DrawArea.left,cRect_DrawArea.top));
 pDC->LineTo(cRect_DrawArea.right,cRect_DrawArea.top);
 pDC->LineTo(cRect_DrawArea.right,cRect_DrawArea.bottom);
 pDC->LineTo(cRect_DrawArea.left,cRect_DrawArea.bottom);
 cPen_Old_Ptr=pDC->SelectObject(cPen_Old_Ptr);
}
//----------------------------------------------------------------------------------------------------
//�������� ������� ��������
//----------------------------------------------------------------------------------------------------
void CFrameCell::GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize)
{
 cSize.cx=0;
 cSize.cy=0;
}
//----------------------------------------------------------------------------------------------------
//������ ���� �������
//----------------------------------------------------------------------------------------------------
void CFrameCell::SetBorderColor(const COLORREF &color)
{
 BorderColor=color;
}
