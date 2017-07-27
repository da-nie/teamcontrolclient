#ifndef CFILL_CELL_H
#define CFILL_CELL_H

//====================================================================================================
//��������
//====================================================================================================

//����� ����������� ������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include "stdafx.h"
#include "cicell.h"

//====================================================================================================
//����� ����������� ������
//====================================================================================================

class CFillCell:public CICell
{
 protected:
  COLORREF BackgroundColor;//���� ����
 public:
  //�����������
  CFillCell(void);
  //����������
  ~CFillCell();
  //-������� ������----------------------------------------------------------
  void Draw(CDC *pDC,const CRect &cRect_DrawArea);//���������
  void GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize);//�������� ������� ��������
  void SetBackgroundColor(const COLORREF &color);//������ ���� ����
};

#endif
