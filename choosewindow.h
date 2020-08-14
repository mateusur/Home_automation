#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>

#include "chickencoop.h"

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

private slots:
    void show_window();
    void publish_message(QString topic, QByteArray msg);
    void on_chickencoop_button_clicked();
    void set_subscription();
    void message_handler(QByteArray message,  QMqttTopicName topic);
    void on_buttonSubscribe_clicked();

private:
    Ui::ChooseWindow *ui;
    Chickencoop *chickencoop_window;
    QMqttClient *m_client;

    void set_icons();

};
#endif // CHOOSEWINDOW_H
