#ifndef PRICEINPUT_H
#define PRICEINPUT_H

#include <QWidget>

namespace Ui {
class priceInput;
}

class priceInput : public QWidget
{
    Q_OBJECT

public:
    explicit priceInput(QWidget *parent = 0);
    ~priceInput();

signals:
    void priceEntering(QString price);

private slots:
    void on_zero_clicked();

    void on_clear_clicked();

    void on_dote_clicked();

    void on_enter_clicked();

    void on_one_clicked();

    void on_two2_clicked();

    void on_three_clicked();

    void on_four_clicked();

    void on_five_clicked();

    void on_six_clicked();

    void on_erase_clicked();

    void on_seven_clicked();

    void on_eight_clicked();

    void on_nine_clicked();

private:
    Ui::priceInput *ui;
};

#endif // PRICEINPUT_H
