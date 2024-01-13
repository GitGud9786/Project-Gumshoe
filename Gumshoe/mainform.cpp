#include "mainclasses.h"
#include "mainform.h"
#include "ui_mainform.h"
#include "userentry.h"
#include "changepass.h"
#include "changeusr.h"
#include "QMessageBox"
#include "QFile"
#include "QString"
#include "functions.h"
#include "displayer.h"
#include<bits/stdc++.h>
#include "info.h"
#include "recommender.h"
using namespace std;
extern ACCOUNTS acc;
extern QString use;
extern QString pass;
extern QString id;
extern QFile* f;
MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_accounbutton_clicked()
{
    ui->movcounT->setText(functions::mov_counter());
    ui->bookcounT->setText(functions::boo_counter());
    ui->tvcount->setText(functions::tv_counter());
    ui->stackedWidget->setCurrentIndex(1);
    ui->namelabel->setText(acc.Getusername());
    ui->idlabel->setText(QString::number(acc.Getuser_id()));
}
void MainForm::on_logoutbutton_clicked()
{
    close();
    delete this;
    userentry *newuser=new userentry();
    newuser->show();
}


void MainForm::on_backbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainForm::on_reccbutton_clicked()
{
    this->hide();
    recommender *dis=new recommender();
    dis->setmf(this);
    dis->show();
}


void MainForm::on_chngpass_clicked()
{
    changepass *cp=new changepass();
    cp->getform(this);
    cp->show();
}


void MainForm::on_changusr_clicked()
{
    changeusr *cu=new changeusr();
    cu->getform(this);
    cu->show();
}


void MainForm::on_extradd_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainForm::mov_ins(QString &title,QString &genre,QString &year,QString &tyme,QString &stat)
{
    bool ok;
    if(title.isEmpty() || genre.isEmpty() || year.isEmpty() || tyme.isEmpty() || stat.isEmpty())throw emptyinputs();
    if(!year.toInt(&ok) || !tyme.toInt(&ok)) throw numinputs();
    if(tyme.toInt(&ok)<15) throw numinputs();
    if(stat!="W" && stat!="D" && stat!="O" && stat!="P") throw movstatus();
    functions F1;
    F1.movie_add(title,genre,year,tyme,stat,f);
    QMessageBox::information(this,"Success!","Movie has been successfully inserted");
    ui->titleadd->clear();
    ui->genreadd->clear();
    ui->yearadd->clear();
    ui->timeadd->clear();
    ui->statadd->clear();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainForm::on_movinsert_clicked()
{
    QString title= ui->titleadd->text();
    QString genre= ui->genreadd->text();
    QString year= ui->yearadd->text();
    QString tyme= ui->timeadd->text();
    QString stat= ui->statadd->text();
    try
    {
        MainForm::mov_ins(title,genre,year,tyme,stat);
    }
    catch(MainForm::emptyinputs)
    {
        QMessageBox::warning(this,"EXCEPTION!","Please ensure that all fields are completed.");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
    }
    catch(MainForm::numinputs)
    {
        QMessageBox::warning(this,"EXCEPTION!","Invalid numeric input(s).");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
    }
    catch(MainForm::movstatus)
    {
        QMessageBox::warning(this,"EXCEPTION!","Invalid completion type.");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
    }

    /*if(title.isEmpty() || genre.isEmpty() || year.isEmpty() || tyme.isEmpty() || stat.isEmpty())
    {
        QMessageBox::warning(this,"Invalid inputs","Please ensure that all fields are completed.");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
        return;
    }
    if(!year.toInt(&ok) || !tyme.toInt(&ok))
    {
        QMessageBox::warning(this,"Invalid input(s)","Invalid numeric input(s).");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
        return;
    }

    int Tyme=tyme.toInt(&ok);
    if(Tyme<15)
    {
        QMessageBox::warning(this,"Invalid input(s)","Runtime must exceed 15 minutes.");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
        return;
    }

    if(stat!="W" && stat!="D" && stat!="O")
    {
        QMessageBox::warning(this,"Invalid input(s)","Invalid completion type.");
        ui->titleadd->clear();
        ui->genreadd->clear();
        ui->yearadd->clear();
        ui->timeadd->clear();
        ui->statadd->clear();
        return;
    }
    functions F1;
    F1.movie_add(title,genre,year,tyme,stat,f);
    QMessageBox::information(this,"Success!","Movie has been successfully inserted");
    ui->titleadd->clear();
    ui->genreadd->clear();
    ui->yearadd->clear();
    ui->timeadd->clear();
    ui->statadd->clear();
    ui->stackedWidget->setCurrentIndex(4);*/
}


void MainForm::on_movadd_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);//movie page
}


