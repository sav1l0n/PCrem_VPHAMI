#include "AddOrderDialog.h"
#include "ui_AddOrderDialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QDialog>

AddOrderDialog::AddOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrderDialog)
{
    ui->setupUi(this);

    // Добавляем статусы в выпадающий список
    ui->comboBox_status->addItems(QStringList()
                                  << "Новый"
                                  << "Выполняется"
                                  << "На согласовании"
                                  << "Ожидание комплектующих"
                                  << "Завершен"
                                  << "Выдача"
                                  << "Выдан");

    // Применяем QSS стили
    this->setStyleSheet("QDialog {"
                        "background-color: #f9f9f9;"
                        "font-family: Arial;"
                        "}"
                        "QLabel {"
                        "font-weight: bold;"
                        "color: #333333;"
                        "}"
                        "QLineEdit, QComboBox, QTextEdit {"
                        "border: 2px solid #cccccc;"
                        "border-radius: 8px;"
                        "padding: 6px;"
                        "background-color: #ffffff;"
                        "}"
                        "QPushButton {"
                        "background-color: #4CAF50;"
                        "color: white;"
                        "border: none;"
                        "border-radius: 8px;"
                        "padding: 8px 15px;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: #45a049;"
                        "}");

    connect(ui->pushButton_ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &QDialog::reject);

}

AddOrderDialog::~AddOrderDialog()
{
    delete ui;
}

void AddOrderDialog::on_saveButton_clicked()
{
    QString fullName = ui->lineEdit_clientName->text();
    QString phone = ui->lineEdit_phoneNumber->text();
    QString email = ui->lineEdit_email->text();
    QString technician = ui->lineEdit_technician->text();
    QString device = ui->lineEdit_device->text();
    QString problem = ui->textEdit_problem->toPlainText();
    QString status = ui->comboBox_status->currentText();
    QString cost = ui->lineEdit_cost->text();

    // Пример валидации
    if (fullName.isEmpty() || phone.isEmpty() || device.isEmpty() || cost.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все обязательные поля!");
        return;
    }

    // Данные готовы для сохранения
    QMessageBox::information(this, "Успешно", "Заказ сохранен!");
    this->accept();
}
