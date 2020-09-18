#ifndef WEATHER_H
#define WEATHER_H

#include <QDialog>

#include <QJsonDocument>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QtNetwork>
#include <QLabel>


namespace Ui {
class Weather;
}

class Weather : public QDialog
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
public slots:
    void on_data_changed();
private slots:
    void managerFinished(QNetworkReply *reply);
    void on_return_button_clicked();
    void on_pushButton_refresh_clicked();

private:
    Ui::Weather *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QVector<double> v_feels_like;
    QVector<double> v_rain;
    QVector<int> v_pressure;
    QVector<double> v_temp;
    QVector<QString> v_description;
    QVector<QString> v_icon;
    QVector<QString> v_time;
    QVector<int> v_clouds;
    void set_icon(QLabel *label, QString icon);
    void set_temp(QLabel *label, double temp);
    void set_feels(QLabel *label, double feels_like);
    void set_rain(QLabel *label, double rain);
    void set_clouds(QLabel *label,int cloudines);
    void set_pressure(QLabel *label,int pressure);
    void set_description(QLabel *label, QString description);
    void set_time(QLabel *label, QString time);
    void set_all_icons();


signals:
    void daneZmienione(QJsonDocument dane);
    void change_window();
};

#endif // WEATHER_H
