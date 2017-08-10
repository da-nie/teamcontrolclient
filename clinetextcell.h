#ifndef CLINE_TEXT_CELL_H
#define CLINE_TEXT_CELL_H

//====================================================================================================
//описание
//====================================================================================================

// ласс €чейки с текстом в одну строку

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include "stdafx.h"
#include "cicell.h"

//====================================================================================================
//класс €чейки с текстом в одну строку
//====================================================================================================

class CLineTextCell:public CICell
{
 protected:
  COLORREF TextColor;//цвет текста
  CFont cFont_Text;//шрифт текста  
  CSafeString Text;//выводимый текст

  COLORREF StrikeOutColor;//текст зачЄркивани€
  bool StrikeOut;//зачеркнуть ли текст
 public:
  //конструктор
  CLineTextCell(void);
  //деструктор
  ~CLineTextCell();
  //функции класса
  void Draw(CDC *pDC,const CRect &cRect_DrawArea);//отрисовка
  void GetSize(CDC *pDC,const CRect &cRect_DrawArea,CSize &cSize);//получить размеры элемента
  void SetText(const CSafeString &text);//задать текст
  void SetTextColor(const COLORREF &color);//задать цвет текста
  void SetStrikeOutColor(const COLORREF &color);//задать цвет зачЄркивани€
  void SetTextFont(const LOGFONT &lf);//задать шрифт текста
  void SetStrikeOut(const bool &state);//задать зачЄркивание текста
 protected:
  //функции класса
  void OutText(CDC *pDC,const CRect &cRect_DrawArea,CRect &cRect_Cell,const bool &draw);//вывести текст в одну строку
};

#endif
