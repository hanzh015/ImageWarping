#include "ImageWarp.h"

ImageWarp::ImageWarp(void)
{

}

ImageWarp::ImageWarp(vector <Line*> datasample,int offset_x,int offset_y)
{
	Line *current_line_;
	int coord_x,coord_y;
	offset_x_=offset_x;
	offset_y_=offset_y;
	for(size_t i=0;i<datasample.size();i++)
	{
		current_line_=new Line();
		(*current_line_)=(*datasample[i]);
		coord_x=(*current_line_).getStartPoint().x();
		coord_y=(*current_line_).getStartPoint().y();
		(*current_line_).setStartPoint(coord_x-offset_x_,coord_y-offset_y_);
		coord_x=(*current_line_).getEndPoint().x();
		coord_y=(*current_line_).getEndPoint().y();
		(*current_line_).setEndPoint(coord_x-offset_x_,coord_y-offset_y_);

		points.push_back(current_line_);
		current_line_=NULL;
	}
}

vector <Line*> ImageWarp::getPoints()
{
	return points;
}


ImageWarp::~ImageWarp(void)
{
}
