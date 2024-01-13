#include "researchinspect.h"
#include "ui_researchinspect.h"

researchinspect::researchinspect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::researchinspect)
{
    ui->setupUi(this);
    movtitle=new QLabel("labelmovie",this);
    movgenre=new QLabel("labelmovgenre",this);
    movyear=new QLabel("labelmovyear",this);
    movtime=new QLabel("labelmovtime",this);
    movstatus=new QLabel("labelstatmov",this);

    tvtitle=new QLabel("labeltvtitle",this);
    tvgenre=new QLabel("labeltvgenre",this);
    tvyear=new QLabel("labeltvyear",this);
    tvtime=new QLabel("labeltvtime",this);
    tvstatus=new QLabel("labelstatmov",this);
    tvtotep=new QLabel("labeltotep",this);
    tvcurrep= new QLabel("labeltvprog",this);
    tvstatus=new QLabel("labeltvstat",this);

    booktitle=new QLabel("labeltitle",this);
    bookgenre=new QLabel("labelbookgenre",this);
    bookyear=new QLabel("labelyear",this);
    bookchap=new QLabel("labelchap",this);
    bookauthor=new QLabel("labelauthor",this);
    booktopg=new QLabel("labeltotpages",this);
    bookcurrpg= new QLabel("labelprogpage",this);
    bookstatus=new QLabel("labelstat",this);
}

researchinspect::~researchinspect()
{
    delete ui;
}
