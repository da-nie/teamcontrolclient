#ifndef CLINE_TEXT_CELL_H
#define CLINE_TEXT_CELL_H

//====================================================================================================
//��������
//====================================================================================================

//����� ������ � ������� � ���� ������

//====================================================================================================
//������������ ����������
//====================================================================================================

#include "stdafx.h"
#include "cicell.h"

//====================================================================================================
//����� ������ � ������� � ���� ������
//====================================================================================================

class CLineTextCell:public CICell
{
 protected:
  COLORREF TextColor;//���� ������
  CFont cFont_Text;//����� ������  
  CSafeString Text;//��������� �����

  COLORREF StrikeOutColor;//����� ������������
  bool StrikeOut;//���������� �� �����
 public:
  //�����������
  CLineTextCell(void);
  //����������
  ~CLineTextCell();
  //������� ������
  void Draw(CDC *pDC,const CRect &cRect_DrawArea);//���������
  void GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize);//�������� ������� ��������
  void SetText(const CSafeString &text);//������ �����
  void SetTextColor(const COLORREF &color);//������ ���� ������
  void SetStrikeOutColor(const COLORREF &color);//������ ���� ������������
  void SetTextFont(const LOGFONT &lf);//������ ����� ������
  void SetStrikeOut(const bool &state);//������ ������������ ������
 protected:
  //������� ������
  void OutText(CDC *pDC,const CRect &cRect_DrawArea,CRect &cRect_Cell,const bool &draw);//������� ����� � ���� ������
};

#endif
