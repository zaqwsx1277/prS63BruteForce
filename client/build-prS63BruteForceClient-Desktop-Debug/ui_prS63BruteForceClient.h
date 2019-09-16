/********************************************************************************
** Form generated from reading UI file 'prS63BruteForceClient.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRS63BRUTEFORCECLIENT_H
#define UI_PRS63BRUTEFORCECLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prS63BruteForceClient
{
public:
    QWidget *centralWidget;
    QLabel *label;

    void setupUi(QMainWindow *prS63BruteForceClient)
    {
        if (prS63BruteForceClient->objectName().isEmpty())
            prS63BruteForceClient->setObjectName(QStringLiteral("prS63BruteForceClient"));
        prS63BruteForceClient->resize(1124, 594);
        centralWidget = new QWidget(prS63BruteForceClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 54, 17));
        prS63BruteForceClient->setCentralWidget(centralWidget);

        retranslateUi(prS63BruteForceClient);

        QMetaObject::connectSlotsByName(prS63BruteForceClient);
    } // setupUi

    void retranslateUi(QMainWindow *prS63BruteForceClient)
    {
        prS63BruteForceClient->setWindowTitle(QApplication::translate("prS63BruteForceClient", "prS63BruteForceClient", Q_NULLPTR));
        label->setText(QApplication::translate("prS63BruteForceClient", "\320\220\320\264\321\200\320\265\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class prS63BruteForceClient: public Ui_prS63BruteForceClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRS63BRUTEFORCECLIENT_H
