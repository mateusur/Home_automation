#ifndef WEATHER_H
#define WEATHER_H

#include <QDialog>

#include <QJsonDocument>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include <QtNetwork>


namespace Ui {
class Weather;
}

class Weather : public QDialog
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
//    double Temperatura() const;
//    double TemperaturaOdczuwalna() const;
//    double TemperaturaMax() const;
//    double TemperaturaMin() const;
//    double PredkoscWiatru() const;
//    unsigned int Wilgotnosc() const;
//    unsigned int Cisnienie() const;
//    unsigned int KatWiatru() const;
//    QTime CzasWschod() const;
//    QTime CzasZachod() const;
//    QString NazwaMiasta() const;
//    QString OpisPogody() const;
//    QString IkonaPogody(uint8_t flag) const;
//    QString Wyswietl();
private slots:
    void managerFinished(QNetworkReply *reply);
    void on_return_button_clicked();

private:
    Ui::Weather *ui;
    QNetworkAccessManager *manager;
    double feels_like;
    unsigned int humidity;
    unsigned int pressure;
    double temp;
    double temp_max;
    double temp_min;
//    QTime sunrise;
//    QTime sunset;
//    unsigned int deg;
//    double speed;
//    QString name;
//    QString description;
//    QString icon;

    QVector<double> v_feels_like;
    QVector<double> v_rain;
    QVector<int> v_pressure;
    QVector<double> v_temp;
    QVector<QString> v_descrption;
    QVector<QString> v_icon;
signals:
    void daneZmienione(QJsonDocument dane);
    void change_window();
};

#endif // WEATHER_H
