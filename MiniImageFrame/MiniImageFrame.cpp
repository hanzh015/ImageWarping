#include "MiniImageFrame.h"
#include <QtWidgets>
#include <QImage>
#include <QPainter>
#include "ImageWidget.h"

MiniImageFrame::MiniImageFrame(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setGeometry(300, 150, 800, 450);

	imagewidget_ = new ImageWidget();
	setCentralWidget(imagewidget_);


	CreateActions();
	CreateMenus();
	CreateToolBars();
	CreateStatusBar();
}

MiniImageFrame::~MiniImageFrame()
{

}

void MiniImageFrame::paintEvent(QPaintEvent* paintevent)
{

}

void MiniImageFrame::closeEvent(QCloseEvent *e)
{

}

void MiniImageFrame::CreateActions()
{
	action_new_ = new QAction(QIcon(":/MiniImageFrame/Resources/images/new.png"), tr("&New"), this);
	action_new_->setShortcut(QKeySequence::New);
	action_new_->setStatusTip(tr("Create a new file"));

	action_open_ = new QAction(QIcon(":/MiniImageFrame/Resources/images/open.png"), tr("&Open..."), this);
	action_open_->setShortcuts(QKeySequence::Open);
	action_open_->setStatusTip(tr("Open an existing file"));
	connect(action_open_, SIGNAL(triggered()), imagewidget_, SLOT(Open()));

	action_save_ = new QAction(QIcon(":/MiniImageFrame/Resources/images/save.png"), tr("&Save"), this);
	action_save_->setShortcuts(QKeySequence::Save);
	action_save_->setStatusTip(tr("Save the document to disk"));

	action_saveas_ = new QAction(tr("Save &As..."), this);
	action_saveas_->setShortcuts(QKeySequence::SaveAs);
	action_saveas_->setStatusTip(tr("Save the document under a new name"));
	connect(action_saveas_, SIGNAL(triggered()), imagewidget_, SLOT(SaveAs()));

	action_invert_ = new QAction(tr("Inverse"), this);
	action_invert_->setStatusTip(tr("Invert all pixel value in the image"));
	connect(action_invert_, SIGNAL(triggered()), imagewidget_, SLOT(Invert()));

	action_mirror_ = new QAction(tr("Mirror"), this);
	action_mirror_->setStatusTip(tr("Mirror image vertically or horizontally"));
	connect(action_mirror_, SIGNAL(triggered()), imagewidget_, SLOT(Mirror()));

	action_gray_ = new QAction(tr("Grayscale"), this);
	action_gray_->setStatusTip(tr("Gray-scale map"));
	connect(action_gray_, SIGNAL(triggered()), imagewidget_, SLOT(TurnGray()));

	action_datasample_ = new QAction(tr("DataSample"), this);			//datasample
	action_datasample_->setStatusTip(tr("Click and drag your mouse to create several pairs of points for interpolation."));
	connect(action_datasample_, SIGNAL(triggered()), imagewidget_, SLOT(PointSample()));

	action_idw_ = new QAction(tr("IDW"), this);
	action_idw_->setStatusTip(tr("Use IDW method."));
	connect(action_idw_, SIGNAL(triggered()), imagewidget_, SLOT(IDWWarp_()));

	action_rbf_ = new QAction(tr("RBF"), this);
	action_rbf_->setStatusTip(tr("Use RBF method."));
	connect(action_rbf_, SIGNAL(triggered()), imagewidget_, SLOT(RBFWarp_()));

	action_restore_ = new QAction(tr("Restore"), this);
	action_restore_->setStatusTip(tr("Show origin image"));
	connect(action_restore_, SIGNAL(triggered()), imagewidget_, SLOT(Restore()));
}

void MiniImageFrame::CreateMenus()
{
	menu_file_ = menuBar()->addMenu(tr("&File"));
	menu_file_->setStatusTip(tr("File menu"));
	menu_file_->addAction(action_new_);
	menu_file_->addAction(action_open_);
	menu_file_->addAction(action_save_);
	menu_file_->addAction(action_saveas_);

	menu_edit_ = menuBar()->addMenu(tr("&Edit"));
	menu_edit_->setStatusTip(tr("Edit menu"));
	menu_edit_->addAction(action_invert_);
	menu_edit_->addAction(action_mirror_);
	menu_edit_->addAction(action_gray_);
	menu_edit_->addAction(action_datasample_);
	menu_edit_->addAction(action_idw_);
	menu_edit_->addAction(action_rbf_);
	menu_edit_->addAction(action_restore_);
}

void MiniImageFrame::CreateToolBars()
{
	toolbar_file_ = addToolBar(tr("File"));
	toolbar_file_->addAction(action_new_);
	toolbar_file_->addAction(action_open_);
	toolbar_file_->addAction(action_save_);

	// Add separator in toolbar 
	toolbar_file_->addSeparator();
	toolbar_file_->addAction(action_invert_);
	toolbar_file_->addAction(action_mirror_);
	toolbar_file_->addAction(action_gray_);
	toolbar_file_->addAction(action_datasample_);
	toolbar_file_->addAction(action_idw_);
	toolbar_file_->addAction(action_rbf_);
	toolbar_file_->addAction(action_restore_);
}

void MiniImageFrame::CreateStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}