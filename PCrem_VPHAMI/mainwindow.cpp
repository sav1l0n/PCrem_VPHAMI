#include "mainwindow.h"
#include "AddOrderDialog.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTextEdit>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableViewOrders->setStyleSheet(
        "QTableView {"
        "   background-color: #f9f9f9;"
        "   color: #333;"
        "   border: 1px solid #ddd;"
        "   font-size: 12pt;"
        "   gridline-color: #ccc;"
        "   selection-background-color: #64b5f6;"
        "   selection-color: white;"
        "   alternate-background-color: #f2f2f2;"
        "}"
        "QTableView::item:selected {"
        "   background-color: #42a5f5;"
        "}"
        "QHeaderView::section {"
        "   background-color: #42a5f5;"
        "   color: white;"
        "   padding: 5px;"
        "   font-weight: bold;"
        "   border: none;"
        "}"
        "QHeaderView::horizontal {"
        "   border: 1px solid #ddd;"
        "}"
        );


    // Соединение с базой данных SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/PCrem_VPHAMI/PCrem_VPHAMI/order.db");
    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных!");
        return;
    }

    // Настройка модели для заказов
    ordersModel = new QSqlTableModel(this, db);
    ordersModel->setTable("orders");
    ordersModel->select();
    ui->tableViewOrders->setModel(ordersModel);

    // Изменение заголовков столбцов для заказов
    ordersModel->setHeaderData(1, Qt::Horizontal, "Клиент");
    ordersModel->setHeaderData(2, Qt::Horizontal, "Техник");
    ordersModel->setHeaderData(3, Qt::Horizontal, "Устройство");
    ordersModel->setHeaderData(4, Qt::Horizontal, "Описание проблемы");
    ordersModel->setHeaderData(5, Qt::Horizontal, "Статус");
    ordersModel->setHeaderData(6, Qt::Horizontal, "Стоимость");
    ui->tableViewOrders->resizeColumnsToContents();

    // Настройка модели для сотрудников
    employeesModel = new QSqlTableModel(this, db);
    employeesModel->setTable("technicians");  // Предположим, что таблица сотрудников называется "employees"
    employeesModel->select();
    ui->tableViewEmployees->setModel(employeesModel);

    // Изменение заголовков столбцов для сотрудников
    employeesModel->setHeaderData(0, Qt::Horizontal, "ID");
    employeesModel->setHeaderData(1, Qt::Horizontal, "Имя");
    employeesModel->setHeaderData(3, Qt::Horizontal, "Телефон");
    ui->tableViewEmployees->resizeColumnsToContents();

    ui->tableViewOrders->setStyleSheet("QTableView {"
                                       "border: 1px solid #ccc;"
                                       "border-radius: 5px;"
                                       "background-color: #f9f9f9;"
                                       "color: #333;"
                                       "selection-background-color: #4CAF50;"
                                       "selection-color: white;"
                                       "font-size: 14px;"
                                       "}");

    ui->tableViewEmployees->setStyleSheet("QTableView {"
                                          "border: 1px solid #ccc;"
                                          "border-radius: 5px;"
                                          "background-color: #f9f9f9;"
                                          "color: #333;"
                                          "selection-background-color: #4CAF50;"
                                          "selection-color: white;"
                                          "font-size: 14px;"
                                          "}");


    this->setStyleSheet("QMainWindow {"
                        "background-color: #ffffff;"
                        "color: #333333;"
                        "font-family: 'Arial';"
                        "}");

    ui->centralwidget->setStyleSheet("background-color: #f0f0f0;");


    // Подключение кнопок
    connect(ui->pushButton_addOrder, &QPushButton::clicked, this, &MainWindow::addOrder);
    connect(ui->pushButton_deleteOrder, &QPushButton::clicked, this, &MainWindow::deleteOrder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadOrders()
{
    // Обновить данные модели
    ordersModel->select();
    ui->tableViewOrders->resizeColumnsToContents();
}

void MainWindow::addOrder()
{
    // Создаем диалог добавления заказа
    AddOrderDialog addOrderDialog(this);

    // Показываем диалог и проверяем, нажата ли кнопка OK
    if (addOrderDialog.exec() == QDialog::Accepted) {
        // Получаем введенные данные из диалога
        QString clientName = addOrderDialog.findChild<QLineEdit*>("lineEdit_clientName")->text();
        QString phoneNumber = addOrderDialog.findChild<QLineEdit*>("lineEdit_phoneNumber")->text();
        QString email = addOrderDialog.findChild<QLineEdit*>("lineEdit_email")->text();
        QString technician = addOrderDialog.findChild<QLineEdit*>("lineEdit_technician")->text();
        QString device = addOrderDialog.findChild<QLineEdit*>("lineEdit_device")->text();
        QString problem = addOrderDialog.findChild<QTextEdit*>("textEdit_problem")->toPlainText();
        QString status = addOrderDialog.findChild<QComboBox*>("comboBox_status")->currentText();
        QString cost = addOrderDialog.findChild<QLineEdit*>("lineEdit_cost")->text();

        // Проверяем, что обязательные поля заполнены
        if (clientName.isEmpty() || phoneNumber.isEmpty() || technician.isEmpty() || device.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все обязательные поля.");
            return;
        }

        // Добавляем данные в базу данных
        QSqlQuery query;
        query.prepare("INSERT INTO orders (client, phone, email, technician, device, problem_description, status, cost) "
                      "VALUES (:client, :phone, :email, :technician, :device, :problem_description, :status, :cost)");
        query.bindValue(":client", clientName);
        query.bindValue(":phone", phoneNumber);
        query.bindValue(":email", email);
        query.bindValue(":technician", technician);
        query.bindValue(":device", device);
        query.bindValue(":problem_description", problem);
        query.bindValue(":status", status);
        query.bindValue(":cost", cost);

        if (query.exec()) {
            QMessageBox::information(this, "Успех", "Заказ успешно добавлен!");
            // Обновляем таблицу на главном окне
            loadOrders();
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить заказ: " + query.lastError().text());
        }
    }
    loadOrders();
}

void MainWindow::deleteOrder()
{
    // Получаем индекс выбранной строки
    QModelIndexList selectedIndexes = ui->tableViewOrders->selectionModel()->selectedRows();

    // Если строка не выбрана, показываем сообщение об ошибке
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите заказ для удаления.");
        return;
    }

    // Получаем индекс первой выбранной строки
    QModelIndex index = selectedIndexes.first();

    // Получаем id заказа из выбранной строки (предположим, что id в первом столбце)
    int orderId = ordersModel->data(ordersModel->index(index.row(), 0)).toInt();  // Столбец с id заказа

    // Запрос на удаление записи из базы данных
    QSqlQuery query;
    query.prepare("DELETE FROM orders WHERE id = :id");
    query.bindValue(":id", orderId);

    // Выполняем запрос на удаление
    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Заказ удален.");
        loadOrders();  // Обновляем таблицу
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить заказ: " + query.lastError().text());
    }
}
