#ifndef RR_CASH_H
#define RR_CASH_H
#include <QtSql>
#include <QTextStream>
#include <QDebug>
#include <QMainWindow>
#include <QString>
#include <QKeyEvent>
#include <fiscal.h>
#include <egais.h>
#include <QApplication>
#include <QTableWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QList>
#include <QDialog>

#include <ui_rr_cash.h>

//#include <ui_rr_cash.h>
//tetetstetete
namespace Ui {
class RR_Cash;
}

class RR_Cash : public QMainWindow {
    Q_OBJECT
public:
    explicit RR_Cash(QWidget *parent = 0);
    ~RR_Cash();
    fiscal SHM;
    bool ok;
    bool alcochek=false;
    double KolVo;
    double SummaItog;
    int VidCheka;// 1-Продажа; 2-Возврат
    //QString CurSumma;
    QString barcode;
    QString count;
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
signals:
    void moneaction();
    void good_edit();
    void serviceDialog();
    void additionalyDialog();
    void status(QString status);
private slots:    
    void on_Exit_triggered();
    void insert_chek(QString cahe_id, int oper_type, QString sum);
    void insert_sale(QString cahe_id, int oper_type, QList<QStringList> goods);
    void UpdateVidCheka(int Vid);
    void UpdateItog();
    void on_action_9_triggered();
    void on_enter_clicked();
    void on_clear_clicked();
    void on_minus_clicked();
    void on_product_clicked();
    void on_tab_clicked();
    void on_zero_clicked();
    void on_dote_clicked();
    void on_one_clicked();
    void on_two2_clicked();
    void on_three_clicked();
    void on_four_clicked();
    void on_five_clicked();
    void on_six_clicked();
    void on_seven_clicked();
    void on_eight_clicked();
    void on_nine_clicked();
    void on_up_clicked();
    void on_Down_clicked();
    void on_pushButton_clicked();
    void on_discont_clicked();
    void on_service_clicked();
    void on_additionaly_clicked();
    void on_tab_2_clicked();
    void on_price_clicked();
    void saveLog(const QString &datastr);
public slots:
    void getaPrice (QString price);
    void on_actionZ_triggered();
    void on_actionX_triggered();
    void on_action_2_triggered();
    void on_action_4_triggered();
    void on_action_triggered();
    void on_action_3_triggered();
    void on_action_6_triggered();
    void on_action_7_triggered();
    void on_action_5_triggered();
    void on_action_8_triggered();
private:
    Ui::RR_Cash *ui;
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};
#endif // RR_CASH_H
