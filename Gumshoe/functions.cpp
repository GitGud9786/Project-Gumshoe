#include "functions.h"
#include <bits/stdc++.h>
#include "QTextStream"
#include "QString"
#include "QMessageBox"
#include "QWidget"
using namespace std;
extern QFile *f;
void functions::movie_add(QString &title,QString &genre,QString &year, QString &runtime, QString &status, QFile* f)
{
    f->open(QFile::ReadOnly | QFile::Text);
    int ID=0;
    QTextStream inread(f);
    int i = 0, pos1=0, pos2=0;
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
    }
    f->close();
    f->open(QFile::WriteOnly | QFile::Text);
    QString buffer = "^";
    ID = pos2 - pos1 - 1;
    QString id= QString::number(ID);
    QString insert = id + buffer + title + buffer + genre + buffer + year + buffer + runtime + buffer + status;
    lines.insert(lines.begin() + (pos2 - 2), insert);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void functions::book_add(QString &title, QString &genre, QString &year, QString &chapter, QString &page, QString &currpage, QString &author, QFile* f,QCheckBox *bplan,QCheckBox *bdrop)
{
    f->open(QFile::ReadOnly | QFile::Text);
    int ID=0;
    QTextStream inread(f);
    int i = 0, pos1=0;
    vector<QString> lines;
    QString line;
    while(!inread.atEnd())
    {
        line = inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---BOOKS---")
            pos1 = i;
    }
    f->close();

    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    QString buffer = "^";
    ID = i - pos1 + 1;
    bool first,second;
    int fi=page.toInt(&first);
    QString status;
    int se=currpage.toInt(&second);
    if(se<fi && se!=0)status="O";
    else if(bplan->isChecked())status = "P";
    else if(bdrop->isChecked())status="D";
    else if(fi==se)
    {
        status="W";
    }
    QString id= QString::number(ID);
    QString insert = id + buffer + title + buffer + genre + buffer + year + buffer + chapter + buffer + page + buffer + currpage + buffer + author + buffer + status;
    lines.push_back(insert);

    for (const QString& outputLine : lines) {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void functions::show_add(QString &title,QString &genre,QString &year, QString &runtime, QString &episode, QString &currepisode,QFile* f,QCheckBox* splan, QCheckBox* sdrop)
{
    int ID=0;
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    int i = 0, pos1=0, pos2=0;
    vector<QString> lines;
    QString line;
    while(!inread.atEnd())
    {
        line = inread.readLine();
        lines.push_back(line);
        i++;
        if(line == "---TVSHOW---")
            pos1 = i;
        if(line == "---BOOKS---")
            pos2 = i;
    }
    f->close();

    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    QString buffer = "^";
    ID = pos2 - pos1 - 1;
    bool first,second;
    int fi=episode.toInt(&first);
    QString status;
    int se=currepisode.toInt(&second);
    if(se<fi && se!=0){status="O";}
    else if(splan->isChecked())status="P";
    else if(sdrop->isChecked())status="D";
    else if(fi==se)
    {
        status="W";
    }
    QString id= QString::number(ID);
    QString insert = id + buffer + title + buffer + genre + buffer + year + buffer + episode + buffer + runtime + buffer + currepisode + buffer + status;
    lines.insert(lines.begin() + (pos2 - 2), insert);

    for (const QString& outputLine : lines) {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void functions::movie_add_auto(ENTERTAINMENT* E,QLineEdit *q)
{
    f->open(QFile::ReadOnly | QFile::Text);
    //int ID=0;
    QTextStream inread(f);
    int i = 0, pos1=0, pos2=0;
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
    }
    f->close();
    for(int i=pos1;i<pos2 - 2;i++)
    {
        QStringList parts=lines[i].split("^");
        if(parts[1]==E->Getname())
        {
            QString buffer = "^";
            lines.erase(lines.begin()+i);
            if(q->text()=="W")parts[5]="W";
            else if(q->text()=="D")parts[5]="D";
            else if(q->text()=="O")parts[5]="O";
            else if(q->text()=="P")parts[5]="P";
            vector<QString>::iterator Position = lines.begin() + i;
            QString insert = parts[0] + buffer + parts[1] + buffer + parts[2] + buffer + parts[3] + buffer + parts[4] + buffer + parts[5];
            lines.insert(Position, insert);
        }
    }
    f->open(QFile::WriteOnly | QFile::Text);
    //QString buffer = "^";
    /*ID = pos2 - pos1 - 1;
    QString id= QString::number(ID);
    if(q->text()=="W")status="W";
    else if(q->text()=="D")status="D";
    else if(q->text()=="O")status="O";
    else if(q->text()=="P")status="P";
    QString insert = id + buffer + E->Getname() + buffer + E->Getgenre() + buffer + QString::number(E->Getrelease_year()) + buffer + QString::number(E->Getruntime()) + buffer + status;
    lines.insert(lines.begin() + (pos2 - 2), insert);*/
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void functions::show_add_auto(ENTERTAINMENT *E,QLineEdit* q)
{
    f->open(QFile::ReadOnly | QFile::Text);
    //int ID=0;
    QTextStream inread(f);
    int i = 0, pos2=0,pos3=0;
    vector<QString> lines;
    QString line;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
        i++;
        //if(line == "---MOVIES---")
            //pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
    }
    f->close();
    bool ok;
    for(int i=pos2;i<pos3 - 2;i++)
    {
        QStringList parts=lines[i].split("^");
        if(parts[1]==E->Getname())
        {
            QString buffer = "^";
            lines.erase(lines.begin()+i);
            if(q->text()=="0")parts[7]="P";
            else if(q->text().toInt(&ok)==E->Gettotal_ep())parts[7]="W";
            else parts[7]="O";
            parts[6]=q->text();
            vector<QString>::iterator Position = lines.begin() + i;
            QString insert = parts[0] + buffer + parts[1] + buffer + parts[2] + buffer + parts[3] + buffer + parts[4] + buffer + parts[5] + buffer + parts[6] + buffer + parts[7];
            lines.insert(Position, insert);
        }
    }
    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void functions::book_add_auto(ENTERTAINMENT *E,QLineEdit* q)
{
    f->open(QFile::ReadOnly | QFile::Text);
    //int ID=0;
    QTextStream inread(f);
    int i = 0,pos3=0;
    vector<QString> lines;
    QString line;
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
    for(unsigned long long i=pos3;i<lines.size();i++)
    {
        QStringList parts=lines[i].split("^");
        if(parts[1]==E->Getname())
        {
            QString buffer = "^";
            lines.erase(lines.begin()+i);
            if(q->text()=="0")parts[8]="P";
            else if(q->text().toInt(&ok)==E->Gettotal_pages())parts[8]="W";
            else parts[8]="O";
            parts[6]=q->text();
            vector<QString>::iterator Position = lines.begin() + i;
            QString insert = parts[0] + buffer + parts[1] + buffer + parts[2] + buffer + parts[3] + buffer + parts[4] + buffer + parts[5] + buffer + parts[6] + buffer + parts[7] + buffer + parts[8];
            lines.insert(Position, insert);
        }
    }
    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
}

void functions::movie_add_search(int pos, QLineEdit * sho)
{
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
    }
    f->close();
    QString buffer="^";
    QStringList parts= lines[pos].split("^");
    if(sho->text()=="W")parts[5]="W";
    else if(sho->text()=="D")parts[5]="D";
    else if(sho->text()=="O")parts[5]="O";
    else if(sho->text()=="P")parts[5]="P";
    lines.erase(lines.begin()+pos);
    vector<QString>::iterator Position = lines.begin() + pos;
    QString insert = parts[0] + buffer + parts[1] + buffer + parts[2] + buffer + parts[3] + buffer + parts[4] + buffer + parts[5];
    lines.insert(Position, insert);
    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
}

int functions::book_add_search(int pos, QLineEdit * sho)
{
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
    }
    f->close();
    bool ok;
    QString buffer="^";
    QStringList parts= lines[pos].split("^");
    if(sho->text()=="0")parts[8]="P";
    else if(sho->text().toInt(&ok) > parts[5].toInt(&ok)) return -1;
    else if(sho->text().toInt(&ok) == parts[5].toInt(&ok))parts[8]="W";
    else if(sho->text().toInt(&ok) < parts[5].toInt(&ok))parts[8]="O";
    parts[6]=sho->text();
    lines.erase(lines.begin()+pos);
    vector<QString>::iterator Position = lines.begin() + pos;
    QString insert = parts[0] + buffer + parts[1] + buffer + parts[2] + buffer + parts[3] + buffer + parts[4] + buffer + parts[5] + buffer+ parts[6] + buffer + parts[7] + buffer + parts[8];
    lines.insert(Position, insert);
    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
    return 1;
}
int functions::show_add_search(int pos, QLineEdit * sho)
{
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    vector<QString> lines;
    QString line;
    while(!inread.atEnd())
    {
        line=inread.readLine();
        lines.push_back(line);
    }
    f->close();
    bool ok;
    QString buffer="^";
    QStringList parts= lines[pos].split("^");
    if(sho->text()=="0")parts[7]="P";
    else if(sho->text().toInt(&ok) > parts[4].toInt(&ok)) return -1;
    else if(sho->text().toInt(&ok) == parts[4].toInt(&ok))parts[7]="W";
    else if(sho->text().toInt(&ok) < parts[4].toInt(&ok))parts[7]="O";
    parts[6]=sho->text();
    lines.erase(lines.begin()+pos);
    vector<QString>::iterator Position = lines.begin() + pos;
    QString insert = parts[0] + buffer + parts[1] + buffer + parts[2] + buffer + parts[3] + buffer + parts[4] + buffer + parts[5] + buffer + parts[6] + buffer + parts[7];
    lines.insert(Position, insert);
    f->open(QFile::WriteOnly | QFile::Text);
    QTextStream inwrite(f);
    for (const QString& outputLine : lines)
    {
        inwrite << outputLine << "\n";
    }
    f->close();
    return 1;
}

void functions::insertTrie(TrieNode* root, const string& word)
{
    TrieNode* node = root;
    for (char ch : word) {
        if (!node->children.count(tolower(ch))) {
            node->children[tolower(ch)] = new TrieNode();
        }
        node = node->children[tolower(ch)];
    }
    node->isEndOfWord = true;

    node->ori=word;
}
bool functions::searchTrie(TrieNode* root, const string& word)
{
    TrieNode* node = root;
    for (char ch : word) {
        if (!node->children.count(tolower(ch))) {
            return false;
        }
        node = node->children[tolower(ch)];
    }
    return node != nullptr && node->isEndOfWord;
}
void functions::getSuggestions(TrieNode* root, const string& prefix, vector<string>& suggestions)
{
    TrieNode* node = root;
    string currentPrefix = "";
    for (char ch : prefix) {
        if (!node->children.count(tolower(ch))) {
            return;
        }
        node = node->children[tolower(ch)];
        currentPrefix += tolower(ch);
    }

    queue<pair<TrieNode*, string>> q;
    q.push({node, currentPrefix});

    while (!q.empty()) {
        TrieNode* currentNode = q.front().first;
        string currentWord = q.front().second;
        q.pop();

        if (currentNode->isEndOfWord) {
            //suggestions.push_back(currentWord);

            //storing the original form in suggestion vector
            suggestions.push_back(currentNode->ori);
        }

        for (const auto& child : currentNode->children) {
            q.push({child.second, currentWord + child.first});
        }
    }
}

void functions::searchperformer(string val, TrieNode *root,QListWidget *sho)
{
    sho->clear();
    f->open(QFile::ReadOnly | QFile::Text);
    QTextStream inread(f);
    QString line;
    while (!inread.atEnd())
    {
        line=inread.readLine();
        if(line=="---MOVIES---" || line=="---TVSHOW---" || line=="---BOOKS---" || line.isEmpty())
            continue;
        QStringList part=line.split("^");
        //QString word;
        //int i=0;
       // while (i<part.size())
        //{
            insertTrie(root, part[1].toStdString());
            //i++;
        //}
    }
    f->close();
        vector<string> suggestions;
        getSuggestions(root, val, suggestions);

        if (!suggestions.empty()) {
            //cout << "Suggestions:" << endl;
            for (const string& suggestion : suggestions) {
                sho->addItem(QString::fromStdString(suggestion) );
            }
        }
}

QString functions::mov_counter()
{
    f->open(QFile::ReadOnly | QFile::Text);
    QString line;
    int cou=0;
    QTextStream inread(f);
    vector<QString> lines;
        int i=0,pos1=0,pos2=0;
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
               // pos3 = i;
        }
        f->close();
        for(int i=pos1;i<pos2 - 2;i++)
        {
            QStringList part=lines[i].split("^");
            if(part[5]=="W")cou++;
        }
        return QString::number(cou);
}

QString functions::boo_counter()
{
        f->open(QFile::ReadOnly | QFile::Text);
        QString line;
        int cou=0;
        QTextStream inread(f);
        vector<QString> lines;
        int i=0,pos3=0;
        while(!inread.atEnd())
        {
            line=inread.readLine();
            lines.push_back(line);
            i++;
            //if(line == "---MOVIES---")
            // pos1 = i;
            //if(line == "---TVSHOW---")
             //pos2 = i;
            if(line == "---BOOKS---")
             pos3 = i;
        }
        f->close();
        for(unsigned long long i=pos3;i<lines.size();i++)
        {
            QStringList part=lines[i].split("^");
            if(part[8]=="W")cou++;
        }
        return QString::number(cou);
}

QString functions::tv_counter()
{
        f->open(QFile::ReadOnly | QFile::Text);
        QString line;
        int cou=0;
        QTextStream inread(f);
        vector<QString> lines;
        int i=0,pos2=0,pos3=0;
        while(!inread.atEnd())
        {
            line=inread.readLine();
            lines.push_back(line);
            i++;
           // if(line == "---MOVIES---")
             //pos1 = i;
            if(line == "---TVSHOW---")
             pos2 = i;
            if(line == "---BOOKS---")
             pos3 = i;
        }
        f->close();
        for(int i=pos2;i<pos3-2;i++)
        {
            QStringList part=lines[i].split("^");
            if(part[7]=="W")cou++;
        }
        return QString::number(cou);
}

void functions::type_finder(QString q,MainForm *h)
{
        f->open(QFile::ReadOnly | QFile::Text);
        QString line;
        QTextStream inread(f);
        vector<QString> lines;
        int i=0,pos2=0,pos3=0;
        while(!inread.atEnd())
        {
            line=inread.readLine();
            lines.push_back(line);
            i++;
             //if(line == "---MOVIES---")
           // pos1 = i;
            if(line == "---TVSHOW---")
             pos2 = i;
            if(line == "---BOOKS---")
             pos3 = i;
        }
        f->close();
        for(int i=0;i<lines.size();i++)
        {
            if(lines[i]!="---MOVIES---" && lines[i]!="---TVSHOW---" && lines[i]!="---BOOKS---" && !lines[i].isEmpty())
            {
             QStringList parts = lines[i].split("^");
             if(parts[1]==q)
             {
                 if(i<pos2)
                 {
                     QString stat;
                     if(parts[5]=="D")stat="Dropped";
                     else if(parts[5]=="W")stat="Watched";
                     else if(parts[5]=="P")stat="Planned";
                     else if(parts[5]=="O")stat="Ongoing";
                     else stat="Not watched";
                     QMessageBox::information(h,"info","Title: "+parts[1]+"\n"+"Genre: "+parts[2]+"\n"+"Year: "+parts[3]+"\n"+"Runtime: "+parts[4]+"\n"+"Status: "+stat);
                 }
                  else if(i>pos2 && i<pos3)
                 {
                     QString stat;
                     if(parts[7]=="D")stat="Dropped";
                     else if(parts[7]=="W")stat="Watched";
                     else if(parts[7]=="P")stat="Planned";
                     else if(parts[7]=="O")stat="Ongoing";
                     else stat="Not watched";
                     QMessageBox::information(h,"info","Title: "+parts[1]+"\n"+"Genre: "+parts[2]+"\n"+"Year: "+parts[3]+"\n"+"Total episodes: "+parts[4]+"\n"+"Runtime: "+parts[5]+"\n"+"Watched episodes: "+parts[6]+"\n"+"Status: "+stat);
                 }
                 else if(i>pos3)
                 {
                     QString stat;
                     if(parts[8]=="D")stat="Dropped";
                     else if(parts[8]=="W")stat="Watched";
                     else if(parts[8]=="P")stat="Planned";
                     else if(parts[8]=="O")stat="Ongoing";
                     else stat="Not watched";
                     QMessageBox::information(h,"info","Title: "+parts[1]+"\n"+"Genre: "+parts[2]+"\n"+"Year: "+parts[3]+"\n"+"Chapters: "+parts[4]+"\n"+"Total pages: "+parts[5]+"\n"+"Current pages: "+parts[6]+"\n"+"Author: "+parts[7]+"\n"+"Status: "+stat);
                 }
            }
        }
        }
}

void functions::type_finder(QString q,recommender *h)
{
        f->open(QFile::ReadOnly | QFile::Text);
        QString line;
        QTextStream inread(f);
        vector<QString> lines;
        int i=0,pos2=0,pos3=0;
        while(!inread.atEnd())
        {
        line=inread.readLine();
        lines.push_back(line);
        i++;
            //if(line == "---MOVIES---")
        // pos1 = i;
        if(line == "---TVSHOW---")
            pos2 = i;
        if(line == "---BOOKS---")
            pos3 = i;
        }
        f->close();
        for(int i=0;i<lines.size();i++)
        {
        if(lines[i]!="---MOVIES---" && lines[i]!="---TVSHOW---" && lines[i]!="---BOOKS---" && !lines[i].isEmpty())
        {
            QStringList parts = lines[i].split("^");
            if(parts[1]==q)
            {
                 if(i<pos2)
                 {
                     QString stat;
                     if(parts[5]=="D")stat="Dropped";
                     else if(parts[5]=="W")stat="Watched";
                     else if(parts[5]=="P")stat="Planned";
                     else if(parts[5]=="O")stat="Ongoing";
                     else stat="Not watched";
                     QMessageBox::information(h,"info","Title: "+parts[1]+"\n"+"Genre: "+parts[2]+"\n"+"Year: "+parts[3]+"\n"+"Runtime: "+parts[4]+"\n"+"Status :"+stat);
                 }
                 else if(i>pos2 && i<pos3)
                 {
                     QString stat;
                     if(parts[7]=="D")stat="Dropped";
                     else if(parts[7]=="W")stat="Watched";
                     else if(parts[7]=="P")stat="Planned";
                     else if(parts[7]=="O")stat="Ongoing";
                     else stat="Not watched";
                     QMessageBox::information(h,"info","Title: "+parts[1]+"\n"+"Genre: "+parts[2]+"\n"+"Year: "+parts[3]+"\n"+"Total episodes: "+parts[4]+"\n"+"Runtime :"+parts[5]+"\n"+"Watched episodes: "+parts[6]+"\n"+"Status: "+stat);
                 }
                 else if(i>pos3)
                 {
                     QString stat;
                     if(parts[8]=="D")stat="Dropped";
                     else if(parts[8]=="W")stat="Watched";
                     else if(parts[8]=="P")stat="Planned";
                     else if(parts[8]=="O")stat="Ongoing";
                     else stat="Not watched";
                     QMessageBox::information(h,"info","Title: "+parts[1]+"\n"+"Genre: "+parts[2]+"\n"+"Year: "+parts[3]+"\n"+"Chapters: "+parts[4]+"\n"+"Total pages :"+parts[5]+"\n"+"Current pages: "+parts[6]+"\n"+"Author: "+parts[7]+"\n"+"Status: "+stat);
                 }
            }
        }
        }
}
