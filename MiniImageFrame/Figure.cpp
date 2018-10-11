#include "Figure.h"


Figure::Figure(void)
{

}

Figure::Figure(QPoint s,QPoint e)
{
	start_point=s;
	end_point=e;
}


Figure::~Figure(void)
{
}

QPoint Figure::getStartPoint()
{
	return start_point;
}

QPoint Figure::getEndPoint()
{
	return end_point;
}

void Figure::setStartPoint(int x,int y)
{
	start_point.rx()=x;
	start_point.ry()=y;
}

void Figure::setEndPoint(int x,int y)
{
	end_point.rx()=x;
	end_point.ry()=y;
}