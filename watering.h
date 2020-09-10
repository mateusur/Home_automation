#ifndef WATERING_H
#define WATERING_H

#include <QDialog>
#include "droplet.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QMqttClient>

namespace Ui {
class Watering;
}

class Watering : public QDialog
{
    Q_OBJECT

public:
    explicit Watering(QWidget *parent = nullptr);
    ~Watering();
public slots:
    void message_handler(QByteArray message,  QMqttTopicName topic);
private slots:
    void on_return_button_clicked();
    void on_radioButton_once_clicked();
    void on_pushButton_accept_clicked();
    void updateCountdown();
    void on_pushButton_turn_off_clicked();

signals:
    void change_window();
    void publish_msg(const QString &topic,const QByteArray &msg);
    void publish_message_retain(const QString &topic,const QByteArray &msg,quint8 qos = 0,bool retain = false);
private:
    Ui::Watering *ui;
    static const int drop_count = 20;
    QLabel *labels[drop_count];
    Droplet *droplets[drop_count];
    const QString topics_watering[8] = { "garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday", "garden/watering/solenoid" };
    QTimer *timer;
    QTimer *timer2;
    QTime countdown;
    const unsigned short cooldown_time = 15;

};

#endif // WATERING_H
