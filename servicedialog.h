
#ifndef SERVICEDIALOG_H
#define SERVICEDIALOG_H

#include <QWidget>

namespace Ui {
class ServiceDialog;
}

class ServiceDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceDialog(QWidget *parent = 0);
    ~ServiceDialog();

private slots:
    void on_xReport_clicked();

    void on_zReport_clicked();

    void on_StatusKKM_clicked();

    void on_options_clicked();

private:
    Ui::ServiceDialog *ui;

signals:
    void xReport();
    void ZReport();
    void StatusKKM();
    void OptionsKKM();

};

#endif // SERVICEDIALOG_H
