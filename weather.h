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
    /*!
    * \brief Konstruktor klasy Weather.
    * \param[in] parent
    */
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
public slots:
    /*!
    * \brief Metoda pobierająca dane pogodowe z serwera.
    */
    void on_data_changed();
private slots:
    /*!
    * \brief Metoda przewarzająca otrzymane informacje.
    * \param[in] reply - wskaźnik na odpowiedź serwera.
    */
    void managerFinished(QNetworkReply *reply);
    /*!
    * \brief Metoda powodująca powrót do głównego okna.
    */
    void on_return_button_clicked();
    /*!
    * \brief Metoda odświeżająca pogodę.
    */
    void on_pushButton_refresh_clicked();

private:
    Ui::Weather *ui;
    /*!
    * \brief Manager dostępu do sieci.
    */
    QNetworkAccessManager *manager;
    /*!
    * \brief Żądanie potrzebne managerowi.
    */
    QNetworkRequest request;
    /*!
    * \brief Tablica odczuwalnych temperatur.
    */
    QVector<double> v_feels_like;
    /*!
    * \brief Tablica opadów deszczu.
    */
    QVector<double> v_rain;
    /*!
    * \brief Tablica ciścień.
    */
    QVector<int> v_pressure;
    /*!
    * \brief Tablica temperatur.
    */
    QVector<double> v_temp;
    /*!
    * \brief Tablica opisów.
    */
    QVector<QString> v_description;
    /*!
    * \brief Tablica ikon.
    */
    QVector<QString> v_icon;
    /*!
    * \brief Tablica dat.
    */
    QVector<QString> v_time;
    /*!
    * \brief Tablica chmur.
    */
    QVector<int> v_clouds;
    /*!
    * \brief Metoda ustawiająca ikone na etykietę.
    * \param[in] label - etykieta.
    * \param[in] icon - nazwa ikony.
    */
    void set_icon(QLabel *label, QString icon);
    /*!
    * \brief Metoda ustawiająca temperature na etykietę.
    * \param[in] label - etykieta.
    * \param[in] temp - temperatura.
    */
    void set_temp(QLabel *label, double temp);
    /*!
    * \brief Metoda ustawiająca temperature odczuwalną na etykietę.
    * \param[in] label - etykieta.
    * \param[in] feels_like - temperatura odczuwalna.
    */
    void set_feels(QLabel *label, double feels_like);
    /*!
    * \brief Metoda ustawiająca opady na etykietę.
    * \param[in] label - etykieta.
    * \param[in] rain - wartość opadów.
    */
    void set_rain(QLabel *label, double rain);
    /*!
    * \brief Metoda ustawiająca zachmurzenie na etykietę.
    * \param[in] label - etykieta.
    * \param[in] cloudines - wartość zachmurzenia.
    */
    void set_clouds(QLabel *label,int cloudines);
    /*!
    * \brief Metoda ustawiająca zachmurzenie na etykietę.
    * \param[in] label - etykieta.
    * \param[in] pressure - wartość ciśnienia.
    */
    void set_pressure(QLabel *label,int pressure);
    /*!
    * \brief Metoda ustawiająca opis pogody na etykietę.
    * \param[in] label - etykieta.
    * \param[in] description - opis pogody.
    */
    void set_description(QLabel *label, QString description);
    /*!
    * \brief Metoda ustawiająca datę na etykietę.
    * \param[in] label - etykieta.
    * \param[in] time - data.
    */
    void set_time(QLabel *label, QString time);
    /*!
    * \brief Metoda ustawiająca opisy i ikony.
    */
    void set_all_icons();


signals:
    /*!
    * \brief Sygnał .
    */
    void daneZmienione(QJsonDocument dane);

    void change_window();
};

#endif // WEATHER_H
