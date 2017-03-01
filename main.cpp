#include <QApplication>
#include "rr_cash.h"
#include <servicedialog.h>
#include <additionaly.h>
#include <priceinput.h>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);  
   RR_Cash w;
    w.showMaximized();
    //соединяем панель Сервис  567567567
    ServiceDialog service;
    QObject::connect(&w,SIGNAL(serviceDialog()),&service,SLOT(close()));
    QObject::connect(&w,SIGNAL(serviceDialog()),&service,SLOT(show()));
        QObject::connect(&service,SIGNAL(xReport()),&w,SLOT(on_actionX_triggered()));
        QObject::connect(&service,SIGNAL(ZReport()),&w,SLOT(on_actionZ_triggered()));
        QObject::connect(&service,SIGNAL(StatusKKM()),&w,SLOT(on_action_2_triggered()));
        QObject::connect(&service,SIGNAL(OptionsKKM()),&w,SLOT(on_action_4_triggered()));
    additionaly dopFunc; 
    QObject::connect(&w,SIGNAL(additionalyDialog()),&dopFunc,SLOT(close()));
    QObject::connect(&w,SIGNAL(additionalyDialog()),&dopFunc,SLOT(show()));
        QObject::connect(&dopFunc,SIGNAL(returnSale()),&w,SLOT(on_action_6_triggered()));
        QObject::connect(&dopFunc,SIGNAL(sale()),&w,SLOT(on_action_7_triggered()));
        QObject::connect(&dopFunc,SIGNAL(collectionMoney()),&w,SLOT(on_action_8_triggered()));
        QObject::connect(&dopFunc,SIGNAL(enteringMoney()),&w,SLOT(on_action_5_triggered()));
        QObject::connect(&dopFunc,SIGNAL(resumePrint()),&w,SLOT(on_action_3_triggered()));
        QObject::connect(&dopFunc,SIGNAL(cancelSale()),&w,SLOT(on_action_triggered()));
    priceInput priceInputWindow;
    QObject::connect(&w,SIGNAL(moneaction()),&priceInputWindow,SLOT(show()));
    QObject::connect(&priceInputWindow,SIGNAL(priceEntering(QString)),&w,SLOT(getaPrice(QString)));
    return a.exec();
}
