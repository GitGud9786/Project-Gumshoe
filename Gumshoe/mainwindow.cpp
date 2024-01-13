#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFile"
#include "QTextStream"
#include "QString"
#include "QMessageBox"
#include "userentry.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*void MainWindow::on_logbutton_clicked()
{
    QString use= ui->userline->text();
    QString pass= ui->passline->text();

    if(use.isEmpty() || pass.isEmpty() )
    {
        QMessageBox::warning(this,"Invalid","Username or password cannot be empty.");
        ui->userline->clear();
        ui->passline->clear();
    }
    else
    {
        QString name=use+'_'+pass;
        QFile f(name);
        if(!f.exists())
        {
            QMessageBox::warning(this,"Invalid","Wrong username or password.");
            ui->userline->clear();
            ui->passline->clear();
        }
        else
        {
            QMessageBox::information(this,"Done!","Logged in successfully!");
        }
    }
}


void MainWindow::on_signbutton_clicked()
{

}*/


void MainWindow::on_enter_clicked()
{
    hide();
    userentry *entered=new userentry();
    entered->show();
}


void MainWindow::on_info_clicked()
{
    QMessageBox::information(this,"Info","To be added");
}


void MainWindow::on_exit_clicked()
{
    close();
}


void MainWindow::on_pushButton_3_clicked()
{
    close();
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"INFORMATION","CREATED WITH QT - CREATOR, GUMSHOE");
}

