#pragma once
#ifndef MINIIMAGEFRAME_H
#define MINIIMAGEFRAME_H


#include <QtWidgets/QMainWindow>
#include "ui_MiniImageFrame.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class ViewWidget;
class QImage;
class QPainter;
class QRect;
class ImageWidget;
QT_END_NAMESPACE

class MiniImageFrame : public QMainWindow
{
	Q_OBJECT

public:
	MiniImageFrame(QWidget *parent = 0);
	~MiniImageFrame();

protected:
	void closeEvent(QCloseEvent *e);
	void paintEvent(QPaintEvent *paintevent);

	private slots:

private:
	void CreateActions();
	void CreateMenus();
	void CreateToolBars();
	void CreateStatusBar();


private:
	Ui::MiniImageFrameClass ui;

	QMenu		*menu_file_;
	QMenu		*menu_edit_;
	QMenu		*menu_help_;
	QToolBar	*toolbar_file_;
	QToolBar	*toolbar_edit_;
	QAction		*action_new_;
	QAction		*action_open_;
	QAction		*action_save_;
	QAction		*action_saveas_;
	QAction		*action_invert_;
	QAction		*action_mirror_;
	QAction		*action_gray_;
	QAction		*action_restore_;
	QAction		*action_datasample_;
	QAction		*action_idw_;
	QAction		*action_rbf_;

	ImageWidget		*imagewidget_;
};

#endif