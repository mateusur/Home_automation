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

    QRegExp lat("([-]?[1-9]\\d{0,1}\\.\\d{0,6})");
    QRegExpValidator *validator = new QRegExpValidator(lat, this);
    ui->lineEdit_latitude->setValidator(validator);

    QRegExp longi("([-]{0,1}[1-9]\\d{0,2}\\.\\d{0,6})");
    QRegExpValidator *validator2 = new QRegExpValidator(longi, this);
    ui->lineEdit_longitude->setValidator(validator2);
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
