#include "settingsmqtt.h"
#include "ui_settingsmqtt.h"

SettingsMQTT::SettingsMQTT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsMQTT)
{
    ui->setupUi(this);
    settings = new QSettings("PrivateApp", "Home_automation",this);
    QString server = settings->value("server", "").toString();
    QString port = settings->value("port", "").toString();
    QString ssid = settings->value("ssid", "").toString();
    QString password = settings->value("password", "").toString();
    ui->lineEdit_IP->setText(server);
    ui->lineEdit_port->setText(port);
    ui->lineEdit_ssid->setText(ssid);
    ui->lineEdit_password->setText(password);
    QRegExp ip("([1-9]\\d{0,2}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
    QRegExpValidator *validator = new QRegExpValidator(ip, this);
    ui->lineEdit_IP->setValidator(validator);

    QRegExp port_exp("([1-9]\\d?\\d?\\d?\\d?)");
    QRegExpValidator *validator2 = new QRegExpValidator(port_exp, this);
    ui->lineEdit_port->setValidator(validator2);

    ui->lineEdit_ssid->setPlaceholderText(tr("Opcjonalnie"));
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password->setPlaceholderText(tr("Opcjonalnie"));
}

SettingsMQTT::~SettingsMQTT()
{
    delete ui;
}

void SettingsMQTT::on_pushButton_save_clicked()
{
    QString server = ui->lineEdit_IP->text();
    int port = ui->lineEdit_port->text().toUInt();
    QString ssid = ui->lineEdit_ssid->text();
    QString password =ui->lineEdit_password->text();

    settings->setValue("server", server);
    settings->setValue("port", port);
    settings->setValue("ssid",ssid);
    settings->setValue("password",password);
    emit on_data_changed();
    this->hide();
}


