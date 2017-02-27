/********************************************************************************
** Form generated from reading UI file 'additionaly.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITIONALY_H
#define UI_ADDITIONALY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_additionaly
{
public:
    QGridLayout *gridLayout;
    QPushButton *resumePrint;
    QPushButton *cancelSale;
    QPushButton *collectionMoney;
    QPushButton *enteringMoney;
    QPushButton *sale;
    QPushButton *return_2;

    void setupUi(QWidget *additionaly)
    {
        if (additionaly->objectName().isEmpty())
            additionaly->setObjectName(QStringLiteral("additionaly"));
        additionaly->resize(588, 348);
        gridLayout = new QGridLayout(additionaly);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        resumePrint = new QPushButton(additionaly);
        resumePrint->setObjectName(QStringLiteral("resumePrint"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resumePrint->sizePolicy().hasHeightForWidth());
        resumePrint->setSizePolicy(sizePolicy);
        resumePrint->setStyleSheet(QStringLiteral("font: 24pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(resumePrint, 2, 0, 1, 2);

        cancelSale = new QPushButton(additionaly);
        cancelSale->setObjectName(QStringLiteral("cancelSale"));
        sizePolicy.setHeightForWidth(cancelSale->sizePolicy().hasHeightForWidth());
        cancelSale->setSizePolicy(sizePolicy);
        cancelSale->setStyleSheet(QStringLiteral("font: 24pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(cancelSale, 2, 2, 1, 1);

        collectionMoney = new QPushButton(additionaly);
        collectionMoney->setObjectName(QStringLiteral("collectionMoney"));
        sizePolicy.setHeightForWidth(collectionMoney->sizePolicy().hasHeightForWidth());
        collectionMoney->setSizePolicy(sizePolicy);
        collectionMoney->setStyleSheet(QStringLiteral("font: 24pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(collectionMoney, 1, 2, 1, 1);

        enteringMoney = new QPushButton(additionaly);
        enteringMoney->setObjectName(QStringLiteral("enteringMoney"));
        sizePolicy.setHeightForWidth(enteringMoney->sizePolicy().hasHeightForWidth());
        enteringMoney->setSizePolicy(sizePolicy);
        enteringMoney->setStyleSheet(QStringLiteral("font: 24pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(enteringMoney, 1, 0, 1, 2);

        sale = new QPushButton(additionaly);
        sale->setObjectName(QStringLiteral("sale"));
        sizePolicy.setHeightForWidth(sale->sizePolicy().hasHeightForWidth());
        sale->setSizePolicy(sizePolicy);
        sale->setStyleSheet(QStringLiteral("font: 24pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(sale, 0, 2, 1, 1);

        return_2 = new QPushButton(additionaly);
        return_2->setObjectName(QStringLiteral("return_2"));
        sizePolicy.setHeightForWidth(return_2->sizePolicy().hasHeightForWidth());
        return_2->setSizePolicy(sizePolicy);
        return_2->setStyleSheet(QStringLiteral("font: 24pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(return_2, 0, 0, 1, 2);


        retranslateUi(additionaly);

        QMetaObject::connectSlotsByName(additionaly);
    } // setupUi

    void retranslateUi(QWidget *additionaly)
    {
        additionaly->setWindowTitle(QApplication::translate("additionaly", "Form", Q_NULLPTR));
        resumePrint->setText(QApplication::translate("additionaly", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214 \320\237\320\265\321\207\320\260\321\202\321\214", Q_NULLPTR));
        cancelSale->setText(QApplication::translate("additionaly", "\320\220\320\275\321\203\320\273\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\247\320\265\320\272", Q_NULLPTR));
        collectionMoney->setText(QApplication::translate("additionaly", "\320\230\320\275\320\272\320\260\321\201\320\260\321\206\320\270\321\217", Q_NULLPTR));
        enteringMoney->setText(QApplication::translate("additionaly", "\320\222\320\275\320\265\321\201\320\265\320\275\320\270\320\265", Q_NULLPTR));
        sale->setText(QApplication::translate("additionaly", "\320\237\321\200\320\276\320\264\320\260\320\266\320\260", Q_NULLPTR));
        return_2->setText(QApplication::translate("additionaly", "\320\222\320\276\320\267\320\262\321\200\320\260\321\202", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class additionaly: public Ui_additionaly {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITIONALY_H
