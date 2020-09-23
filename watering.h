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
    * \param[in] parent
    */
    explicit Watering(QWidget *parent = nullptr);
    ~Watering();
public slots:
    /*!
    * \brief Metoda odpowiedzialna za obsługę odebranych wiadomości.
    * \param[in] message -  wiadomość jaka została opublikowana.
    * \param[in] topic - temat do, którego wiadomość została opublikowana.
    */
    void message_handler(QByteArray message,  QMqttTopicName topic);
private slots:
    /*!
    * \brief Metoda odpowiedzialna za powrót do głównego okna.
    */
    void on_return_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za jednorazowe nawodnienie.
    */
    void on_radioButton_once_clicked();
    /*!
    * \brief Metoda odpowiedzialna za opublikowanie wiadomości.
    */
    void on_pushButton_accept_clicked();
    /*!
    * \brief Metoda odpowiedzialna za odświeżenie timera.
    */
    void updateCountdown();
    /*!
    * \brief Metoda odpowiedzialna wyłączenie nawadniania.
    */
    void on_pushButton_turn_off_clicked();

signals:
    /*!
    * \brief Sygnał odpowiedzialny za zmianę okna.
    */
    void change_window();
    /*!
    * \brief Sygnał odpowiedzialny za wysłanie wiadomości przez MQTT.
    * \param[in] topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    */
    void publish_msg(const QString &topic,const QByteArray &msg);
    /*!
    * \brief Sygnał odpowiedzialny za wysłanie wiadomości przez MQTT z opcją przetrzymania wiadomości.
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
    */
    static const int drop_count = 20;
    /*!
    * \brief Tablica etykiet do animacji kropel.
    */
    QLabel *labels[drop_count];
    /*!
    * \brief Tablica kropli.
    */
    Droplet *droplets[drop_count];
    /*!
    * \brief Tablica tematów do których jest wysyłane są wiadomości.
    */
    const QString topics_watering[8] = { "garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday", "garden/watering/solenoid" };
    /*!
    * \brief Timer odświeżający minutnik.
    */
    QTimer *timer;
    /*!
    * \brief Timer do odświeżający minutnik ochładzania.
    */
    QTimer *timer2; // Sa dwa poniewaz musze wiedziec, ktory wyslal informacje (slot itd)
    /*!
    * \brief Minutnik do wyświetlania pozostałego czasu nawadniania/ochładzania.
    */
    QTime countdown;
    /*!
    * \brief Czas schładzania elektrozaworu.
    */
    const unsigned short cooldown_time = 15;

};

#endif // WATERING_H
