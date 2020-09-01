#ifndef WATERING_H
#define WATERING_H

#include <QDialog>
#include "droplet.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QTime>

namespace Ui {
class Watering;
}

class Watering : public QDialog
{
    Q_OBJECT

public:
    explicit Watering(QWidget *parent = nullptr);
    ~Watering();

private slots:
    void on_return_button_clicked();
    void on_radioButton_once_clicked();
    void on_pushButton_accept_clicked();
    void updateCountdown();


signals:
    void change_window();
    void publish_msg(const QString &topic,const QByteArray &msg);

private:
    Ui::Watering *ui;
    static const int drop_count = 15;
    QLabel *labels[drop_count];
    Droplet *droplets[drop_count];
    const QString topic = "garden/watering/solenoid";
    QTimer *timer;
    QTimer *timer2;
    QTime countdown;

};

#endif // WATERING_H
