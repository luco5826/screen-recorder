#ifndef RECORDER_H
#define RECORDER_H

#include <QMainWindow>
#include "resizableframe.h"
#include <QTimer>
#include <QTime>


QT_BEGIN_NAMESPACE
namespace Ui { class Recorder; }
QT_END_NAMESPACE

enum State {RECORDING, PAUSE, STOP};

class Recorder : public QMainWindow
{
Q_OBJECT

public:
    Recorder(QWidget *parent = nullptr);
    ~Recorder();

private slots:
    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void updateCaption();

    void on_stopButton_clicked();

    void on_resolutionComboBox_currentTextChanged(const QString &arg1);

    void on_drawRegionButton_clicked();

private:
    ResizableFrame* rf;
    Ui::Recorder *ui;
    QTimer *timer;
    QTime timeToDisplay;
    State STATE;
};
#endif // MAINWINDOW_H
