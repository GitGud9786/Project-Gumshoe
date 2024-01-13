#ifndef CHANGEUSR_H
#define CHANGEUSR_H

#include <QWidget>
#include "mainform.h"
namespace Ui {
class changeusr;
}

class changeusr : public QWidget
{
    Q_OBJECT

public:
    explicit changeusr(QWidget *parent = nullptr);
    ~changeusr();
    void getform(MainForm *m)
    {
        u=m;
    }
    MainForm* uform()
    {
        return u;
    }

private slots:
    void on_updatebutton_clicked();

private:
    Ui::changeusr *ui;
    MainForm *u;
};

#endif // CHANGEUSR_H
