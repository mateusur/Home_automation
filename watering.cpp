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

void Watering::on_radioButton_once_clicked()
{
    if(ui->radioButton_once->isChecked()){
        ui->checkBox_monday->setEnabled(false);
        ui->checkBox_tuesday->setEnabled(false);
        ui->checkBox_wednesday->setEnabled(false);
        ui->checkBox_thursday->setEnabled(false);
        ui->checkBox_friday->setEnabled(false);
        ui->checkBox_saturday->setEnabled(false);
        ui->checkBox_sunday->setEnabled(false);
    }
    else{
        ui->checkBox_monday->setEnabled(true);
        ui->checkBox_tuesday->setEnabled(true);
        ui->checkBox_wednesday->setEnabled(true);
        ui->checkBox_thursday->setEnabled(true);
        ui->checkBox_friday->setEnabled(true);
        ui->checkBox_saturday->setEnabled(true);
        ui->checkBox_sunday->setEnabled(true);
    }

}

void Watering::on_pushButton_accept_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setText("Musisz zaznaczyc regularność nawadniania.");

    if(ui->radioButton_once->isChecked() || ui->checkBox_monday->isChecked() || ui->checkBox_tuesday->isChecked() || ui->checkBox_wednesday->isChecked()
            || ui->checkBox_thursday->isChecked() || ui->checkBox_friday->isChecked() || ui->checkBox_saturday->isChecked() || ui->checkBox_sunday->isChecked()){
    qDebug() << ui->doubleSpinBox_interval->value();
    double minutes = ui->doubleSpinBox_interval->value();
    QByteArray array(reinterpret_cast<const char*>(&minutes), sizeof(minutes));
    emit publish_msg(topic,array);

    }else
        msgBox.exec();
}
