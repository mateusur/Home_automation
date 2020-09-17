#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>

#include "chickencoop.h"
#include "weather.h"
#include "watering.h"
#include "settingsmqtt.h"
#include "author.h"
#include <QMqttClient>
#include <QMqttSubscription>
#include <QThread>
#include <QTimer>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class ChooseWindow; }
QT_END_NAMESPACE

class ChooseWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChooseWindow(QWidget *parent = nullptr);
    ~ChooseWindow();
public slots:
    void publish_message(const QString &topic,const QByteArray &msg);
    void publish_message_retain(const QString &topic,const QByteArray &msg,quint8 qos = 0,bool retain = false);
private slots:
    void on_chickencoop_button_clicked();
    void on_weather_button_clicked();
    void on_water_button_clicked();
    void show_window();
    void set_subscription();
    void message_handler(QByteArray message,  QMqttTopicName topic);
    void on_action_optionsMQTT_2_triggered();
    void on_action_about_author_triggered();
    void set_Mqtt();
signals:

private:
    Ui::ChooseWindow *ui;
    Chickencoop *chickencoop_window;
    Weather *weather_window;
    Watering *watering_window;
    SettingsMQTT *mqtt_settings_window;
    Author *about_author_window;
    QMqttClient *m_client;
//    QString server_ip;
//    int port;
    void set_icons();

    const std::array<QString,3> sub_topics_chickencoop = {"chickencoop/temperature","chickencoop/humidity","chickencoop/doors/status"};
    const std::array<QString,7> sub_topics_watering = {"garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                                        , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday"};
};
#endif // CHOOSEWINDOW_H
