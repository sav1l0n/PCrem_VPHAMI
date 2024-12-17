#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H

#include <QDialog>

namespace Ui {
class AddOrderDialog;
}

class AddOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrderDialog(QWidget *parent = nullptr);
    ~AddOrderDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddOrderDialog *ui;
};

#endif // ADDORDERDIALOG_H
