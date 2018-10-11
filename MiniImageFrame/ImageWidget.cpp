#include "ImageWidget.h"
#include <QImage>
#include <QPainter>
#include <QtWidgets> 
#include <iostream>

using std::cout;
using std::endl;

ImageWidget::ImageWidget(void)
{
	ptr_image_ = new QImage();
	ptr_image_backup_ = new QImage();
	draw_status_=false;
	fun_Stat_=KDEFAULT;
}


ImageWidget::~ImageWidget(void)
{
	delete ptr_image_;							//take care!Remember to delete what you applied.
	ptr_image_=NULL;
	delete ptr_image_backup_;					//delete
	ptr_image_backup_=NULL;
	for(size_t i=0;i<points_pairs_.size();i++)
	{
		if(points_pairs_[i])
		{
			delete points_pairs_[i];
			points_pairs_[i]=NULL;
		}
	}
	points_pairs_.clear();
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
	if(!ptr_image_backup_->isNull())
	{
/*		cout<<"yes1\n";*/
		if(Qt::LeftButton==event->button()&&fun_Stat_==DATA_SAMPLE)
		{
			/*cout<<"yes2\n";*/
// 			cout<<event->pos().x()<<"\n";
// 			cout<<event->pos().y()<<"\n";
// 			cout<<width()<<"\n";
// 			cout<<ptr_image_->width();
			if(event->pos().x()>=(width()-ptr_image_->width())/2&&
				event->pos().x()<=(width()+ptr_image_->width())/2&&
				event->pos().y()>=(height()-ptr_image_->height())/2&&
				event->pos().y()<=(height()+ptr_image_->height())/2)
			{
				/*cout<<"yes3\n";*/
				draw_status_=1;
				start_point_=end_point_=event->pos();
			}
		}
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	end_point_=event->pos();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	Line* current_line_=NULL;
	if(draw_status_)
	{
		if(event->pos().x()>=(width()-ptr_image_->width())/2&&
			event->pos().x()<=(width()+ptr_image_->width())/2&&
			event->pos().y()>=(height()-ptr_image_->height())/2&&
			event->pos().y()<=(height()+ptr_image_->height())/2)
		{
			current_line_=new Line(start_point_,end_point_);
			points_pairs_.push_back(current_line_);
			draw_status_=false;
			current_line_=NULL;
		}
	}
}

void ImageWidget::paintEvent(QPaintEvent *paintevent)
{
	QPainter painter;
	QPen pen;
	painter.begin(this);

	// Draw background
	painter.setBrush(Qt::lightGray);
	QRect back_rect(0, 0, width(), height());
	painter.drawRect(back_rect);

	// Draw image
	QRect rect = QRect( (width()-ptr_image_->width())/2, (height()-ptr_image_->height())/2, ptr_image_->width(), ptr_image_->height());
	painter.drawImage(rect, *ptr_image_); 

	pen.setBrush(Qt::red);
	pen.setWidth(5);
	painter.setPen(pen);
	for(size_t i=0;i<points_pairs_.size();i++)
	{
		points_pairs_[i]->Draw(painter);
	}

	painter.end();

	update();
}

void ImageWidget::Open()
{
	// Open file
	QString fileName = QFileDialog::getOpenFileName(this, tr("Read Image"), ".", tr("Images(*.bmp *.png *.jpg)"));

	// Load file
	if (!fileName.isEmpty())
	{
		ptr_image_->load(fileName);
		*(ptr_image_backup_) = *(ptr_image_);
	}

	//ptr_image_->invertPixels(QImage::InvertRgb);
	//*(ptr_image_) = ptr_image_->mirrored(true, true);
	//*(ptr_image_) = ptr_image_->rgbSwapped();
	cout<<"image size: "<<ptr_image_->width()<<' '<<ptr_image_->height()<<endl;
	cout<<"xmin  "<<(width()-ptr_image_->width())/2<<endl;
	cout<<"xmax  "<<(width()+ptr_image_->width())/2<<endl;
	cout<<"ymin  "<<(height()-ptr_image_->height())/2<<endl;
	cout<<"ymax  "<<(height()+ptr_image_->height())/2<<endl;
	update();
}

void ImageWidget::Save()
{
	SaveAs();
}

void ImageWidget::SaveAs()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Images(*.bmp *.png *.jpg)"));
	if (filename.isNull())
	{
		return;
	}	

	ptr_image_->save(filename);
}

void ImageWidget::Invert()
{
	for (int i=0; i<ptr_image_->width(); i++)
	{
		for (int j=0; j<ptr_image_->height(); j++)
		{
			QRgb color = ptr_image_->pixel(i, j);
			ptr_image_->setPixel(i, j, qRgb(255-qRed(color), 255-qGreen(color), 255-qBlue(color)) );
		}
	}

	// equivalent member function of class QImage
	// ptr_image_->invertPixels(QImage::InvertRgb);
	update();
}

