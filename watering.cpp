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
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateCountdown()));


}

Watering::~Watering()
{
    qDebug() << "Destruktor garden window";

    for(auto i=0; i<drop_count; i++){
        delete droplets[i];
    }
    delete ui;
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
    //QByteArray array(reinterpret_cast<const char*>(&minutes), sizeof(minutes));
    QByteArray ba = QByteArray::number(minutes, 'f', 0);
    emit publish_msg(topic,ba);

    timer->start(1000);
    countdown.setHMS(0,minutes,0);
    ui->pushButton_accept->setEnabled(false);
    }else
        msgBox.exec();
}



void Watering::updateCountdown()
{
    if(QObject::sender() == timer){
    countdown = countdown.addSecs(-1);
    ui->label_3->setText("Pozostały czas nawadniania:");
    ui->label_countdown->setText( countdown.toString("mm:ss"));
    if(countdown <= QTime(0,0,0,0)){
      timer->stop();
      ui->label_countdown->setText("-- --");
      countdown.setHMS(0,15,0);
      timer2->start(1000);
        }
    }

    else{
        countdown = countdown.addSecs(-1);
        ui->label_3->setText("Pozostały czas schładzania:");
        ui->label_countdown->setText( countdown.toString("mm:ss"));
        if(countdown <= QTime(0,0,0,0)){
          timer2->stop();
          ui->label_countdown->setText("-- --");
          ui->pushButton_accept->setEnabled(true);
        }
    }


}
