#pragma once
#include <QtGui>

class Figure
{
public:
	Figure(void);
	Figure(QPoint s, QPoint e);
	virtual ~Figure(void);
	QPoint getStartPoint();
	void setStartPoint(int x, int y);
	QPoint getEndPoint();
	void setEndPoint(int x,int y);

	virtual void Draw(QPainter &paint)=0;

protected:
	QPoint start_point;
	QPoint end_point;
};

