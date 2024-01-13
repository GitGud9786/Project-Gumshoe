#include "singupentry.h"
#include "ui_singupentry.h"
#include "userentry.h"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
singupentry::singupentry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singupentry)
{
    ui->setupUi(this);
}

singupentry::~singupentry()
{
    delete ui;
}

void singupentry::on_signbutton_clicked()
{
    QString use= ui->userline->text();
    QString pass= ui->passline->text();
    QString repass= ui->repassline->text();
    QString id = ui->idline->text();
    bool ok;
    if(use.isEmpty() || pass.isEmpty() )
    {
        QMessageBox::warning(this,"Invalid","Username or password cannot be empty.");
        ui->userline->clear();
        ui->passline->clear();
        ui->repassline->clear();
        ui->idline->clear();
    }
    else if(repass!=pass)
    {
        QMessageBox::information(this,"Password mismatch","Please ensure that the passwords are matching.");
        ui->userline->clear();
        ui->passline->clear();
        ui->repassline->clear();
        ui->idline->clear();

    }
    if(!id.toInt(&ok))
    {
        QMessageBox::warning(this,"Invalid ID","ID must be an integer");
        ui->userline->clear();
        ui->passline->clear();
        ui->repassline->clear();
        ui->idline->clear();
    }
    else
    {
        QString name=use+'_'+id+"_"+pass+".txt";
        QFile f(name);
        QFile d("database.txt");
        if(f.open(QFile::WriteOnly) && d.open(QFile::ReadOnly))
        {
            QMessageBox::information(this,"User created","User creation successful! Log in to continue!");
            ui->userline->clear();
            ui->passline->clear();
            ui->repassline->clear();
            ui->idline->clear();
            QTextStream input(&d);
            QTextStream output(&f);
            while(!input.atEnd())
            {
                QString line= input.readLine();
                output<<line<<"\n";
            }
            d.close();
            f.close();
        }
    }
}


void singupentry::on_logbutton_clicked()
{
    close();
    delete this;
    userentry *user=new userentry();
    user->show();
}

