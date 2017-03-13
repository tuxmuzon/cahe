#include "priceinput.h"
#include "ui_priceinput.h"
#include <QDebug>
bool comaFind=false;
int realCount=0;
priceInput::priceInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::priceInput){
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    //   QDoubleValidator* validator =  new QDoubleValidator( 0.0, 9999.0, 2 );
    //         validator->setNotation( QDoubleValidator::ScientificNotation );
    //       ui->lineEdit->setValidator( validator );
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
}
priceInput::~priceInput(){
    delete ui;
}
void priceInput::on_zero_clicked(){
    addSymbol("0");
}
void priceInput::on_clear_clicked(){
    ui->lineEdit->clear();
    comaFind=false;
    realCount=0;
}
void priceInput::on_dote_clicked(){
    addSymbol(",");
}
void priceInput::on_enter_clicked(){
    QString price=ui->lineEdit->text();
    ui->lineEdit->clear();
    on_clear_clicked();
    price.replace(",",".");
    if (price.toDouble()>0){
        emit priceEntering(price);
        //qlog введена цена в ручную price
        this->close();
    }
    else  QMessageBox::warning(0,"Предупреждение", "Цена должна быть больше 0");
}
void priceInput::on_one_clicked(){
    addSymbol("1");
}
void priceInput::on_two2_clicked(){
    addSymbol("2");
}
void priceInput::on_three_clicked(){
    addSymbol("3");
}
void priceInput::on_four_clicked(){
    addSymbol("4");
}
void priceInput::on_five_clicked(){
    addSymbol("5");
}
void priceInput::on_six_clicked(){
    addSymbol("6");
}
void priceInput::on_erase_clicked(){
    ui->lineEdit->backspace();
    if (realCount>0) {realCount-1;}
    if (realCount==0) {comaFind=false;}
    if (ui->lineEdit->text().length()==0) {
        on_clear_clicked();
    }
}
void priceInput::on_seven_clicked(){
    addSymbol("7");
}
void priceInput::on_eight_clicked(){
    addSymbol("8");
}
void priceInput::on_nine_clicked(){
    addSymbol("9");
}
void priceInput::keyPressEvent(QKeyEvent *event) {
    qDebug() <<"нажат кей "<< event->key();
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
        on_enter_clicked();
    }
    if(event->key()==Qt::Key_F11){
        on_clear_clicked();
    }
    if(event->key()==46){
        addSymbol(",");
    }
    if(event->key()==44){
        addSymbol(",");
    }
    if(event->key()==Qt::Key_0){
        addSymbol("0");
    }
    if(event->key()==Qt::Key_1){
        addSymbol("1");
    }
    if(event->key()==Qt::Key_2){
        addSymbol("2");
    }
    if(event->key()==Qt::Key_3){
        addSymbol("3");
    }
    if(event->key()==Qt::Key_4){
        addSymbol("4");
    }
    if(event->key()==Qt::Key_5){
        addSymbol("5");
    }
    if(event->key()==Qt::Key_6){
        addSymbol("6");
    }
    if(event->key()==Qt::Key_7){
        addSymbol("7");
    }
    if(event->key()==Qt::Key_8){
        addSymbol("8");
    }
    if(event->key()==Qt::Key_9){
        addSymbol("9");
    }
    if(event->key()==Qt::Key_Backspace){
        on_erase_clicked();
    }
    // QWidget::keyPressEvent(event);
}

void priceInput::addSymbol(QString symbol){
    if(symbol==","&&comaFind==false){
        qDebug() << "1";
        comaFind=true;
        ui->lineEdit->setText(ui->lineEdit->text()+symbol);
    }
    if(symbol==","&&comaFind==true){
        qDebug() << "2";
    }
    if(symbol!=","&&comaFind==true&&realCount<2){
        realCount=realCount+1;
        qDebug() << "3";
        ui->lineEdit->setText(ui->lineEdit->text()+symbol);
    }
    if(symbol!=","&&comaFind==false){
        qDebug() << "4";
        ui->lineEdit->setText(ui->lineEdit->text()+symbol);
    }
}
