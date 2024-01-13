#ifndef DISPLAYER_H
#define DISPLAYER_H
#include "mainform.h"
#include <QWidget>

namespace Ui {
class displayer;
}

class displayer : public QWidget
{
    Q_OBJECT

public:
    explicit displayer(QWidget *parent = nullptr);
    ~displayer();
    void setmf(MainForm *m){mf=m;}
    MainForm *getmf(){return mf;}
    void inspector();
    class noinspect{};
private slots:
    void on_detcheck_clicked();

    void on_return_button_clicked();

    void on_arranger_currentIndexChanged(int index);

    void on_bookreturn_clicked();

    void on_showreturn_clicked();

    void on_movreturn_clicked();

private:
    Ui::displayer *ui;
    MainForm *mf;
};

#endif // DISPLAYER_H
