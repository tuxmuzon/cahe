/********************************************************************************
** Form generated from reading UI file 'servicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVICEDIALOG_H
#define UI_SERVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServiceDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *StatusKKM;
    QPushButton *options;
    QPushButton *zReport;
    QPushButton *xReport;

    void setupUi(QWidget *ServiceDialog)
    {
        if (ServiceDialog->objectName().isEmpty())
            ServiceDialog->setObjectName(QStringLiteral("ServiceDialog"));
        ServiceDialog->resize(609, 336);
        gridLayout = new QGridLayout(ServiceDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        StatusKKM = new QPushButton(ServiceDialog);
        StatusKKM->setObjectName(QStringLiteral("StatusKKM"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StatusKKM->sizePolicy().hasHeightForWidth());
        StatusKKM->setSizePolicy(sizePolicy);
        StatusKKM->setStyleSheet(QStringLiteral("font: 28pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(StatusKKM, 1, 0, 1, 2);

        options = new QPushButton(ServiceDialog);
        options->setObjectName(QStringLiteral("options"));
        sizePolicy.setHeightForWidth(options->sizePolicy().hasHeightForWidth());
        options->setSizePolicy(sizePolicy);
        options->setStyleSheet(QStringLiteral("font: 28pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(options, 1, 2, 1, 1);

        zReport = new QPushButton(ServiceDialog);
        zReport->setObjectName(QStringLiteral("zReport"));
        sizePolicy.setHeightForWidth(zReport->sizePolicy().hasHeightForWidth());
        zReport->setSizePolicy(sizePolicy);
        zReport->setStyleSheet(QStringLiteral("font: 28pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(zReport, 0, 2, 1, 1);

        xReport = new QPushButton(ServiceDialog);
        xReport->setObjectName(QStringLiteral("xReport"));
        sizePolicy.setHeightForWidth(xReport->sizePolicy().hasHeightForWidth());
        xReport->setSizePolicy(sizePolicy);
        xReport->setStyleSheet(QStringLiteral("font: 28pt \"MS Shell Dlg 2\";"));

        gridLayout->addWidget(xReport, 0, 0, 1, 2);


        retranslateUi(ServiceDialog);

        QMetaObject::connectSlotsByName(ServiceDialog);
    } // setupUi

    void retranslateUi(QWidget *ServiceDialog)
    {
        ServiceDialog->setWindowTitle(QApplication::translate("ServiceDialog", "Form", Q_NULLPTR));
        StatusKKM->setText(QApplication::translate("ServiceDialog", "\320\241\321\202\320\260\321\202\321\203\321\201 \320\232\320\260\321\201\321\201\321\213", Q_NULLPTR));
        options->setText(QApplication::translate("ServiceDialog", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\232\320\260\321\201\321\201\321\213", Q_NULLPTR));
        zReport->setText(QApplication::translate("ServiceDialog", "Z-\320\236\321\202\321\207\320\265\321\202", Q_NULLPTR));
        xReport->setText(QApplication::translate("ServiceDialog", "X-\320\236\321\202\321\207\320\265\321\202", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ServiceDialog: public Ui_ServiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVICEDIALOG_H
