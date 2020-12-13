#ifndef CHICKENCOOP_H
#define CHICKENCOOP_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMqttClient>
namespace Ui {
class Chickencoop;
}

class Chickencoop : public QDialog
{
    Q_OBJECT

public:
    /*!
    * \brief Konstruktor klasy Chickencoop.
    *
    * Konstruktor klasy Chickencoop.
    * \param[in] parent
    */
    explicit Chickencoop(QWidget *parent = nullptr);
    ~Chickencoop();

private slots:
    /*!
    * \brief Metoda odpowiedzialna za powrót do okna głównego.
    *
    * Metoda odpowiedzialna za powrót do okna głównego.
    */
    void on_return_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za podniesienie drzwi kurnika.
    *
    * Metoda odpowiedzialna za podniesienie drzwi kurnika.
    */
    void on_up_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za opuszczenie drzwi kurnika.
    *
    * Metoda odpowiedzialna za opuszczenie drzwi kurnika.
    */
    void on_down_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za zaktualizowanie zmiany IP oraz portu z którego jest nadawny stream.
    *
    * Metoda odpowiedzialna za zaktualizowanie zmiany IP oraz portu z którego jest nadawny stream uv4l.
    */
public slots:
    /*!
    * \brief Metoda odpowiedzialna za dezaktywacje odpowiedniego przycisku.
    *
    * Metoda odpowiedzialna za dezaktywacje przycisku podnoszącego drzwi jeśli drzwi są już podniesione oraz analogicznie dezaktywująca
    * przycisk opuszczania jeśli drzwi są opuszczone.
    */
    void disable_button(const QByteArray& message,const QMqttTopicName& topic);

signals:
    /*!
    * \brief Sygnał odpowiedzialny za przełączanie między oknem głównym a oknem Chickencoop.
    *
    * Sygnał odpowiedzialny za przełączanie między oknem głównym a oknem Chickencoop.
    */
    void change_window();
    /*!
    * \brief Sygnał odpowiedzialny za wysyłanie wiadomości przez MQTT.
    *
    * Sygnał odpowiedzialny za wysyłanie wiadomości przez MQTT.
    * \param[in] pub_topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    */
    void publish_msg(const QString &pub_topic,const QByteArray &msg);
private:
    Ui::Chickencoop *ui;
    /*!
    * \brief Metoda ustawiająca ikony strzałek na poszczególne przyciski.
    *
    * Metoda ustawiająca ikony strzałek na poszczególne przyciski.
    */
    void set_icons();
    /*!
    * \brief Temat do którego są publikowane wiadomości związane z drzwiami kurnika.
    *
    * Temat do którego są publikowane wiadomości związane z drzwiczkami kurnika.
    */
    const QString pub_topic = "chickencoop/door";
    /*!
    * \brief Wskaźnik na player do streamu.
    *
    * Wskaźnik na player wymagany do odtwarzania streamu.
    */
    QMediaPlayer *player;
    /*!
    * \brief Wskaźnik na Video Widget potrzebny do odtworzenia streamu.
    *
    * Wskaźnik na Video Widget potrzebny do odtworzenia streamu.
    */
    QVideoWidget *videoWidget;
    /*!
    * \brief Wskaźnik na ustawienia z których pobierane jest IP oraz port stremu.
    *
    * Wskaźnik na ustawienia dzięki, którym jest możliwość zapisywania oraz odczytywania raz wprowadzonego IP serwera oraz portu.
    */
    QSettings *settings;
    /*!
    * \brief Link do streamu.
    *
    * Link do streamu (testowane na uv4l działającym na Raspberry Pi).
    */
    QUrl link;

};

#endif // CHICKENCOOP_H
