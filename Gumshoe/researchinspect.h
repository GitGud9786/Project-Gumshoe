#ifndef RESEARCHINSPECT_H
#define RESEARCHINSPECT_H
#include "QLabel"
#include "QStackedWidget"
#include <QWidget>

namespace Ui {
class researchinspect;
}

class researchinspect : public QWidget
{
    Q_OBJECT

public:
    explicit researchinspect(QWidget *parent = nullptr);
    ~researchinspect();
    QLabel *movtitle,*movgenre,*movyear,*movtime,*movstatus;//movie
    QLabel *tvtitle,*tvgenre,*tvyear,*tvtime,*tvstatus,*tvtotep,*tvcurrep;//tvshow
    QLabel *booktitle,*bookgenre,*bookyear,*bookchap,*bookstatus,*booktopg,*bookcurrpg,*bookauthor;//books
    QStackedWidget *s;


private:
    Ui::researchinspect *ui;
};

#endif // RESEARCHINSPECT_H