void MainForm::on_bacc_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainForm::on_movbacc_clicked()
{
    ui->titleadd->clear();
    ui->genreadd->clear();
    ui->yearadd->clear();
    ui->timeadd->clear();
    ui->statadd->clear();
    ui->stackedWidget->setCurrentIndex(4);
}


void MainForm::on_ebookadd_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);//ebook page
}

void MainForm::book_ins(QString &title,QString &genre,QString &author,QString &year,QString &chapter,QString &page,QString &currpage)
{
    bool ok;
    if(title.isEmpty() || genre.isEmpty() || year.isEmpty() || author.isEmpty() || page.isEmpty() || currpage.isEmpty() || chapter.isEmpty())
        throw emptyinputs();
    if(!chapter.toInt(&ok) || !page.toInt(&ok) || (!currpage.toInt(&ok)&&currpage!="0") || !year.toInt(&ok)) throw numinputs();
    if(page.toInt(&ok)<currpage.toInt(&ok)) throw lessthan();
    functions F1;
    F1.book_add(title,genre,year,chapter,page,currpage,author,f,ui->bookplan,ui->bookdrop);
    QMessageBox::information(this,"Success","Book has been successfully added!");
    ui->titleline->clear();
    ui->genreline->clear();
    ui->authorline->clear();
    ui->yearline->clear();
    ui->chapline->clear();
    ui->pageline->clear();
    ui->progline->clear();
    ui->bookplan->setChecked(false);
    ui->bookdrop->setChecked(false);
    ui->stackedWidget->setCurrentIndex(4);
}

void MainForm::on_insertbook_clicked()
{
    QString title = ui->titleline->text();
    QString genre = ui->genreline->text();
    QString author = ui->authorline->text();
    QString year = ui->yearline->text();
    QString chapter = ui->chapline->text();
    QString page = ui->pageline->text();
    QString currpage = ui->progline->text();
    try
    {
        MainForm::book_ins(title,genre,author,year,chapter,page,currpage);
    }
    catch(MainForm::emptyinputs)
    {
        QMessageBox::warning(this,"Invalid inputs","Please ensure that all fields are completed.");
        ui->titleline->clear();
        ui->genreline->clear();
        ui->authorline->clear();
        ui->yearline->clear();
        ui->chapline->clear();
        ui->pageline->clear();
        ui->progline->clear();
        ui->bookplan->setChecked(false);
        ui->bookdrop->setChecked(false);
    }
    catch(MainForm::lessthan)
    {
        QMessageBox::warning(this,"EXCEPTION!","Your progress seems invalid.");
        ui->titleline->clear();
        ui->genreline->clear();
        ui->authorline->clear();
        ui->yearline->clear();
        ui->chapline->clear();
        ui->pageline->clear();
        ui->progline->clear();
        ui->bookplan->setChecked(false);
        ui->bookdrop->setChecked(false);
    }
    catch(MainForm::numinputs)
    {
        QMessageBox::warning(this,"EXCEPTION!","Invalid numeric input(s).");
        ui->titleline->clear();
        ui->genreline->clear();
        ui->authorline->clear();
        ui->yearline->clear();
        ui->chapline->clear();
        ui->pageline->clear();
        ui->progline->clear();
        ui->bookplan->setChecked(false);
        ui->bookdrop->setChecked(false);
    }

    /*if(title.isEmpty() || genre.isEmpty() || year.isEmpty() || author.isEmpty() || page.isEmpty() || currpage.isEmpty() || chapter.isEmpty())
    {
        QMessageBox::warning(this,"Invalid inputs","Please ensure that all fields are completed.");
        ui->titleline->clear();
        ui->genreline->clear();
        ui->authorline->clear();
        ui->yearline->clear();
        ui->chapline->clear();
        ui->pageline->clear();
        ui->progline->clear();
        return;
    }
    if(!chapter.toInt(&ok) || !page.toInt(&ok) || !currpage.toInt(&ok) || !year.toInt(&ok))
    {
        QMessageBox::warning(this,"Invalid input(s)","Invalid numeric input(s).");
        ui->titleline->clear();
        ui->genreline->clear();
        ui->authorline->clear();
        ui->yearline->clear();
        ui->chapline->clear();
        ui->pageline->clear();
        ui->progline->clear();
        return;
    }
    if(page.toInt(&ok)<currpage.toInt(&ok))
    {
        QMessageBox::warning(this,"Invalid input(s)","Invalid numeric input(s).");
        ui->titleline->clear();
        ui->genreline->clear();
        ui->authorline->clear();
        ui->yearline->clear();
        ui->chapline->clear();
        ui->pageline->clear();
        ui->progline->clear();
        return;
    }
    functions F1;
    F1.book_add(title,genre,year,chapter,page,currpage,author,f);
    QMessageBox::information(this,"Success","Book has been successfully added!");
    ui->titleline->clear();
    ui->genreline->clear();
    ui->authorline->clear();
    ui->yearline->clear();
    ui->chapline->clear();
    ui->pageline->clear();
    ui->progline->clear();
    ui->stackedWidget->setCurrentIndex(4);*/
}


