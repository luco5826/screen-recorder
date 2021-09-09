//
// Created by alessandro on 12/07/21.
//

#ifndef SCREENRECORDER_RECORDER_H
#define SCREENRECORDER_RECORDER_H

#include <QWidget>
#include <QMainWindow>

namespace RC_UI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Recorder; }
    QT_END_NAMESPACE

    class Recorder : public QMainWindow {
    Q_OBJECT

    public:
        explicit Recorder(QWidget *parent = nullptr);

        ~Recorder() override;

    private:
        Ui::Recorder *ui;
    };
} // RC_UI#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::Recorder *ui;
    QTimer *timer;
    QTime timeToDisplay;
    State STATE;
};
#endif // MAINWINDOW_H


#endif //SCREENRECORDER_RECORDER_H
