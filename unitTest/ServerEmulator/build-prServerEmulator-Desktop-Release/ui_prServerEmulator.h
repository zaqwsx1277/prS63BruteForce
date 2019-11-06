/********************************************************************************
** Form generated from reading UI file 'prServerEmulator.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRSERVEREMULATOR_H
#define UI_PRSERVEREMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prServerEmulator
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *spClientAddress;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLabel *spClientState;
    QTableView *spLog;

    void setupUi(QMainWindow *prServerEmulator)
    {
        if (prServerEmulator->objectName().isEmpty())
            prServerEmulator->setObjectName(QStringLiteral("prServerEmulator"));
        prServerEmulator->resize(1165, 520);
        centralWidget = new QWidget(prServerEmulator);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spClientAddress = new QLabel(centralWidget);
        spClientAddress->setObjectName(QStringLiteral("spClientAddress"));

        gridLayout->addWidget(spClientAddress, 0, 1, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 0));
        pushButton_2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        spClientState = new QLabel(centralWidget);
        spClientState->setObjectName(QStringLiteral("spClientState"));
        spClientState->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(spClientState);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        spLog = new QTableView(centralWidget);
        spLog->setObjectName(QStringLiteral("spLog"));

        gridLayout_2->addWidget(spLog, 2, 0, 1, 1);

        prServerEmulator->setCentralWidget(centralWidget);

        retranslateUi(prServerEmulator);

        QMetaObject::connectSlotsByName(prServerEmulator);
    } // setupUi

    void retranslateUi(QMainWindow *prServerEmulator)
    {
        prServerEmulator->setWindowTitle(QApplication::translate("prServerEmulator", "prServerEmulator", Q_NULLPTR));
        label->setText(QApplication::translate("prServerEmulator", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\271 \320\272\320\273\320\270\320\265\320\275\321\202 :", Q_NULLPTR));
        spClientAddress->setText(QApplication::translate("prServerEmulator", "spClientAddress", Q_NULLPTR));
        pushButton->setText(QApplication::translate("prServerEmulator", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("prServerEmulator", "\320\227\320\260\320\277\321\200\320\276\321\201 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\321\217 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("prServerEmulator", "\320\227\320\260\320\277\321\200\320\276\321\201", Q_NULLPTR));
        label_3->setText(QApplication::translate("prServerEmulator", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\272\320\273\320\270\320\265\320\275\321\202\320\260 :", Q_NULLPTR));
        spClientState->setText(QApplication::translate("prServerEmulator", "spClientState", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class prServerEmulator: public Ui_prServerEmulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRSERVEREMULATOR_H
