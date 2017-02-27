#ifndef ADDITIONALY_H
#define ADDITIONALY_H

#include <QWidget>

namespace Ui {
class additionaly;
}

class additionaly : public QWidget
{
    Q_OBJECT

public:
    explicit additionaly(QWidget *parent = 0);
    ~additionaly();

private:
    Ui::additionaly *ui;
signals:
    void returnSale();
    void sale();
    void enteringMoney();
    void collectionMoney();
    void resumePrint();
    void cancelSale();
private slots:
    void on_return_2_clicked();
    void on_sale_clicked();
    void on_enteringMoney_clicked();
    void on_collectionMoney_clicked();
    void on_resumePrint_clicked();
    void on_cancelSale_clicked();
};

#endif // ADDITIONALY_H
