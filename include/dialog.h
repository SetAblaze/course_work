#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QPushButton>
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

/*!
	\brief Класс окна авторизации.

	Данный класс осуществляет подключение к авторизационной базе данных и авторизацию пользовательского аккаунта.
*/
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    
public:   
    void connClose()
    {
        authDb.close();
        authDb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        authDb = QSqlDatabase::addDatabase("QSQLITE");
        authDb.setDatabaseName("./authDB.db");

        if(authDb.open())
        {
            qDebug("open");
            return true;
        }
        else
        {
            qDebug("Error database was not opened");
            return false;
        }
    }
    
    friend class RegDialog;
    
private:
    QSqlDatabase authDb;
    QSqlQuery *authTableQuery;
    Ui::Dialog *ui;

signals:
    void sendData(QString str);

private slots:
   void on_pushButton_login_clicked();
   void on_pushButton_reg_clicked();
   void on_Button_Send();

};

#endif // DIALOG_H
