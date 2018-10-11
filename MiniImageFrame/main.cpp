#include "MiniImageFrame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MiniImageFrame w;
	w.show();
	return a.exec();
}
