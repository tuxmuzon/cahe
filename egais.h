#ifndef EGAIS_H
#define EGAIS_H

#include <QObject>
#include <QList>
#include "QDebug"
#include "QSqlQuery"
#include "QFile"
#include "QXmlStreamWriter"
#include "QProcess"
#include "fiscal.h"
#include "QMessageBox"
#include "QFileDialog"
#include <QApplication>
class egais : public QObject
{
    Q_OBJECT
public:
    explicit egais(QObject *parent = 0);

signals:

public slots:  
    QString getalcocode( QString axcise_mark);
    QString GetEgaisString(QList<QStringList> egaisgoods, QString FrN, int VidCheka);
    QStringList ParseXML();

};

#endif // EGAIS_H
