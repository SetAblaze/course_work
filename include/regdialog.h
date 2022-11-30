#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QPushButton>
#include "dialog.h"

namespace Ui {
class RegDialog;
}

/*!
	\brief Класс окна регистрации пользователя.

	Данный класс осуществляет регистрацию пользовательского аккаунта.
*/
class RegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegDialog(QWidget *parent = nullptr);
    ~RegDialog();
public:
    Dialog connToAuthDb;
private:
    Ui::RegDialog *ui;
private slots:
    void on_pushButton_regUsr_clicked();
};

#endif // REGDIALOG_H
