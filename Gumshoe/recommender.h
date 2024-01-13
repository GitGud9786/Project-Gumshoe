#ifndef RECOMMENDER_H
#define RECOMMENDER_H
#include "mainform.h"
#include <QWidget>
#include "QLineEdit"
#include "mainclasses.h"
namespace Ui {
class recommender;
}

class recommender : public QWidget
{
    Q_OBJECT

public:
    explicit recommender(QWidget *parent = nullptr);
    ~recommender();
    void setmf(MainForm* m){M=m;}
    MainForm* getmf(){return M;}
    void tooadd();

    class nocheck{};
    class noselect{};
    class shouldbenumbers{};
    class shouldbeinteger{};
private slots:
    void on_recbox_currentIndexChanged(int index);

    void on_reccreturn_clicked();

    void on_addmovrecbutton_clicked();

    void on_reccinspect_clicked();

private:
    Ui::recommender *ui;
    MainForm *M;
};

#endif // RECOMMENDER_H
