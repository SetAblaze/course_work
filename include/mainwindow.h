#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QPushButton>


namespace Ui { 
class MainWindow; 
}

/*!
	\brief Класс основного рабочего окна.

	Данный класс осуществляет взаимодействие пользователя с базой данных.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    int row; //номер активной строки в таблице

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void recieveData(QString str);
    void on_tableView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
