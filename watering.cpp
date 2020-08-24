#include "watering.h"
#include "ui_watering.h"

Watering::Watering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Watering)
{
    ui->setupUi(this);
}

Watering::~Watering()
{
    delete ui;
}
