#include "IDWWarp.h"


IDWWarp::IDWWarp(void)
{
}

IDWWarp::IDWWarp(vector<Line*> point,int offsx,int offsy):ImageWarp(point,offsx,offsy)
{
	//we need to contruct T-matrice
	Matrix2f *t_vec_;
	Vector4f temp_sol;
	VectorXf q_vec;
	MatrixXf equations_;
	double sigma;
	int indicator;
	//calculate t_vectors
	if(point.size()==1)
	{
		//only one point
		t_vec_=new Matrix2f();
		(*t_vec_)<<1,0,0,1;
		t_vectors.push_back(t_vec_);
		t_vec_=NULL;
	}
	else if(point.size()==2)
	{
		//two points,let's set them diagonal
		temp_sol(0)=(point[1]->getEndPoint().x()-point[0]->getEndPoint().x())/
			(point[1]->getStartPoint().x()-point[0]->getStartPoint().x()+0.1-0.1);
		temp_sol(1)=(point[1]->getEndPoint().y()-point[0]->getEndPoint().y())/
			(point[1]->getStartPoint().y()-point[0]->getStartPoint().y()+0.1-0.1);
		for(size_t i=0;i<point.size();i++)
		{
			t_vec_=new Matrix2f();
			(*t_vec_)<<temp_sol(0),0,0,temp_sol(1);
			t_vectors.push_back(t_vec_);
			t_vec_=NULL;
		}
	}
	else if(point.size()==3)
	{
		//three points,enough to solve 4 by 4 linear equations
		q_vec.resize(4);
		q_vec(0)=point[1]->getEndPoint().x()-point[0]->getEndPoint().x();
		q_vec(1)=point[1]->getEndPoint().y()-point[0]->getEndPoint().y();
		q_vec(2)=point[2]->getEndPoint().x()-point[0]->getEndPoint().x();
		q_vec(3)=point[2]->getEndPoint().y()-point[0]->getEndPoint().y();
		equations_.resize(4,4);
		for(size_t i=0;i<point.size()-1;i++)
		{
			equations_.row(2*i)<<point[i+1]->getStartPoint().x()-point[0]->getStartPoint().x(),
				point[i+1]->getStartPoint().y()-point[0]->getStartPoint().y(),0,0;
			equations_.row(2*i+1)<<0,0,point[i+1]->getStartPoint().x()-point[0]->getStartPoint().x(),
				point[i+1]->getStartPoint().y()-point[0]->getStartPoint().y();
		}
		temp_sol=equations_.colPivHouseholderQr().solve(q_vec);
		for(size_t i=0;i<point.size();i++)
		{
			t_vec_=new Matrix2f();
			(*t_vec_).row(0)=temp_sol.block<2,1>(0,0);
			(*t_vec_).row(1)=temp_sol.block<2,1>(2,0);
			t_vectors.push_back(t_vec_);
			t_vec_=NULL;
		}
	}
	else
	{
		//more than three points,solve linear least square system
		equations_.resize((point.size()-1)*2,4);
		q_vec.resize((point.size()-1)*2);
		for(size_t i=0;i<point.size();i++)
		{
			for(size_t j=0;j<point.size();j++)
			{
				if(j==i)
				{
					continue;
				}
				else
				{
					if(j>i)
					{
						indicator=j-1;
					}
					else
					{
						indicator=j;
					}
					sigma=sqrt(inverse_distance_(point[i]->getStartPoint().x(),point[i]->getStartPoint().y(),
						point[j]->getStartPoint().x(),point[j]->getStartPoint().y()));//please check function sqrt
					equations_.row(2*indicator)<<sigma*(point[j]->getStartPoint().x()-point[i]->getStartPoint().x()),
						sigma*(point[j]->getStartPoint().y()-point[i]->getStartPoint().y()),0,0;
					equations_.row(2*indicator+1)<<0,0,sigma*(point[j]->getStartPoint().x()-point[i]->getStartPoint().x()),
						sigma*(point[j]->getStartPoint().y()-point[i]->getStartPoint().y());
					q_vec(2*indicator)=sigma*(point[j]->getEndPoint().x()-point[i]->getEndPoint().x());
					q_vec(2*indicator+1)=sigma*(point[j]->getEndPoint().y()-point[i]->getEndPoint().y());
				}
			}
// 			cout<<"equation_="<<endl<<equations_<<endl;
// 			cout<<"q_vec"<<endl<<q_vec<<endl;

			temp_sol=equations_.jacobiSvd(ComputeThinU|ComputeThinV).solve(q_vec);
		/*	cout<<"tmatrix_i="<<endl<<temp_sol<<endl;*/
			t_vec_=new Matrix2f();
			(*t_vec_).row(0)=temp_sol.block<2,1>(0,0);
			(*t_vec_).row(1)=temp_sol.block<2,1>(2,0);
			t_vectors.push_back(t_vec_);
			t_vec_=NULL;
		}
	}
// 	for(size_t i=0;i<t_vectors.size();i++)
// 	{
// 		cout<<(*t_vectors[i])<<endl<<endl;
// 	}
}


