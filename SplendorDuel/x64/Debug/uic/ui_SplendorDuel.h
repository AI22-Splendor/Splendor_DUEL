/********************************************************************************
** Form generated from reading UI file 'SplendorDuel.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLENDORDUEL_H
#define UI_SPLENDORDUEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SplendorDuelClass
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SplendorDuelClass)
    {
        if (SplendorDuelClass->objectName().isEmpty())
            SplendorDuelClass->setObjectName("SplendorDuelClass");
        SplendorDuelClass->resize(600, 400);
        centralWidget = new QWidget(SplendorDuelClass);
        centralWidget->setObjectName("centralWidget");
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(240, 80, 104, 71));
        SplendorDuelClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SplendorDuelClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        SplendorDuelClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SplendorDuelClass);
        mainToolBar->setObjectName("mainToolBar");
        SplendorDuelClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SplendorDuelClass);
        statusBar->setObjectName("statusBar");
        SplendorDuelClass->setStatusBar(statusBar);

        retranslateUi(SplendorDuelClass);

        QMetaObject::connectSlotsByName(SplendorDuelClass);
    } // setupUi

    void retranslateUi(QMainWindow *SplendorDuelClass)
    {
        SplendorDuelClass->setWindowTitle(QCoreApplication::translate("SplendorDuelClass", "SplendorDuel", nullptr));
        textEdit->setHtml(QCoreApplication::translate("SplendorDuelClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">TEST</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SplendorDuelClass: public Ui_SplendorDuelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLENDORDUEL_H
