#include "changeusr.h"
#include "ui_changeusr.h"
#include "QFile"
#include "QMessageBox"
#include "userentry.h"
#include "QString"
#include "mainclasses.h"
extern ACCOUNTS acc;
extern QString use;
extern QString pass;
extern QString id;
extern QFile *f;
changeusr::changeusr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeusr)
{
    ui->setupUi(this);
}

changeusr::~changeusr()
{
    delete ui;
}

void changeusr::on_updatebutton_clicked()
{
    QString newp=ui->newusr->text();
    QString oldu=ui->oldusr->text();
    QString oldp=ui->oldpass->text();

    if(newp.isEmpty() || oldu.isEmpty() || oldp.isEmpty())
    {
        QMessageBox::warning(this,"Invalid","Please ensure all the slots are filled");
        ui->newusr->clear();
        ui->oldusr->clear();
        ui->oldpass->clear();
    }
    else if(oldp!=acc.Getpassword() || oldu!=acc.Getusername())
    {
        QMessageBox::warning(this,"Invalid","Old username or password doesn't match");
        ui->newusr->clear();
        ui->oldusr->clear();
        ui->oldpass->clear();
    }
    else
    {
        QString newname=newp+"_"+QString::number(acc.Getuser_id())+"_"+acc.Getpassword()+".txt";
        f->rename(newname);
        f->close();
        this->uform()->close();
        close();
        userentry *u=new userentry();
        u->show();
    }
}

