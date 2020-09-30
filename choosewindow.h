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
    * \param[in] parent
    */
    ChooseWindow(QWidget *parent = nullptr);
    ~ChooseWindow();
public slots:
    /*!
    * \brief Metoda odpowiedzialna za przesłanie wiadmości za pomocą MQTT.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    */
    void publish_message(const QString &topic,const QByteArray &msg);
    /*!
    * \brief Metoda odpowiedzialna za przesłanie wiadmości za pomocą MQTT z możliwością ustawienia przetrzymania wiadomości.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    * \param[in] qos - jakość serwisu (quality of service).
    * \param[in] retain - czy wiadmość ma być przetrzymana przez server (broker).
    */
    void publish_message_retain(const QString &topic,const QByteArray &msg,quint8 qos = 0,bool retain = false);
private slots:
    void connection_handler(QMqttClient::ClientState state);
    /*!
    * \brief Metoda otwierająca okno kurnika.
    */
    void on_chickencoop_button_clicked();
    /*!
    * \brief Metoda otwierająca okno pogody.
    */
    void on_weather_button_clicked();
    /*!
    * \brief Metoda otwierająca okno nawadniania.
    */
    void on_water_button_clicked();
    /*!
    * \brief Metoda otwierająca główne okno.
    */
    void show_window();
    /*!
    * \brief Metoda ustawiająca subskrypcje dla wszytkich klas.
    */
    void set_subscription();
    /*!
    * \brief Metoda obsługująca odebrane wiadomości.
    */
    void message_handler(QByteArray message,  QMqttTopicName topic);
    /*!
    * \brief Metoda otwierająca okno z opcjami MQTT.
    */
    void on_action_optionsMQTT_2_triggered();
    /*!
    * \brief Metoda otwierająca okno z opcjami pogody.
    */
    void on_action_options_weather_triggered();
    /*!
    * \brief Metoda otwierająca okno z informacjami o autorze i licencji ikon.
    */
    void on_action_about_author_triggered();
    /*!
    * \brief Metoda pozwalająca zmienić język interfejsu na język angielski.
    */
    void on_action_English_triggered();
    /*!
    * \brief Metoda pozwalająca zmienić język interfejsu na język polski.
    */
    void on_action_Polish_triggered();
    /*!
    * \brief Metoda ustawiająca opcje związane z klientem MQTT.
    */
    void set_Mqtt();
signals:

private:
    Ui::ChooseWindow *ui;
    /*!
    * \brief Wskaźnik na okno kurnika.
    */
    Chickencoop *chickencoop_window;
    /*!
    * \brief Wskaźnik na okno pogody.
    */
    Weather *weather_window;
    /*!
    * \brief Wskaźnik na okno nawadniania.
    */
    Watering *watering_window;
    /*!
    * \brief Wskaźnik na okno opcji MQTT.
    */
    SettingsMQTT *mqtt_settings_window;
    /*!
    * \brief Wskaźnik na okno opcji pogody.
    */
    SettingsWeather *weather_settings_window;
    /*!
    * \brief Wskaźnik na okno informacji o autorze.
    */
    Author *about_author_window;
    /*!
    * \brief Wskaźnik na klienta MQTT.
    */
    QMqttClient *m_client;
    /*!
    * \brief Metoda ustawiająca wszystkie ikony.
    */
    void set_icons();
    /*!
    * \brief Tablica przechowująca subskrybowane tematy związane z kurnikiem.
    */
    const std::array<QString,3> sub_topics_chickencoop = {"chickencoop/temperature","chickencoop/humidity","chickencoop/doors/status"};
    /*!
    * \brief Tablica przechowująca subskrybowane tematy związane z nawadnianiem.
    */
    const std::array<QString,7> sub_topics_watering = {"garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                                        , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday"};
};
#endif // CHOOSEWINDOW_H
