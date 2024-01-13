#pragma once
#include "QString"
#include "QFile"
#include "QCheckBox"
#include "mainclasses.h"
#include "mainform.h"
#include "recommender.h"
#include "QLineEdit"
struct TrieNode {
    bool isEndOfWord;
    string ori; //to store data as it was in database
    unordered_map<char, TrieNode*> children;
};
class functions
{
public:

    void movie_add(QString &t,QString &g,QString &y, QString &r, QString &s,QFile* f);
    void book_add(QString &t,QString &g,QString &y, QString &c, QString &p, QString &cp,QString &a,QFile* f,QCheckBox *bplan, QCheckBox *bdrop);
    void show_add(QString &t,QString &g,QString &y, QString &r, QString &e, QString &ce,QFile* f,QCheckBox *splan, QCheckBox *sdrop);

    static void insertTrie(TrieNode* root, const string& word);
    static bool searchTrie(TrieNode* root, const string& word);
    static void getSuggestions(TrieNode* root, const string& prefix, vector<string>& suggestions);

    static void searchperformer(string val,TrieNode *root,QListWidget *sho);
    static void searchadd(QLineEdit *s, QListWidget *q);

    static void movie_add_search(int pos, QLineEdit * sho);
    static int book_add_search(int pos, QLineEdit * sho);
    static int show_add_search(int pos, QLineEdit * sho);

    static void movie_add_auto(ENTERTAINMENT *E,QLineEdit* q);
    static void show_add_auto(ENTERTAINMENT *E,QLineEdit* q);
    static void book_add_auto(ENTERTAINMENT *E,QLineEdit* q);
    static QString mov_counter();
    static QString boo_counter();
    static QString tv_counter();
    static void type_finder(QString q,MainForm *m);
    static void type_finder(QString q,recommender *m);
    class emptiness{};
    class noselect{};
    class nointeger{};
    class nocharacter{};
};

