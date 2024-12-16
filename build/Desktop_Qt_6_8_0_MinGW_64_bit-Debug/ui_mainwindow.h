/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *chooseBtn;
    QLineEdit *inputImagePathName;
    QPushButton *InputViewBtn;
    QLabel *inputImage;
    QRadioButton *radioButton_2x;
    QRadioButton *radioButton_4x;
    QLineEdit *outputImagePathName;
    QPushButton *outputChooseBtn;
    QPushButton *outputImageViewBtn;
    QLabel *label;
    QPushButton *generateBtn;
    QPushButton *resetBtn;
    QLabel *errorMessage;
    QPushButton *pushButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(746, 574);
        MainWindow->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    layout: vertical;\n"
"    alignment: AlignHCenter | AlignVCenter;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        chooseBtn = new QPushButton(centralwidget);
        chooseBtn->setObjectName("chooseBtn");
        chooseBtn->setEnabled(true);
        chooseBtn->setGeometry(QRect(410, 90, 41, 31));
        chooseBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        chooseBtn->setMouseTracking(true);
        chooseBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 81, 255);\n"
"	font: 600 12pt \"Segoe UI\";\n"
"	border-radius : 10px;\n"
"	color : white;	\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(0, 0, 255);\n"
"}"));
        inputImagePathName = new QLineEdit(centralwidget);
        inputImagePathName->setObjectName("inputImagePathName");
        inputImagePathName->setGeometry(QRect(20, 90, 381, 31));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputImagePathName->sizePolicy().hasHeightForWidth());
        inputImagePathName->setSizePolicy(sizePolicy);
        inputImagePathName->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	color : white;\n"
"	font: 600 11pt \"Segoe UI\";\n"
"}"));
        InputViewBtn = new QPushButton(centralwidget);
        InputViewBtn->setObjectName("InputViewBtn");
        InputViewBtn->setGeometry(QRect(460, 90, 61, 31));
        InputViewBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        InputViewBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 81, 255);\n"
"	font: 600 12pt \"Segoe UI\";\n"
"	border-radius : 10px;\n"
"	color : white;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(0, 0, 255);\n"
"}"));
        inputImage = new QLabel(centralwidget);
        inputImage->setObjectName("inputImage");
        inputImage->setGeometry(QRect(10, 490, 721, 41));
        inputImage->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        radioButton_2x = new QRadioButton(centralwidget);
        radioButton_2x->setObjectName("radioButton_2x");
        radioButton_2x->setGeometry(QRect(30, 150, 41, 20));
        radioButton_2x->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton_2x->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"	color : white;\n"
"	font: 600 11pt \"Segoe UI\";\n"
"}"));
        radioButton_4x = new QRadioButton(centralwidget);
        radioButton_4x->setObjectName("radioButton_4x");
        radioButton_4x->setGeometry(QRect(80, 150, 41, 20));
        radioButton_4x->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton_4x->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"	color : white;\n"
"	font: 600 11pt \"Segoe UI\";\n"
"}"));
        outputImagePathName = new QLineEdit(centralwidget);
        outputImagePathName->setObjectName("outputImagePathName");
        outputImagePathName->setGeometry(QRect(20, 200, 381, 31));
        outputImagePathName->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	color : white;\n"
"	font: 600 11pt \"Segoe UI\";\n"
"}"));
        outputChooseBtn = new QPushButton(centralwidget);
        outputChooseBtn->setObjectName("outputChooseBtn");
        outputChooseBtn->setGeometry(QRect(410, 200, 41, 31));
        outputChooseBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        outputChooseBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 81, 255);\n"
"	font: 600 12pt \"Segoe UI\";\n"
"	border-radius : 10px;\n"
"	color : white;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(0, 0, 255);\n"
"}"));
        outputImageViewBtn = new QPushButton(centralwidget);
        outputImageViewBtn->setObjectName("outputImageViewBtn");
        outputImageViewBtn->setGeometry(QRect(460, 200, 61, 31));
        outputImageViewBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        outputImageViewBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 81, 255);\n"
"	font: 600 12pt \"Segoe UI\";\n"
"	border-radius : 10px;\n"
"	color : white;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(0, 0, 255);\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 10, 231, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	 background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,\n"
"                                stop: 0 rgb(255, 128, 0),\n"
"                                stop: 1 rgb(255, 255, 0));\n"
"	color : black;\n"
"	font: 700 16pt \"Segoe UI\";\n"
"	border-radius : 8px;\n"
"}"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        generateBtn = new QPushButton(centralwidget);
        generateBtn->setObjectName("generateBtn");
        generateBtn->setGeometry(QRect(20, 260, 101, 41));
        generateBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        generateBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	 background-color: rgb(255, 128, 0);\n"
"	font: 700 12pt \"Segoe UI\";\n"
"	border-radius : 10px;\n"
"	color : white;\n"
"}\n"
"QPushButton:hover{\n"
"	 background-color: rgb(200, 100, 0);\n"
"}"));
        resetBtn = new QPushButton(centralwidget);
        resetBtn->setObjectName("resetBtn");
        resetBtn->setGeometry(QRect(130, 260, 101, 41));
        resetBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        resetBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 81, 255);\n"
"	font: 700 12pt \"Segoe UI\";\n"
"	border-radius : 10px;\n"
"	color : white;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(0, 0, 255);\n"
"}"));
        errorMessage = new QLabel(centralwidget);
        errorMessage->setObjectName("errorMessage");
        errorMessage->setGeometry(QRect(30, 410, 471, 41));
        errorMessage->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	font: 600 14pt \"Segoe UI\";\n"
"}"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(710, 20, 21, 21));
        pushButton->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:white;\n"
"	border-radius : 10px;\n"
"}"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 80, 2, 2));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 746, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Super Resolution Finder", nullptr));
        chooseBtn->setText(QCoreApplication::translate("MainWindow", "....", nullptr));
        inputImagePathName->setText(QString());
        InputViewBtn->setText(QCoreApplication::translate("MainWindow", "View", nullptr));
        inputImage->setText(QString());
        radioButton_2x->setText(QCoreApplication::translate("MainWindow", "2X", nullptr));
        radioButton_4x->setText(QCoreApplication::translate("MainWindow", "4X", nullptr));
        outputChooseBtn->setText(QCoreApplication::translate("MainWindow", "....", nullptr));
        outputImageViewBtn->setText(QCoreApplication::translate("MainWindow", "View", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Super Resolution", nullptr));
        generateBtn->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        resetBtn->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        errorMessage->setText(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
