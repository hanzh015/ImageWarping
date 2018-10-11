#include "Line.h"


Line::Line(void)
{

}

Line::Line(QPoint s,QPoint e):Figure(s,e)
{
}


Line::~Line(void)
{
}

void Line::Draw(QPainter &paint)
{
	paint.drawLine(start_point,end_point);
}