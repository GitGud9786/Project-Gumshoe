#ifndef SINGUPENTRY_H
#define SINGUPENTRY_H

#include <QWidget>

namespace Ui {
class singupentry;
}

class singupentry : public QWidget
{
    Q_OBJECT

public:
    explicit singupentry(QWidget *parent = nullptr);
    ~singupentry();

private slots:
    void on_signbutton_clicked();

    void on_logbutton_clicked();

private:
    Ui::singupentry *ui;
};

#endif // SINGUPENTRY_H
