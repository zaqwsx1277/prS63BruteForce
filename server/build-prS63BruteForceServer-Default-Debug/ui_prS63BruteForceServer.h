/********************************************************************************
** Form generated from reading UI file 'prS63BruteForceServer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRS63BRUTEFORCESERVER_H
#define UI_PRS63BRUTEFORCESERVER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prS63BruteForceServer
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *spPathFrom;
    QToolButton *btnPathFrom;
    QToolButton *btnRun;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *spThreadCount;
    QLabel *label_2;
    QLineEdit *spKeyStart;
    QLabel *label_7;
    QLineEdit *spKeyStop;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *spTimeStart;
    QLabel *label_4;
    QLineEdit *spTimeStop;
    QLabel *label_5;
    QLineEdit *spTimeDuration;
    QLabel *label_8;
    QLabel *spState;
    QGroupBox *spThreads;
    QGridLayout *gridLayout;
    QTableView *spLog;
    QGroupBox *spKeys;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QTableView *spLogKeys;
    QVBoxLayout *verticalLayout;
    QPushButton *btnSave;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *prS63BruteForceServer)
    {
        if (prS63BruteForceServer->objectName().isEmpty())
            prS63BruteForceServer->setObjectName(QStringLiteral("prS63BruteForceServer"));
        prS63BruteForceServer->resize(1210, 627);
        centralWidget = new QWidget(prS63BruteForceServer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spPathFrom = new QLineEdit(centralWidget);
        spPathFrom->setObjectName(QStringLiteral("spPathFrom"));
        spPathFrom->setReadOnly(true);
        spPathFrom->setClearButtonEnabled(false);

        horizontalLayout->addWidget(spPathFrom);

        btnPathFrom = new QToolButton(centralWidget);
        btnPathFrom->setObjectName(QStringLiteral("btnPathFrom"));

        horizontalLayout->addWidget(btnPathFrom);

        btnRun = new QToolButton(centralWidget);
        btnRun->setObjectName(QStringLiteral("btnRun"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icones/icones/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRun->setIcon(icon);

        horizontalLayout->addWidget(btnRun);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        spThreadCount = new QLineEdit(centralWidget);
        spThreadCount->setObjectName(QStringLiteral("spThreadCount"));
        spThreadCount->setReadOnly(false);
        spThreadCount->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(spThreadCount);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spKeyStart = new QLineEdit(centralWidget);
        spKeyStart->setObjectName(QStringLiteral("spKeyStart"));
        spKeyStart->setReadOnly(false);
        spKeyStart->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(spKeyStart);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        spKeyStop = new QLineEdit(centralWidget);
        spKeyStop->setObjectName(QStringLiteral("spKeyStop"));
        spKeyStop->setReadOnly(false);
        spKeyStop->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(spKeyStop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        spTimeStart = new QLineEdit(centralWidget);
        spTimeStart->setObjectName(QStringLiteral("spTimeStart"));
        spTimeStart->setReadOnly(true);

        horizontalLayout_3->addWidget(spTimeStart);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        spTimeStop = new QLineEdit(centralWidget);
        spTimeStop->setObjectName(QStringLiteral("spTimeStop"));
        spTimeStop->setReadOnly(true);

        horizontalLayout_3->addWidget(spTimeStop);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        spTimeDuration = new QLineEdit(centralWidget);
        spTimeDuration->setObjectName(QStringLiteral("spTimeDuration"));
        spTimeDuration->setReadOnly(true);

        horizontalLayout_3->addWidget(spTimeDuration);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_3->addWidget(label_8);

        spState = new QLabel(centralWidget);
        spState->setObjectName(QStringLiteral("spState"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spState->sizePolicy().hasHeightForWidth());
        spState->setSizePolicy(sizePolicy);
        spState->setMinimumSize(QSize(120, 0));
        spState->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(spState);


        gridLayout_2->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        spThreads = new QGroupBox(centralWidget);
        spThreads->setObjectName(QStringLiteral("spThreads"));
        gridLayout = new QGridLayout(spThreads);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spLog = new QTableView(spThreads);
        spLog->setObjectName(QStringLiteral("spLog"));

        gridLayout->addWidget(spLog, 0, 0, 1, 1);


        gridLayout_2->addWidget(spThreads, 3, 0, 1, 1);

        spKeys = new QGroupBox(centralWidget);
        spKeys->setObjectName(QStringLiteral("spKeys"));
        gridLayout_3 = new QGridLayout(spKeys);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        spLogKeys = new QTableView(spKeys);
        spLogKeys->setObjectName(QStringLiteral("spLogKeys"));

        horizontalLayout_4->addWidget(spLogKeys);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnSave = new QPushButton(spKeys);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("res/icones/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon1);

        verticalLayout->addWidget(btnSave);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout);


        gridLayout_3->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        gridLayout_2->addWidget(spKeys, 4, 0, 1, 1);

        prS63BruteForceServer->setCentralWidget(centralWidget);

        retranslateUi(prS63BruteForceServer);

        QMetaObject::connectSlotsByName(prS63BruteForceServer);
    } // setupUi

    void retranslateUi(QMainWindow *prS63BruteForceServer)
    {
        prS63BruteForceServer->setWindowTitle(QApplication::translate("prS63BruteForceServer", "prHackS63MainWindow", nullptr));
        label->setText(QApplication::translate("prS63BruteForceServer", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \320\272\320\260\321\202\320\260\320\273\320\276\320\263 :", nullptr));
        spPathFrom->setText(QApplication::translate("prS63BruteForceServer", "spPathFrom", nullptr));
        btnPathFrom->setText(QApplication::translate("prS63BruteForceServer", "...", nullptr));
        btnRun->setText(QString());
        label_6->setText(QApplication::translate("prS63BruteForceServer", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\276\321\202\320\276\320\272\320\276\320\262 :", nullptr));
        spThreadCount->setText(QApplication::translate("prS63BruteForceServer", "spThreadCount", nullptr));
        label_2->setText(QApplication::translate("prS63BruteForceServer", "\320\232\320\273\321\216\321\207\320\270 c :", nullptr));
        spKeyStart->setText(QApplication::translate("prS63BruteForceServer", "spKeyStart", nullptr));
        label_7->setText(QApplication::translate("prS63BruteForceServer", "\320\277\320\276 :", nullptr));
        spKeyStop->setText(QApplication::translate("prS63BruteForceServer", "spKeyStop", nullptr));
        label_3->setText(QApplication::translate("prS63BruteForceServer", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\207\320\260\320\273\320\260:", nullptr));
        spTimeStart->setText(QApplication::translate("prS63BruteForceServer", "spTimeStart", nullptr));
        label_4->setText(QApplication::translate("prS63BruteForceServer", "\320\276\320\272\320\276\320\275\321\207\320\260\320\275\320\270\321\217 :", nullptr));
        spTimeStop->setText(QApplication::translate("prS63BruteForceServer", "spTimeStop", nullptr));
        label_5->setText(QApplication::translate("prS63BruteForceServer", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 :", nullptr));
        spTimeDuration->setText(QApplication::translate("prS63BruteForceServer", "spTimeDuration", nullptr));
        label_8->setText(QApplication::translate("prS63BruteForceServer", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 :", nullptr));
        spState->setText(QApplication::translate("prS63BruteForceServer", "spState", nullptr));
        spThreads->setTitle(QApplication::translate("prS63BruteForceServer", "\320\237\320\276\321\202\320\276\320\272\320\270", nullptr));
        spKeys->setTitle(QApplication::translate("prS63BruteForceServer", "\320\232\320\273\321\216\321\207\320\270", nullptr));
        btnSave->setText(QApplication::translate("prS63BruteForceServer", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class prS63BruteForceServer: public Ui_prS63BruteForceServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRS63BRUTEFORCESERVER_H