IDWWarp::~IDWWarp(void)
{
	//two variables to delete
	//1.points--the vector of Line instances
	//2.t-vectors
	for(size_t i=0;i<getPoints().size();i++)
	{
		if(getPoints()[i])
		{
			delete getPoints()[i];
			getPoints()[i]=NULL;
		}
	}
	for(size_t j=0;j<t_vectors.size();j++)
	{
		if(t_vectors[j])
		{
			delete t_vectors[j];
			t_vectors[j]=NULL;
		}
	}
}

QPoint IDWWarp::warp_(int x,int y)
{
	QPoint idw_;
	int x_=0,y_=0;
	Vector2f ans;
	Vector2f p;
	ans<<0,0;
	p<<x,y;
	for(size_t i=0;i<getPoints().size();i++)
	{
		if(x==getPoints()[i]->getStartPoint().x()&&
			y==getPoints()[i]->getStartPoint().y())
		{
			ans(0)=getPoints()[i]->getEndPoint().x();
			ans(1)=getPoints()[i]->getEndPoint().y();
			break;
		}
		else
		{
// 			x_+=wi_func_(x,y,i)*fi_func_x(x,i);
// 			y_+=wi_func_(x,y,i)*fi_func_y(y,i);
			ans+=wi_func_(x,y,i)*fi_func_(p,i);
		}
	}
	idw_.rx()=ans(0);
	idw_.ry()=ans(1);
	return idw_;
}

double IDWWarp::inverse_distance_(int xi,int yi,int x0,int y0)
{
	if(xi==x0&&yi==y0)
	{
		cout<<"Warning:invalid input, zero divider"<<endl<<xi<<endl<<yi<<endl;
		return -1;
	}
	else
	{
		return 1.0/((xi-x0)*(xi-x0)+(yi-y0)*(yi-y0));
	}
}

double IDWWarp::wi_func_(int x,int y,int i)
{
	double sum=0;
	double x_,y_;
	for(size_t j=0;j<getPoints().size();j++)
	{
		if(x==getPoints()[j]->getStartPoint().x()&&y==getPoints()[j]->getStartPoint().y())
		{
			if(j==i)
			{
				return 1;
			}
			else
				return 0;
		}
		else
		{
			x_=getPoints()[j]->getStartPoint().x();
			y_=getPoints()[j]->getStartPoint().y();
			sum+=inverse_distance_(x_,y_,x,y);
		}
	}
	x_=getPoints()[i]->getStartPoint().x();
	y_=getPoints()[i]->getStartPoint().y();
	return (inverse_distance_(x_,y_,x,y))/sum;
}

Vector2f IDWWarp::fi_func_(Vector2f ini,int i)
{
	Vector2f qi;
	Vector2f pi;
	if(i>=0&&i<getPoints().size())
	{
		qi(0)=getPoints()[i]->getEndPoint().x();
		qi(1)=getPoints()[i]->getEndPoint().y();
		pi(0)=getPoints()[i]->getStartPoint().x();
		pi(1)=getPoints()[i]->getStartPoint().y();
		return qi+(*t_vectors[i])*(ini-pi);
	}
	else
	{
		cout<<"warning,invalid input"<<endl;
		return ini;
	}
}