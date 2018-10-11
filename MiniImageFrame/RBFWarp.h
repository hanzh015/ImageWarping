#pragma once
#include "ImageWarp.h"
#include <Eigen/Dense>

#define MIU 25

using namespace Eigen;
class RBFWarp :
	public ImageWarp
{
public:
	RBFWarp(void);
	RBFWarp(vector <Line*> point,int offsx,int offsy);

	~RBFWarp(void);

	QPoint warp_(int x,int y);


private:
	double distance_square_(int xi,int yi,int x0,int y0);
	MatrixXf coefficients;

};

