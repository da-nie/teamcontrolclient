#ifndef CFRAME_CELL_H
#define CFRAME_CELL_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������� ������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include "stdafx.h"
#include "cicell.h"

//====================================================================================================
//����� ������� ������
//====================================================================================================

class CFrameCell:public CICell
{
 protected:
  COLORREF BorderColor;//���� �������
 public:
  //�����������
  CFrameCell(void);
  //����������
  ~CFrameCell();
  //-������� ������----------------------------------------------------------
  void Draw(CDC *pDC,const CRect &cRect_DrawArea) override;//���������
  void GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize) override;//�������� ������� ��������
  void SetBorderColor(const COLORREF &color);//������ ���� �������
};

#endif
