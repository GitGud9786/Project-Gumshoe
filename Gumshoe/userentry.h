#ifndef USERENTRY_H
#define USERENTRY_H

#include <QWidget>

namespace Ui {
class userentry;
}

class userentry : public QWidget
{
    Q_OBJECT

public:
    explicit userentry(QWidget *parent = nullptr);
    ~userentry();

private slots:
    void on_signbutton_clicked();

    void on_logbutton_clicked();

private:
    Ui::userentry *ui;
};

#endif // USERENTRY_H
