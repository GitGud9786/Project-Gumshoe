#pragma once
#include <bits/stdc++.h>
#include "QString"
#include "QLineEdit"
#include "QCheckBox"
#include "QListWidget"
#include "QStackedWidget"
#include "QLabel"
#include "unordered_map"
using namespace std;

class HOME
{
public:
    HOME();
    ~HOME();

    //search();
    void user_logout();
    void set_theme();
    void getFAQ();

protected:

private:
};
//enum ent_type {mov, tv, book};
const int MAX_ENTERTAINMENTS = 1000;
class ENTERTAINMENT
{
public:
    ENTERTAINMENT(){};
    ENTERTAINMENT(QString n, int i, QString g, int ry, QString s) : name(n), ID(i), genre(g), release_year(ry), status(s) {};
    virtual ~ENTERTAINMENT(){};

    QString Getname() { return name; }
    void Setname(QString val) { name = val; }
    int GetID() { return ID; }
    void SetID(int val) { ID = val; }
    QString Getgenre() { return genre; }
    void Setgenre(QString val) { genre = val; }
    int Getrelease_year() { return release_year; }
    void Setrelease_year(int val) { release_year = val; }
    void Setstatus(QString s){status=s;}
    QString Getstatus(){return status;}
    QString gettype(){return type;}
    //void changeshared(){shared=true;}
    //bool getshared(){return shared;}

    static void completedAll(QListWidget *sho);
    static void ongoingAll(QListWidget *sho);
    static void droppedAll(QListWidget *sho);
    static void plannedAll(QListWidget *sho);


    class unfilled{};
    class namenotfound{};

    virtual int Getruntime() {return -1;}

    virtual int Getavg_runtime() { return -1; }
    virtual int Getseason_number() { return -1; }
    virtual int Gettotal_ep() { return -1; }
    virtual int Getcurrent_ep() { return -1; }

    virtual int Gettotal_pages() { return -1; }
    virtual int Getchapters() { return -1; }
    virtual QString Getauthor() { return "W"; }
    virtual int Getcurrent_page() { return -1; }
    //static void readMovie();
    //static void readTvshow();
    //static void readEbook();

    //ent_type get_type();

protected:

    QString name;
    int ID;
    QString genre;
    int release_year;
    QString status;
    QString type;
    //bool shared=false;
    //static ENTERTAINMENT* arrap[MAX_ENTERTAINMENTS];
    //static int n;
};
class MOVIE : public ENTERTAINMENT
{
public:
    MOVIE(){type="M";};
    MOVIE(QString name, int id, QString gen, int r_year, int r, QString s ) :ENTERTAINMENT(name, id, gen, r_year, s), runtime(r) {type="M";};
    ~MOVIE(){};

    int Getruntime() { return runtime; }
    void Setruntime(int val) { runtime = val; }

    static void movieStatusUpdate(QLineEdit *movname, QLineEdit *movstat);
    static void show_Mov_W(QListWidget *sho);
    //static void show_Mov_N(vector<QString> lines, int pos1, int pos2);
    static void show_Mov_P(QListWidget* sho);
    static void show_Mov_D(QListWidget* sho);
    static void show_Mov_ong(QListWidget* sho);
    static void inspection(ENTERTAINMENT *E,QLabel *title,QLabel *genre, QLabel *year, QLabel *runtime, QLabel *status);
    static void show_rec_MOV(QListWidget* sho);
    class invalidstat{};
    class namenfound{};
protected:

private:
    int runtime;
};