void MainForm::on_bookbacc_clicked()
{
    ui->titleline->clear();
    ui->genreline->clear();
    ui->authorline->clear();
    ui->yearline->clear();
    ui->chapline->clear();
    ui->pageline->clear();
    ui->progline->clear();
    ui->bookplan->setChecked(false);
    ui->bookdrop->setChecked(false);
    ui->stackedWidget->setCurrentIndex(4);
}


void MainForm::on_tvshowadd_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);//show page
}

void MainForm::tvshow_ins(QString &title, QString &genre, QString &year, QString &runtime, QString &tepisode, QString &currepisode)
{
    bool ok;
    if(title.isEmpty() || genre.isEmpty() || year.isEmpty() || runtime.isEmpty() || tepisode.isEmpty() || currepisode.isEmpty())
        throw emptyinputs();
    if(!year.toInt(&ok) || !runtime.toInt(&ok) || !tepisode.toInt(&ok) || (!currepisode.toInt(&ok)&&currepisode!="0"))
        throw numinputs();
    if(tepisode.toInt(&ok)<currepisode.toInt(&ok))
        throw lessthan();
    functions F1;
    F1.show_add(title,genre,year,runtime,tepisode,currepisode,f,ui->showplan,ui->showdrop);
    QMessageBox::information(this,"Success","The series has been successfully added!");
    ui->stitleline->clear();
    ui->sgenreline->clear();
    ui->syearline->clear();
    ui->stimeline->clear();
    ui->sepisodeline->clear();
    ui->pepisodeline->clear();
    ui->showplan->setChecked(false);
    ui->showdrop->setChecked(false);
    ui->stackedWidget->setCurrentIndex(4);
}

