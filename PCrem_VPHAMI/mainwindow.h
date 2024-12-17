#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadOrders();   // Загрузка данных из БД
    void addOrder();     // Добавление нового заказа
    void deleteOrder();  // Удаление выбранного заказа

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;           // Соединение с базой данных
    QSqlTableModel *ordersModel;     // Модель для работы с таблицей
    QSqlTableModel *employeesModel;
};

#endif // MAINWINDOW_H
