/********************************************************************************
** Form generated from reading UI file 'priceinput.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRICEINPUT_H
#define UI_PRICEINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_priceInput
{
public:
    QGridLayout *gridLayout;
    QPushButton *eight;
    QPushButton *nine;
    QPushButton *clear;
    QPushButton *seven;
    QPushButton *two2;
    QPushButton *one;
    QPushButton *three;
    QPushButton *enter;
    QPushButton *dote;
    QPushButton *zero;
    QPushButton *five;
    QPushButton *erase;
    QPushButton *six;
    QLineEdit *lineEdit;
    QPushButton *four;
    QLabel *label;

    void setupUi(QWidget *priceInput)
    {
        if (priceInput->objectName().isEmpty())
            priceInput->setObjectName(QStringLiteral("priceInput"));
        priceInput->resize(540, 384);
        gridLayout = new QGridLayout(priceInput);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        eight = new QPushButton(priceInput);
        eight->setObjectName(QStringLiteral("eight"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(eight->sizePolicy().hasHeightForWidth());
        eight->setSizePolicy(sizePolicy);
        eight->setFocusPolicy(Qt::NoFocus);
        eight->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(eight, 2, 1, 1, 1);

        nine = new QPushButton(priceInput);
        nine->setObjectName(QStringLiteral("nine"));
        sizePolicy.setHeightForWidth(nine->sizePolicy().hasHeightForWidth());
        nine->setSizePolicy(sizePolicy);
        nine->setFocusPolicy(Qt::NoFocus);
        nine->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(nine, 2, 2, 1, 1);

        clear = new QPushButton(priceInput);
        clear->setObjectName(QStringLiteral("clear"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(clear->sizePolicy().hasHeightForWidth());
        clear->setSizePolicy(sizePolicy1);
        clear->setFocusPolicy(Qt::NoFocus);
        clear->setStyleSheet(QStringLiteral("font: 26pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(clear, 2, 3, 1, 1);

        seven = new QPushButton(priceInput);
        seven->setObjectName(QStringLiteral("seven"));
        sizePolicy.setHeightForWidth(seven->sizePolicy().hasHeightForWidth());
        seven->setSizePolicy(sizePolicy);
        seven->setFocusPolicy(Qt::NoFocus);
        seven->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(seven, 2, 0, 1, 1);

        two2 = new QPushButton(priceInput);
        two2->setObjectName(QStringLiteral("two2"));
        sizePolicy1.setHeightForWidth(two2->sizePolicy().hasHeightForWidth());
        two2->setSizePolicy(sizePolicy1);
        two2->setFocusPolicy(Qt::NoFocus);
        two2->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(two2, 6, 1, 1, 1);

        one = new QPushButton(priceInput);
        one->setObjectName(QStringLiteral("one"));
        sizePolicy1.setHeightForWidth(one->sizePolicy().hasHeightForWidth());
        one->setSizePolicy(sizePolicy1);
        one->setFocusPolicy(Qt::NoFocus);
        one->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(one, 6, 0, 1, 1);

        three = new QPushButton(priceInput);
        three->setObjectName(QStringLiteral("three"));
        sizePolicy1.setHeightForWidth(three->sizePolicy().hasHeightForWidth());
        three->setSizePolicy(sizePolicy1);
        three->setFocusPolicy(Qt::NoFocus);
        three->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(three, 6, 2, 1, 1);

        enter = new QPushButton(priceInput);
        enter->setObjectName(QStringLiteral("enter"));
        sizePolicy1.setHeightForWidth(enter->sizePolicy().hasHeightForWidth());
        enter->setSizePolicy(sizePolicy1);
        enter->setFocusPolicy(Qt::NoFocus);
        enter->setContextMenuPolicy(Qt::NoContextMenu);
        enter->setStyleSheet(QStringLiteral("font: 26pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(enter, 6, 3, 2, 1);

        dote = new QPushButton(priceInput);
        dote->setObjectName(QStringLiteral("dote"));
        sizePolicy1.setHeightForWidth(dote->sizePolicy().hasHeightForWidth());
        dote->setSizePolicy(sizePolicy1);
        dote->setFocusPolicy(Qt::NoFocus);
        dote->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(dote, 7, 2, 1, 1);

        zero = new QPushButton(priceInput);
        zero->setObjectName(QStringLiteral("zero"));
        sizePolicy1.setHeightForWidth(zero->sizePolicy().hasHeightForWidth());
        zero->setSizePolicy(sizePolicy1);
        zero->setFocusPolicy(Qt::NoFocus);
        zero->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(zero, 7, 0, 1, 2);

        five = new QPushButton(priceInput);
        five->setObjectName(QStringLiteral("five"));
        sizePolicy.setHeightForWidth(five->sizePolicy().hasHeightForWidth());
        five->setSizePolicy(sizePolicy);
        five->setFocusPolicy(Qt::NoFocus);
        five->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(five, 3, 1, 1, 1);

        erase = new QPushButton(priceInput);
        erase->setObjectName(QStringLiteral("erase"));
        sizePolicy1.setHeightForWidth(erase->sizePolicy().hasHeightForWidth());
        erase->setSizePolicy(sizePolicy1);
        erase->setFocusPolicy(Qt::NoFocus);
        erase->setContextMenuPolicy(Qt::NoContextMenu);
        erase->setStyleSheet(QStringLiteral("font: 26pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(erase, 3, 3, 1, 1);

        six = new QPushButton(priceInput);
        six->setObjectName(QStringLiteral("six"));
        sizePolicy.setHeightForWidth(six->sizePolicy().hasHeightForWidth());
        six->setSizePolicy(sizePolicy);
        six->setFocusPolicy(Qt::NoFocus);
        six->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(six, 3, 2, 1, 1);

        lineEdit = new QLineEdit(priceInput);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        QFont font;
        font.setPointSize(20);
        lineEdit->setFont(font);
        lineEdit->setEchoMode(QLineEdit::Normal);

        gridLayout->addWidget(lineEdit, 1, 0, 1, 4);

        four = new QPushButton(priceInput);
        four->setObjectName(QStringLiteral("four"));
        sizePolicy.setHeightForWidth(four->sizePolicy().hasHeightForWidth());
        four->setSizePolicy(sizePolicy);
        four->setFocusPolicy(Qt::NoFocus);
        four->setStyleSheet(QStringLiteral("font: 36pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(four, 3, 0, 1, 1);

        label = new QLabel(priceInput);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setStyleSheet(QStringLiteral("font: 20pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(label, 0, 0, 1, 4);


        retranslateUi(priceInput);

        QMetaObject::connectSlotsByName(priceInput);
    } // setupUi

    void retranslateUi(QWidget *priceInput)
    {
        priceInput->setWindowTitle(QApplication::translate("priceInput", "Form", Q_NULLPTR));
        eight->setText(QApplication::translate("priceInput", "8", Q_NULLPTR));
        nine->setText(QApplication::translate("priceInput", "9", Q_NULLPTR));
        clear->setText(QApplication::translate("priceInput", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", Q_NULLPTR));
        seven->setText(QApplication::translate("priceInput", "7", Q_NULLPTR));
        two2->setText(QApplication::translate("priceInput", "2", Q_NULLPTR));
        one->setText(QApplication::translate("priceInput", "1", Q_NULLPTR));
        three->setText(QApplication::translate("priceInput", "3", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        enter->setWhatsThis(QApplication::translate("priceInput", "\320\276\321\201\321\203\321\211\320\265\321\201\321\202\320\262\320\273\321\217\321\202\321\201\321\217 \320\277\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\320\265 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\270", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        enter->setText(QApplication::translate("priceInput", "\320\222\320\262\320\276\320\264", Q_NULLPTR));
        dote->setText(QApplication::translate("priceInput", ",", Q_NULLPTR));
        zero->setText(QApplication::translate("priceInput", "0", Q_NULLPTR));
        five->setText(QApplication::translate("priceInput", "5", Q_NULLPTR));
        erase->setText(QApplication::translate("priceInput", "\320\241\321\202\320\265\321\200\320\265\321\202\321\214", Q_NULLPTR));
        six->setText(QApplication::translate("priceInput", "6", Q_NULLPTR));
        lineEdit->setInputMask(QString());
        four->setText(QApplication::translate("priceInput", "4", Q_NULLPTR));
        label->setText(QApplication::translate("priceInput", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\206\320\265\320\275\321\203", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class priceInput: public Ui_priceInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRICEINPUT_H
