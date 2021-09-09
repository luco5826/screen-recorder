/********************************************************************************
** Form generated from reading UI file 'MainView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace MW_UI {

class Ui_MainView
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QLabel *label;
    QLabel *recordingTime;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MW_UI__MainView)
    {
        if (MW_UI__MainView->objectName().isEmpty())
            MW_UI__MainView->setObjectName(QString::fromUtf8("MW_UI__MainView"));
        MW_UI__MainView->resize(400, 300);
        centralwidget = new QWidget(MW_UI__MainView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(500, 210, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 30, 181, 191));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(verticalLayoutWidget_2);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout_2->addWidget(startButton);

        pauseButton = new QPushButton(verticalLayoutWidget_2);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        verticalLayout_2->addWidget(pauseButton);

        stopButton = new QPushButton(verticalLayoutWidget_2);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout_2->addWidget(stopButton);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 200, 58, 18));
        recordingTime = new QLabel(centralwidget);
        recordingTime->setObjectName(QString::fromUtf8("recordingTime"));
        recordingTime->setGeometry(QRect(280, 200, 58, 18));
        MW_UI__MainView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MW_UI__MainView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 30));
        MW_UI__MainView->setMenuBar(menubar);
        statusbar = new QStatusBar(MW_UI__MainView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MW_UI__MainView->setStatusBar(statusbar);

        retranslateUi(MW_UI__MainView);

        QMetaObject::connectSlotsByName(MW_UI__MainView);
    } // setupUi

    void retranslateUi(QMainWindow *MW_UI__MainView)
    {
        MW_UI__MainView->setWindowTitle(QCoreApplication::translate("MW_UI::MainView", "Recorder", nullptr));
        startButton->setText(QCoreApplication::translate("MW_UI::MainView", "Start", nullptr));
        pauseButton->setText(QCoreApplication::translate("MW_UI::MainView", "Pause", nullptr));
        stopButton->setText(QCoreApplication::translate("MW_UI::MainView", "Stop", nullptr));
        label->setText(QCoreApplication::translate("MW_UI::MainView", "Time:", nullptr));
        recordingTime->setText(QCoreApplication::translate("MW_UI::MainView", "0", nullptr));
    } // retranslateUi

};

} // namespace MW_UI

namespace MW_UI {
namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui
} // namespace MW_UI

#endif // UI_MAINVIEW_H
