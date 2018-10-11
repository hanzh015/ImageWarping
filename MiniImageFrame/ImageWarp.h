#pragma once

#include "Line.h"
#include <iostream>
#include "qpoint.h"

using namespace std;
class ImageWarp
{
public:
	ImageWarp(void);
	ImageWarp(vector <Line*> datasample,int offset_x,int offset_y);
	vector <Line*> getPoints();
	virtual ~ImageWarp(void);
	virtual QPoint warp_(int x,int y)=0;

private:
	vector <Line*> points;
	int offset_x_;
	int offset_y_;
};

