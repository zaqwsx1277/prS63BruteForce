/********************************************************************************
** Form generated from reading UI file 'prTestDecrypt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRTESTDECRYPT_H
#define UI_PRTESTDECRYPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prTestDecrypt
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *spPathFrom;
    QToolButton *btnPathFrom;
    QToolButton *btnMake;
    QLabel *label_2;
    QLineEdit *spPathTo;
    QToolButton *btnPathFrom_2;

    void setupUi(QMainWindow *prTestDecrypt)
    {
        if (prTestDecrypt->objectName().isEmpty())
            prTestDecrypt->setObjectName(QStringLiteral("prTestDecrypt"));
        prTestDecrypt->resize(1243, 437);
        centralWidget = new QWidget(prTestDecrypt);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 19, 881, 66));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spPathFrom = new QLineEdit(widget);
        spPathFrom->setObjectName(QStringLiteral("spPathFrom"));
        spPathFrom->setReadOnly(true);

        gridLayout->addWidget(spPathFrom, 0, 1, 1, 1);

        btnPathFrom = new QToolButton(widget);
        btnPathFrom->setObjectName(QStringLiteral("btnPathFrom"));

        gridLayout->addWidget(btnPathFrom, 0, 2, 1, 1);

        btnMake = new QToolButton(widget);
        btnMake->setObjectName(QStringLiteral("btnMake"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/icones/res/icones/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMake->setIcon(icon);

        gridLayout->addWidget(btnMake, 0, 3, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spPathTo = new QLineEdit(widget);
        spPathTo->setObjectName(QStringLiteral("spPathTo"));
        spPathTo->setReadOnly(true);

        gridLayout->addWidget(spPathTo, 1, 1, 1, 1);

        btnPathFrom_2 = new QToolButton(widget);
        btnPathFrom_2->setObjectName(QStringLiteral("btnPathFrom_2"));

        gridLayout->addWidget(btnPathFrom_2, 1, 2, 1, 1);

        prTestDecrypt->setCentralWidget(centralWidget);

        retranslateUi(prTestDecrypt);

        QMetaObject::connectSlotsByName(prTestDecrypt);
    } // setupUi

    void retranslateUi(QMainWindow *prTestDecrypt)
    {
        prTestDecrypt->setWindowTitle(QApplication::translate("prTestDecrypt", "prTestDecrypt", Q_NULLPTR));
        label->setText(QApplication::translate("prTestDecrypt", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \321\204\320\260\320\271\320\273 S63 :", Q_NULLPTR));
        spPathFrom->setText(QApplication::translate("prTestDecrypt", "spPathFrom", Q_NULLPTR));
        btnPathFrom->setText(QApplication::translate("prTestDecrypt", "...", Q_NULLPTR));
        btnMake->setText(QApplication::translate("prTestDecrypt", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("prTestDecrypt", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 \321\200\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\272\320\270 S57:", Q_NULLPTR));
        spPathTo->setText(QApplication::translate("prTestDecrypt", "spPathTo", Q_NULLPTR));
        btnPathFrom_2->setText(QApplication::translate("prTestDecrypt", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class prTestDecrypt: public Ui_prTestDecrypt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRTESTDECRYPT_H
