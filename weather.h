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
    *
    * Konstruktor klasy Weather.
    * \param[in] parent
    */
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
public slots:
    /*!
    * \brief Metoda pobierająca dane pogodowe z serwera.
    *
    * Metoda pobierająca dane pogodowe z serwera wywoływana przy uruchomieniu programu, zmianie miejscowości oraz kliknięciu przycisku odświeżania.
    */
    void data_changed();
private slots:
    /*!
    * \brief Metoda przewarzająca otrzymane informacje.
    *
    * Metoda umieszczająca otrzymane dane z serwera w odpowiednich kontenerach.
    * \param[in] reply - wskaźnik na odpowiedź serwera.
    */
    void managerFinished(QNetworkReply *reply);
    /*!
    * \brief Metoda powodująca powrót do głównego okna.
    *
    * Metoda odpowiedzialna za powrót do głównego okna.
    */
    void on_return_button_clicked();
    /*!
    * \brief Metoda odświeżająca pogodę.
    *
    * Metoda odświeżająca pogodę poprzez wysłanie żądania do serwera o nowe dane.
    */
    void on_pushButton_refresh_clicked();

private:
    Ui::Weather *ui;
    /*!
    * \brief Manager dostępu do sieci.
    *
    * Manager dostępu do sieci.
    */
    QNetworkAccessManager *manager;
    /*!
    * \brief Żądanie potrzebne managerowi.
    *
    * Żądanie potrzebne managerowi.
    */
    QNetworkRequest request;
    /*!
    * \brief Tablica odczuwalnych temperatur.
    *
    * Tablica odczuwalnych temperatur.
    */
    QVector<double> v_feels_like;
    /*!
    * \brief Tablica opadów deszczu.
    *
    * Tablica opadów deszczu.
    */
    QVector<double> v_rain;
    /*!
    * \brief Tablica ciścień.
    *
    * Tablica ciścień.
    */
    QVector<int> v_pressure;
    /*!
    * \brief Tablica temperatur.
    *
    * Tablica temperatur.
    */
    QVector<double> v_temp;
    /*!
    * \brief Tablica opisów pogody na dany dzień.
    *
    * Tablica opisów pogody na dany dzień.
    */
    QVector<QString> v_description;
    /*!
    * \brief Tablica ikon.
    *
    * Tablica ikon.
    */
    QVector<QString> v_icon;
    /*!
    * \brief Tablica dat.
    *
    * Tablica dat.
    */
    QVector<QString> v_time;
    /*!
    * \brief Tablica dni tygodnia.
    *
    * Tablica dni tygodnia.
    */
    QVector<QString> v_time_days;
    /*!
    * \brief Tablica zachmurzeń.
    *
    * Tablica zachmurzeń.
    */
    QVector<int> v_clouds;
    /*!
    * \brief Metoda ustawiająca ikone na etykietę.
    *
    * Metoda ustawiająca ikone na etykietę.
    * \param[in] label - etykieta.
    * \param[in] icon - nazwa ikony.
    */
    void set_icon(QLabel *label,const QString& icon);
    /*!
    * \brief Metoda ustawiająca temperature na etykietę.
    *
    * Metoda ustawiająca temperature na etykietę.
    * \param[in] label - etykieta.
    * \param[in] temp - temperatura.
    */
    void set_temp(QLabel *label,const double& temp);
    /*!
    * \brief Metoda ustawiająca temperature odczuwalną na etykietę.
    *
    * Metoda ustawiająca temperature odczuwalną na etykietę.
    * \param[in] label - etykieta.
    * \param[in] feels_like - temperatura odczuwalna.
    */
    void set_feels(QLabel *label, const double& feels_like);
    /*!
    * \brief Metoda ustawiająca opady na etykietę.
    *
    * Metoda ustawiająca opady na etykietę.
    * \param[in] label - etykieta.
    * \param[in] rain - wartość opadów.
    */
    void set_rain(QLabel *label, const double& rain);
    /*!
    * \brief Metoda ustawiająca zachmurzenie na etykietę.
    *
    * Metoda ustawiająca zachmurzenie na etykietę.
    * \param[in] label - etykieta.
    * \param[in] cloudines - wartość zachmurzenia.
    */
    void set_clouds(QLabel *label,const int& cloudines);
    /*!
    * \brief Metoda ustawiająca wartość ciśnienia na etykietę.
    *
    * Metoda ustawiająca wartość ciśnienia na etykietę.
    * \param[in] label - etykieta.
    * \param[in] pressure - wartość ciśnienia.
    */
    void set_pressure(QLabel *label,const int& pressure);
    /*!
    * \brief Metoda ustawiająca opis pogody na etykietę.
    *
    * Metoda ustawiająca opis pogody na etykietę.
    * \param[in] label - etykieta.
    * \param[in] description - opis pogody.
    */
    void set_description(QLabel *label,const QString& description);
    /*!
    * \brief Metoda ustawiająca datę na etykietę.
    *
    * Metoda ustawiająca datę na etykietę.
    * \param[in] label - etykieta.
    * \param[in] time - data.
    */
    void set_time(QLabel *label,const QString& time);
    /*!
    * \brief Metoda ustawiająca opisy i ikony.
    *
    * Metoda ustawiająca opisy i ikony na wszystkie dni przy użyciu odpowiednich metod.
    */
    void set_all_icons();
    /*!
    * \brief Metoda tłumacząca na język angielski nazwę dnia.
    *
    * Metoda tłumacząca na język angielski nazwę dnia. Używana w przypadku gdy wybrany język interfejsu to język angielski.
    */
    void translate_day(QString &day);


signals:
    /*!
    * \brief Sygnał informujący, że dane zostały zmienione.
    *
    * Sygnał informujący, że dane zostały zmienione.
    */
    void daneZmienione(QJsonDocument dane);
    /*!
     * \brief Sygnał informujący o tym, że należy zmienić okno.
     *
     * Sygnał informujący o tym, że należy zmienić okno.
     */
    void change_window();
};

#endif // WEATHER_H