class TVSHOW : public ENTERTAINMENT
{
public:
    TVSHOW(){type="T";};
    TVSHOW(QString name, int id, QString gen, int r_year, int dur, int total, int curr, QString s) :ENTERTAINMENT(name, id, gen, r_year,s), total_ep(total), current_ep(curr),avg_runtime(dur){type="T";};
    ~TVSHOW(){};
    //SEASON Getseason() { return season; }
    //void Setseason(SEASON val) { season = val; }
    //int Getprogress_season() { return progress_season; }
    //void Setprogress_season(int val) { progress_season = val; }
    int Getavg_runtime() { return avg_runtime; }
    void Setavg_runtime(int val) { avg_runtime = val; }
    int Getseason_number() { return season_number; }
    void Setseason_number(int val) { season_number = val; }
    int Gettotal_ep() { return total_ep; }
    void Settotal_ep(int val) { total_ep = val; }
    int Getcurrent_ep() { return current_ep; }
    void Setcurrent_ep(int val) { current_ep = val; }
    static void inspection(ENTERTAINMENT *e,QLabel *title, QLabel *genre, QLabel *year, QLabel *totep, QLabel *time, QLabel *currep, QLabel *stat);

    void Display() const;

    static void tv_Ep_update(QLineEdit *showupdname,QLineEdit *showepcount,QCheckBox *dropbox);
    //static void tv_status_update();
    static void show_TV_W(QListWidget *sho);
    //static void show_TV_N(vector<string> lines, int pos1, int pos2);
    static void show_TV_ong(QListWidget* sho);
    static void show_TV_P(QListWidget* sho);
    static void show_TV_D(QListWidget* sho);
    static void show_rec_TV(QListWidget* sho);

    class toomanyeps{};
protected:

private:
    //SEASON season;
    int season_number;
    QString season;
    int total_ep;
    int current_ep;
    int avg_runtime;
    //int current_season;
};

class EBOOK : public ENTERTAINMENT
{
public:
    EBOOK(){type="B";};
    EBOOK(QString name, int id, QString gen, int r_year, int p, int cp, int c, QString a, QString s) :ENTERTAINMENT(name, id, gen, r_year,s), total_pages(p), chapters(c),author(a),current_page(cp){type="B";}
    ~EBOOK(){};

    int Gettotal_pages() { return total_pages; }
    void Settotal_pages(int val) { total_pages = val; }
    int Getchapters() { return chapters; }
    void Setchapters(int val) { chapters = val; }
    QString Getauthor() { return author; }
    void Setauthor(QString val) { author = val; }
    //QString Getpublisher() { return publisher; }
    //void Setpublisher(QString val) { publisher = val; }
    //int Getvolumes() { return volumes; }
    //void Setvolumes(int val) { volumes = val; }
    int Getcurrent_page() { return current_page; }
    void Setcurrent_page(int val) { current_page = val; }
    static void inspection(ENTERTAINMENT *e,QLabel *title,QLabel *genre, QLabel *time, QLabel *chap, QLabel *totpage, QLabel *currpage, QLabel *author,QLabel *stat);

    static void bookPageUpdate(QLineEdit *bookname, QLineEdit *pagename,QCheckBox* dropbookupd);
    //static void bookStatusUpdate(QLineEdit *bookname);
    static void show_BOO_W(QListWidget* sho);
    //static void show_BOO_N(vector<QString> lines, int pos);
    static void show_BOO_ong(QListWidget * sho);
    static void show_BOO_P(QListWidget *sho);
    static void show_BOO_D(QListWidget *sho);
    static void show_rec_BOO(QListWidget* sho);

    class toomuchpage{};
    class notpage{};

protected:

private:
    int total_pages;
    int chapters;
    QString author;
    //string publisher;
    //int volumes;
    int current_page;
};

class ACCOUNTS
{
public:
    //ACCOUNTS();
    //~ACCOUNTS();

    QString Getusername() { return username; }
    void Setusername(QString val) { username = val; }
    int Getuser_id() { return user_id; }
    void Setuser_id(int val) { user_id = val; }
    QString Getpassword() { return password; }
    void Setpassword(QString val) { password = val; }


    //void change_pass();
    //void change_username();

protected:

private:
    QString username;
    int user_id;
    QString password;
};
