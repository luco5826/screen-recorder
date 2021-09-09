//
// Created by alessandro on 12/07/21.
//

#ifndef SCREENRECORDER_MAINVIEW_H
#define SCREENRECORDER_MAINVIEW_H

#include <QMainWindow>


namespace MW_UI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainView; }
    QT_END_NAMESPACE

    class MainView : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainView(QWidget *parent = nullptr);

        ~MainView() override;

    private:
        Ui::MainView *ui;
    };
} // MW_UI

#endif //SCREENRECORDER_MAINVIEW_H
