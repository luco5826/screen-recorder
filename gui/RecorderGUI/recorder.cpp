#include "recorder.h"
#include "ui_Recorder.h"
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
    int width = ui->resolutionComboBox->currentText().split("x")[0].toInt();
    int height = ui->resolutionComboBox->currentText().split("x")[1].toInt();
    this->rf = new ResizableFrame(0,width, height);
    // rf->setMainWindow(ui);
    //qDebug() << ui->resolutionComboBox->currentText().split("x");

    //rf->show();
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
    rf->hide();

    ui->resolutionComboBox->setDisabled(true);

    ui->currentResolution->setText(QString::number(rf->width()) + "x" + QString::number(rf->height()));
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
    ui->resolutionComboBox->setDisabled(false);
    ui->resolutionComboBox->setCurrentIndex(0);
    ui->stopButton->setDisabled(true);
    ui->playButton->setDisabled(false);
    ui->pauseButton->setText("Pause");
    ui->pauseButton->setDisabled(true);

    timer->stop();

}


void Recorder::on_resolutionComboBox_currentTextChanged(const QString &arg1)
{
    if(rf->isHidden() && arg1 == "Custom") rf->show();
    else {
        rf->setFrameWidth(arg1.split("x")[0].toInt());
        rf->setFrameHeight(arg1.split("x")[1].toInt());
    }
}


void Recorder::on_drawRegionButton_clicked()
{
    if(rf->isHidden()) rf->show();
    else rf->hide();
}