void MainForm::on_sinsert_clicked()
{
    QString title = ui->stitleline->text();
    QString genre = ui->sgenreline->text();
    QString year = ui->syearline->text();
    QString runtime = ui->stimeline->text();
    QString tepisode = ui->sepisodeline->text();
    QString currepisode = ui->pepisodeline->text();
    try
    {
        MainForm::tvshow_ins(title,genre,year,runtime,tepisode,currepisode);
    }
    catch(MainForm::numinputs)
    {
        QMessageBox::warning(this,"EXCEPTION!","Invalid numeric input(s).");
        ui->stitleline->clear();
        ui->sgenreline->clear();
        ui->syearline->clear();
        ui->stimeline->clear();
        ui->sepisodeline->clear();
        ui->pepisodeline->clear();
        ui->showplan->setChecked(false);
        ui->showdrop->setChecked(false);
    }
    catch(MainForm::emptyinputs)
    {
        QMessageBox::warning(this,"EXCEPTION!","Please ensure that all fields are completed.");
        ui->stitleline->clear();
        ui->sgenreline->clear();
        ui->syearline->clear();
        ui->stimeline->clear();
        ui->sepisodeline->clear();
        ui->pepisodeline->clear();
        ui->showplan->setChecked(false);
        ui->showdrop->setChecked(false);
    }
    catch(MainForm::lessthan)
    {
        QMessageBox::warning(this,"EXCEPTION!","Your progress seems invalid.");
        ui->stitleline->clear();
        ui->sgenreline->clear();
        ui->syearline->clear();
        ui->stimeline->clear();
        ui->sepisodeline->clear();
        ui->pepisodeline->clear();
        ui->showplan->setChecked(false);
        ui->showdrop->setChecked(false);
    }

    /*if(title.isEmpty() || genre.isEmpty() || year.isEmpty() || runtime.isEmpty() || tepisode.isEmpty() || currepisode.isEmpty())
    {
        QMessageBox::warning(this,"Invalid inputs","Please ensure that all fields are completed.");
        ui->stitleline->clear();
        ui->sgenreline->clear();
        ui->syearline->clear();
        ui->stimeline->clear();
        ui->sepisodeline->clear();
        ui->pepisodeline->clear();
        return;
    }
    if(!year.toInt(&ok) || !runtime.toInt(&ok) || !tepisode.toInt(&ok) || !currepisode.toInt(&ok))
    {
        QMessageBox::warning(this,"Invalid input(s)","Invalid numeric input(s).");
        ui->stitleline->clear();
        ui->sgenreline->clear();
        ui->syearline->clear();
        ui->stimeline->clear();
        ui->sepisodeline->clear();
        ui->pepisodeline->clear();
        return;
    }
    if(tepisode.toInt(&ok)<currepisode.toInt(&ok))
    {
        QMessageBox::warning(this,"Invalid input(s)","Invalid numeric input(s).");
        ui->stitleline->clear();
        ui->sgenreline->clear();
        ui->syearline->clear();
        ui->stimeline->clear();
        ui->sepisodeline->clear();
        ui->pepisodeline->clear();
        return;
    }
    functions F1;
    F1.show_add(title,genre,year,runtime,tepisode,currepisode,f);
    QMessageBox::information(this,"Success","The series has been successfully added!");
    ui->stitleline->clear();
    ui->sgenreline->clear();
    ui->syearline->clear();
    ui->stimeline->clear();
    ui->sepisodeline->clear();
    ui->pepisodeline->clear();
    ui->stackedWidget->setCurrentIndex(4);*/
}


void MainForm::on_show_gobacc_clicked()
{
    ui->stitleline->clear();
    ui->sgenreline->clear();
    ui->syearline->clear();
    ui->stimeline->clear();
    ui->sepisodeline->clear();
    ui->pepisodeline->clear();
    ui->showplan->setChecked(false);
    ui->showdrop->setChecked(false);
    ui->stackedWidget->setCurrentIndex(4);
}

void MainForm::on_bookplan_clicked()
{
    if(ui->bookdrop->isChecked())ui->bookdrop->setChecked(false);
}


void MainForm::on_bookdrop_clicked()
{
    if(ui->bookplan->isChecked())ui->bookplan->setChecked(false);
}


void MainForm::on_showplan_clicked()
{
    if(ui->showdrop->isChecked())ui->showdrop->setChecked(false);
}


void MainForm::on_showdrop_clicked()
{
    if(ui->showplan->isChecked())ui->showplan->setChecked(false);
}


void MainForm::on_ebookupd_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}


void MainForm::on_updcoll_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainForm::on_updbookbutton_clicked()
{
    try
    {
        EBOOK::bookPageUpdate(ui->bookname,ui->newpage,ui->dropbookupd);
        QMessageBox::information(this,"Success","Updated successfully!");
        ui->bookname->clear();
        ui->newpage->clear();
        ui->dropbookupd->setChecked(false);
        ui->stackedWidget->setCurrentIndex(8);
    }
    catch(EBOOK::toomuchpage)
    {
        QMessageBox::warning(this,"EXCEPTION!","Page count error!");
        ui->bookname->clear();
        ui->newpage->clear();
        ui->dropbookupd->setChecked(false);
    }
    catch(EBOOK::notpage)
    {
        QMessageBox::warning(this,"EXCEPTION!","Invalid page count!");
        ui->bookname->clear();
        ui->newpage->clear();
        ui->dropbookupd->setChecked(false);
    }
    catch(ENTERTAINMENT::namenotfound)
    {
        QMessageBox::warning(this,"EXCEPTION!","Book doesn't exist in database");
        ui->bookname->clear();
        ui->newpage->clear();
        ui->dropbookupd->setChecked(false);
    }
    catch(ENTERTAINMENT::unfilled)
    {
        QMessageBox::warning(this,"EXCEPTION!","Ensure all slots are filled.");
        ui->bookname->clear();
        ui->newpage->clear();
        ui->dropbookupd->setChecked(false);
    }
}


