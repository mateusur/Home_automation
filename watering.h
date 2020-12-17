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
    /*!
    * \brief Konstruktor klasy Watering.
    *
    * Konstruktor klasy Watering.
    * \param[in] parent
    */
    explicit Watering(QWidget *parent = nullptr);
    ~Watering();
public slots:
    /*!
    * \brief Metoda odpowiedzialna za obsługę odebranych wiadomości.
    *
    * Metoda odpowiedzialna za obsługę odebranych wiadomości - ustawia etykiete odpowiedniego dnia na godzine i czas nawadniania.
    * Brak etykiety danego dnia oznacza brak nawadniania tego dnia.
    * \param[in] message -  wiadomość jaka została opublikowana.
    * \param[in] topic - temat do, którego wiadomość została opublikowana.
    */
    void message_handler(const QByteArray& message, const QMqttTopicName& topic);
private slots:
    /*!
    * \brief Metoda odpowiedzialna za powrót do głównego okna.
    *
    * Metoda odpowiedzialna za powrót do głównego okna.
    */
    void on_return_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za jednorazowe nawodnienie.
    *
    * Metoda odpowiedzialna za jednorazowe nawodnienie - pozwala użytkownikowi natychmiast włączyć nawadnianie na określoną ilość czasu.
    */
    void on_radioButton_once_clicked();
    /*!
    * \brief Metoda odpowiedzialna za opublikowanie wiadomości.
    *
    * Metoda odpowiedzialna za zaakceptowanie wybranych przez użytkownika opcji i przesłanie ich do serwera.
    */
    void on_pushButton_accept_clicked();
    /*!
    * \brief Metoda odpowiedzialna za odświeżenie timera.
    *
    * Metoda odpowiedzialna za odświeżenie timera. Timer informuje o pozostałym czasie nawadniania
    * (gdy zostało wybrane nawadnianie jednorazowe) oraz o pozostałym czasie schładzania wymaganym przez elektrozawór.
    */
    void updateCountdown();
    /*!
    * \brief Metoda odpowiedzialna wyłączenie nawadniania.
    *
    * Metoda odpowiedzialna wyłączenie nawadniania w wybranym dniu.
    */
    void on_pushButton_turn_off_clicked();

    void on_checkBox_mode_stateChanged(int arg1);

    void on_pushButton_edit_clicked();

signals:
    /*!
    * \brief Sygnał odpowiedzialny za zmianę okna.
    *
    * Sygnał odpowiedzialny za zmianę okna - ukrywa okno nawadniania i pokazuje okno ChooseWindow \ref ChooseWindow .
    */
    void change_window();
    /*!
    * \brief Sygnał odpowiedzialny za wysłanie wiadomości przez MQTT.
    *
    * Metoda wykorzystująca klienta MQTT do przesłania odpowiedniej wiadomości do odpowiedniego tematu.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    */
    void publish_msg(const QString &topic,const QByteArray &msg);
    /*!
    * \brief Sygnał odpowiedzialny za wysłanie wiadomości przez MQTT z opcją przetrzymania wiadomości.
    *
    * Metoda wykorzystująca klienta MQTT do przesłania odpowiedniej wiadomości do odpowiedniego tematu. Ponadto pozwala
    * ustawić jakość serwisu oraz czy wiadomość powinna być przetrzymana przez serwer.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    * \param[in] qos - jakość serwisu (quality of service).
    * \param[in] retain - czy wiadmość ma być przetrzymana przez server (broker).
    */
    void publish_message_retain(const QString &topic,const QByteArray &msg,quint8 qos = 0,bool retain = false);
private:
    Ui::Watering *ui;
    /*!
    * \brief Liczba kropel, które chcemy animować.
    *
    * Liczba kropel, które chcemy animować.
    */
    static const int drop_count = 20;
    /*!
    * \brief Tablica etykiet do animacji kropel.
    *
    * Tablica etykiet do animacji kropel.
    */
    QLabel *labels[drop_count];
    /*!
    * \brief Tablica kropli.
    *
    * Tablica kropli.
    */
    Droplet *droplets[drop_count];
    /*!
    * \brief Tablica tematów do których jest wysyłane są wiadomości.
    *
    * Tablica tematów do których jest wysyłane są wiadomości związane z nawadnianiem.
    */
    const QString topics_watering[8] = { "garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday", "garden/watering/solenoid" };
    //TODO: Zakomentowac ponizsze tematy
    const QString topics_soil_sensor[2] = {"garden/watering/soil/level","garden/watering/soil/mode"};
    /*!
    * \brief Timer odświeżający wyświetlany minutnik.
    *
    * Timer odświeżający wyświetlany minutnik informujący o pozostałym czasie nawadniania/schładznia.
    */
    QTimer *timer;
    /*!
    * \brief Timer do odświeżający minutnik ochładzania.
    *
    * Timer do odświeżający minutnik ochładzania.
    */
    QTimer *timer2; //NOTE Sa dwa poniewaz musze wiedziec, ktory wyslal informacje (slot itd)
    /*!
    * \brief Minutnik do wyświetlania pozostałego czasu nawadniania/schładzania.
    *
    * Minutnik do wyświetlania pozostałego czasu nawadniania/schładzania.
    */
    QTime countdown;
    /*!
    * \brief Czas schładzania elektrozaworu.
    *
    * Czas schładzania elektrozaworu.
    */
    const unsigned short cooldown_time = 1;

};

#endif // WATERING_H
