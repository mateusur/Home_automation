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
    player->setMedia(link);
    player->play();
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

