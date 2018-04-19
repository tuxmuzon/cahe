#include "fiscal.h"

fiscal::fiscal(QObject *parent) : QObject(parent){


#if defined(Q_OS_WIN32)
drvFR->setControl("AddIn.DrvFR");
#endif

}

//FNDiscountOperation
//ФНОперацияСоСкидками
QString fiscal::GetStatus(QString FrN) { //Получение состояния ККМ
    //  drvFR->setControl("AddIn.DrvFR");
#if defined(Q_OS_WIN32)


    QString FiscalStatus = "";
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Connect()");  //Disconnect
    drvFR->dynamicCall("GetShortECRStatus()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    QVariant ECRMode = drvFR->dynamicCall("ECRMode()");
    QVariant ECRModeDescription = drvFR->dynamicCall("ECRModeDescription()");
    QVariant ECRAdvancedMode = drvFR->dynamicCall("ECRAdvancedMode()");
    QVariant ECRAdvancedModeDescription = drvFR->dynamicCall("ECRAdvancedModeDescription()");
    /*      FiscalStatus = "("
            + ResultCode.value<QString>() + ") "
            + ResultDescription.value<QString>() + " / ("
            + ECRMode.value<QString>() + ") "
            + ECRModeDescription.value<QString>();
    */
    if (ResultCode.value<QString>()=="0") {
        if (ECRMode.value<QString>()=="0"||ECRMode.value<QString>()=="2"||ECRMode.value<QString>()=="4") {
            qDebug() << ECRMode.value<QString>() << "/"  << ECRModeDescription.value<QString>();
            if(ECRAdvancedMode.value<QString>()=="0"){
                FiscalStatus="0";
            }   else {
                FiscalStatus=ECRAdvancedMode.value<QString>()+"/"+ECRAdvancedModeDescription.value<QString>();
            }
        }
        else {
            FiscalStatus=ECRMode.value<QString>()+"/" + ECRModeDescription.value<QString>();
        }
    } else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
    #endif
}
QString fiscal::CancelDocument(QString FrN){
    #if defined(Q_OS_WIN32)
    QString FiscalStatus = "";
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Connect()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("SysAdminCancelCheck()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
    #endif
}
QString fiscal::Get_Z_Report(QString FrN){
     #if defined(Q_OS_WIN32)
    QString FiscalStatus = "";
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Connect()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("PrintReportWithCleaning()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
     #endif
}
QString fiscal::Get_X_Report(QString FrN){
     #if defined(Q_OS_WIN32)
    QString FiscalStatus = "";
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Connect()");
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("PrintReportWithoutCleaning()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
    #endif
}
QString fiscal::SaleDocument(QList<QStringList> egaisgoods, QString FrN,  QString nal_sum, QString discont){
    qApp->processEvents();
    QTextStream cout(stdout);

    if (FrN=="0") {FrN="1";}
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    //  drvFR->setProperty("DiscountOnCheck", discont);
    QStringList row;
    for (int i=0; i < egaisgoods.size(); i++) {
        // <<StringForPrint << Price << Quantity
        row = egaisgoods[i];
        qDebug() <<"roww" <<row;
        qDebug() <<"nal_summ" <<nal_sum;
        QString price=row[3];
        price=price.replace(".",",");
        drvFR->setProperty("Quantity", row[1]);
        drvFR->dynamicCall("SetPrice(0,0)", price);
        //drvFR->setProperty("Price", price);//.toInt(&ok, 10)
        drvFR->setProperty("Department", "1");
        drvFR->setProperty("Tax1", "0");
        drvFR->setProperty("Tax2", "0");
        drvFR->setProperty("Tax3", "0");
        drvFR->setProperty("Tax4", "0");
        drvFR->setProperty("StringForPrinting", row[0]);
        drvFR->dynamicCall("Sale()");
        drvFR->dynamicCall("SetSumm1(456,01)", "1,00");
        drvFR->setProperty("Tax1", "0");
        drvFR->setProperty("Tax2", "0");
        drvFR->setProperty("Tax3", "0");
        drvFR->setProperty("Tax4", "0");
         drvFR->setProperty("StringForPrinting", "СКИДКА");
        QVariant ResultCode1 = drvFR->dynamicCall("Discount()");
        cout << "discont error" << ResultCode1.value<QString>();
        //   drvFR->dynamicCall("StornoDiscount()");
         qApp->processEvents();
    }
    // drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("SetSumm1(456,01)", "1,00");
    drvFR->setProperty("Tax1", "0");
    drvFR->setProperty("Tax2", "0");
    drvFR->setProperty("Tax3", "0");
    drvFR->setProperty("Tax4", "0");
    drvFR->setProperty("StringForPrinting", "");
     qApp->processEvents();
    drvFR->dynamicCall("SetSumm1(456,01)", nal_sum);
    drvFR->setProperty("StringForPrinting", "+++++++++++++++++-------+++++++++++++++");
    drvFR->dynamicCall("CloseCheck()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    QString FiscalStatus = "";
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
    #endif
}
QString fiscal::collection(QString nal_su, QString FrN) { //инкасация
    QString FiscalStatus = "";
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("SetSumm1(456,01)", nal_su);
    drvFR->dynamicCall("CashOutcome()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return FiscalStatus;
    #endif
}
QString fiscal::entering_monye(QString nal_sum, QString FrN){ //внесение
    QString FiscalStatus = "";
     #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    qDebug() << "FR №" << FrN;
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Connect()");
    drvFR->dynamicCall("SetSumm1(456,01)", nal_sum);
    drvFR->dynamicCall("CashIncome()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return FiscalStatus;
     #endif
}
QString fiscal::ReturnDocument(QList<QStringList> egaisgoods, QString FrN,  QString nal_sum,QString discont){
    if (FrN=="0") {FrN="1";}
    qApp->processEvents();
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    QStringList row;
    for (int i=0; i < egaisgoods.size(); i++) {
        // <<StringForPrint << Price << Quantity
        row = egaisgoods[i];
        qDebug() <<"roww" <<row;
        qDebug() <<"nal_summ" <<nal_sum;
        drvFR->setProperty("Quantity", row[1]);
        drvFR->dynamicCall("SetPrice(0,0)", row[3]);
        //drvFR->setProperty("Price", price);//.toInt(&ok, 10)
        QTextStream cout(stdout);
        drvFR->setProperty("Department", "1");
        drvFR->setProperty("Tax1", "0");
        drvFR->setProperty("Tax2", "0");
        drvFR->setProperty("Tax3", "0");
        drvFR->setProperty("Tax4", "0");
        drvFR->setProperty("StringForPrinting", row[0]);
        drvFR->dynamicCall("ReturnSale()");
    }
    drvFR->setProperty("DiscountOnCheck", discont);
    drvFR->dynamicCall("SetSumm1(456,01)", nal_sum);
    drvFR->setProperty("StringForPrinting", "+++++++++++++++++-------+++++++++++++++");
    drvFR->dynamicCall("CloseCheck()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    QString FiscalStatus = "";
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
    #endif
}
QString fiscal::GetDateTime(QString FrN){
    //not get fisacal status
    //ДДММГГЧЧММ
    QString DateTime;
    QString FiscalStatus = "";
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("GetECRStatus()");
    drvFR->dynamicCall("LDNumber",FrN);
    QDate Date = drvFR->dynamicCall("Date()").value<QDate>();
    QTime Time = drvFR->dynamicCall("Time()").value<QTime>();
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    QString DD, MM, YY, HH, MI;
    DD.setNum(Date.day()); MM.setNum(Date.month()); YY.setNum(Date.year()); HH.setNum(Time.hour()); MI.setNum(Time.minute());
    if (DD.length() <2 ) {DD.prepend("0");}
    if (MM.length() <2 ) {MM.prepend("0");}
    if (YY.length() <2 ) {YY.prepend("0");}
    if (HH.length() <2 ) {HH.prepend("0");}
    if (MI.length() <2 ) {MI.prepend("0");}
    if (YY.length() ==4 ) {YY=YY.mid(2,2);}
    DateTime = DD + MM + YY + HH + MI;
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
    }   else {
        DateTime=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return DateTime;
    #endif
}
QString fiscal::PrintURL(QStringList url, QString FrN){
    qApp->processEvents();
    QString FiscalStatus = "";
    QSqlQuery company("select company.name, company.INN, company.KPP, Addres, Host  from device, company where company.ID=device.org_id and logical_name="+FrN);
    company.next();
    #if defined(Q_OS_WIN32)
    //INN //kpp // №кассы №смены № документа Дата веремя
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->setProperty("BarCode", url[0]);
    drvFR->setProperty("LineNumber", "200");
    drvFR->setProperty("BarcodeType", "3");
    drvFR->setProperty("BarcodeAlignment", "0");
    drvFR->setProperty("BarWidth", "6");
    drvFR->setProperty("StringForPrinting"," ");
    drvFR->dynamicCall("PrintString()");
    drvFR->dynamicCall("PrintBarcodeGraph()");
    drvFR->setProperty("StringForPrinting"," ");
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting","ИНН: "+company.value("INN").toString());
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting","КПП: "+company.value("KPP").toString());
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting","№ ККМ: "+GetSerialNumber(FrN));
    drvFR->dynamicCall("PrintString()");
    //QString CurrensShift = GetCurrentShift();
    drvFR->setProperty("StringForPrinting","№ Смены: "+QString::number(GetCurrentShift(FrN).toInt()+1));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting","№ Документа: "+GetCurrentDoc(FrN));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + url[0].left(30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + url[0].mid(30,30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + url[0].mid(60,30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + url[0].mid(90));
    drvFR->dynamicCall("PrintString()");
    QString KEP = url[1];
    KEP.replace("\n","");
    qDebug() << KEP;
    drvFR->setProperty("StringForPrinting"," ");
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + KEP.left(30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + KEP.mid(30,30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + KEP.mid(60,30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + KEP.mid(90,30));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("StringForPrinting"," " + KEP.mid(120,9));
    drvFR->dynamicCall("PrintString()");
    drvFR->setProperty("FeedDocument", "10");
    drvFR->dynamicCall("FeedDocument()");
    drvFR->dynamicCall("CutCheck()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return FiscalStatus;
#   endif
}
QString fiscal::GetCurrentDoc(QString FrN){
    //последний напечатанный, для егаиса нужно добавить номер, если доавляем после продажи то не наращивать
    QString NumberDoc;
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("GetECRStatus()");
    NumberDoc = drvFR->dynamicCall("OpenDocumentNumber()").value<QString>();
    //  NumberDoc = NumberDoc.number(NumberDoc.toInt()+1);
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
        //  FiscalStatus="0";
    }   else {
        NumberDoc=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return NumberDoc;
    #endif
}
QString fiscal::GetCurrentShift(QString FrN){
    QString CurrentShift;
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("GetECRStatus()");
    CurrentShift  = drvFR->dynamicCall("SessionNumber()").value<QString>();
    CurrentShift = CurrentShift.number(CurrentShift.toInt()+1);
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
        //  FiscalStatus="0";
    }   else {
        CurrentShift=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return CurrentShift;
    #endif
}
QString fiscal::GetSerialNumber(QString FrN){
    QString SerialNumber;
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("GetECRStatus()");
    SerialNumber  = drvFR->dynamicCall("SerialNumberAsInteger()").value<QString>();
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    if (ResultCode.value<QString>()=="0"){
        //  FiscalStatus="0";
    }   else {
        SerialNumber=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    return SerialNumber;
    #endif
}
QString fiscal::FNDiscountOperation(QList<QStringList> egaisgoods, QString FrN,  QString nal_sum, QString discont){
    qApp->processEvents();
    QTextStream cout(stdout);
    if (FrN=="0") {FrN="1";}
    #if defined(Q_OS_WIN32)
    drvFR->dynamicCall("LDNumber",FrN);
    drvFR->dynamicCall("SetActiveLD()");
    drvFR->setProperty("Password", "30");
    drvFR->setProperty("CheckType","0");
   QStringList row;
    for (int i=0; i < egaisgoods.size(); i++) {
        // <<StringForPrint << Price << Quantity
        row = egaisgoods[i];
        qDebug() <<"roww" <<row;
        qDebug() <<"nal_summ" <<nal_sum;
        QString price=row[3];
        price=price.replace(".",",");
        drvFR->setProperty("Quantity", row[1]);
        drvFR->dynamicCall("SetPrice(0,0)", price);
        drvFR->dynamicCall("SetDiscountValue(0,0)","1,00");
       // drvFR->dynamicCall("SeChargeValue(0,0)","0,00");
        //drvFR->setProperty("Price", price);//.toInt(&ok, 10)
        drvFR->setProperty("Department", "1");
        drvFR->setProperty("Tax1", "0");
      //  drvFR->setProperty("Tax2", "0");
          drvFR->setProperty("DocumentName", "DocumentName");
        drvFR->setProperty("BarCode", "123467");
        drvFR->setProperty("StringForPrinting", row[0]);
        drvFR->dynamicCall("FNDiscountOperation()");
         qApp->processEvents();
    }
    // drvFR->setProperty("Password", "30");
    drvFR->dynamicCall("SetSumm1(456,01)", "1,00");
    drvFR->setProperty("Tax1", "0");
    drvFR->setProperty("Tax2", "0");
    drvFR->setProperty("Tax3", "0");
    drvFR->setProperty("Tax4", "0");
    drvFR->setProperty("StringForPrinting", "");
     qApp->processEvents();
    drvFR->dynamicCall("SetSumm1(456,01)", nal_sum);
    drvFR->setProperty("StringForPrinting", "+++++++++++++++++-------+++++++++++++++");
    drvFR->dynamicCall("CloseCheck()");
    QVariant ResultCode = drvFR->dynamicCall("ResultCode()");
    QVariant ResultDescription = drvFR->dynamicCall("ResultCodeDescription()");
    QString FiscalStatus = "";
    if (ResultCode.value<QString>()=="0"){
        FiscalStatus="0";
    }   else {
        FiscalStatus=ResultCode.value<QString>()+"/" + ResultDescription.value<QString>();
    }
    drvFR->setProperty("Password", "01");
    drvFR->dynamicCall("Disconnect()");
    return FiscalStatus;
    #endif
}
