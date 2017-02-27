#include "egais.h"
//#include <QTextCodec>

egais::egais(QObject *parent) : QObject(parent) {
 //   QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
}

QString egais::getalcocode( QString axcise_mark){
    bool ok;
    QString alcocode;
    alcocode = axcise_mark.mid(3,16);
    alcocode =  alcocode.setNum(alcocode.toULongLong(&ok,36));
    while (alcocode.length()<19){
        alcocode.prepend("0");
    }
    return alcocode;
}

QString egais::GetEgaisString( QList<QStringList> egaisgoods, QString FrN ){

    //1) Create xml to send
    //2) send xml
    //retur string for print or error code


    //    QByteArray body = file.readAll();

    //      manager = new QNetworkAccessManager(this);
    //    QUrl url("http://10.8.0.4:8080/xml");
    //      QUrl url("http://192.168.0.8:3333/");

    //         QNetworkRequest request;
    //       request.setUrl(url);
    //  request.setRawHeader("Host", url.host());
    //    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)");
    //    request.setRawHeader("Accept", "*/*");
    //    request.setRawHeader("Accept-Language", "ru,en-us;q=0.7,en;q=0.3");
    //    request.setRawHeader("Accept-Charset", "utf-8;q=0.7,*;q=0.7");
    //    request.setRawHeader("Keep-Alive", "300");
    //    request.setRawHeader("Connection", "keep-alive");
    //   request.setRawHeader("Referer", "http:/test.ru/..откуда пришли");
    //   request.setRawHeader("Cookie", "auth=NO");
    //   request.setRawHeader("Content-Type", "application/xml");
    //    request.setHeader(QNetworkRequest::ContentTypeHeader,
    //                       "application/xml");
    //      QNetworkReply* reply=  manager->post(request, body);


    //   QNetworkReply* ExtRequest::stravaUploadFile2(QString access_token, QString activityName, QString activityDescription, QString pathToFile) {

    //      connect( reply, SIGNAL(finished()),
    //                 this, SLOT(replyFinished()) );
    // return reply;


    //  if (alcochek){
    //      QString filename = QFileDialog::getSaveFileName(this,
    //                                       tr("Save Xml"), ".",
    //                                          tr("Xml files (*.xml)"));
    //

    //  QFile file(filename);
    //   qDebug() <<   CurrencyFormat(text).toInt(&ok, 10);
    //  }
    //язык С++ и библиотека Qt
    //        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //параметр 1 - какое-то поле, параметр 2 - файл
    //   QByteArray param1Name="param1" ,param1Value="value1";
    //      QByteArray param2Name="xml_file", param2FileName="send.xml",
    //         param2ContentType="application/xml",param2Data="А вот такая новость, которая лежит в файле news.txt";

    //       param2Data = file.readAll();
    //qDebug() << "file" << param2Data;
    //   Сформируем для начала тело запроса:

    //задаем разделитель
    //   QByteArray postData,boundary="2f2625ef49b5ee8c";
    //первый параметр
    //   postData.append("--------------------------"+boundary+"\r\n");//разделитель
    //имя параметра
    //   postData.append("Content-Disposition: form-data; name=\"");
    //   postData.append(param1Name);
    //   postData.append("\"\r\n\r\n");
    //значение параметра
    //  postData.append(param1Value);
    //   postData.append("\r\n");

    //параметр 2 - файл
    //   postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    //      postData.append("Content-Disposition: form-data; name=\"");
    //      postData.append(param2Name);
    //имя файла
    //     postData.append("\"; filename=\"");
    //     postData.append(param2FileName);
    //     postData.append("\"\r\n");
    //тип содержимого файла
    //    postData.append("Content-Type: "+param2ContentType+"\r\n");
    //передаем в base64
    //   postData.append("Content-Transfer-Encoding: base64\r\n\r\n");
    //данные
    //     postData.append(param2Data);
    //     postData.append("\r\n");
    //"хвост" запроса
    //    postData.append("--------------------------"+boundary+"--\r\n");

    //  В переменной postData получаем готовое тело запроса — осталось только отослать и не забыть установить дополнительные заголовки запроса:

    //     QNetworkRequest request(QUrl("http://192.168.0.8:3333/"));
    // QNetworkRequest request(QUrl("http://10.8.0.2:8080/xml"));
    //         request.setHeader(QNetworkRequest::ContentLengthHeader,
    //                QByteArray::number(postData.length()));
    //  request.setRawHeader("Accept", "*/*");
    //   request.setRawHeader("Expect", "100-continue");


    //      request.setHeader(QNetworkRequest::ContentTypeHeader,
    //         "multipart/form-data; boundary="+boundary);


    //     QNetworkReply *reply=manager->post(request,postData);
    //     connect( reply, SIGNAL(finished()),
    //                           this, SLOT(replyFinished()) );



    //qDebug() << console->readAllStandardOutput();

    QString StringForPrint="0";

    QSqlQuery company("select company.name, company.INN, company.KPP, Addres, Host  from device, company where company.ID=device.org_id and logical_name="+FrN);


    company.next();

    fiscal egaisFR;
    QString FrStatus=egaisFR.GetStatus(FrN);
    if (FrStatus!="0"){
        QMessageBox::warning(0,"Ошибка КАССЫ ЕГАИС",FrStatus+"УСТРАНИТЕ ОШИБКУ И НАЖМИТЕ ЗАПРОСИТЬ СТАТУС");
        StringForPrint="-1";
    } else {

        QFile file("send.xml");
        file.open(QIODevice::WriteOnly);
        QXmlStreamWriter xml(&file);
        /*...*/
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("Cheque");
        xml.writeAttribute("inn",company.value("INN").toString());
        xml.writeAttribute("datetime",egaisFR.GetDateTime(FrN)); //ДДММГГЧЧММ
        xml.writeAttribute("kpp",company.value("KPP").toString());
        xml.writeAttribute("kassa",egaisFR.GetSerialNumber(FrN)); // заводской номер ккм
        xml.writeAttribute("address",company.value("Addres").toString());
        xml.writeAttribute("name",company.value("name").toString()); //имя магазина
        xml.writeAttribute("number",QString::number(egaisFR.GetCurrentDoc(FrN).toInt()+1)); //номер чека
        xml.writeAttribute("shift",QString::number(egaisFR.GetCurrentShift(FrN).toInt()+1)); // номер смены
        for (int i =0; i<egaisgoods.size(); i++){
            QStringList row;
            row=egaisgoods[i];
            qDebug() << "row_egais"  <<row;
            //пошли сами виноводчне изделия
            // здесь цикл по элементам таблицы содержащим акцизную марку

            xml.writeStartElement("Bottle");
            xml.writeAttribute("barcode",row[5]);
            xml.writeAttribute("ean",row[7]);
            QString price =  row[4];
            price.replace(",",".");
            qint8 realPart=0;
            for (int i=0; i<price.length(); i++){
               // qDebug() << volume[i];
                if (price[i]=='.'){
                    realPart = price.length()-i-1;
                }
            }
            if (realPart>0){
                for(int i=0;i<2-realPart;i++){
                    price.append("0");
                }


            } else {price.append(".00");}

        //    qDebug() << price <<  price;
            xml.writeAttribute("price",price);

            QString volume =  row[6];
            volume.replace(",",".");
             realPart=0;
            for (int i=0; i<volume.length(); i++){
               // qDebug() << volume[i];
                if (volume[i]=='.'){
                    realPart = volume.length()-i-1;
                }
            }
            if (realPart>0){
                for(int i=0;i<2-realPart;i++){
                    volume.append("0");
                }


            } else {volume.append(".00");}

            qDebug() << volume <<  volume;

            xml.writeAttribute("volume",volume);
            xml.writeEndElement();
        }

        xml.writeEndElement();
        xml.writeEndDocument();
        file.close();
        file.open(QIODevice::ReadOnly);
        QProcess *console = new QProcess();//создаем процесс
        //отправляем запрос с последующим контролем
        QString FileName= "send.xml";
        QString Patch=company.value("Host").toString()+"/xml";
        qDebug() << "CURL " <<  "curl.exe -F \"xml_file=@" + FileName + "\" " + Patch;
        console->start("curl.exe -F \"xml_file=@" + FileName + "\" " + Patch);

        qDebug() << "start" <<console->waitForStarted();
       // qDebug() << "finish" <<console->waitForFinished();
       qApp->processEvents();
        if(!console->waitForFinished(10000)){ //10000

            QMessageBox::warning(0,"Нет связи с УТМ","Проверьте УТМ и повторите попытку.");
            StringForPrint="-1";
        } else {
            QFile *file2 = new QFile("Request.xml");
            // Создаём файл или открываем его на перезапись ...
           if(file2->open(QFile::WriteOnly)){
                file2->write(console->readAllStandardOutput());
               file2->close();
            }
        }
    }
    return StringForPrint;
}

