#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MiniImageFrame.h"

class MiniImageFrame : public QMainWindow
{
	Q_OBJECT

public:
	MiniImageFrame(QWidget *parent = Q_NULLPTR);

private:
	Ui::MiniImageFrameClass ui;
};
