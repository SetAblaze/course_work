#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./tDB.db");

    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE PharmBook(PRODUCT TEXT, COMPANY TEXT, IDENTIFIER INT, DESCRIPTION TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("PharmBook");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
Метод,реализующий кнопку удаления строки в таблице отображаемой модели базы данных.
*/
void MainWindow::on_pushButton_clicked()
{
    model->removeRow(row);
}

/*!
Метод,реализующий кнопку добавления строки в таблицу отображаемой модели базы данных.
*/
void MainWindow::on_pushButton_2_clicked()
{
    model->insertRow(model->rowCount());
}

/*!
Метод,реализующий кнопку поиска по отображаемой модели базе данных.
*/
void MainWindow::on_pushButton_3_clicked()
{
    QString textline = ui->txtFarm->text(); //строка поля ввода

    if(!textline.isEmpty())
    {
        model->setFilter(QString("PRODUCT='%1'").arg(textline));
        model->select();
    }
}

/*!
Метод,реализующий обновление модели отображаемой модели базы данных.
*/
void MainWindow::on_pushButton_4_clicked()
{
    model->setTable("PharmBook");
    model->select();
}

/*!
Метод выделения строки отображаемой модели базы данных.
*/
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void MainWindow::recieveData(QString str)
{
    if(str != "admin")
    {
        ui->pushButton->hide();
        ui->pushButton_2->hide();
    }
}