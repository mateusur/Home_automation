#include "chickencoop.h"
#include "ui_chickencoop.h"

Chickencoop::Chickencoop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chickencoop)
{
    ui->setupUi(this);
    //connect(ui->pushButton,SIGNAL(on_pushButton_clicked()),)
    set_icons();

    player= new QMediaPlayer(this);
    videoWidget= new QVideoWidget(ui->widget);
    player->setVideoOutput(videoWidget);
    videoWidget->setGeometry(-20,-40,640,480);
    videoWidget->show();

    settings = new QSettings("PrivateApp", "Home_automation",this);
    QString stream_ip  = settings->value("stream_ip", "").toString();
    QString stream_port = settings->value("stream_port", "").toString();
    QString format = settings->value("format","").toString();
    if(format=="")
        format="h264";
    ui->comboBox_format->setCurrentText(format);
    link = "http://"+stream_ip+":"+stream_port+"/stream/video."+format;
    ui->lineEdit_ip->setText(stream_ip);
    ui->lineEdit_port->setText(stream_port);
    player->setMedia(link);
    player->play();
    QRegExp ip("([1-9]\\d{0,2}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
    QRegExpValidator *validator = new QRegExpValidator(ip, this);
    ui->lineEdit_ip->setValidator(validator);

    QRegExp port("([1-9]\\d?\\d?\\d?\\d?)");
    QRegExpValidator *validator2 = new QRegExpValidator(port, this);
    ui->lineEdit_port->setValidator(validator2);
}

Chickencoop::~Chickencoop()
{
    qDebug() << "Destruktor chickencoop window";
    delete ui;
}

void Chickencoop::on_return_button_clicked()
{
  this->hide();
    emit change_window();
}

void Chickencoop::set_icons()
{
    QPixmap pixmap_return(":/Icons/left_48.png");
    QIcon ButtonIcon_return(pixmap_return);
    ui->return_button->setIcon(ButtonIcon_return);
    ui->return_button->setIconSize(pixmap_return.rect().size());

    QPixmap pixmap_up(":/Icons/thick_arrow_pointing_up_96.png");
    QIcon ButtonIcon_up(pixmap_up);
    ui->up_button->setIcon(ButtonIcon_up);
    ui->up_button->setIconSize(pixmap_up.rect().size());

    QPixmap pixmap_down(":/Icons/thick_arrow_pointing_down_96.png");
    QIcon ButtonIcon_down(pixmap_down);
    ui->down_button->setIcon(ButtonIcon_down);
    ui->down_button->setIconSize(pixmap_down.rect().size());
}

void Chickencoop::on_up_button_clicked()
{
    //const QMqttTopicName topic(QString::fromLatin1("chickencoop/door"));
    const QByteArray msg = "UP";
    emit publish_msg(pub_topic,msg);
}

void Chickencoop::on_down_button_clicked()
{
    //const QMqttTopicName topic(QString::fromLatin1("chickencoop/door"));
    const QByteArray msg = "DOWN";
    emit publish_msg(pub_topic,msg);
}

void Chickencoop::on_pushButton_stream_clicked()
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
    }
    msgBox.exec();
}
