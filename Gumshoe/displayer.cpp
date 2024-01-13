 #include "displayer.h"
#include "ui_displayer.h"
#include "mainclasses.h"
#include "QMessageBox"
extern vector<ENTERTAINMENT*> E;
displayer::displayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::displayer)
{
    ui->setupUi(this);

    //ui->arranger->addItem("Completed(all)");//0
    ui->arranger->addItem("Completed(books)");//0
    ui->arranger->addItem("Completed(tv shows)");//1
    ui->arranger->addItem("Completed(movies)");//2
    //ui->arranger->addItem("Ongoing(all)");//
    ui->arranger->addItem("Ongoing(books)");//3
    ui->arranger->addItem("Ongoing(tvshows)");//4
    ui->arranger->addItem("Ongoing(movies)");//5
    //ui->arranger->addItem("Planned(all)");//
    ui->arranger->addItem("Planned(books)");//6
    ui->arranger->addItem("Planned(tv shows)");//7
    ui->arranger->addItem("Planned(movies)");//8
    //ui->arranger->addItem("Dropped(all)");//
    ui->arranger->addItem("Dropped(books)");//9
    ui->arranger->addItem("Dropped(tv shows)");//10
    ui->arranger->addItem("Dropped(movies)");//11
}
displayer::~displayer()
{
    delete ui;
}
void displayer::inspector()
{
    if(ui->displaystuff->currentRow()==-1)throw noinspect();
    else
    {
        if(E[ui->displaystuff->currentRow()]->gettype()=="M")
        {
            ui->stackedWidget->setCurrentIndex(1);
            MOVIE::inspection(E[ui->displaystuff->currentRow()],ui->labelmovie,ui->labelmovgenre,ui->labelmovyear,ui->labelmovtime,ui->labelstatmov);
        }
        else if(E[ui->displaystuff->currentRow()]->gettype()=="T")
        {
            ui->stackedWidget->setCurrentIndex(2);
            TVSHOW::inspection(E[ui->displaystuff->currentRow()],ui->labeltvtitle,ui->labeltvgenre,ui->labeltvyear,ui->labeltotep,ui->labeltvprog,ui->labeltvtime,ui->labeltvstat);
        }
        else if(E[ui->displaystuff->currentRow()]->gettype()=="B")
        {
            ui->stackedWidget->setCurrentIndex(3);
            EBOOK::inspection(E[ui->displaystuff->currentRow()],ui->labeltitle,ui->labelbookgenre,ui->labelyear,ui->labelchapters,ui->labeltotpages,ui->labelprogpage,ui->labelauthor,ui->labelstat);
        }
    }
}
void displayer::on_detcheck_clicked()
{
    try
    {
        inspector();
    }
    catch(displayer::noinspect)
    {
        QMessageBox::warning(this,"EXCEPTION","Select a row for inspection.");
    }
}


void displayer::on_return_button_clicked()
{
    this->getmf()->show();
    delete this;
}


void displayer::on_arranger_currentIndexChanged(int index)
{
    if(index==0)
    {
        EBOOK::show_BOO_W(ui->displaystuff);
    }
    else if(index==1)
    {
        TVSHOW::show_TV_W(ui->displaystuff);
    }
    else if(index==2)
    {
        MOVIE::show_Mov_W(ui->displaystuff);
    }
    else if(index==3)
    {
        EBOOK::show_BOO_ong(ui->displaystuff);
    }
    else if(index==4)
    {
        TVSHOW::show_TV_ong(ui->displaystuff);
    }
    else if(index==5)
    {
        MOVIE::show_Mov_ong(ui->displaystuff);
    }
    else if(index==6)
    {
        EBOOK::show_BOO_P(ui->displaystuff);
    }
    else if(index==7)
    {
        TVSHOW::show_TV_P(ui->displaystuff);
    }
    else if(index==8)
    {
        MOVIE::show_Mov_P(ui->displaystuff);
    }
    else if(index==9)
    {
        EBOOK::show_BOO_D(ui->displaystuff);
    }
    else if(index==10)
    {
        TVSHOW::show_TV_D(ui->displaystuff);
    }
    else if(index==11)
    {
        MOVIE::show_Mov_D(ui->displaystuff);
    }
}


void displayer::on_bookreturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void displayer::on_showreturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void displayer::on_movreturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

