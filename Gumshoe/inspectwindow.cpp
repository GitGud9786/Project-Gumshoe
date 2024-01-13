#include "inspectwindow.h"
#include "ui_inspectwindow.h"

inspectwindow::inspectwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inspectwindow)
{
    ui->setupUi(this);
}

inspectwindow::~inspectwindow()
{
    delete ui;
}