void MainForm::on_bookupdbacc_clicked()
{
    ui->bookname->clear();
    ui->newpage->clear();
    ui->dropbookupd->setChecked(false);
    ui->stackedWidget->setCurrentIndex(8);
}


void MainForm::on_upd_bacc_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainForm::on_movieupd_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void MainForm::on_movupdbutton_clicked()
{
    try
    {
        MOVIE::movieStatusUpdate(ui->movupdname,ui->movstatupd);
        QMessageBox::information(this,"Success","Updated successfully!");
        ui->movstatupd->clear();
        ui->movupdname->clear();
        ui->stackedWidget->setCurrentIndex(8);
    }
    catch(ENTERTAINMENT::namenotfound)
    {
        QMessageBox::warning(this,"EXCEPTION!","Movie doesn't exist in database");
        ui->movupdname->clear();
        ui->movstatupd->clear();
    }
    catch(ENTERTAINMENT::unfilled)
    {
        QMessageBox::warning(this,"EXCEPTION!","Ensure all slots are filled.");
        ui->movupdname->clear();
        ui->movstatupd->clear();
    }
    catch(MOVIE::invalidstat)
    {
        QMessageBox::warning(this,"EXCEPTION!","Please maintain one of the mentioned status formats.");
        ui->movupdname->clear();
        ui->movstatupd->clear();
    }
}


void MainForm::on_movupdbacc_clicked()
{
    ui->movstatupd->clear();
    ui->movupdname->clear();
    ui->stackedWidget->setCurrentIndex(8);
}


void MainForm::on_showupdbacc_clicked()
{
    ui->showupdname->clear();
    ui->showepcount->clear();
    ui->showdropbox->setChecked(false);
    ui->stackedWidget->setCurrentIndex(8);
}


void MainForm::on_showupdbutton_clicked()
{
    try
    {
        TVSHOW::tv_Ep_update(ui->showupdname,ui->showepcount,ui->showdropbox);
        QMessageBox::information(this,"Success","Updated successfully!");
        ui->showupdname->clear();
        ui->showepcount->clear();
        ui->showdropbox->setChecked(false);
        ui->stackedWidget->setCurrentIndex(8);
    }
    catch(TVSHOW::toomanyeps)
    {
        QMessageBox::warning(this,"EXCEPTION","Episode count is crossed!");
        ui->showupdname->clear();
        ui->showepcount->clear();
        ui->showdropbox->setChecked(false);
    }
    catch(ENTERTAINMENT::unfilled)
    {
        QMessageBox::warning(this,"EXCEPTION!","Ensure all slots are filled.");
        ui->bookname->clear();
        ui->newpage->clear();
        ui->showdropbox->setChecked(false);
        ui->dropbookupd->setChecked(false);
    }
    catch(ENTERTAINMENT::namenotfound)
    {
        QMessageBox::warning(this,"EXCEPTION!","Show doesn't exist in database");
        ui->showupdname->clear();
        ui->showepcount->clear();
        ui->showdropbox->setChecked(false);
    }
}


void MainForm::on_tvshowupd_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}


void MainForm::on_collbutton_clicked()
{
    this->hide();
    displayer *dis=new displayer();
    dis->setmf(this);
    dis->show();
}

/*void MainForm::searcher()
{
    if(ui->searchbar->text().isEmpty())throw nosearch();
    else
    {
        TrieNode* Root = new TrieNode();
        functions::searchperformer(ui->searchbar->text().toStdString(),Root);
    }
}*/

