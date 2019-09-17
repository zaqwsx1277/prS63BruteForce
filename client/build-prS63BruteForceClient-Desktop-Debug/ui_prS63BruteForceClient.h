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
#include <QtWidgets/QCheckBox>
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

class Ui_prS63BruteForceClient
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *spServerAddress;
    QLabel *label_2;
    QLineEdit *spServerPort;
    QLabel *label_3;
    QLineEdit *spBlockSize;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_7;
    QCheckBox *checkBox;
    QLabel *label_5;
    QLabel *label_6;
    QToolButton *toolButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *prS63BruteForceClient)
    {
        if (prS63BruteForceClient->objectName().isEmpty())
            prS63BruteForceClient->setObjectName(QStringLiteral("prS63BruteForceClient"));
        prS63BruteForceClient->resize(1124, 594);
        centralWidget = new QWidget(prS63BruteForceClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spServerAddress = new QLineEdit(centralWidget);
        spServerAddress->setObjectName(QStringLiteral("spServerAddress"));

        gridLayout_2->addWidget(spServerAddress, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);

        spServerPort = new QLineEdit(centralWidget);
        spServerPort->setObjectName(QStringLiteral("spServerPort"));

        gridLayout_2->addWidget(spServerPort, 0, 3, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        spBlockSize = new QLineEdit(centralWidget);
        spBlockSize->setObjectName(QStringLiteral("spBlockSize"));
        spBlockSize->setReadOnly(true);

        gridLayout_2->addWidget(spBlockSize, 1, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 2, 1, 1);

        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_2->addWidget(lineEdit_4, 1, 3, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(checkBox, 2, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 2, 2, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 3, 1, 1);

        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icones/icones/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);

        gridLayout_2->addWidget(toolButton, 2, 4, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(groupBox);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../res/icones/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icones/icones/cancelar.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon2);

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        prS63BruteForceClient->setCentralWidget(centralWidget);

        retranslateUi(prS63BruteForceClient);

        QMetaObject::connectSlotsByName(prS63BruteForceClient);
    } // setupUi

    void retranslateUi(QMainWindow *prS63BruteForceClient)
    {
        prS63BruteForceClient->setWindowTitle(QApplication::translate("prS63BruteForceClient", "\320\232\320\273\320\270\320\265\320\275\321\202 \320\264\320\273\321\217 \321\200\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \320\277\320\276\320\264\320\261\320\276\321\200\320\260 \320\277\320\260\321\200\320\276\320\273\320\265\320\271 \320\275\320\260 S63", Q_NULLPTR));
        label->setText(QApplication::translate("prS63BruteForceClient", "\320\220\320\264\321\200\320\265\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260:", Q_NULLPTR));
        spServerAddress->setText(QApplication::translate("prS63BruteForceClient", "spServerAddress", Q_NULLPTR));
        label_2->setText(QApplication::translate("prS63BruteForceClient", "\320\277\320\276\321\200\321\202:", Q_NULLPTR));
        spServerPort->setText(QApplication::translate("prS63BruteForceClient", "spServerPort", Q_NULLPTR));
        label_3->setText(QApplication::translate("prS63BruteForceClient", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\261\320\273\320\276\320\272\320\260:", Q_NULLPTR));
        spBlockSize->setText(QApplication::translate("prS63BruteForceClient", "spBlockSize", Q_NULLPTR));
        label_4->setText(QApplication::translate("prS63BruteForceClient", "<html><head/><body><p>\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\276\321\202\320\276\320\272\320\276\320\262:</p></body></html>", Q_NULLPTR));
        label_7->setText(QApplication::translate("prS63BruteForceClient", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\217\321\202\321\214 \320\273\320\276\320\263:", Q_NULLPTR));
        checkBox->setText(QString());
        label_5->setText(QApplication::translate("prS63BruteForceClient", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265:", Q_NULLPTR));
        label_6->setText(QApplication::translate("prS63BruteForceClient", "\320\222\321\213\320\261\320\276\321\200 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", Q_NULLPTR));
        toolButton->setText(QString());
        groupBox->setTitle(QApplication::translate("prS63BruteForceClient", "\320\233\320\276\320\263 \321\200\320\260\320\261\320\276\321\202\321\213 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", Q_NULLPTR));
        pushButton->setText(QApplication::translate("prS63BruteForceClient", "\320\237\320\260\321\203\320\267\320\260", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("prS63BruteForceClient", "\320\241\321\202\320\276\320\277", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class prS63BruteForceClient: public Ui_prS63BruteForceClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRS63BRUTEFORCECLIENT_H
