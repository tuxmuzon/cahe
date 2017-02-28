#include "servicedialog.h"
#include "ui_servicedialog.h"

ServiceDialog::ServiceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceDialog){
    ui->setupUi(this);
}
ServiceDialog::~ServiceDialog(){
    delete ui;
}
void ServiceDialog::on_xReport_clicked(){
    emit xReport();
    this->close();
}
void ServiceDialog::on_zReport_clicked(){
    emit ZReport();
    this->close();
}
void ServiceDialog::on_StatusKKM_clicked(){
    emit StatusKKM();
    this->close();
}
void ServiceDialog::on_options_clicked(){
    emit OptionsKKM();
    this->close();
}
