#pragma once
#include "Figure.h"
class Line :
	public Figure
{
public:
	Line(void);
	Line(QPoint s,QPoint e);
	~Line(void);

	void Draw(QPainter &paint);
};

