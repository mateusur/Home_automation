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
#include "settingsweather.h"
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
    /*!
    * \brief Konstruktor klasy ChooseWindow.
    *
    * Konstruktor klasy ChooseWindow.
    * \param[in] parent
    */
    ChooseWindow(QWidget *parent = nullptr);
    ~ChooseWindow();
public slots:
    /*!
    * \brief Metoda odpowiedzialna za przesłanie wiadmości za pomocą MQTT.
    *
    * Metoda wykorzystująca klienta MQTT do przesłania odpowiedniej wiadomości do odpowiedniego tematu.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    */
    void publish_message(const QString &topic,const QByteArray &msg);
    /*!
    * \brief Metoda odpowiedzialna za przesłanie wiadmości za pomocą MQTT z możliwością ustawienia przetrzymania wiadomości.
    *
    * Metoda wykorzystująca klienta MQTT do przesłania odpowiedniej wiadomości do odpowiedniego tematu. Ponadto pozwala
    * ustawić jakość serwisu oraz czy wiadomość powinna być przetrzymana przez serwer.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    * \param[in] qos - jakość serwisu (quality of service).
    * \param[in] retain - czy wiadmość ma być przetrzymana przez server (broker).
    */
    void publish_message_retain(const QString &topic,const QByteArray &msg,quint8 qos = 0,bool retain = false);
private slots:
    /*!
    * \brief Metoda wywołująca ponowne łącznie z serwerem lub zasubskrybowanie tematów.
    *
    * Metoda wywołująca ponowne łącznie z serwerem jeśli status klienta MQTT zwrócił błąd połączenia z serwerem lub metode \ref set_subscription
    *  odpowiadającą za zasubskrybowanie odpowiednich tematów jeśli nastąpiło poprawne połączenie z serwerem.
    */
    void connection_handler(QMqttClient::ClientState state);
    /*!
    * \brief Metoda otwierająca okno kurnika.
    *
    * Metoda otwierająca okno kurnika.
    */
    void on_chickencoop_button_clicked();
    /*!
    * \brief Metoda otwierająca okno pogody.
    *
    * Metoda otwierająca okno pogody.
    */
    void on_weather_button_clicked();
    /*!
    * \brief Metoda otwierająca okno nawadniania.
    *
    * Metoda otwierająca okno nawadniania.
    */
    void on_water_button_clicked();
    /*!
    * \brief Metoda otwierająca główne okno.
    *
    * Metoda otwierająca główne okno.
    */
    void show_window();
    /*!
    * \brief Metoda ustawiająca subskrypcje dla wszytkich klas.
    *
    * Metoda ustawiająca subskrypcje tematów (\ref sub_topics_chickencoop, \ref sub_topics_watering) dla wszytkich klas.
    */
    void set_subscription();
    /*!
    * \brief Metoda obsługująca odebrane wiadomości.
    *
    * Metoda obsługująca odebrane wiadomości - ustawiająca odebraną temperature, wilgotność oraz status drzwi (otwarte/zamknięte).
    */
    void message_handler(QByteArray message,  QMqttTopicName topic);
    /*!
    * \brief Metoda otwierająca okno z opcjami serwera MQTT.
    *
    * Metoda otwierająca okno z opcjami serwera MQTT.
    */
    void on_action_optionsMQTT_2_triggered();
    /*!
    * \brief Metoda otwierająca okno z opcjami pogody.
    *
    * Metoda otwierająca okno z opcjami pogody.
    */
    void on_action_options_weather_triggered();
    /*!
    * \brief Metoda otwierająca okno z informacjami o autorze i licencji ikon.
    *
    * Metoda otwierająca okno z informacjami o autorze i licencji ikon.
    */
    void on_action_about_author_triggered();
    /*!
    * \brief Metoda pozwalająca zmienić język interfejsu na język angielski.
    *
    * Metoda pozwalająca zmienić język interfejsu na język angielski.
    */
    void on_action_English_triggered();
    /*!
    * \brief Metoda pozwalająca zmienić język interfejsu na język polski.
    *
    * Metoda pozwalająca zmienić język interfejsu na język polski.
    */
    void on_action_Polish_triggered();
    /*!
    * \brief Metoda konfigurjąca klienta MQTT.
    *
    * Metoda konfigurująca klienta MQTT oraz nawiązująca połączenie z serwerem.
    */
    void set_Mqtt();
signals:

private:
    Ui::ChooseWindow *ui;
    /*!
    * \brief Wskaźnik na okno kurnika.
    *
    * Wskaźnik na okno kurnika.
    */
    Chickencoop *chickencoop_window;
    /*!
    * \brief Wskaźnik na okno pogody.
    *
    * Wskaźnik na okno pogody.
    */
    Weather *weather_window;
    /*!
    * \brief Wskaźnik na okno nawadniania.
    *
    * Wskaźnik na okno nawadniania.
    */
    Watering *watering_window;
    /*!
    * \brief Wskaźnik na okno opcji MQTT.
    *
    * Wskaźnik na okno opcji MQTT.
    */
    SettingsMQTT *mqtt_settings_window;
    /*!
    * \brief Wskaźnik na okno opcji pogody.
    *
    * Wskaźnik na okno opcji pogody.
    */
    SettingsWeather *weather_settings_window;
    /*!
    * \brief Wskaźnik na okno informacji o autorze.
    *
    * Wskaźnik na okno informacji o autorze.
    */
    Author *about_author_window;
    /*!
    * \brief Wskaźnik na klienta MQTT.
    *
    * Wskaźnik na klienta MQTT.
    */
    QMqttClient *m_client;
    /*!
    * \brief Metoda ustawiająca wszystkie ikony.
    *
    * Metoda ustawiająca wszystkie ikony w oknie ChooseWindow.
    */
    void set_icons();
    /*!
    * \brief Tablica przechowująca subskrybowane tematy związane z kurnikiem.
    *
    * Tablica przechowująca subskrybowane tematy związane z kurnikiem.
    */
    const std::array<QString,3> sub_topics_chickencoop = {"chickencoop/temperature","chickencoop/humidity","chickencoop/doors/status"};
    /*!
    * \brief Tablica przechowująca subskrybowane tematy związane z nawadnianiem.
    *
    * Tablica przechowująca subskrybowane tematy związane z nawadnianiem.
    */
    const std::array<QString,7> sub_topics_watering = {"garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                                        , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday"};
};
#endif // CHOOSEWINDOW_H
