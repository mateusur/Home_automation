#include "settingsweather.h"
#include "ui_settingsweather.h"

SettingsWeather::SettingsWeather(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWeather)
{
    ui->setupUi(this);
    settings = new QSettings("PrivateApp", "Home_automation",this);
    QString latitude  = settings->value("latitude", "").toString();
    QString longitude = settings->value("longitude", "").toString();
    ui->lineEdit_latitude->setText(latitude);
    ui->lineEdit_longitude->setText(longitude);
}

SettingsWeather::~SettingsWeather()
{
    delete ui;
}

void SettingsWeather::on_pushButton_save_clicked()
{
    QString latitude  = ui->lineEdit_latitude->text();
    QString longitude = ui->lineEdit_longitude->text();
    settings->setValue("latitude", latitude);
    settings->setValue("longitude", longitude);
    emit on_data_changed();
    this->hide();
}
