#ifndef FISCAL_H
#define FISCAL_H

//#include <QObject>
#include <QWidget>
//#include <QtGui>
#include <QAxWidget>
//#include "QAxObject"
#include <QSqlQuery>
#include <QApplication>


class fiscal : public QObject
{
    Q_OBJECT
public:

    explicit fiscal(QObject *parent = 0);

signals:

public slots:
    QString GetStatus(QString FrN);
    QString CancelDocument(QString FrN);
    QString Get_Z_Report(QString FrN);
    QString Get_X_Report(QString FrN);
    QString SaleDocument(QList<QStringList> egaisgoods,  QString FrN, QString nal_sum, QString discont);
    QString ReturnDocument(QList<QStringList> egaisgoods, QString FrN,  QString nal_sum, QString discont);
    QString collection(QString nal_sum, QString FrN); //Инкасация
    QString entering_monye(QString nal_sum, QString FrN); //внесение
    QString PrintURL(QStringList url, QString nal_sum);
    QString GetDateTime(QString FrN);
    QString GetCurrentShift(QString FrN);
    QString GetCurrentDoc(QString FrN);
    QString GetSerialNumber(QString FrN);

private:

    QAxWidget *drvFR = new QAxWidget();


};

#endif // FISCAL_H
