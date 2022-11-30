#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "regdialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    if(connOpen())
    {
        qDebug("open");
    }
    else
    {
        qDebug("Error database was not opened");
    }

    authTableQuery = new QSqlQuery(authDb);
    authTableQuery->exec("CREATE TABLE AuthTable(USERNAME TEXT, PASSWORD TEXT);");
    
    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(on_Button_Send()));
}

Dialog::~Dialog()
{
    delete ui;
}

/*!
Метод,реализующий функионал кнопки "login", взаимодействие пользователя с полями ввода для последующей авторизации аккаунта.
*/
void Dialog::on_pushButton_login_clicked()
{
    QString username,password;
    username = ui->lineEdit_usrname->text();
    password = ui->lineEdit_password->text();
    
    //Подключение к базе данных
    connOpen();

    if(!connOpen())
    {
        qDebug("Error database was not opened");
        return;
    }
    
    //Подготовления запроса аутентификации для базы данных
    QSqlQuery authQry;
    authQry.prepare("SELECT * FROM AuthTable WHERE USERNAME='"+username+"' AND PASSWORD='"+password+"'");

    //Проверка прохождения запроса 
    if(authQry.exec())
    {
        int authCount = 0;//счётчик совпадений логинов и паролей

        while(authQry.next())
        {
            authCount++;
        }

        if(authCount == 1)
        {
            ui->label_3->setText("Authentication complete");
            connClose();
            this->hide();
            
            MainWindow* window = new MainWindow();
            connect(this, SIGNAL(sendData(QString)), window, SLOT(recieveData(QString)));
            window->show();
        }
        if(authCount > 1)
            ui->label_3->setText("Username and password duplicate");
        if(authCount < 1)
            ui->label_3->setText("Authentication failed");        
    }

}

/*!
Метод,реализующий кнопку перехода к окну регистрации пользователя.
*/
void Dialog::on_pushButton_reg_clicked()
{
    RegDialog* regdialog = new RegDialog();
    regdialog->setModal(true);
    regdialog->exec();
}

void Dialog::on_Button_Send()
{
    emit sendData(ui->lineEdit_usrname->text());
}
