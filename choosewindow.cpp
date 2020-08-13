#include "choosewindow.h"
#include "ui_choosewindow.h"

ChooseWindow::ChooseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);
    chickencoop_window = new Chickencoop(this);
    connect(chickencoop_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    set_icons();

    //MQTT
    connect(chickencoop_window,SIGNAL(publish_msg(QString, QByteArray)),this,SLOT(publish_msg(QString, QByteArray)));
    m_client = new QMqttClient(this);
    //m_client->setHostname("192.168.1.8");
    //m_client->setPort(1883);
    //m_client->setClientId("Qt_app");
    //m_client->connectToHost();


}

ChooseWindow::~ChooseWindow()
{
    qDebug() << "Destruktor choose_window";
    delete ui;
}

void ChooseWindow::show_window()
{
    this->show();
}

void ChooseWindow::publish_msg(QString topic, QByteArray msg)
{
    qDebug() << topic;
    qDebug() << msg;
    const QMqttTopicName topic2(topic);
    m_client->publish(topic2,msg);
}

void ChooseWindow::on_chickencoop_button_clicked()
{
    chickencoop_window->show();
    this->hide();
    qDebug() << "Hello";

}

void ChooseWindow::set_icons()
{
    QPixmap pixmap_chicken(":/Icons/chicken_100.png");
    QIcon ButtonIcon_chicken(pixmap_chicken);
    ui->chickencoop_button->setIcon(ButtonIcon_chicken);
    ui->chickencoop_button->setIconSize(pixmap_chicken.rect().size());

    QPixmap pixmap_garden(":/Icons/irrigation_96.png");
    QIcon ButtonIcon_garden(pixmap_garden);
    ui->garden_button->setIcon(ButtonIcon_garden);
    ui->garden_button->setIconSize(pixmap_garden.rect().size());

    QPixmap pixmap_weather(":/Icons/cloud_96.png");
    QIcon ButtonIcon_weather(pixmap_weather);
    ui->weather_button->setIcon(ButtonIcon_weather);
    ui->weather_button->setIconSize(pixmap_weather.rect().size());

    QPixmap pixmap_lights(":/Icons/automation_96.png");
    QIcon ButtonIcon_lights(pixmap_lights);
    ui->lights_button->setIcon(ButtonIcon_lights);
    ui->lights_button->setIconSize(pixmap_lights.rect().size());
}
