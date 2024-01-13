#include "changepass.h"
#include "ui_changepass.h"
#include "QMessageBox"
#include "QFile"
#include "QString"
#include "mainclasses.h"
#include "userentry.h"
extern ACCOUNTS acc;
extern QString use;
extern QString pass;
extern QString id;
extern QFile *f;
changepass::changepass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changepass)
{
    ui->setupUi(this);
}

changepass::~changepass()
{
    delete ui;
}

void changepass::on_updatebutton_clicked()
{
    QString newp=ui->newpass1->text();
    QString renewp=ui->newpass2->text();
    QString oldp=ui->oldpass->text();

    if(newp.isEmpty() || renewp.isEmpty() || oldp.isEmpty())
    {
        QMessageBox::warning(this,"Invalid","Please ensure all the slots are filled");
        ui->newpass1->clear();
        ui->newpass2->clear();
        ui->oldpass->clear();
    }
    else if(newp!=renewp || oldp!=acc.Getpassword())
    {
        QMessageBox::warning(this,"Invalid","New passwords or old password doesn't match");
        ui->newpass1->clear();
        ui->newpass2->clear();
        ui->oldpass->clear();
    }
    else
    {
        QString newname=use+"_"+QString::number(acc.Getuser_id())+"_"+newp+".txt";
        f->rename(newname);
        f->close();
        this->cform()->close();
        close();
        userentry *u=new userentry();
        u->show();
    }
}

