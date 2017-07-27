#ifndef CTEXT_CELL_H
#define CTEXT_CELL_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������ � �������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include "stdafx.h"
#include "cicell.h"

//====================================================================================================
//����� ������ � �������
//====================================================================================================

class CTextCell:public CICell
{
 protected:
  COLORREF TextColor;//���� ������
  CFont cFont_Text;//����� ������  
  CString Text;//��������� �����

  COLORREF StrikeOutColor;//����� ������������

  long MinLineWidth;//����������� ������ ������
  long TextHeightOffset;//������ ������ �� ������������ ������
  long TextWidthOffset;//������ ������ �� �������������� ������

  bool StrikeOut;//���������� �� �����
 public:
  //�����������
  CTextCell(void);
  //����������
  ~CTextCell();
  //������� ������
  void Draw(CDC *pDC,const CRect &cRect_DrawArea);//���������
  void GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize);//�������� ������� ��������
  void SetText(const CString &text);//������ �����
  void SetTextColor(const COLORREF &color);//������ ���� ������
  void SetStrikeOutColor(const COLORREF &color);//������ ���� ������������
  void SetTextFont(const LOGFONT &lf);//������ ����� ������
  void SetStrikeOut(const bool &state);//������ ������������ ������
 protected:
  //������� ������
  void OutText(CDC *pDC,const CRect &cRect_DrawArea,CRect &cRect_Cell,const bool &draw);//������� ����� � ���������� �� ������
};

#endif
