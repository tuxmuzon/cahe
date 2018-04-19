#ifndef FISCAL_H
#define FISCAL_H
#include <QWidget>
#if defined(Q_OS_WIN32)
#include <QAxWidget>
#endif
#include <QSqlQuery>
#include <QApplication>
#include <QDebug>
#include <QDate>


class fiscal : public QObject{
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
    QString FNDiscountOperation(QList<QStringList> egaisgoods, QString FrN,  QString nal_sum, QString discont);
private:
    #if defined(Q_OS_WIN32)
    QAxWidget *drvFR = new QAxWidget();
    #endif
};
#endif // FISCAL_H
