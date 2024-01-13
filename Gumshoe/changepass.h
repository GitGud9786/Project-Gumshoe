#ifndef CHANGEPASS_H
#define CHANGEPASS_H

#include <QWidget>
#include "mainform.h"
namespace Ui {
class changepass;
}

class changepass : public QWidget
{
    Q_OBJECT

public:
    explicit changepass(QWidget *parent = nullptr);
    ~changepass();
    void getform(MainForm *M)
    {
        m=M;
    }
    MainForm* cform()
    {
        return m;
    }

private slots:
    void on_updatebutton_clicked();

private:
    Ui::changepass *ui;
    MainForm *m;
};

#endif // CHANGEPASS_H
