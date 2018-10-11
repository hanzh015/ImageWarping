#pragma once
#include <QWidget>
//#include <vector>
//#include "Line.h"

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
QT_END_NAMESPACE

class ImageWidget :
	public QWidget
{
	Q_OBJECT

public:
	ImageWidget(void);
	~ImageWidget(void);

//	void mousePressEvent(QMouseEvent *event);
//	void mouseMoveEvent(QMouseEvent *event);
//	void mouseReleaseEvent(QMouseEvent *event);
//	enum Function_Status_
//	{
//		KDEFAULT=0,
//		DATA_SAMPLE=1,
//		IDWWARP=2,
//		RBFWARP=3,
//	};

protected:
	void paintEvent(QPaintEvent *paintevent);

public slots:
	// File IO
	void Open();												// Open an image file, support ".bmp, .png, .jpg" format
	void Save();												// Save image to current file
	void SaveAs();												// Save image to another file

	// Image processing
	void Invert();												// Invert pixel value in image
	void Mirror(bool horizontal=false, bool vertical=true);		// Mirror image vertically or horizontally
	void TurnGray();											// Turn image to gray-scale map
	void Restore();												// Restore image to origin (need to be updated)
//	void PointSample();											// Sample points unchanged
//	void IDWWarp();												// Warp points using IDW method;
//	void RBFWarp();												// Warp points using RBF method;

private:
	QImage		*ptr_image_;				// image 
	QImage		*ptr_image_backup_;

//	QPoint		start_point_;				//Drawing related arguments
//	QPoint		end_point_;	
	bool		draw_status_;
//	std::vector <Line*> points_pairs_;

//	Function_Status_ fun_Stat_; 

}