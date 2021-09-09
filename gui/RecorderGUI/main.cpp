#include <QApplication>
#include <QPushButton>
#include "ui_Recorder.h"
#include "recorder.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Recorder r;
    r.show();



    return QApplication::exec();
}
