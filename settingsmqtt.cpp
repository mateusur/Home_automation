#include "settingsmqtt.h"
#include "ui_settingsmqtt.h"

SettingsMQTT::SettingsMQTT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsMQTT)
{
    ui->setupUi(this);
    settings = new QSettings("PrivateApp", "Home_automation",this);
    QString ssid = settings->value("server", "").toString();
    QString password = settings->value("port", "").toString();
    ui->lineEdit_ssid->setText(ssid);
    ui->lineEdit_password->setText(password);
}

SettingsMQTT::~SettingsMQTT()
{
    delete ui;
}

void SettingsMQTT::on_pushButton_save_clicked()
{
    QString ssid = ui->lineEdit_ssid->text();
    int password = ui->lineEdit_password->text().toUInt();
    settings->setValue("server", ssid);
    settings->setValue("port", password);
    emit on_data_changed();
    this->hide();
}


