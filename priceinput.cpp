#include "priceinput.h"
#include "ui_priceinput.h"

priceInput::priceInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::priceInput){
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    QDoubleValidator* validator =  new QDoubleValidator( 0.0, 9999.0, 2 );
           validator->setNotation( QDoubleValidator::StandardNotation );
          ui->lineEdit->setValidator( validator );
}
priceInput::~priceInput(){
    delete ui;
}
void priceInput::on_zero_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"0");
}
void priceInput::on_clear_clicked(){
    ui->lineEdit->clear();
}
void priceInput::on_dote_clicked(){
   ui->lineEdit->setText(ui->lineEdit->text()+",");
}
void priceInput::on_enter_clicked(){
    QString price=ui->lineEdit->text();
    ui->lineEdit->clear();   
    price.replace(",",".");
    emit priceEntering(price);    
    //qlog введена цена в ручную price
    this->close();
}
void priceInput::on_one_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"1");
}
void priceInput::on_two2_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"2");
}
void priceInput::on_three_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"3");
}
void priceInput::on_four_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"4");
}
void priceInput::on_five_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"5");
}
void priceInput::on_six_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"6");
}
void priceInput::on_erase_clicked(){
    ui->lineEdit->backspace();
}
void priceInput::on_seven_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"7");
}
void priceInput::on_eight_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"8");
}
void priceInput::on_nine_clicked(){
    ui->lineEdit->setText(ui->lineEdit->text()+"9");
}
void priceInput::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Enter){
        on_enter_clicked();
    }
    QWidget::keyPressEvent(event);
}
