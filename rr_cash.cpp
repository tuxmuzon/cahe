#include "rr_cash.h"
#include "ui_rr_cash.h"


egais newEgais;
QStringList kkms;
QString discont;

RR_Cash::RR_Cash(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::RR_Cash){
    ui->setupUi(this);
    ui->table_tovar->hideColumn(5);
    ui->table_tovar->hideColumn(6);
    ui->table_tovar->hideColumn(7);
    ui->table_tovar->hideColumn(8);
    ui->table_tovar->hideColumn(9);
    ui->table_tovar->resizeColumnsToContents();
    ui->table_tovar->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    KolVo = 1;
    SummaItog = 0;
    discont = "0";
    ui->discont_2->setText(discont);
    UpdateVidCheka(1);
    ui->label_KolVo->setText(trUtf8("1 x")); //Поле для количества
    ui->label_Itog->setText(trUtf8("0.00"));
    QString result_code = SHM.GetStatus("1");
    if(result_code=="0") {
        // log  "KKM 1 OK ";
    }  else{
        QMessageBox::warning(0,"Ошибка КАССЫ 1", result_code+"УСТРАНИТЕ ОШИБКУ И НАЖМИТЕ ЗАПРОСИТЬ СТАТУС");
       // log "Ошибка КАССЫ 1" + result_code+"УСТРАНИТЕ ОШИБКУ И НАЖМИТЕ ЗАПРОСИТЬ СТАТУС"
    }
 result_code = SHM.GetStatus("2");
    if(result_code=="0") {
        //log  "KKM 2 OK";
    }  else{
        QMessageBox::warning(0,"Ошибка КАССЫ 2", result_code+"УСТРАНИТЕ ОШИБКУ И НАЖМИТЕ ЗАПРОСИТЬ СТАТУС");
        // log "Ошибка КАССЫ 2" + result_code+"УСТРАНИТЕ ОШИБКУ И НАЖМИТЕ ЗАПРОСИТЬ СТАТУС"
    }
    if (! QFile::exists("settings.conf")){
        // log не найден файл с настройками, генерируем по дефолту
        QSettings *settingscr = new QSettings("settings.conf",QSettings::IniFormat);
        settingscr->setValue("main/version","0.1.1");  //устанавливаем значение value=1
           settingscr->setValue("database/path","main.db");
           settingscr->sync();
    }
     QSettings *settings = new QSettings("settings.conf",QSettings::IniFormat);
if (! QFile::exists(settings->value("database/path").toString())){
   //log отствует файл бд проверьте его наличие, размер должен быть !=0
    QMessageBox::warning(0,"Ошибка БД", "УСТРАНИТЕ ОШИБКУ ПУТЬ К БД НЕ НАЙДЕН");
}
    dbase.setDatabaseName(settings->value("database/path").toString());
    if (!dbase.open()) {
        qDebug() << dbase.lastError();
         QMessageBox::warning(0,"Ошибка БД", dbase.lastError().text());
        qDebug() << "Db file not found";
    }
    QSqlQuery query("select logical_name, name from device where active=\"1\" and type=\"FR\" ");
    while (query.next()) {
        kkms << query.value(1).toString();
    }
}
RR_Cash::~RR_Cash(){
    delete ui;
}
void RR_Cash::on_Exit_triggered() {
    RR_Cash::close();
}
void RR_Cash::keyPressEvent(QKeyEvent *event) {
    //Перемещение по строкам для сторнирования продаж
    if (event->key()==Qt::Key_Down) {
        ui->table_tovar->selectRow(ui->table_tovar->currentRow()+1);
    }
    //Перемещение по строкам для сторнирования продаж
    if (event->key()==Qt::Key_Up){
        ui->table_tovar->selectRow(ui->table_tovar->currentRow()-1);
    }
    //выполнение операции
    if (event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return) {
        if (ui->table_tovar->rowCount()>0&& VidCheka==1) {// чек продажи, здесь продажу + запрос егаис, если егаис не продался то спросить продавть без егаиса или нет?          
            QString sum_nall;
            if (ui->label_KolVo->text()!=""){
                sum_nall = ui->label_KolVo->text();
            } else  {sum_nall = ui->label_Itog->text();}
            qApp->processEvents();
            if(sum_nall.toDouble()>ui->label_Itog->text().toDouble()){
                QString change;
                qDebug() << "sum nall" << sum_nall;
                qDebug() << "lable_itog" << ui->label_Itog->text().replace(",",".");
                qDebug() << "sale_calculate" << (1-0.01*discont.toDouble());
                change = change.number((sum_nall.replace(",",".").toDouble()-ui->label_Itog->text().replace(",",".").toDouble()*(1-0.01*discont.toDouble())));
                qDebug() << "change " << change.replace(".",",");
                ui->label_KolVo->setText("СДАЧА : " + change);
            }
            if ( sum_nall.toDouble()<ui->label_Itog->text().toDouble()) {
            } else  {
                while (ui->table_tovar->rowCount()>0) {
                    qDebug() << "формируем список для отправки в егаис и фискальник.";
                    QStringList urlKEP;
                    QList<QStringList> goods;
                    // ui->table_tovar->removeRow(0);
                    QStringList row;
                    for (int i=0; i < ui->table_tovar->rowCount(); i++){
                        row.clear();
                        for (int j=0; j< ui->table_tovar->columnCount();j++){
                            row << ui->table_tovar->item(i,j)->text();
                        }
                        // qDebug() << row;
                        goods << row;
                    }
                    qDebug() << "берем группу печати 0 го элемента";
                    row.clear();
                    row = goods[0];
                    QString group_print= row[8];
                    QList<QStringList> goodsGroupPrint;
                    double summ=0;
                    QString summ_row;
                    qDebug() << "отбираем товары из этой группы печати";
                    for (int i=0; i < goods.length(); i++){
                        row.clear();
                        row = goods[i];
                        row << QString::number(i);
                        qDebug() << row;
                        if (row[8]==group_print){
                            goodsGroupPrint << row;
                            summ_row=row[4];
                            summ=summ+summ_row.replace(",",".").toDouble();
                        }
                    }
                    summ=summ*(1-0.01*discont.toDouble());
                    qDebug() << "находим алкотовары";
                    QList<QStringList> goodsAlcoPrint;
                    for (int i=0; i < goodsGroupPrint.length(); i++){
                        row.clear();
                        row = goodsGroupPrint[i];
                        //  qDebug() << row;
                        if (row[5]!=""){
                            goodsAlcoPrint << row;
                        }
                    }
                    //провеярем alcolist что он не пустой
                    if(!goodsAlcoPrint.empty()){
                        qDebug() << "alcolist is not clean";
                       ui->label_KolVo->setText("Отправка в ЕГАИС");
                        if(newEgais.GetEgaisString(goodsAlcoPrint,group_print)!="-1"){
                             ui->label_KolVo->setText("Разбор ответа");
                            urlKEP =    newEgais.ParseXML();
                            qDebug() << "GETT"  << urlKEP;
                            if (SHM.GetStatus(group_print)=="0"&&urlKEP[0]!="-1"){
                                 ui->label_KolVo->setText("Ответ успешен ,Печать чека № "+group_print);
                                if (SHM.SaleDocument(goodsGroupPrint,group_print,QString::number(summ).replace(".",","),discont)=="0"){
                                    insert_sale(group_print,VidCheka,goodsGroupPrint);
                                    UpdateItog();
                                    discont = "0";
                                    for(int i=0; i < goodsGroupPrint.length();i++) {
                                        row.clear();
                                        row << goodsGroupPrint[i];
                                        QString id=row[10];
                                        ui->table_tovar->removeRow(id.toInt());
                                    }
                                }
                                ui->label_KolVo->setText("Ответ успешен ,Печать QR кода");
                                SHM.PrintURL(urlKEP,group_print);
                            } else { QMessageBox::warning(0,"Ошибка КАССЫ", "Касса          "+group_print + " " +SHM.GetStatus(group_print)); break;}
                            //начинаем парсить ответ
                        } else {break;}
                    } else {
                        if (SHM.GetStatus(group_print)=="0"){
                            ui->label_KolVo->setText("печать чека № "+group_print);
                            if (SHM.SaleDocument(goodsGroupPrint,group_print,QString::number(summ).replace(".",","),discont)=="0"){
                                qDebug() << "discont" << discont;
                                insert_sale(group_print,VidCheka,goodsGroupPrint);
                                UpdateItog();
                                discont = "0";
                                for(int i=0; i < goodsGroupPrint.length();i++) {
                                    row.clear();
                                    row << goodsGroupPrint[i];
                                    QString id=row[10];
                                    ui->table_tovar->removeRow(id.toInt());
                                }
                            }
                        } else {QMessageBox::warning(0,"Ошибка КАССЫ", "Касса "+group_print + " " +SHM.GetStatus(group_print)); break;}
                    }
                }
            }
            ui->discont_2->setText(discont);
        }
        if (VidCheka==3){
            QString text = ui->label_KolVo->text();
            QInputDialog *dialog = new QInputDialog();
            bool accepted;
            QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
            QSqlQuery query("select logical_name from device where name=\""+item+"\"");
            query.next();
            if (accepted){
                QString status= SHM.entering_monye(text,query.value(0).toString());
                if(status=="0") {
                    QMessageBox::warning(0,"Внесение успешно", "Внесение успешно");
                    insert_chek(query.value(0).toString(),VidCheka,text);
                    UpdateVidCheka(1);
                }
                else{
                    QMessageBox::warning(0,"Ошибка", status);
                }
            }
        }
        if (VidCheka==4){
            QString text = ui->label_KolVo->text();
            QInputDialog *dialog = new QInputDialog();
            bool accepted;
            QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
            QSqlQuery query("select logical_name from device where name=\""+item+"\"");
            query.next();
            //  QString test = query.lastError().text();
            // cout << test;
            qDebug() << "fr №" << query.value(0).toString();
            if (accepted){
                QString status= SHM.collection(text,query.value(0).toString());
                if(status=="0") {
                    QMessageBox::warning(0,"Выдача успешна", "Выдача успешна");
                    insert_chek(query.value(0).toString(),VidCheka,text);
                    UpdateVidCheka(1);
                }
                else{
                    qDebug() << "fisal_error";
                    QMessageBox::warning(0,"Ошибка", status);
                }
            }
        }
        if (ui->table_tovar->rowCount()>0&&VidCheka==2){ // возвтрат            
            QString sum_nall;
            if (ui->label_KolVo->text()!=""){
                sum_nall = ui->label_KolVo->text();
            } else  {sum_nall = ui->label_Itog->text();}
            if(sum_nall.toDouble()>ui->label_Itog->text().toDouble()){
                QString change;
                qDebug() << "sum nall" << sum_nall;
                qDebug() << "lable_itog" << ui->label_Itog->text().replace(",",".");
                qDebug() << "sale_calculate" << (1-0.01*discont.toDouble());
                change = change.number((sum_nall.replace(",",".").toDouble()-ui->label_Itog->text().replace(",",".").toDouble()*(1-0.01*discont.toDouble())));
                qDebug() << "change " << change.replace(".",",");
                ui->label_KolVo->setText("СДАЧА : " + change);
            }
            if ( sum_nall.toDouble()<ui->label_Itog->text().toDouble()) {
                QMessageBox::warning(0,"Ошибка", "Сумма наличности меньше суммы чека");
            } else  {
                while (ui->table_tovar->rowCount()>0) {
                    qDebug() << "формируем список для отправки в егаис и фискальник.";
                    QStringList urlKEP;
                    QList<QStringList> goods;
                    // ui->table_tovar->removeRow(0);
                    QStringList row;
                    for (int i=0; i < ui->table_tovar->rowCount(); i++){
                        row.clear();
                        for (int j=0; j< ui->table_tovar->columnCount();j++){
                            row << ui->table_tovar->item(i,j)->text();
                        }
                        // qDebug() << row;
                        goods << row;
                    }
                    qDebug() << "берем группу печати 0 го элемента";
                    row.clear();
                    row = goods[0];
                    QString group_print= row[8];
                    QList<QStringList> goodsGroupPrint;
                    double summ=0;
                    QString summ_row;
                    qDebug() << "отбираем товары из этой группы печати";
                    for (int i=0; i < goods.length(); i++){
                        row.clear();
                        row = goods[i];
                        row << QString::number(i);
                        qDebug() << row;
                        if (row[8]==group_print){
                            goodsGroupPrint << row;
                            summ_row=row[4];
                            summ=summ+summ_row.replace(",",".").toDouble();
                        }
                    }
                    summ=summ*(1-0.01*discont.toDouble());
                    qDebug() << "находим алкотовары";
                    QList<QStringList> goodsAlcoPrint;
                    for (int i=0; i < goodsGroupPrint.length(); i++){
                        row.clear();
                        row = goodsGroupPrint[i];
                        //  qDebug() << row;
                        if (row[5]!=""){
                            goodsAlcoPrint << row;
                        }
                    }
                    //провеярем alcolist что он не пустой
                    if(!goodsAlcoPrint.empty()){
                        qDebug() << "alcolist is not clean";
                        if(newEgais.GetEgaisString(goodsAlcoPrint,group_print)!="-1"){
                            urlKEP =    newEgais.ParseXML();
                            qDebug() << "GETT"  << urlKEP;
                            if (SHM.GetStatus(group_print)=="0"&&urlKEP[0]!="-1"){
                                if (SHM.ReturnDocument(goodsGroupPrint,group_print,QString::number(summ).replace(".",","),discont)=="0"){
                                    insert_sale(group_print,VidCheka,goodsGroupPrint);
                                    UpdateItog();
                                    discont = "0";
                                    for(int i=0; i < goodsGroupPrint.length();i++) {
                                        row.clear();
                                        row << goodsGroupPrint[i];
                                        QString id=row[10];
                                        ui->table_tovar->removeRow(id.toInt());
                                    }
                                }
                                SHM.PrintURL(urlKEP,group_print);
                            } else { QMessageBox::warning(0,"Ошибка КАССЫ", "Касса          "+group_print + " " +SHM.GetStatus(group_print)); break;}
                            //начинаем парсить ответ
                        } else {break;}
                    } else {
                        if (SHM.GetStatus(group_print)=="0"){
                            if (SHM.ReturnDocument(goodsGroupPrint,group_print,QString::number(summ).replace(".",","),discont)=="0"){
                                qDebug() << "discont" << discont;
                                insert_sale(group_print,VidCheka,goodsGroupPrint);
                                UpdateItog();
                                discont = "0";
                                for(int i=0; i < goodsGroupPrint.length();i++)
                                {
                                    row.clear();
                                    row << goodsGroupPrint[i];
                                    QString id=row[10];
                                    ui->table_tovar->removeRow(id.toInt());
                                }
                            }
                        } else {QMessageBox::warning(0,"Ошибка КАССЫ", "Касса "+group_print + " " +SHM.GetStatus(group_print)); break;}
                    }
                }
            }
            UpdateVidCheka(1);
            ui->discont_2->setText(discont);
        }
    }
    if (event->key()==Qt::Key_Tab){
        on_tab_2_clicked();
    }
    if (event->key()>=Qt::Key_0 && event->key()<=Qt::Key_9) { //Цифровые клавиши 0..9
        //qDebug() << "1" << ui->label_main->text();
        //в глобальную переменную складывать куски штрих-кода
        QString str = QString(event->key());
        qDebug() <<str;
        barcode = barcode+str;
    }
    if ((event->key()>=Qt::Key_0 && event->key()<=Qt::Key_9) ||  event->key()==44) { //Цифровые клавиши 0..9+ . символ точки
        // Здесь собираем строку для количества, игнорируем Вторую точку,
        //нужно добавить что если ввели , то в начале ввести 0
        // три знака после , 000
        bool dot_find;
        dot_find = false;
        QString str = QString(event->key());
        count = count+str;
        ui->label_KolVo->setText(count);        
        for (int i = 0; i< count.length(); i++ ) {
            if ((QString(count[i])==QString(",") || count[i]=='.' )&& dot_find==true) {                
                count.chop(1);
                ui->label_KolVo->setText(count);             
            }
            if (i>2 && (count[i-3]==',' || count[i-3]=='.')){
                count.chop(1);
                ui->label_KolVo->setText(count);
            }
            if (QString(count[i])==QString(",") || count[i]=='.') {
                count[i]='.';
                dot_find=true;             
            }
        }
    }
    else if (event->key()==42) {// символ * ввод количества
        if (ui->table_tovar->rowCount()>0 && ui->table_tovar->item(ui->table_tovar->currentRow(),5)->text()==""){            
            ui->table_tovar->setItem(ui->table_tovar->currentRow(),1,new QTableWidgetItem(count));
            QString sum_row;
            sum_row.setNum(ui->table_tovar->item(ui->table_tovar->currentRow(),3)->text().replace(",",".").toDouble()*ui->table_tovar->item(ui->table_tovar->currentRow(),1)->text().toDouble());
            qDebug() << sum_row;
            ui->table_tovar->setItem(ui->table_tovar->currentRow(),4,new QTableWidgetItem(sum_row));
            RR_Cash::UpdateItog();
            barcode.clear();
            count.clear();
        }
    }
    //Удаляем текущую строку.
    else if (event->key()==Qt::Key_Minus) {
        ui->table_tovar->removeRow(ui->table_tovar->currentRow());
        RR_Cash::UpdateItog();
    }
    if (event->key()==Qt::Key_Q) {
        count.clear();
        barcode.clear();        
        for(int i=ui->table_tovar->rowCount();i>=0;i--) {
            // qDebug() << i;
            ui->table_tovar->removeRow(i);
        }
    }
    //скидка
    if(event->key()==Qt::Key_F11){
        on_discont_clicked();
    }
    //поиск по коду
    if(event->key()==Qt::Key_F10){
        on_tab_2_clicked();
    }
    switch(event->key()) {
    case Qt::Key_X:
        if(event->modifiers() & Qt::ShiftModifier) {
            qDebug() << " Ctrl Shift + X";
             count.clear();
            barcode.clear();
            ui->label_Itog->clear();
            ui->label_KolVo->clear();
            ui->label_Itog->clear();            
            for(int i=ui->table_tovar->rowCount();i>=0;i--) {
                ui->table_tovar->removeRow(i);
            }
        }
    default:
        QWidget::keyPressEvent(event);
    }
}
void RR_Cash::UpdateVidCheka(int Vid){
    if (Vid == 1) {
        VidCheka = 1;
        ui->label_VidCheka->setText(trUtf8("Продажа"));
    }else if (Vid == 2){
        VidCheka = 2;
        ui->label_VidCheka->setText(trUtf8("Возврат"));
    }else if (Vid == 3){
        VidCheka = 3;
        ui->label_VidCheka->setText(trUtf8("Внесение"));
    }else if (Vid == 4){
        VidCheka = 4;
        ui->label_VidCheka->setText(trUtf8("Выплата"));
    }
}
void RR_Cash::UpdateItog(){
    double result=0;
    for (int i=0;i<ui->table_tovar->rowCount();i++) {
        result=ui->table_tovar->item(i,4)->text().replace(",",".").toDouble()+result;
    }
    QString lablereuslt;
    lablereuslt.setNum(result);
    ui->label_Itog->setText(lablereuslt);
}
void RR_Cash::on_actionZ_triggered(){ // Z - отчет 5 - код!!
    QInputDialog *dialog = new QInputDialog();
    bool accepted;
    QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
    QSqlQuery query("select logical_name from device where name=\""+item+"\"");
    query.next();    
    qDebug() << "fr №" << query.value(0).toString();
    if (accepted){
        QString status= SHM.Get_Z_Report(query.value(0).toString());
        if(status=="0") {
            QMessageBox::warning(0,"Z отчет снят", "Успешно");
            insert_chek(query.value(0).toString(),5,"");
            UpdateVidCheka(1);
        }
        else{
            qDebug() << "fisal_error";
            QMessageBox::warning(0,"Ошибка", status);
        }
    }
}
void RR_Cash::on_actionX_triggered(){ // Х - отчет 6 код
    QInputDialog *dialog = new QInputDialog();
    bool accepted;
    QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
    QSqlQuery query("select logical_name from device where name=\""+item+"\"");
    query.next();
    //  QString test = query.lastError().text();
    // qDebug() << test;
    qDebug() << "fr №" << query.value(0).toString();
    if (accepted){
        QString status= SHM.Get_X_Report(query.value(0).toString());
        if(status=="0") {
            QMessageBox::warning(0,"Х отчет снят", "Успешно");
            insert_chek(query.value(0).toString(),6,"");
            UpdateVidCheka(1);
        }
        else{
            qDebug() << "fisal_error";
            QMessageBox::warning(0,"Ошибка", status);
        }
    }
}
void RR_Cash::on_action_4_triggered(){ //Окно настроек драйвера
    // вынести в fiscal
    QAxWidget *drvFR = new QAxWidget("AddIn.DrvFR");
    drvFR->setControl("AddIn.DrvFR");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Connect()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("ShowProperties()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Disconnect()");
}
void RR_Cash::on_action_2_triggered(){ //проверка статуса кассы
    QInputDialog *dialog = new QInputDialog();
    bool accepted;
    QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
    QSqlQuery query("select logical_name from device where name=\""+item+"\"");
    query.next();
    //  QString test = query.lastError().text();
    // cout << test;
    qDebug() << "fr №" << query.value(0).toString();
    if (accepted){
        QString status= SHM.GetStatus(query.value(0).toString());
        if(status=="0") {
            QMessageBox::warning(0,"KKM Доступна", "Можно продолжать работу");
        }
        else{
            qDebug() << "fisal_error";
            QMessageBox::warning(0,"Ошибка", status);
        }
    }
}
void RR_Cash::on_action_triggered(){ // Отмена текущего чека
    QInputDialog *dialog = new QInputDialog();
    bool accepted;
    QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
    QSqlQuery query("select logical_name from device where name=\""+item+"\"");
    query.next();
    //  QString test = query.lastError().text();
    // cout << test;
    qDebug() << "fr №" << query.value(0).toString();
    if (accepted){
        QString status= SHM.CancelDocument(query.value(0).toString());
        if(status=="0") {
            QMessageBox::warning(0,"Чек отменен ", "Можно продолжать работу");
        }
        else{
            qDebug() << "fisal_error";
            QMessageBox::warning(0,"Ошибка", status);
        }
    }
}
void RR_Cash::on_action_3_triggered(){ //Продолжить печать
    //вынести в фискал
    QInputDialog *dialog = new QInputDialog();
    bool accepted;
    QString item = dialog->getItem(0, "Выберете Кассу", "Номер касс", kkms, 0, false, &accepted);
    QSqlQuery query("select logical_name from device where name=\""+item+"\"");
    query.next();
    //  QString test = query.lastError().text();
    // cout << test;
    qDebug() << "fr №" << query.value(0).toString();
    if (accepted){
        QAxWidget *test = new QAxWidget("AddIn.DrvFR");
        test->setControl("AddIn.DrvFR");
        test->dynamicCall("LDNumber",query.value(0).toString());
        test->dynamicCall("SetActiveLD()");
        test->setProperty("Password", "30");
        test->dynamicCall("Connect()");
        test->setProperty("Password", "30");
        test->dynamicCall("ContinuePrint()");
        test->setProperty("Password", "30");
        test->dynamicCall("Disconnect()");
    }
}
void RR_Cash::on_action_6_triggered() {// Меняем вид чека на "Возврат"
    UpdateVidCheka(2);
    RR_Cash::saveLog("Изменили тип операции на возврат");
}
void RR_Cash::on_action_7_triggered() { // Меняем вид чека на "Продажа"
    UpdateVidCheka(1);
    saveLog("Изменили тип операции на продажа");
}
void RR_Cash::on_action_5_triggered(){ // Меняем вид чека на "Внесение"
    UpdateVidCheka(3);
    saveLog("Изменили тип операции на внесение");
}
void RR_Cash::on_action_8_triggered() { // Меняем вид чека на "Выплата"
    UpdateVidCheka(4);
    saveLog("Изменили тип операции на выплата");
}
void RR_Cash::on_action_9_triggered(){  // Выводит таблицу с товарами
    qDebug() << "Entren goods table";
    emit good_edit();
}
void RR_Cash::insert_chek(QString cahe_id, int oper_type, QString sum){
    QSqlQuery query;
    saveLog("Проведена операция "+oper_type+' cache '+cahe_id+'На сумму'+sum);
    query.prepare("INSERT INTO chek ( goods_code, count, price, cost, shift, sale_number, excise, date_time, ope_type, cahe_id ) "
                  "VALUES ( :goods_code, :count, :price, :cost, :shift, :sale_number, :excise, :date_time, :ope_type, :cahe_id)");
    query.bindValue(":goods_code", 0);
    query.bindValue(":count", 1);
    query.bindValue(":price", sum);
    query.bindValue(":cost", sum);
    query.bindValue(":shift", SHM.GetCurrentShift(cahe_id).toInt()+1);
    query.bindValue(":sale_number", SHM.GetCurrentDoc(cahe_id).toInt());
    query.bindValue(":excise", 0);
    query.bindValue(":date_time", SHM.GetDateTime(cahe_id));
    query.bindValue(":ope_type", oper_type);
    query.bindValue(":cahe_id", cahe_id);
    query.exec();
}
void RR_Cash::insert_sale(QString cahe_id, int oper_type, QList<QStringList> goods){
    QString CurentDoc =SHM.GetCurrentDoc(cahe_id);
    QString CurentShift =SHM.GetCurrentShift(cahe_id);
    QString CurentDateTime =SHM.GetDateTime(cahe_id);
    QStringList row;
    QSqlQuery query;
    saveLog("Проведена операция продажи"+cahe_id+" "+CurentDateTime+" № смены "+CurentShift+"№ документа"+CurentDoc);
    for (int i=0;i<goods.length();i++){
        row=goods[i];
        QString price=row[4];
        QString count=row[1];
        query.prepare("INSERT INTO chek ( goods_code, count, price, cost, shift, sale_number, excise, date_time, ope_type, cahe_id ) "
                      "VALUES ( :goods_code, :count, :price, :cost, :shift, :sale_number, :excise, :date_time, :ope_type, :cahe_id)");
        query.bindValue(":goods_code", row[9]);
        query.bindValue(":count", count);
        query.bindValue(":price", price);
        query.bindValue(":cost",row[4]);
        query.bindValue(":shift", CurentShift.toInt()+1);
        query.bindValue(":sale_number", CurentDoc.toInt()+1);
        query.bindValue(":excise", row[5]);
        query.bindValue(":date_time", CurentDateTime);
        query.bindValue(":ope_type", oper_type);
        query.bindValue(":cahe_id", cahe_id);
        query.exec();
    }
}
void RR_Cash::on_enter_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша ВВод");
}
void RR_Cash::on_clear_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Q, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша Очистка");
}
void RR_Cash::on_minus_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Minus, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша Минус, операция сторно");
}
void RR_Cash::on_product_clicked(){
    QKeyEvent event(QEvent::KeyPress, 42, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша * измененено количество");
}
void RR_Cash::on_tab_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша Tab Ввод шк кнопкой");
}
void RR_Cash::on_zero_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 0");
}
void RR_Cash::on_dote_clicked(){
    QKeyEvent event(QEvent::KeyPress, 44, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша .");
}
void RR_Cash::on_one_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 1");
}
void RR_Cash::on_two2_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_2, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 2");
}
void RR_Cash::on_three_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_3, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 3");
}
void RR_Cash::on_four_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_4, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 4");
}
void RR_Cash::on_five_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_5, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 5");
}
void RR_Cash::on_six_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_6, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 6");
}
void RR_Cash::on_seven_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_7, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 7");
}
void RR_Cash::on_eight_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_8, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 8");
}
void RR_Cash::on_nine_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_9, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша 9");
}
void RR_Cash::on_up_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша Up");
}
void RR_Cash::on_Down_clicked(){
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    saveLog("Нажата клавиша Down");
}
void RR_Cash::on_pushButton_clicked(){
    saveLog("очистка ввода");
    ui->label_KolVo->clear();
    barcode.clear();
    count.clear();
}
void RR_Cash::on_discont_clicked(){       
    if(ui->label_KolVo->text().toDouble()<=5&&ui->label_KolVo->text().toDouble()>0){
         ui->discont_2->setText(ui->label_KolVo->text());
        discont=ui->label_KolVo->text(); ui->label_KolVo->clear(); barcode.clear(); count.clear();
    QMessageBox::warning(0,"Установдена скидка ", "Поставили скидку "+discont+" процентов");
     saveLog(" установлена скидка"+discont);
     }
    else { QMessageBox::warning(0,"Не верный диапазон скидки ", "Проверьте ввод");
        saveLog(" неверная скидка скидка"+discont);
    }
}
void RR_Cash::on_service_clicked(){
    emit serviceDialog();
    saveLog(" вызван сервисный диалог");
}
void RR_Cash::on_additionaly_clicked(){
    emit additionalyDialog();
    saveLog("вызван дополнительный диалог");
}
void RR_Cash::getaPrice(QString price){
    // log цена price введена в ручную
    ui->table_tovar->setItem(0,3,new QTableWidgetItem(price));
    QString sum_row;
    sum_row.setNum(ui->table_tovar->item(0,3)->text().replace(",",".").toDouble()*ui->table_tovar->item(0,1)->text().replace(",",".").toDouble());
    ui->table_tovar->setItem(0,4,new QTableWidgetItem(sum_row.replace(".",",")));
    UpdateItog();    
}
void RR_Cash::on_tab_2_clicked(){
    // лог тоже поиск по коду, логика как со ШК, можно свернуть в процедуру
    barcode=ui->label_KolVo->text();
    QString queryString;
    if (barcode.length()>5) {
        queryString="SELECT name, units, price, alc, excise, code, barcode, group_print  FROM goods, barcode WHERE barcode.goods_id=goods.code and barcode.barcode="+barcode;
    } else {
    queryString="SELECT name, units, price, alc, excise, code, barcode, group_print, volume  FROM goods, barcode WHERE barcode.goods_id=goods.code and user_code="+barcode;
        }
    QSqlQuery query(queryString);
    query.next();
qDebug()    << query.value(0).toString();
    if(query.value(0).toString()!="") {
        // ищем товар в текущем виджете, если его нет то перейдем дальше
        bool find_repeat, ok;
        find_repeat=false;
        for(int i =0; i< ui->table_tovar->rowCount(); i++){
            qDebug() << "barcode in query" << query.value(7).toString();
            if (ui->table_tovar->item(i,7)->text()==query.value(6).toString() && ui->table_tovar->item(i,5)->text()=="") {
                ui->table_tovar->setItem(i,1,new QTableWidgetItem(QString::number(ui->table_tovar->item(i,1)->text().toInt()+1)));
                QString sum_row;
                sum_row.setNum(ui->table_tovar->item(ui->table_tovar->currentRow(),3)->text().replace(",",".").toDouble()*ui->table_tovar->item(ui->table_tovar->currentRow(),1)->text().toDouble());
                qDebug() << sum_row.replace(".",",");
                ui->table_tovar->setItem(ui->table_tovar->currentRow(),4,new QTableWidgetItem(sum_row));
                find_repeat=true;
                saveLog( "добавлен "+query.value(0).toString()+ "повторяйщийся товар  код "+query.value(5).toString()+" цена "+query.value(2).toString());
            }
        }
         //
        if (!find_repeat){
            qDebug() << "return id" << query.value(0).toString() << QObject::tr("\n");
            ui->table_tovar->insertRow(0);
            ui->table_tovar->setItem(0,0,new QTableWidgetItem(query.value(0).toString()));
            ui->table_tovar->setItem(0,1,new QTableWidgetItem("1"));
            ui->table_tovar->setItem(0,2,new QTableWidgetItem(query.value(1).toString()));
            if(query.value(2).toString()=="0"){
                emit moneaction();
                ui->table_tovar->setItem(0,3,new QTableWidgetItem("0"));               
            }
            else {  ui->table_tovar->setItem(0,3,new QTableWidgetItem(QString::number(query.value(2).toDouble()).replace(".",","))); }
            QString sum_row;
            sum_row.setNum(ui->table_tovar->item(0,3)->text().replace(",",".").toDouble()*ui->table_tovar->item(0,1)->text().replace(",",".").toDouble());
            ui->table_tovar->setItem(0,4,new QTableWidgetItem(sum_row.replace(".",",")));
            ui->table_tovar->setItem(0,5,new QTableWidgetItem(""));
            ui->table_tovar->setItem(0,6,new QTableWidgetItem(""));
            ui->table_tovar->setItem(0,7,new QTableWidgetItem(query.value(6).toString()));
            ui->table_tovar->setItem(0,8,new QTableWidgetItem(query.value(7).toString()));
            ui->table_tovar->setItem(0,9,new QTableWidgetItem(query.value(5).toString()));
            saveLog( "добавлен "+query.value(0).toString()+ "товар  код "+query.value(5).toString()+" цена "+query.value(2).toString());
            ui->label_Itog->setText(sum_row.replace(".",","));
            ui->table_tovar->selectRow(0);
            ui->label_KolVo->clear();            
            if (query.value(4).toString()=="yes"){
                //keyboardInputInterval - сие свойство позволяет отличить штрих код от вводжа с клавы
                //                       QString lang = QApplication::inputMethod()->locale().name();
                //                      qDebug()<<lang;

                QString text = QInputDialog::getText(this, tr("Акцизный товар марка"),
                                                     tr("Отсканируйте акцизную марку"), QLineEdit::Normal,"", &ok);
                if (ok) {
                    alcochek = true;
                    barcode.clear();
                    ui->table_tovar->setItem(0,5,new QTableWidgetItem(text));                   
                    ui->table_tovar->setItem(0,6,new QTableWidgetItem(query.value(8).toString()));
                    qDebug() << ui->table_tovar->item(0,5)->text();
                    saveLog( "добавлен акцизный товар с кодом "+ query.value(5).toString() +" и маркой "+text);
                } else { ui->table_tovar->removeRow(0);}
            }
        }
    }
    else {
        saveLog("код"+barcode+"не найден");
        QMessageBox::warning(0,"Предупреждение", "Код не найден");
    }
    barcode.clear();
    count.clear();
    RR_Cash::UpdateItog();
}
void RR_Cash::on_price_clicked(){
    // пологике пересчет можно вынести в функцию отделюную
    QString sum_row;
     ui->table_tovar->setItem(ui->table_tovar->currentRow(),3,new QTableWidgetItem(ui->label_KolVo->text()));
     saveLog("Установлена цена в ручную "+ ui->label_KolVo->text());
     sum_row.setNum(ui->table_tovar->item(ui->table_tovar->currentRow(),3)->text().replace(",",".").toDouble()*ui->table_tovar->item(ui->table_tovar->currentRow(),1)->text().toDouble());
     qDebug() << sum_row;
     ui->table_tovar->setItem(ui->table_tovar->currentRow(),4,new QTableWidgetItem(sum_row));
     RR_Cash::UpdateItog();
     ui->label_KolVo->clear();
     barcode.clear();
     count.clear();
}

void RR_Cash::saveLog(const QString &datastr){
       if (! QFile::exists("log")){
           QDir().mkdir("log");
       }
        QFile *logfile = new QFile("log/"+QDate::currentDate().toString("dd.MM.yyyy")+".txt");
        if (!logfile->open(QIODevice::Append | QIODevice::Text)) {
            qDebug()<<"Fail "<<logfile->fileName()<<" not open";
            return;
        }
        else
            logfile->write(("\n"+QTime::currentTime().toString()).toLocal8Bit()+" ");
    if (!logfile->isOpen())
        return;
    logfile->write(datastr.toLocal8Bit());
    logfile->close();
}