QStringList egais::ParseXML(){
    qApp->processEvents();
    QFile file("Request.xml");
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "eror";
    }

    QFile file2("chek.xml");
    file2.remove();
    if (!file2.open(QIODevice::WriteOnly)){
        qDebug() << "eror";

    }

    QTextStream outstream(&file2);
    outstream.setCodec("cp1251");
        int i=0;
    while (!file.atEnd()) {
        QString row;
        row = file.readLine();
        if (i==0&&row[0]=='<'&&row[1]!='?') {
            outstream << "<?xml version=\"1.0\" encoding=\"windows-1251\"?>";
        }
        if(row[0]!='<'&&row[1]!='?'){
            row.replace("=","&equiv;");
            row.replace("&","&amp;");
        }
        qDebug() << "row" <<row;
        outstream << row;
        i++;
    }

    file2.close();
    QStringList egaisurl;
    //  QFile file("chek.xml");

    if (file2.open(QIODevice::ReadOnly)) {

        QXmlStreamReader xmlfile(&file2);
        //    xmlfile.set

        do {
            xmlfile.readNext();

            if(xmlfile.hasError()){
                qDebug() << "Error" << xmlfile.errorString() ;
                QMessageBox::warning(0,"Ошибка Разбора XML", xmlfile.errorString());
                egaisurl << "-1";
                break;
            }
            if(xmlfile.name()=="error"){
                QMessageBox::warning(0,"Ошибка ЕГАИС", xmlfile.readElementText());
                 egaisurl << "-1";
                break;
            }
            if(xmlfile.name()=="url"){
               QString url= xmlfile.readElementText();
               url.replace("&equiv;","=");
               url.replace("&amp;","&");
               egaisurl << url;
            }

            if(xmlfile.name()=="sign"){
               egaisurl << xmlfile.readElementText();

            }


            //  qDebug() << xmlfile.tokenString() << xmlfile.name() << xmlfile.text();
            //QXmlStreamAttributes atribures=xmlfile.attributes();
            //   qDebug() <<"lrngh atributes" <<  atribures.length();

        } while (!xmlfile.atEnd());



    } else {QMessageBox::warning(0,"Файл Ответа не найден","Файл Ответа не найден проверьте работу ЕГАИС");}
    return egaisurl;
}
