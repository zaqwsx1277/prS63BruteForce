/********************************************************************************
** Form generated from reading UI file 'prServerEmulator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRSERVEREMULATOR_H
#define UI_PRSERVEREMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prServerEmulator
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *spState;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *prServerEmulator)
    {
        if (prServerEmulator->objectName().isEmpty())
            prServerEmulator->setObjectName(QStringLiteral("prServerEmulator"));
        prServerEmulator->resize(400, 300);
        centralWidget = new QWidget(prServerEmulator);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 20, 87, 29));
        spState = new QLabel(centralWidget);
        spState->setObjectName(QStringLiteral("spState"));
        spState->setGeometry(QRect(20, 40, 58, 18));
        prServerEmulator->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(prServerEmulator);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 30));
        prServerEmulator->setMenuBar(menuBar);
        mainToolBar = new QToolBar(prServerEmulator);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        prServerEmulator->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(prServerEmulator);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        prServerEmulator->setStatusBar(statusBar);

        retranslateUi(prServerEmulator);

        QMetaObject::connectSlotsByName(prServerEmulator);
    } // setupUi

    void retranslateUi(QMainWindow *prServerEmulator)
    {
        prServerEmulator->setWindowTitle(QApplication::translate("prServerEmulator", "prServerEmulator", nullptr));
        pushButton->setText(QApplication::translate("prServerEmulator", "PushButton", nullptr));
        spState->setText(QApplication::translate("prServerEmulator", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class prServerEmulator: public Ui_prServerEmulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRSERVEREMULATOR_H
