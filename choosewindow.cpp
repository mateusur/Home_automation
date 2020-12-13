#include "choosewindow.h"
#include "ui_choosewindow.h"

//TODO:poczyscic z qDebug
ChooseWindow::ChooseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseWindow)
{

    ui->setupUi(this);

    chickencoop_window = new Chickencoop(this);
    weather_window = new Weather(this);
    watering_window = new Watering(this);
    mqtt_settings_window = new SettingsMQTT(this);
    about_author_window = new Author(this);
    weather_settings_window = new SettingsWeather(this);
    m_client = new QMqttClient(this);
    stream_settings = new SettingsStream(this);

    connect(chickencoop_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    connect(weather_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    connect(watering_window,SIGNAL(change_window()),this,SLOT(show_window())); // Connect to toggle between windows
    set_icons();
    set_Mqtt();
    connect(m_client,SIGNAL(messageReceived( QByteArray,  QMqttTopicName)),this,SLOT(message_handler(QByteArray,  QMqttTopicName)));
    connect(m_client,SIGNAL(messageReceived( QByteArray,  QMqttTopicName)),watering_window,SLOT(message_handler(QByteArray,  QMqttTopicName)));
    connect(m_client,SIGNAL(messageReceived( QByteArray,  QMqttTopicName)),chickencoop_window,SLOT(disable_button(QByteArray,  QMqttTopicName)));
    connect(m_client,&QMqttClient::stateChanged,this,&ChooseWindow::connection_handler);

    connect(chickencoop_window,&Chickencoop::publish_msg,this, &ChooseWindow::publish_message);
    connect(watering_window,&Watering::publish_msg,this, &ChooseWindow::publish_message);
    connect(watering_window,&Watering::publish_message_retain,this, &ChooseWindow::publish_message_retain);

    connect(mqtt_settings_window,&SettingsMQTT::data_changed,this,&ChooseWindow::set_Mqtt);
    connect(weather_settings_window,&SettingsWeather::data_changed,weather_window,&Weather::data_changed);

    ui->groupBox->setToolTip(tr("Temperatura, wilgotność i status otwarcia drzwi w kurniku"));
    ui->chickencoop_button->setToolTip(tr("Okno sterowania kurnikiem"));
    ui->water_button->setToolTip(tr("Okno sterowania nawodnieniem"));
    ui->weather_button->setToolTip(tr("Okno pogody"));
    ui->lights_button->setToolTip(tr("Okno sterowania oświetleniem"));
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

void ChooseWindow::publish_message_retain(const QString &topic, const QByteArray &msg, quint8 qos, bool retain)
{
    const QMqttTopicName topic2(topic);
    m_client->publish(topic2,msg,qos,retain);
}

void ChooseWindow::connection_handler(QMqttClient::ClientState state)
{
    qDebug() << "Connection Handler" << '\n';
    if(state == QMqttClient::Disconnected){
        QTimer::singleShot(5000, this, &ChooseWindow::set_Mqtt);
        qDebug() << "Disconected" << '\n';
    }else if(state == QMqttClient::Connected){
        QTimer::singleShot(1500, this, &ChooseWindow::set_subscription);
        qDebug() << "Conected" << '\n';
    }
}
void ChooseWindow::on_chickencoop_button_clicked()
{
    chickencoop_window->show();
    this->hide();
    qDebug() << "Otwarto okno chickencoop";

}

void ChooseWindow::message_handler(const QByteArray& message,const QMqttTopicName& topic)
{
    const QString doors_opened("open");
    const QString doors_closed("close");
    int w = ui->label_hum->width();
    int h = ui->label_hum->height();
    const QPixmap pixmap_doors_opened(":/Icons/open_door_96.png");
    const QPixmap pixmap_doors_closed(":/Icons/door_closed_96.png");

    qDebug() <<"Odebrana wiadomosc: "<< message << " ,topic: "<< topic;

    if(topic ==sub_topics_chickencoop[0])
        ui->lineEdit_temp->setText(message);
    else if (topic ==sub_topics_chickencoop[1]) {
        ui->lineEdit_hum->setText(message);
    }
    else if (topic ==sub_topics_chickencoop[2]) {
        if(message == doors_opened){
            ui->label_doors->setPixmap(pixmap_doors_opened.scaled(w,h,Qt::KeepAspectRatioByExpanding));
        }
        else if(message == doors_closed){
            ui->label_doors->setPixmap(pixmap_doors_closed.scaled(w,h,Qt::KeepAspectRatioByExpanding));
        }
    }
    else if(topic == sub_topics_driveway_lights){
        qDebug() << "sub_topics_driveway_lights message : " << message << endl;
        char msg = message[0]-'0';
        int mode = (int)msg;
        QPixmap pixmap_lights;
        if(mode == 1){ //mode 1 - lights on, mode 0 - lights off
            ui->lights_button->setChecked(true);
            if(ui->lights_button->isChecked()){
                pixmap_lights.load(":/Icons/light_on_80.png");
            }
        }
        else{
            ui->lights_button->setChecked(false);
            if(!ui->lights_button->isChecked()){
            pixmap_lights.load(":/Icons/light_off2_80.png");
            }
        }
        QIcon ButtonIcon_lights(pixmap_lights);
        ui->lights_button->setIcon(ButtonIcon_lights);
        ui->lights_button->setIconSize(pixmap_lights.rect().size());
        qDebug() << "Hej, zmieniles status na: " << mode << endl;
    }

    ui->lights_button->setStyleSheet("QPushButton:checked{background-color: rgb(250, 255, 205);}");
}

void ChooseWindow::on_action_optionsMQTT_2_triggered()
{
    mqtt_settings_window -> show();
}

void ChooseWindow::on_action_options_weather_triggered()
{
    weather_settings_window -> show();
}

void ChooseWindow::on_action_options_stream_triggered()
{
    stream_settings->show();
}

void ChooseWindow::on_action_about_author_triggered()
{
    about_author_window->show();
}

void ChooseWindow::on_action_English_triggered()
{
     QSettings settings("PrivateApp", "Home_automation");
     settings.setValue("Language", "English");

     QMessageBox msgBox(this);
     msgBox.setStyleSheet("QPushButton{ width:125; font-size: 18px; }");
     msgBox.setWindowTitle(tr("Inteligentny dom"));
     msgBox.setText(tr("Zmiany zostaną wprowadzone po restarcie aplikacji."));
     msgBox.exec();
}

void ChooseWindow::on_action_Polish_triggered()
{
    QSettings settings("PrivateApp", "Home_automation");
    settings.setValue("Language", "Polish");
    QMessageBox msgBox(this);
    msgBox.setStyleSheet("QPushButton{ width:125; font-size: 18px; }");
    msgBox.setWindowTitle(tr("Inteligentny dom"));
    msgBox.setText(tr("Zmiany zostaną wprowadzone po restarcie aplikacji."));
    msgBox.exec();
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

    //QPixmap pixmap_lights(":/Icons/automation_96.png");
    QPixmap pixmap_lights(":/Icons/light_off2_80.png");
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

void ChooseWindow::set_Mqtt()
{
    m_client->disconnectFromHost();
    QSettings settings("PrivateApp", "Home_automation");
    QString server_ip = settings.value("server", "").toString();
    int port = settings.value("port", "").toInt();
    QString ssid = settings.value("ssid", "").toString();
    QString password = settings.value("password", "").toString();
    m_client->setClientId("Home_automation_app");
    m_client->setHostname(server_ip);
    m_client->setPort(port);
    m_client->connectToHost();
    if(ssid !="")
        m_client->setUsername(ssid);
    if(password!="")
        m_client->setPassword(password);
}

void ChooseWindow::set_subscription()
{
    for(unsigned i=0; i < sub_topics_chickencoop.size();++i)
    { m_client->subscribe(sub_topics_chickencoop[i]);}
    for(unsigned i=0; i<sub_topics_watering.size();++i)
    {m_client->subscribe(sub_topics_watering[i]);}
    for(unsigned i =0; i< sub_topics_soil_sensor.size(); ++i)
    {m_client->subscribe(sub_topics_soil_sensor[i]);}
     m_client->subscribe(sub_topics_driveway_lights);

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


void ChooseWindow::on_lights_button_clicked()
{
    char on[] = "1";
    char off[] = "0";
    QByteArray databuf;
    if(ui->lights_button->isChecked()){
         databuf = QByteArray((char*)on, 2);
        publish_message_retain(sub_topics_driveway_lights,databuf,0,true);
    }
     else{
           databuf = QByteArray((char*)off, 2);
         publish_message_retain(sub_topics_driveway_lights,databuf,0,true);
    }
}
