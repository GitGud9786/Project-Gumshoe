#ifndef INSPECTWINDOW_H
#define INSPECTWINDOW_H
#include "displayer.h"
#include <QWidget>

namespace Ui {
class inspectwindow;
}

class inspectwindow : public QWidget
{
    Q_OBJECT

public:
    explicit inspectwindow(QWidget *parent = nullptr);
    ~inspectwindow();
    void setd(displayer *D){d=D;}
    displayer* getd(){return d;}
private:
    Ui::inspectwindow *ui;
    displayer *d;
};

#endif // INSPECTWINDOW_H
