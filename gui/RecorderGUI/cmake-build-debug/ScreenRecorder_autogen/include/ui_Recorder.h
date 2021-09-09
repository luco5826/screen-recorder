/********************************************************************************
** Form generated from reading UI file 'Recorder.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDER_H
#define UI_RECORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Recorder
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QCheckBox *captureAudioCheckBox;
    QLabel *label_2;
    QComboBox *resolutionComboBox;
    QVBoxLayout *videoControlButtons;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QLabel *timeLabel;
    QLabel *label_3;
    QLabel *currentResolution;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Recorder)
    {
        if (Recorder->objectName().isEmpty())
            Recorder->setObjectName(QString::fromUtf8("Recorder"));
        Recorder->resize(790, 162);
        centralwidget = new QWidget(Recorder);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        captureAudioCheckBox = new QCheckBox(centralwidget);
        captureAudioCheckBox->setObjectName(QString::fromUtf8("captureAudioCheckBox"));

        verticalLayout->addWidget(captureAudioCheckBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        resolutionComboBox = new QComboBox(centralwidget);
        resolutionComboBox->addItem(QString());
        resolutionComboBox->addItem(QString());
        resolutionComboBox->addItem(QString());
        resolutionComboBox->addItem(QString());
        resolutionComboBox->setObjectName(QString::fromUtf8("resolutionComboBox"));

        gridLayout->addWidget(resolutionComboBox, 2, 1, 1, 1);

        videoControlButtons = new QVBoxLayout();
        videoControlButtons->setObjectName(QString::fromUtf8("videoControlButtons"));
        videoControlButtons->setSizeConstraint(QLayout::SetDefaultConstraint);
        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setCheckable(false);

        videoControlButtons->addWidget(playButton);

        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        videoControlButtons->addWidget(pauseButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        videoControlButtons->addWidget(stopButton);


        gridLayout->addLayout(videoControlButtons, 0, 3, 6, 1);

        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));

        gridLayout->addWidget(timeLabel, 0, 2, 1, 1, Qt::AlignHCenter);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        currentResolution = new QLabel(centralwidget);
        currentResolution->setObjectName(QString::fromUtf8("currentResolution"));

        gridLayout->addWidget(currentResolution, 5, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1, Qt::AlignHCenter);

        Recorder->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Recorder);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 790, 23));
        Recorder->setMenuBar(menubar);
        statusbar = new QStatusBar(Recorder);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Recorder->setStatusBar(statusbar);

        retranslateUi(Recorder);

        QMetaObject::connectSlotsByName(Recorder);
    } // setupUi

    void retranslateUi(QMainWindow *Recorder)
    {
        Recorder->setWindowTitle(QCoreApplication::translate("Recorder", "MainWindow", nullptr));
        captureAudioCheckBox->setText(QCoreApplication::translate("Recorder", "Capture Audio", nullptr));
        label_2->setText(QCoreApplication::translate("Recorder", "Default Resolution", nullptr));
        resolutionComboBox->setItemText(0, QCoreApplication::translate("Recorder", "800x600", nullptr));
        resolutionComboBox->setItemText(1, QCoreApplication::translate("Recorder", "1280x720", nullptr));
        resolutionComboBox->setItemText(2, QCoreApplication::translate("Recorder", "1920x1080", nullptr));
        resolutionComboBox->setItemText(3, QCoreApplication::translate("Recorder", "Custom", nullptr));

        playButton->setText(QCoreApplication::translate("Recorder", "Play", nullptr));
        pauseButton->setText(QCoreApplication::translate("Recorder", "Pause", nullptr));
        stopButton->setText(QCoreApplication::translate("Recorder", "Stop", nullptr));
        timeLabel->setText(QCoreApplication::translate("Recorder", "00:00:00", nullptr));
        label_3->setText(QCoreApplication::translate("Recorder", "Current resolution", nullptr));
        currentResolution->setText(QCoreApplication::translate("Recorder", "0", nullptr));
        label->setText(QCoreApplication::translate("Recorder", "Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Recorder: public Ui_Recorder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDER_H
