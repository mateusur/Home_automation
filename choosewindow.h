#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>

#include "chickencoop.h"
#include "weather.h"
#include "watering.h"
#include <QMqttClient>
#include <QMqttSubscription>
#include <QThread>
#include <QTimer>
#include <QString>
//::fromlatin1

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
private slots:
    void show_window();

    void on_chickencoop_button_clicked();
    void set_subscription();
    void message_handler(QByteArray message,  QMqttTopicName topic);
    void on_buttonSubscribe_clicked();

    void on_weather_button_clicked();

    void on_water_button_clicked();

private:
    Ui::ChooseWindow *ui;
    Chickencoop *chickencoop_window;
    QMqttClient *m_client;

    void set_icons();
    Weather *weather_window;
    Watering *watering_window;

};
#endif // CHOOSEWINDOW_H
