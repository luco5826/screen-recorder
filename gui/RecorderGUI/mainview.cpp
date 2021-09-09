//
// Created by alessandro on 12/07/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainView.h" resolved

#include "mainview.h"
#include "ui_MainView.h"


namespace MW_UI {
    MainView::MainView(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::MainView) {

        ui->setupUi(this);
    }

    MainView::~MainView() {
        delete ui;
    }
} // MW_UI
