#include "mainclasses.h"
#include "QTextStream"
#include "QFile"
#include "QCheckBox"
extern QFile* f;
vector<ENTERTAINMENT*> E;
void EBOOK::bookPageUpdate(QLineEdit *bookname, QLineEdit *newpage,QCheckBox* dropbookupd)
{
    bool ok,found=false;
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---BOOKS---")
            pos1 = i;
    }
    f->close();

    //forgot that all class members aint string so if u wanna use member variables then comment out
    //following declaration and use atoi idk:(
    EBOOK E1;
    //QString name, genre, release_year, status, chapters, total_pages, current_page, author, ID;
    QString input, user_pg;
    QString buffer = "^";
    input=bookname->text();
    user_pg=newpage->text();
    if(input.isEmpty() || user_pg.isEmpty())throw unfilled();
    //getline(cin, input);
    for(unsigned long long i=pos1; i<lines.size(); i++)
    {
        QStringList parts = lines[i].split("^");
        E1.SetID(parts[0].toInt(&ok));
        //getline(iss, part, '^');
        E1.Setname(parts[1]);
        if(E1.Getname() != input)
            continue;
        else if(parts[8]=="N")throw namenotfound();
        else
        {
            found=true;
            E1.Setgenre(parts[2]);
            E1.Setrelease_year(parts[3].toInt(&ok));
            E1.Setchapters(parts[4].toInt(&ok));
            E1.Settotal_pages(parts[5].toInt(&ok));
            E1.Setcurrent_page(parts[6].toInt(&ok));
            E1.Setauthor(parts[7]);
            if(!user_pg.toInt(&ok)) throw notpage();
            if(E1.Gettotal_pages()<user_pg.toInt(&ok)) throw toomuchpage();
            if(E1.Gettotal_pages()==user_pg.toInt(&ok))E1.Setstatus("W");
            else if(dropbookupd->isChecked())E1.Setstatus("D");
            else E1.Setstatus("O");
            E1.Setcurrent_page(user_pg.toInt(&ok));
            lines[i]=QString::number(E1.GetID()) + buffer + E1.Getname() + buffer + E1.Getgenre() + buffer + QString::number(E1.Getrelease_year()) + buffer + QString::number(E1.Getchapters()) + buffer + QString::number(E1.Gettotal_pages()) + buffer + QString::number(E1.Getcurrent_page()) + buffer + E1.Getauthor() + buffer + E1.Getstatus();
            break;
        }
    }
    if(!found)
    {
        throw namenotfound();
    }
    QTextStream inwrite(f);
    f->open(QFile::WriteOnly | QFile::Text);
    for (const QString& outputLine : lines) {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void MOVIE::movieStatusUpdate(QLineEdit *movname, QLineEdit *movstat)
{
    bool ok,found=false;
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---MOVIES---")
            pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
    }
    f->close();
    MOVIE m1;
    QString input=movname->text();
    QString status=movstat->text();
    if(input.isEmpty() || status.isEmpty())throw unfilled();
    if(status!="O" && status!="D" && status!="W") throw invalidstat();
    QString buffer = "^";
    for(i=pos1; i<pos2-2; i++)
    {
        QStringList comps = lines[i].split("^");
        m1.SetID(comps[0].toInt(&ok));
        m1.Setname(comps[1]);
        if(m1.Getname() != input)
            continue;
        else if(comps[5]=="N")throw namenotfound();
        else
        {
            found=true;
            m1.Setgenre(comps[2]);
            m1.Setrelease_year(comps[3].toInt(&ok));
            m1.Setruntime(comps[4].toInt(&ok));
            m1.Setstatus(status);
            lines[i] = QString::number(m1.GetID()) + buffer + m1.Getname() + buffer + m1.Getgenre() + buffer + QString::number(m1.Getrelease_year()) + buffer + QString::number(m1.Getruntime()) + buffer + m1.Getstatus();
            break;
        }
    }
    if(!found){throw namenotfound();}
    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines) {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void TVSHOW::tv_Ep_update(QLineEdit *showupdname,QLineEdit *showepcount,QCheckBox *dropbox)
{
    bool ok,found=false;
    f->open(QFile::ReadOnly|QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---TVSHOW---")
            pos1 = i;
        if(line == "---BOOKS---")
            pos2 = i;
    }
    f->close();

    TVSHOW t1;
    //QString name, genre, release_year, avg_runtime, status, total_ep, current_ep, ID;
    QString buffer = "^";
    QString input=showupdname->text();
    QString newep=showepcount->text();
    if(input.isEmpty() || newep.isEmpty())throw unfilled();
    for(i=pos1; i<pos2-2; i++)
    {
        QStringList shows=lines[i].split("^");
        //getline(iss, part, '^');
        t1.SetID(shows[0].toInt(&ok));
        //getline(iss, part, '^');
        t1.Setname(shows[1]);
        if(t1.Getname() != input)
            continue;
        else if(shows[7]=="N")throw namenotfound();
        else
        {
            found=true;
            t1.Setgenre(shows[2]);
            t1.Setrelease_year(shows[3].toInt(&ok));
            t1.Settotal_ep(shows[4].toInt(&ok));
            t1.Setavg_runtime(shows[5].toInt(&ok));
            //t1.Setcurrent_ep(showsp[6].toInt(&ok));
            //t1.Setstatus(shows[7]);
            t1.Setcurrent_ep(newep.toInt(&ok));
            if(newep.toInt(&ok)==t1.Gettotal_ep())t1.Setstatus("W");
            else if(dropbox->isChecked())t1.Setstatus("D");
            else if(newep.toInt(&ok)<t1.Gettotal_ep()) t1.Setstatus("O");
            else if(newep.toInt(&ok)>t1.Gettotal_ep()) throw toomanyeps();
            lines[i] = QString::number(t1.GetID()) + buffer + t1.Getname() + buffer + t1.Getgenre() + buffer + QString::number(t1.Getrelease_year()) + buffer + QString::number(t1.Gettotal_ep()) + buffer + QString::number(t1.Getavg_runtime()) + buffer + QString::number(t1.Getcurrent_ep()) + buffer + t1.Getstatus();
            break;
        }
    }
    if(!found){throw namenotfound();}
    f->open(QFile::WriteOnly|QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines) {
        inwrite << outputLine << "\n";
    }
    f->close();
}

/*void ENTERTAINMENT::completedAll(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1, pos2, pos3;
    while(!inread.atEnd())
    {
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

    vector<QString> list;
    bool ok;
    for(int i=pos1; i<pos2-2; i++)
    {
        QString name,genre,status;
        int release_year, runtime, ID;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        runtime=parts[4].toInt(&ok);
        status=parts[5];
        if(status=="W")
        {
            MOVIE* m1 = new MOVIE(name, ID, genre, release_year, runtime, status);
            E.push_back(m1);
        }
    }

    for(int i=pos2; i<pos3-2; i++)
    {
        QString name,genre,status,author;
        int release_year, curr_page,total_pages, ID,chapters;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        chapters=parts[4].toInt(&ok);
        total_pages=parts[5].toInt(&ok);
        curr_page=parts[6].toInt(&ok);
        author=parts[7];
        status=parts[8];
        if(status=="W")
        {
            EBOOK *e1 = new EBOOK(name, ID, genre, release_year, total_pages, curr_page, chapters, author, status);
            E.push_back(e1);
        }
    }

    for(unsigned long long i=pos3; i<lines.size(); i++)
    {
        QString name,genre,status;
        int release_year, curr_ep,total_ep, ID,runtime;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        total_ep=parts[4].toInt(&ok);
        runtime=parts[5].toInt(&ok);
        curr_ep=parts[6].toInt(&ok);
        status=parts[7];
        if(status=="W")
        {
            //TVSHOW t1("Huckleberry", 123, "Action", 2001, 48, 0, 0, status);
            TVSHOW *t1=new TVSHOW(name, ID, genre, release_year, runtime,total_ep, curr_ep, status);
            E.push_back(t1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }

}*/

void MOVIE::show_Mov_W(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---MOVIES---")
            pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        //if(line == "---BOOKS---")
            //pos3 = i;
    }
    f->close();

    bool ok;
    for(int i=pos1; i<pos2-2; i++)
    {
        QString name,genre,status;
        int release_year, runtime, ID;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        runtime=parts[4].toInt(&ok);
        status=parts[5];
        if(status=="W")
        {
            MOVIE* m1 = new MOVIE(name, ID, genre, release_year, runtime, status);
            E.push_back(m1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
    /*for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();*/
}

void MOVIE::show_Mov_ong(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---MOVIES---")
            pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        //if(line == "---BOOKS---")
        //pos3 = i;
    }
    f->close();

    bool ok;
    for(int i=pos1; i<pos2-2; i++)
    {
        QString name,genre,status;
        int release_year, runtime, ID;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        runtime=parts[4].toInt(&ok);
        status=parts[5];
        if(status=="O")
        {
            MOVIE* m1 = new MOVIE(name, ID, genre, release_year, runtime, status);
            E.push_back(m1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
    /*for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();*/
}

void MOVIE::show_Mov_D(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---MOVIES---")
            pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        //if(line == "---BOOKS---")
        //pos3 = i;
    }
    f->close();

    bool ok;
    for(int i=pos1; i<pos2-2; i++)
    {
        QString name,genre,status;
        int release_year, runtime, ID;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        runtime=parts[4].toInt(&ok);
        status=parts[5];
        if(status=="D")
        {
            MOVIE* m1 = new MOVIE(name, ID, genre, release_year, runtime, status);
            E.push_back(m1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
    /*for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();*/
}

void MOVIE::show_Mov_P(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---MOVIES---")
            pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        //if(line == "---BOOKS---")
        //pos3 = i;
    }
    f->close();

    bool ok;
    for(int i=pos1; i<pos2-2; i++)
    {
        QString name,genre,status;
        int release_year, runtime, ID;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        runtime=parts[4].toInt(&ok);
        status=parts[5];
        if(status=="P")
        {
            MOVIE* m1 = new MOVIE(name, ID, genre, release_year, runtime, status);
            E.push_back(m1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
    /*for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();*/
}

void EBOOK::show_BOO_W(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
          //  pos1 = i;
        //if(line == "---TVSHOW---")
          //  pos2 = i;
        if(line == "---BOOKS---")
        pos3 = i;
    }
    f->close();

    bool ok;
    for(unsigned long i=pos3; i<lines.size(); i++)
    {
        QString name,genre,status,author;
        int release_year, curr_page,total_pages, ID,chapters;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        chapters=parts[4].toInt(&ok);
        total_pages=parts[5].toInt(&ok);
        curr_page=parts[6].toInt(&ok);
        author=parts[7];
        status=parts[8];
        if(status=="W")
        {
            EBOOK *e1 = new EBOOK(name, ID, genre, release_year, total_pages, curr_page, chapters, author, status);
            E.push_back(e1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
    /*for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();*/
}

void TVSHOW::show_TV_W(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos2=0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    for(i=pos2; i<pos3 - 2; i++)
    {
        QString name,genre,status;
        int release_year, curr_ep,total_ep, ID,runtime;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        total_ep=parts[4].toInt(&ok);
        runtime=parts[5].toInt(&ok);
        curr_ep=parts[6].toInt(&ok);
        status=parts[7];
        if(status=="W")
        {
            //TVSHOW t1("Huckleberry", 123, "Action", 2001, 48, 0, 0, status);
            TVSHOW *t1=new TVSHOW(name, ID, genre, release_year, runtime,total_ep, curr_ep, status);
            E.push_back(t1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void TVSHOW::show_TV_D(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos2=0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    for(i=pos2; i<pos3 - 2; i++)
    {
        QString name,genre,status;
        int release_year, curr_ep,total_ep, ID,runtime;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        total_ep=parts[4].toInt(&ok);
        runtime=parts[5].toInt(&ok);
        curr_ep=parts[6].toInt(&ok);
        status=parts[7];
        if(status=="D")
        {
            //TVSHOW t1("Huckleberry", 123, "Action", 2001, 48, 0, 0, status);
            TVSHOW *t1=new TVSHOW(name, ID, genre, release_year, runtime,total_ep, curr_ep, status);
            E.push_back(t1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void TVSHOW::show_TV_ong(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos2=0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    for(i=pos2; i<pos3 - 2; i++)
    {
        QString name,genre,status;
        int release_year, curr_ep,total_ep, ID,runtime;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        total_ep=parts[4].toInt(&ok);
        runtime=parts[5].toInt(&ok);
        curr_ep=parts[6].toInt(&ok);
        status=parts[7];
        if(status=="O")
        {
            //TVSHOW t1("Huckleberry", 123, "Action", 2001, 48, 0, 0, status);
            TVSHOW *t1=new TVSHOW(name, ID, genre, release_year, runtime,total_ep, curr_ep, status);
            E.push_back(t1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void TVSHOW::show_TV_P(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos2=0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    for(i=pos2; i<pos3 - 2; i++)
    {
        QString name,genre,status;
        int release_year, curr_ep,total_ep, ID,runtime;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        total_ep=parts[4].toInt(&ok);
        runtime=parts[5].toInt(&ok);
        curr_ep=parts[6].toInt(&ok);
        status=parts[7];
        if(status=="P")
        {
            //TVSHOW t1("Huckleberry", 123, "Action", 2001, 48, 0, 0, status);
            TVSHOW *t1=new TVSHOW(name, ID, genre, release_year, runtime,total_ep, curr_ep, status);
            E.push_back(t1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void EBOOK::show_BOO_ong(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        //if(line == "---TVSHOW---")
        //  pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();

    bool ok;
    for(unsigned long i=pos3; i<lines.size(); i++)
    {
        QString name,genre,status,author;
        int release_year, curr_page,total_pages, ID,chapters;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        chapters=parts[4].toInt(&ok);
        total_pages=parts[5].toInt(&ok);
        curr_page=parts[6].toInt(&ok);
        author=parts[7];
        status=parts[8];
        if(status=="O")
        {
            EBOOK *e1 = new EBOOK(name, ID, genre, release_year, total_pages, curr_page, chapters, author, status);
            E.push_back(e1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void EBOOK::show_BOO_P(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        //if(line == "---TVSHOW---")
        //  pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();

    bool ok;
    for(unsigned long i=pos3; i<lines.size(); i++)
    {
        QString name,genre,status,author;
        int release_year, curr_page,total_pages, ID,chapters;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        chapters=parts[4].toInt(&ok);
        total_pages=parts[5].toInt(&ok);
        curr_page=parts[6].toInt(&ok);
        author=parts[7];
        status=parts[8];
        if(status=="P")
        {
            EBOOK *e1 = new EBOOK(name, ID, genre, release_year, total_pages, curr_page, chapters, author, status);
            E.push_back(e1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void EBOOK::show_BOO_D(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
        //  pos1 = i;
        //if(line == "---TVSHOW---")
        //  pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();

    bool ok;
    for(unsigned long i=pos3; i<lines.size(); i++)
    {
        QString name,genre,status,author;
        int release_year, curr_page,total_pages, ID,chapters;
        QStringList parts=lines[i].split("^");
        ID=parts[0].toInt(&ok);
        name=parts[1];
        genre=parts[2];
        release_year=parts[3].toInt(&ok);
        chapters=parts[4].toInt(&ok);
        total_pages=parts[5].toInt(&ok);
        curr_page=parts[6].toInt(&ok);
        author=parts[7];
        status=parts[8];
        if(status=="D")
        {
            EBOOK *e1 = new EBOOK(name, ID, genre, release_year, total_pages, curr_page, chapters, author, status);
            E.push_back(e1);
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void MOVIE::inspection(ENTERTAINMENT *E,QLabel *title,QLabel *genre, QLabel *year, QLabel *runtime, QLabel *status)
{
    title->setText(E->Getname());
    genre->setText(E->Getgenre());
    year->setText(QString::number(E->Getrelease_year()));
    runtime->setText(QString::number(E->Getruntime()));
    if(E->Getstatus()=="W")status->setText("Watched");
    else if(E->Getstatus()=="O")status->setText("Ongoing");
    else if(E->Getstatus()=="D")status->setText("Dropped");
    else if(E->Getstatus()=="P")status->setText("Planned");
}
void TVSHOW::inspection(ENTERTAINMENT *E,QLabel *title, QLabel *genre, QLabel *year, QLabel *totep, QLabel *currep, QLabel *time, QLabel *status)
{
    title->setText(E->Getname());
    genre->setText(E->Getgenre());
    year->setText(QString::number(E->Getrelease_year()));
    totep->setText(QString::number(E->Gettotal_ep()));
    time->setText(QString::number(E->Getavg_runtime()));
    currep->setText(QString::number(E->Getcurrent_ep()));
    if(E->Getstatus()=="W")status->setText("Watched");
    else if(E->Getstatus()=="O")status->setText("Ongoing");
    else if(E->Getstatus()=="D")status->setText("Dropped");
    else if(E->Getstatus()=="P")status->setText("Planned");
}
void EBOOK::inspection(ENTERTAINMENT *E, QLabel *title, QLabel *genre, QLabel *year, QLabel *chap, QLabel *totpage, QLabel *currpage, QLabel *author, QLabel *status)
{
    title->setText(E->Getname());
    genre->setText(E->Getgenre());
    year->setText(QString::number(E->Getrelease_year()));
    chap->setText(QString::number(E->Getchapters()));
    totpage->setText(QString::number(E->Gettotal_pages()));
    currpage->setText(QString::number(E->Getcurrent_page()));
    author->setText(E->Getauthor());
    if(E->Getstatus()=="W")status->setText("Read");
    else if(E->Getstatus()=="O")status->setText("Ongoing");
    else if(E->Getstatus()=="D")status->setText("Dropped");
    else if(E->Getstatus()=="P")status->setText("Planned");
}

void TVSHOW::show_rec_TV(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos2=0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
       // if(line == "---MOVIES---")
           // pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    QString status;
    vector<QString> watched;          //A vector containing all the watched entries
    for(int i=pos2; i<pos3-2; i++)
    {
        QStringList comp=lines[i].split("^");
        status=comp[7];
        if(status == "W")
        {
            watched.push_back(lines[i]);
        }
    }
    if(watched.empty())return;
    unordered_map<int,bool> usage;
    int n = 50;
    while(n--)             //Repeats Loop a few times to ensure that a movie can be recommended if there are recommendable movies
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, watched.size() - 1);
        int rand = distribution(gen);
        QStringList stuff=watched[rand].split("^");               //Takes a random entry from "watched" vector
        QString rec_gen = stuff[2];                  //Stores a random genre
        int count = 0;
        for(int i=pos2; i<pos3 - 2; i++)
        {
            QString name,genre,status;
            int ID, runtime, year,curr_ep,tot_ep;
            QStringList morestuff=lines[i].split("^");
            ID=morestuff[0].toInt(&ok);
            name=morestuff[1];
            genre=morestuff[2];
            year=morestuff[3].toInt(&ok);
            tot_ep=morestuff[4].toInt(&ok);
            runtime=morestuff[5].toInt(&ok);
            curr_ep=morestuff[6].toInt(&ok);
            status=morestuff[7];
            if(status != "W" && status!= "O" && status != "D" && status!="P" && genre == rec_gen && usage[i]!=true)
            {
                usage[i]=true;
                TVSHOW *m1=new TVSHOW(name, ID, genre, year, runtime,tot_ep,curr_ep, status);
                //MOVIE *m1=new MOVIE(watchedobj[rand].Getname(),watchedobj[rand].GetID(),watchedobj[rand].Getgenre(),watchedobj[rand].Getrelease_year(),watchedobj[rand].Getruntime(),watchedobj[rand].Getstatus());
                E.push_back(m1);
                count ++;
                if(count == 6)
                    break;
            }
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void EBOOK::show_rec_BOO(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0,pos3=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
            //pos1 = i;
        //if(line == "---TVSHOW---")
           // pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    QString status;
    vector<QString> watched;          //A vector containing all the watched entries
    for(unsigned long long i=pos3; i<lines.size(); i++)
    {
        QStringList comp=lines[i].split("^");
        status=comp[8];
        if(status == "W")
        {
            watched.push_back(lines[i]);
        }
    }
    if(watched.empty())return;
    unordered_map<int,bool> usage;
    int n = 50;
    while(n--)             //Repeats Loop a few times to ensure that a movie can be recommended if there are recommendable movies
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, watched.size() - 1);
        int rand = distribution(gen);
        QStringList stuff=watched[rand].split("^");               //Takes a random entry from "watched" vector
        QString rec_gen = stuff[2];                  //Stores a random genre
        int count = 0;
        for(unsigned long long i=pos3; i<lines.size(); i++)
        {
            QString name,genre,status,author;
            int ID, chapters,tot_pg,curr_pg, year;
            QStringList morestuff=lines[i].split("^");
            ID=morestuff[0].toInt(&ok);
            name=morestuff[1];
            genre=morestuff[2];
            year=morestuff[3].toInt(&ok);
            chapters=morestuff[4].toInt(&ok);
            tot_pg=morestuff[5].toInt(&ok);
            curr_pg=morestuff[6].toInt(&ok);
            author=morestuff[7];
            status=morestuff[8];
            if(status != "W" && status!= "O" && status != "D" && status!="P" && genre == rec_gen && usage[i]!=true)
            {
                usage[i]=true;
                EBOOK *m1=new EBOOK(name, ID, genre, year, tot_pg,curr_pg,chapters,author,status);
                //MOVIE *m1=new MOVIE(watchedobj[rand].Getname(),watchedobj[rand].GetID(),watchedobj[rand].Getgenre(),watchedobj[rand].Getrelease_year(),watchedobj[rand].Getruntime(),watchedobj[rand].Getstatus());
                E.push_back(m1);
                count ++;
                if(count == 6)
                    break;
            }
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}

void MOVIE::show_rec_MOV(QListWidget *sho)
{
    for(unsigned long long i=0;i<E.size();i++)
    {
        delete E[i];
    }
    E.clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    int i = 0, pos1=0, pos2=0;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---MOVIES---")
            pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        //if(line == "---BOOKS---")
        //pos3 = i;
    }
    f->close();
    bool ok;
    QString status;
    vector<QString> watched;          //A vector containing all the watched entries
    for(int i=pos1; i<pos2-2; i++)
    {
        QStringList comp=lines[i].split("^");
        status=comp[5];
        if(status == "W")
        {
            watched.push_back(lines[i]);
        }
    }
    if(watched.empty())return;
    unordered_map<int,bool> usage;
    int n = 50;
    while(n--)             //Repeats Loop a few times to ensure that a movie can be recommended if there are recommendable movies
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, watched.size() - 1);
        int rand = distribution(gen);
        QStringList stuff=watched[rand].split("^");               //Takes a random entry from "watched" vector
        QString rec_gen = stuff[2];                  //Stores a random genre
        int count = 0;
        for(int i=pos1; i<pos2 - 2; i++)
        {
            QString name,genre,status;
            int ID, runtime, year;
            QStringList morestuff=lines[i].split("^");
            ID=morestuff[0].toInt(&ok);
            name=morestuff[1];
            genre=morestuff[2];
            year=morestuff[3].toInt(&ok);
            runtime=morestuff[4].toInt(&ok);
            status=morestuff[5];
            if(status != "W" && status!= "O" && status != "D" && status!="P" && genre == rec_gen && usage[i]!=true)
            {
                usage[i]=true;
                MOVIE *m1=new MOVIE(name, ID, genre, year, runtime, status);
                //MOVIE *m1=new MOVIE(watchedobj[rand].Getname(),watchedobj[rand].GetID(),watchedobj[rand].Getgenre(),watchedobj[rand].Getrelease_year(),watchedobj[rand].Getruntime(),watchedobj[rand].Getstatus());
                E.push_back(m1);
                count ++;
                if(count == 6)
                    break;
            }
        }
    }
    sho->clear();
    for(unsigned long long i=0;i<E.size();i++)
    {
        sho->addItem(E[i]->Getname());
    }
}
