#include "choosewindow.h"
#include "ui_choosewindow.h"

ChooseWindow::ChooseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);
    chickencoop_window = new Chickencoop(this);
    weather_window = new Weather(this);
    watering_window = new Watering(this);
    connect(chickencoop_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    connect(weather_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    connect(watering_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    set_icons();

    //MQTT
    //connect(chickencoop_window,SIGNAL(publish_message(QString, QByteArray)),
    //        this,SLOT(publish_message(QString, QByteArray))); // Send "UP", "DOWN" from chickencoop window
    //connect(watering_window,SIGNAL(publish_message(QString &, QByteArray &)),
    //        this,SLOT(publish_message(QString, QByteArray))); // Send minutes from watering window
    //connect(watering_window,&Watering::publish_msg(QString, QByteArray),this,&ChooseWindow::publish_message(QString, QByteArray));
    m_client = new QMqttClient(this);
    m_client->setHostname("192.168.1.8");
    m_client->setPort(1883);
    m_client->setClientId("Qt_app");
    m_client->connectToHost();

    connect(m_client,SIGNAL(messageReceived( QByteArray,  QMqttTopicName)),this,SLOT(message_handler(QByteArray,  QMqttTopicName)));
    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
           const QString content = QDateTime::currentDateTime().toString()
                       + QLatin1String(" Received Topic: ")
                       + topic.name()
                       + QLatin1String(" Message: ")
                       + message
                       + QLatin1Char('\n');
           ui->editLog->insertPlainText(content);
       });
    QTimer::singleShot(5000, this, &ChooseWindow::set_subscription);

    connect(chickencoop_window,&Chickencoop::publish_msg,this, &ChooseWindow::publish_message);
    connect(watering_window,&Watering::publish_msg,this, &ChooseWindow::publish_message);
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

void ChooseWindow::publish_message(const QString &topic,const QByteArray &msg)
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
    qDebug() << "Otwarto okno chickencoop";

}

void ChooseWindow::message_handler(QByteArray message,  QMqttTopicName topic)
{
    const QMqttTopicName temp("chickencoop/temperature");
    const QMqttTopicName hum("chickencoop/humidity");
    const QMqttTopicName doors("chickencoop/doors/status");
    const QString doors_opened("opened");
    const QString doors_closed("closed");
    int w = ui->label_hum->width();
    int h = ui->label_hum->height();
    const QPixmap pixmap_doors_opened(":/Icons/open_door_96.png");
    const QPixmap pixmap_doors_closed(":/Icons/door_closed_96.png");
    ui->label_doors->setPixmap(pixmap_doors_opened.scaled(w,h,Qt::KeepAspectRatioByExpanding));

   qDebug() <<"Odebralem info";
   qDebug() << message;
   qDebug() << topic;
   if(topic == temp)
       ui->lineEdit_temp->setText(message);
   else if (topic == hum) {
       ui->lineEdit_hum->setText(message);
   }
   else if (topic == doors) {
       if(message == doors_opened){
            ui->label_doors->setPixmap(pixmap_doors_opened.scaled(w,h,Qt::KeepAspectRatioByExpanding));
       }
       else if(message == doors_closed){
            ui->label_doors->setPixmap(pixmap_doors_closed.scaled(w,h,Qt::KeepAspectRatioByExpanding));
       }
   }
}

void ChooseWindow::set_icons()
{
    QPixmap pixmap_chicken(":/Icons/chicken_100.png");
    QIcon ButtonIcon_chicken(pixmap_chicken);
    ui->chickencoop_button->setIcon(ButtonIcon_chicken);
    ui->chickencoop_button->setIconSize(pixmap_chicken.rect().size());

    QPixmap pixmap_garden(":/Icons/irrigation_96.png");
    QIcon ButtonIcon_garden(pixmap_garden);
    ui->water_button->setIcon(ButtonIcon_garden);
    ui->water_button->setIconSize(pixmap_garden.rect().size());

    QPixmap pixmap_weather(":/Icons/cloud_96.png");
    QIcon ButtonIcon_weather(pixmap_weather);
    ui->weather_button->setIcon(ButtonIcon_weather);
    ui->weather_button->setIconSize(pixmap_weather.rect().size());

    QPixmap pixmap_lights(":/Icons/automation_96.png");
    QIcon ButtonIcon_lights(pixmap_lights);
    ui->lights_button->setIcon(ButtonIcon_lights);
    ui->lights_button->setIconSize(pixmap_lights.rect().size());

    int w = ui->label_hum->width();
    int h = ui->label_hum->height();
    QPixmap pixmap_thermometer(":/Icons/thermometer_64.png");
    QPixmap pixmap_humidity(":/Icons/humidity_80.png");
    ui->label_temp->setPixmap(pixmap_thermometer.scaled(w,h,Qt::KeepAspectRatioByExpanding));
    ui->label_hum->setPixmap(pixmap_humidity.scaled(w,h,Qt::KeepAspectRatioByExpanding));
    ui->label_temp_2->setText(" °C");
    ui->label_hum_2->setText(" %");
}

void ChooseWindow::set_subscription()
{
    const QString temp("chickencoop/temperature");
    const QString hum("chickencoop/humidity");
    const QString doors("chickencoop/doors/status");
    m_client->subscribe(temp);
    m_client->subscribe(hum);
    m_client->subscribe(doors);

}

void ChooseWindow::on_buttonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    qDebug() << subscription->state();
}

void ChooseWindow::on_weather_button_clicked()
{
    weather_window->show();
    this->hide();
    qDebug() << "Otwarto okno weather";
}

void ChooseWindow::on_water_button_clicked()
{
    watering_window->show();
    this->hide();
    qDebug() << "Otwarto okno watering";
}
