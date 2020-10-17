#include "settingsstream.h"
#include "ui_settingsstream.h"

SettingsStream::SettingsStream(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsStream)
{
    ui->setupUi(this);
    settings = new QSettings("PrivateApp", "Home_automation",this);
    QString stream_ip  = settings->value("stream_ip", "").toString();
    QString stream_port = settings->value("stream_port", "").toString();
    QString format = settings->value("format","").toString();
    if(format=="")
        format="h264";
    ui->comboBox_format->setCurrentText(format);

    ui->lineEdit_ip->setText(stream_ip);
    ui->lineEdit_port->setText(stream_port);

    QRegExp ip("([1-9]\\d{0,2}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
    QRegExpValidator *validator = new QRegExpValidator(ip, this);
    ui->lineEdit_ip->setValidator(validator);

    QRegExp port("([1-9]\\d?\\d?\\d?\\d?)");
    QRegExpValidator *validator2 = new QRegExpValidator(port, this);
    ui->lineEdit_port->setValidator(validator2);
}

SettingsStream::~SettingsStream()
{
    delete ui;
}

void SettingsStream::on_pushButton_save_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setStyleSheet("QPushButton{ width:125; font-size: 18px; }");
    msgBox.setWindowTitle(tr("Kurnik"));
    QString stream_ip  = ui->lineEdit_ip->text();
    QString stream_port = ui->lineEdit_port->text();

    if(stream_ip =="" || stream_port =="")
        msgBox.setText(tr("Wszystkie pola muszą być uzupełnione."));
    else{
        msgBox.setText(tr("Zmiany zostaną wprowadzone po restarcie aplikacji."));
        settings->setValue("stream_ip", stream_ip);
        settings->setValue("stream_port", stream_port);
        settings->setValue("format",ui->comboBox_format->currentText());
        this->hide();
    }
    msgBox.exec();
}
