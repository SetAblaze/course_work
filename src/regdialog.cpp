#include "regdialog.h"
#include "ui_regdialog.h"
#include "dialog.h"

RegDialog::RegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);

    if(connToAuthDb.connOpen())
    {
        qDebug("open");
    }
    else
    {
        qDebug("Error database was not opened");
    }
}

RegDialog::~RegDialog()
{
    delete ui;
}

/*!
Метод,реализующий проверку полей регистрации на заполненность всех необходимых полей ввода, 
совпадение паролей, совпадение существующих логинов, с последующей регистрацией пользователя и занесением данных в базу данных авторизации.
*/
void RegDialog::on_pushButton_regUsr_clicked()
{
    QString login = ui->lineEdit_login1->text();
    QString password1 = ui->lineEdit_password1->text();
    QString password2 = ui->lineEdit_password2->text();

    connToAuthDb.connOpen();
    QSqlQuery regQry,logQry;

    if(!login.isEmpty() || !password1.isEmpty() || !password2.isEmpty())
    {
        if(login.isEmpty())
        {
            ui->label_regStatus->setText("Enter login");
            return;
        }
        if(password1.isEmpty())
        {
            ui->label_regStatus->setText("Enter your password");
            return;
        }
        if(password2.isEmpty())
        {
            ui->label_regStatus->setText("Please, enter your password again");
            return;
        }
        if(password1 != password2)
        {
            ui->label_regStatus->setText("Passwords do not match");
            return;
        }
        
        //Проверка совпадений имён в базе данных
        logQry.prepare("SELECT * FROM AuthTable WHERE USERNAME='"+login+"'");
        if(logQry.exec())
        {
            int count = 0;//счётчик совпадений логинов
            while(logQry.next())
            {
                count++;
            }

            if(count >= 1)
            {
                ui->label_regStatus->setText("Login already taken. Please, enter another login");
                return;
            }
            else{
                regQry.prepare("INSERT INTO AuthTable (USERNAME,PASSWORD) VALUES ('"+login+"','"+password1+"')");
                regQry.exec();
                ui->label_regStatus->setText("Registration complete");
                this->hide();
            }
        }

        connToAuthDb.connClose();
    }
    else
    {
        ui->label_regStatus->setText("Fill in all of the fields");
    }
}