void MainForm::on_searchbutton_clicked()
{
    if(ui->searchbar->text().isEmpty() || ui->searchbar->text()=="Look for something!")
    {
        QMessageBox::warning(this,"EXCEPTION","Please enter a valid search name.");
        ui->searchbar->setText("Look for something!");
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(12);
        TrieNode* Root = new TrieNode();
        functions::searchperformer(ui->searchbar->text().toStdString(),Root,ui->searchlist);
        delete Root;
    }
}


void MainForm::on_searchreturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->searchlist->clear();
    ui->searchbar->setText("Look for something!");
    //ui->type_label->clear();
}

void functions::searchadd(QLineEdit *s, QListWidget *q)//to throw exceptions
{
    if(s->text().isEmpty())throw emptiness();
    else if(q->currentRow()==-1)throw noselect();
    else
    {
        f->open(QFile::ReadOnly | QFile::Text);
        QTextStream inread(f);
        int i = 0, pos1=0, pos2=0,pos3=0;
        vector<QString> lines;
        QString line;
        while(!inread.atEnd())
        {
            line=inread.readLine();
            lines.push_back(line);
            i++;
            if(line == "---MOVIES---")
                pos1 = i;
            if(line == "---TVSHOW---")
                pos2 = i;
            if(line == "---BOOKS---")
                pos3 = i;
        }
        f->close();
        int tracker=0;
        for(unsigned long long i=0;i<lines.size();i++)
        {
            if(lines[i]!="---MOVIES---" && lines[i]!="---TVSHOW---" && lines[i]!="---BOOKS---" && !lines[i].isEmpty())
            {
                QStringList parts = lines[i].split("^");
                if(parts[1]==q->currentItem()->text())
                {
                    if(tracker>pos1 && tracker<pos2)//Movie
                    {
                        if(s->text().isEmpty() || (s->text()!="W" && s->text()!="O" && s->text()!="P" && s->text()!="D"))throw nocharacter();
                        functions::movie_add_search(tracker,s);
                        break;
                    }
                    else if(tracker>pos2 && tracker<pos3) //tv shows
                    {
                        bool ok;
                        QString val=s->text();
                        if(!val.toInt(&ok) && val != "0") throw nointeger();
                        int i=functions::show_add_search(tracker, s);
                        if(i==-1)throw nointeger();
                        break;
                    }
                    else if(tracker>pos3)
                    {
                        bool ok;
                        QString val=s->text();
                        if(!val.toInt(&ok) && val != "0") throw nointeger();
                        int i=functions::book_add_search(tracker, s);
                        if(i==-1)throw nointeger();
                        break;
                    }
                }
            }
            tracker++;
        }
    }
}

void MainForm::on_searchadd_clicked()
{
    try
    {
        functions::searchadd(ui->searchstat,ui->searchlist);
        QMessageBox::information(this,"SUCCESS!","Insertion is successful!");
        ui->stackedWidget->setCurrentIndex(0);
        ui->searchstat->setText("Provide a valid status or episode/page count for the respective type to be added");
        ui->searchbar->setText("Look for something!");
        //ui->type_label->clear();
    }
    catch(functions::emptiness)
    {
        QMessageBox::warning(this,"EXCEPTION","Please fill the slot");
        ui->searchstat->clear();
    }
    catch(functions::noselect)
    {
        QMessageBox::warning(this,"EXCEPTION","Please select a row for addition");
        ui->searchstat->clear();
    }
    catch(functions::nocharacter)
    {
        QMessageBox::warning(this,"EXCEPTION","Please provide a valid status");
        ui->searchstat->clear();
    }
    catch(functions::nointeger)
    {
        QMessageBox::warning(this,"EXCEPTION","Please input a proper number");
        ui->searchstat->clear();
    }
}


void MainForm::on_FAQsbutton_clicked()
{
    info *i= new info();
    i->show();
}


void MainForm::on_searchlist_itemSelectionChanged()
{
    //QString type=functions::type_finder(ui->searchlist->currentItem()->text());
    //ui->type_label->clear();
    //ui->type_label->setText(type);
}


void MainForm::on_inspectsearch_clicked()
{
    functions::type_finder(ui->searchlist->currentItem()->text(),this);
}