void ImageWidget::Mirror(bool ishorizontal, bool isvertical)
{
	QImage image_tmp(*(ptr_image_));
	int width = ptr_image_->width();
	int height = ptr_image_->height();

	if (ishorizontal)
	{
		if (isvertical)
		{
			for (int i=0; i<width; i++)
			{
				for (int j=0; j<height; j++)
				{
					ptr_image_->setPixel(i, j, image_tmp.pixel(width-1-i, height-1-j));
				}
			}
		} 
		else
		{
			for (int i=0; i<width; i++)
			{
				for (int j=0; j<height; j++)
				{
					ptr_image_->setPixel(i, j, image_tmp.pixel(i, height-1-j));
				}
			}
		}
		
	}
	else
	{
		if (isvertical)
		{
			for (int i=0; i<width; i++)
			{
				for (int j=0; j<height; j++)
				{
					ptr_image_->setPixel(i, j, image_tmp.pixel(width-1-i, j));
				}
			}
		}
	}

	// equivalent member function of class QImage
	//*(ptr_image_) = ptr_image_->mirrored(true, true);
	update();
}

void ImageWidget::TurnGray()
{
	for (int i=0; i<ptr_image_->width(); i++)
	{
		for (int j=0; j<ptr_image_->height(); j++)
		{
			QRgb color = ptr_image_->pixel(i, j);
			int gray_value = (qRed(color)+qGreen(color)+qBlue(color))/3;
			ptr_image_->setPixel(i, j, qRgb(gray_value, gray_value, gray_value) );
		}
	}

	update();
}

void ImageWidget::Restore()			//to be modified
{
	*(ptr_image_) = *(ptr_image_backup_);
	for(size_t i=0;i<points_pairs_.size();i++)
	{
		if(points_pairs_[i])
		{
			delete points_pairs_[i];
			points_pairs_[i]=NULL;
		}
	}
	points_pairs_.clear();
	update();
}

void ImageWidget::PointSample()
{
	fun_Stat_=DATA_SAMPLE;
}

void ImageWidget::generate_Warpped_Image(Function_Status_ stat)
{
	if(!points_pairs_.empty())
	{
		QImage temp((*ptr_image_));
		ImageWarp *image_warp_;
		QRgb val;
		int r=0,g=0,b=0;
		switch(stat)
		{
		case IDWWARP:
			image_warp_=new IDWWarp(points_pairs_,(width()-ptr_image_->width())/2,(height()-ptr_image_->height())/2);
			break;
		case RBFWARP:
			image_warp_=new RBFWarp(points_pairs_,(width()-ptr_image_->width())/2,(height()-ptr_image_->height())/2);
			//to be continued
			break;
		default:
			break;
		}

		int wid=ptr_image_->width();
		int hght=ptr_image_->height();
		int x=0,y=0;
		QPoint warpped;

		temp.fill(Qt::white);
		val=temp.pixel(0,0);

		for(int i=0;i<wid;i++)
		{
			for(int j=0;j<hght;j++)
			{
				warpped=image_warp_->warp_(i,j);
				x=warpped.x();
				y=warpped.y();
				if(x>=0&&
					x<ptr_image_->width()&&
					y>=0&&
					y<ptr_image_->height())
				{
					temp.setPixel(x,y,ptr_image_->pixel(i,j));
				/*	cout<<"cout";*/
				}
			}
		}
		//fill white gaps
		for(int i=0;i<wid;i++)
		{
			for(int j=0;j<hght;j++)
			{
				if(temp.pixel(i,j)==val)
				{
					/*cout<<"cout"<<endl;*/
					temp.setPixel(i,j,mask(i,j,temp));
				}

			}
		}
		(*ptr_image_)=temp;
		delete image_warp_;
		for(size_t i=0;i<points_pairs_.size();i++)
		{
			if(points_pairs_[i])
			{
				delete points_pairs_[i];
				points_pairs_[i]=NULL;
			}
		}
		points_pairs_.clear();
	}
	else
	{
		QMessageBox::about(this,tr("Warning"),tr("Please select points"));
	}

	//to be continued
}
void ImageWidget::IDWWarp_()
{
	fun_Stat_=IDWWARP;
	generate_Warpped_Image(fun_Stat_);
}

void ImageWidget::RBFWarp_()
{
	fun_Stat_=RBFWARP;
	generate_Warpped_Image(fun_Stat_);;
}

QRgb ImageWidget::mask(int i,int j,QImage image_)
{
	int hght;
	int wid;
	int r=0,g=0,b=0;
	QRgb color;
	hght=image_.height();
	wid=image_.width();
	for(int ii=-1;ii<=1;ii++)
	{
		for(int jj=-1;jj<=1;jj++)
		{
			if(jj==0&&ii==0)
			{
				continue;
			}
			else
			{
				color=image_.pixel((i+ii+wid)%wid,(j+jj+hght)%hght);
				r+=qRed(color);
				g+=qGreen(color);
				b+=qBlue(color);
			}
		}
	}
	r/=8;
	g/=8;
	b/=8;
	return qRgb(r,g,b);

}