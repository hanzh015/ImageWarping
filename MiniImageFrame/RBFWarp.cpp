#include "RBFWarp.h"


RBFWarp::RBFWarp(void)
{
}

RBFWarp::RBFWarp(vector <Line*> point,int offsx,int offsy):ImageWarp(point,offsx,offsy)
{
	//We assume the affine part is identical
	//using Guassians as basis functions
	MatrixXf equations_;
	VectorXf temp_sol;
	VectorXf q_vec_x;
	VectorXf q_vec_y;
	int xi,yi,xj,yj;
	

	equations_.resize(point.size(),point.size());
	temp_sol.resize(point.size());
	q_vec_x.resize(point.size());
	q_vec_y.resize(point.size());
	coefficients.resize(2,point.size());

	//1.construct coefficient matrix
	for(size_t i=0;i<point.size();i++)
	{
		xi=point[i]->getStartPoint().x();
		yi=point[i]->getStartPoint().y();
		for(size_t j=0;j<point.size();j++)
		{
			xj=point[j]->getStartPoint().x();
			yj=point[j]->getStartPoint().y();
			equations_(i,j)=exp(-distance_square_(xi,yi,xj,yj)/(MIU*MIU));
		}
		q_vec_x(i)=point[i]->getEndPoint().x()-xi;
		q_vec_y(i)=point[i]->getEndPoint().y()-yi;
	}
	//2.extract x and y coefficients by solving linear equations
	temp_sol=equations_.colPivHouseholderQr().solve(q_vec_x);
	coefficients.row(0)=temp_sol;
	temp_sol=equations_.colPivHouseholderQr().solve(q_vec_y);
	coefficients.row(1)=temp_sol;


}


RBFWarp::~RBFWarp(void)
{
	for(size_t i=0;i<getPoints().size();i++)
	{
		if(getPoints()[i])
		{
			delete getPoints()[i];
			getPoints()[i]=NULL;
		}
	}
}

QPoint RBFWarp::warp_(int x,int y)
{
	QPoint warpped;
	Vector2f initial;
	Vector2f final;
	MatrixXf dis;
	int xi,yi;

	dis.resize(getPoints().size(),1);
	initial<<x,y;
	for(size_t i=0;i<getPoints().size();i++)
	{
		xi=getPoints()[i]->getStartPoint().x();
		yi=getPoints()[i]->getStartPoint().y();
		dis(i,0)=exp(-distance_square_(x,y,xi,yi)/(MIU*MIU));
	}

	final=coefficients*dis+initial;
	warpped.rx()=final(0);
	warpped.ry()=final(1);

	return warpped;

}

double RBFWarp::distance_square_(int xi,int yi,int x0,int y0)
{
	return (xi-x0)*(xi-x0)+(yi-y0)*(yi-y0);
}