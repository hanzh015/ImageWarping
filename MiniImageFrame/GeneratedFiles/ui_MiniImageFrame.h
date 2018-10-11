/********************************************************************************
** Form generated from reading UI file 'MiniImageFrame.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIIMAGEFRAME_H
#define UI_MINIIMAGEFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniImageFrameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniImageFrameClass)
    {
        if (MiniImageFrameClass->objectName().isEmpty())
            MiniImageFrameClass->setObjectName(QStringLiteral("MiniImageFrameClass"));
        MiniImageFrameClass->resize(600, 400);
        menuBar = new QMenuBar(MiniImageFrameClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MiniImageFrameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MiniImageFrameClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MiniImageFrameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MiniImageFrameClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MiniImageFrameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MiniImageFrameClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniImageFrameClass->setStatusBar(statusBar);

        retranslateUi(MiniImageFrameClass);

        QMetaObject::connectSlotsByName(MiniImageFrameClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniImageFrameClass)
    {
        MiniImageFrameClass->setWindowTitle(QApplication::translate("MiniImageFrameClass", "MiniImageFrame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MiniImageFrameClass: public Ui_MiniImageFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIIMAGEFRAME_H
