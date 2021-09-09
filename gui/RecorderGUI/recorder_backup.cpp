//
// Created by alessandro on 12/07/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Recorder.h" resolved


#include "./ui_Recorder.h"
#include <QTimer>
#include <QTime>
#include <QDebug>

    Recorder::Recorder(QWidget *parent)
            : QMainWindow(parent)
            , ui(new Ui::Recorder)
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
        timeToDisplay = QTime(0,0,0);

        ui->setupUi(this);
        ui->pauseButton->setDisabled(true);
    }

    void Recorder::updateCaption()
    {
        timeToDisplay = timeToDisplay.addSecs(1);
        ui->timeLabel->setText(timeToDisplay.toString("hh:mm:ss"));
    }

    Recorder::~Recorder()
    {
        delete ui;
    }

// clicked playButton
    void Recorder::on_playButton_clicked()
    {

        if(STATE == STOP) {
            timeToDisplay = QTime(0,0,0);
        }
        STATE = RECORDING;
        ui->pauseButton->setDisabled(false);
        ui->stopButton->setDisabled(false);
        ui->playButton->setDisabled(true);

        timer->start();

    }


// clicked pauseButton
    void Recorder::on_pauseButton_clicked()
    {

        if(STATE == RECORDING) {
            ui->pauseButton->setText("Resume");
            STATE = PAUSE;
            timer->stop();

        } else if (STATE == PAUSE) {
            ui->pauseButton->setText("Pause");
            STATE = RECORDING;
            timer->start();
        }
    }


    void Recorder::on_stopButton_clicked()
    {

        STATE = STOP;
        ui->stopButton->setDisabled(true);
        ui->playButton->setDisabled(false);
        ui->pauseButton->setText("Pause");
        ui->pauseButton->setDisabled(true);

        timer->stop();

    }



    Recorder::~Recorder() {
        delete ui;
    }
} // RC_UI
