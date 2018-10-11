#pragma once
#include "ImageWarp.h"
#include <Eigen/Dense>

using namespace Eigen;

class IDWWarp :
	public ImageWarp
{
public:
	IDWWarp(void);
	IDWWarp(vector <Line*> point,int offsx,int offsy);
	~IDWWarp(void);

	QPoint warp_(int x,int y);

private:
	double inverse_distance_(int xi,int yi,int x0,int y0);
	double wi_func_(int x,int y,int i);
	vector <Matrix2f*> t_vectors;
	Vector2f fi_func_(Vector2f ini,int i);
};

