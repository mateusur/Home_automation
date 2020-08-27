#include "watering.h"
#include "ui_watering.h"

Watering::Watering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Watering)
{
    ui->setupUi(this);

    for(auto i=0; i<drop_count; i++){
        labels[i] = new QLabel(this);
    }
    for(auto i=0; i<drop_count; i++){
        droplets[i] = new Droplet(labels[i]);
    }
}

Watering::~Watering()
{
    qDebug() << "Destruktor garden window";
    delete ui;
    for(auto i=0; i<drop_count; i++){
        delete droplets[i];
    }
}

void Watering::on_return_button_clicked()
{
    this->hide();
      emit change_window();
}
