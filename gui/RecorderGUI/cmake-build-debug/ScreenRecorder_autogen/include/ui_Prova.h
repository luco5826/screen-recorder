/********************************************************************************
** Form generated from reading UI file 'Prova.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVA_H
#define UI_PROVA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

namespace UI_PROVA {

class Ui_Prova
{
public:

    void setupUi(QWidget *UI_PROVA__Prova)
    {
        if (UI_PROVA__Prova->objectName().isEmpty())
            UI_PROVA__Prova->setObjectName(QString::fromUtf8("UI_PROVA__Prova"));
        UI_PROVA__Prova->resize(400, 300);

        retranslateUi(UI_PROVA__Prova);

        QMetaObject::connectSlotsByName(UI_PROVA__Prova);
    } // setupUi

    void retranslateUi(QWidget *UI_PROVA__Prova)
    {
        UI_PROVA__Prova->setWindowTitle(QCoreApplication::translate("UI_PROVA::Prova", "Prova", nullptr));
    } // retranslateUi

};

} // namespace UI_PROVA

namespace UI_PROVA {
namespace Ui {
    class Prova: public Ui_Prova {};
} // namespace Ui
} // namespace UI_PROVA

#endif // UI_PROVA_H
