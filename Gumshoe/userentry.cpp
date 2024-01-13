#include "userentry.h"
#include "ui_userentry.h"
#include "QMessageBox"
#include "QFile"
#include "singupentry.h"
#include "mainform.h"
#include "mainclasses.h"
ACCOUNTS acc;
QString use;
QString pass;
QString id;
QFile *f;
userentry::userentry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userentry)
{
    ui->setupUi(this);
}

userentry::~userentry()
{
    delete ui;
}

void userentry::on_signbutton_clicked()
{
    close();
    delete this;
    singupentry *newsign= new singupentry();
    newsign->show();
}


void userentry::on_logbutton_clicked()
{
    use= ui->userline->text();
    pass= ui->passline->text();
    id = ui->idline->text();

    if(use.isEmpty() || pass.isEmpty() )
    {
        QMessageBox::warning(this,"Invalid","Username or password cannot be empty.");
        ui->userline->clear();
        ui->passline->clear();
        ui->idline->clear();
    }
    else
    {
        bool ok;
        acc.Setusername(use);
        acc.Setpassword(pass);
        acc.Setuser_id(id.toInt(&ok));
        QString name=use+'_'+id+"_"+pass+".txt";
        f=new QFile(name);
        if(!f->exists())
        {
            QMessageBox::warning(this,"Invalid","Wrong username or password.");
            ui->userline->clear();
            ui->passline->clear();
            ui->idline->clear();
        }
        else
        {
            //QMessageBox::information(this,"Done!","Logged in successfully!");
            close();
            delete this;
            //f->open(QFile::ReadWrite | QFile::Text);
            MainForm *newform=new MainForm();
            newform->show();
        }
    }
}

