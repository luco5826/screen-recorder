#include "recorder.h"
#include "ui_Recorder.h"
#include <QTimer>
#include <QTime>
#include <QDebug>

#include "ffmpeg/ScreenRecorder.h"

Recorder::Recorder(QWidget *parent)
    : 
    QMainWindow(parent), 
    ui(new Ui::Recorder), 
    screenRecorder(new ScreenRecorder("output.mp4", "")),
    currentState(State::STOP)
{
  ui->setupUi(this);
  screenRecorder->Init();

  timeToDisplay = QTime(0, 0, 0);
  timer.setInterval(1000);
  connect(&timer, SIGNAL(timeout()), this, SLOT(updateCaption()));

  auto resolution = ui->resolutionComboBox->currentText().split("x");
  this->rf = new ResizableFrame(nullptr, resolution[0].toInt(), resolution[1].toInt());
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

void Recorder::on_playButton_clicked()
{
  currentState = RECORDING;
  rf->hide();
  {
    screenRecorder->OpenVideo(rf->pos().x(), rf->pos().y(), rf->width(), rf->height(), 30);
    if (ui->captureAudioCheckBox->isChecked())
      screenRecorder->OpenAudio();
    screenRecorder->Start();
  }

  ui->resolutionComboBox->setDisabled(true);
  ui->currentResolution->setText(QString::number(rf->width()) + "x" + QString::number(rf->height()));
  ui->pauseButton->setDisabled(false);
  ui->stopButton->setDisabled(false);
  ui->playButton->setDisabled(true);

  timer.start();
}

// clicked pauseButton
void Recorder::on_pauseButton_clicked()
{
  if (currentState == RECORDING)
  {
    ui->pauseButton->setText("Resume");
    currentState = PAUSE;
    timer.stop();
  }
  else if (currentState == PAUSE)
  {
    ui->pauseButton->setText("Pause");
    currentState = RECORDING;
    timer.start();
  }
}

void Recorder::on_stopButton_clicked()
{
  currentState = STOP;
  timeToDisplay.setHMS(0,0,0);
  ui->timeLabel->setText(timeToDisplay.toString("hh:mm:ss"));

  ui->resolutionComboBox->setDisabled(false);
  ui->resolutionComboBox->setCurrentIndex(0);
  ui->stopButton->setDisabled(true);
  ui->pauseButton->setDisabled(true);
  ui->playButton->setDisabled(false);
  ui->pauseButton->setText("Pause");
  screenRecorder->Stop();
  timer.stop();
}

void Recorder::on_resolutionComboBox_currentTextChanged(const QString &arg1)
{
  if (rf->isHidden() && arg1 == "Custom")
    rf->show();
  else
  {
    rf->setFrameWidth(arg1.split("x")[0].toInt());
    rf->setFrameHeight(arg1.split("x")[1].toInt());
  }
}

void Recorder::on_drawRegionButton_clicked()
{
  if (rf->isHidden())
    rf->show();
  else
    rf->hide();
}
