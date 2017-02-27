#include "additionaly.h"
#include "ui_additionaly.h"

additionaly::additionaly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::additionaly){
    ui->setupUi(this);
}

additionaly::~additionaly(){
    delete ui;
}

void additionaly::on_return_2_clicked(){
    emit returnSale();
    this->close();
}

void additionaly::on_sale_clicked(){
    emit sale();
    this->close();
}

void additionaly::on_enteringMoney_clicked(){
    emit enteringMoney();
    this->close();
}

void additionaly::on_collectionMoney_clicked(){
    emit collectionMoney();
    this->close();
}

void additionaly::on_resumePrint_clicked(){
    emit resumePrint();
    this->close();
}

void additionaly::on_cancelSale_clicked(){
    emit cancelSale();
    this->close();
}
