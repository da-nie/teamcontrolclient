#ifndef CTEXT_CELL_H
#define CTEXT_CELL_H

//====================================================================================================
//описание
//====================================================================================================

// ласс €чейки с текстом

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include "stdafx.h"
#include "cicell.h"

//====================================================================================================
//класс €чейки с текстом
//====================================================================================================

class CTextCell:public CICell
{
 protected:
  COLORREF TextColor;//цвет текста
  CFont cFont_Text;//шрифт текста  
  CSafeString Text;//выводимый текст

  COLORREF StrikeOutColor;//текст зачЄркивани€

  long MinLineWidth;//минимальный размер строки
  long TextHeightOffset;//отступ текста от вертикальных границ
  long TextWidthOffset;//отступ текста от горизонтальных границ

  bool StrikeOut;//зачеркнуть ли текст
 public:
  //конструктор
  CTextCell(void);
  //деструктор
  ~CTextCell();
  //функции класса
  void Draw(CDC *pDC,const CRect &cRect_DrawArea) override;//отрисовка
  void GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize) override;//получить размеры элемента
  void SetText(const CSafeString &text);//задать текст
  void SetTextColor(const COLORREF &color);//задать цвет текста
  void SetStrikeOutColor(const COLORREF &color);//задать цвет зачЄркивани€
  void SetTextFont(const LOGFONT &lf);//задать шрифт текста
  void SetStrikeOut(const bool &state);//задать зачЄркивание текста
 protected:
  //функции класса
  void OutText(CDC *pDC,const CRect &cRect_DrawArea,CRect &cRect_Cell,const bool &draw);//вывести текст с разбиением на строки
};

#endif
