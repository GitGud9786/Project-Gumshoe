#include "recommender.h"
#include "ui_recommender.h"
#include "functions.h"
#include "QMessageBox"
extern vector<ENTERTAINMENT*> E;
recommender::recommender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recommender)
{
    ui->setupUi(this);
    ui->recbox->addItem("Movies");//0
    ui->recbox->addItem("TV shows");//1
    ui->recbox->addItem("EBooks");//2
}

recommender::~recommender()
{
    delete ui;
}

void recommender::on_recbox_currentIndexChanged(int index)
{
    if(index==0)
    {
        ui->recclist->clear();
        MOVIE::show_rec_MOV(ui->recclist);
    }
    if(index==1)
    {
        ui->recclist->clear();
        TVSHOW::show_rec_TV(ui->recclist);
        ui->recstat->setText("Input an appropiate episode number.");
    }
    if(index==2)
    {
        ui->recclist->clear();
        EBOOK::show_rec_BOO(ui->recclist);
        ui->recstat->setText("Input an appropiate page number.");
    }
}

void recommender::tooadd()
{
    if(ui->recclist->currentRow()==-1)throw noselect();
    else if(ui->recstat->text()!="W" && ui->recstat->text()!="D" && ui->recstat->text()!="O" && ui->recstat->text()!="P" && ui->recbox->currentIndex()==0)throw nocheck();
    else
    {
        if(E[ui->recclist->currentRow()]->gettype()=="M")
        {
            functions::movie_add_auto(E[ui->recclist->currentRow()],ui->recstat);
        }
        else if(E[ui->recclist->currentRow()]->gettype()=="T")
        {
            bool ok;
            QString val=ui->recstat->text();
            if((!val.toInt(&ok) && val != "0")&& ui->recbox->currentIndex()==1)throw shouldbeinteger();
            else if((val.toInt(&ok)>E[ui->recclist->currentRow()]->Gettotal_ep())  && ui->recbox->currentIndex()==1)throw shouldbenumbers();
            //if((!val.toInt(&ok) || val!="0" /*|| val.toInt(&ok)>E[ui->recclist->currentRow()]->Gettotal_ep()*/) && ui->recbox->currentIndex()==1)throw shouldbenumbers();
            functions::show_add_auto(E[ui->recclist->currentRow()],ui->recstat);
        }
        else if(E[ui->recclist->currentRow()]->gettype()=="B")
        {
            bool ok;
            QString val=ui->recstat->text();
            if((!val.toInt(&ok) && val != "0")&& ui->recbox->currentIndex()==2)throw shouldbeinteger();
            else if((val.toInt(&ok)>E[ui->recclist->currentRow()]->Gettotal_pages())  && ui->recbox->currentIndex()==1)throw shouldbenumbers();
            //if((!val.toInt(&ok) || val!="0" /*|| val.toInt(&ok)>E[ui->recclist->currentRow()]->Gettotal_ep()*/) && ui->recbox->currentIndex()==1)throw shouldbenumbers();
            functions::book_add_auto(E[ui->recclist->currentRow()],ui->recstat);
        }
    }
}

void recommender::on_reccreturn_clicked()
{
    this->getmf()->show();
    delete this;
}


void recommender::on_addmovrecbutton_clicked()
{
    try
    {
        recommender::tooadd();
        QMessageBox::information(this,"Success","Added successfully");
        ui->recstat->clear();
    }
    catch(recommender::nocheck)
    {
        QMessageBox::warning(this,"EXCEPTION!","Select a valid method of addition");
        ui->recstat->clear();
    }
    catch(recommender::noselect)
    {
        QMessageBox::warning(this,"EXCEPTION!","Select a row for addition");
        ui->recstat->clear();
    }
    catch(recommender::shouldbenumbers)
    {
        QMessageBox::warning(this,"EXCEPTION!","Input a proper number.");
        ui->recstat->clear();
    }
    catch(recommender::shouldbeinteger)
    {
        QMessageBox::warning(this,"EXCEPTION!","Characters aren't allowed.");
        ui->recstat->clear();
    }
}


void recommender::on_reccinspect_clicked()
{
    functions::type_finder(ui->recclist->currentItem()->text(),this);
}

