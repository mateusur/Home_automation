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
namespace Ui {
class Chickencoop;
}

class Chickencoop : public QDialog
{
    Q_OBJECT

public:
    /*!
    * \brief Konstruktor klasy Chickencoop.
    * \param[in] parent
    */
    explicit Chickencoop(QWidget *parent = nullptr);
    ~Chickencoop();

private slots:
    /*!
    * \brief Metoda odpowiedzialna za powrót do okna głównego.
    */
    void on_return_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za podniesienie drzwi kurnika.
    */
    void on_up_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za opuszczenie drzwi kurnika.
    */
    void on_down_button_clicked();
    /*!
    * \brief Metoda odpowiedzialna za zatwierdzenie zmiany ip oraz portu z którego jest nadawny stream.
    */
    void on_pushButton_stream_clicked();

signals:
    /*!
    * \brief Sygnał odpowiedzialny za przełączanie między oknem głównym a oknem Chickencoop.
    */
    void change_window();
    /*!
    * \brief Sygnał odpowiedzialny za wysyłanie wiadomości przez MQTT.
    * \param[in] pub_topic - temat do, którego publikujemy.
    * \param[in] msg - wiadomość jaką publikujemy.
    */
    void publish_msg(const QString &pub_topic,const QByteArray &msg);
private:
    Ui::Chickencoop *ui;
    /*!
    * \brief Metoda ustawiająca ikony strzałek na poszczególne przyciski.
    */
    void set_icons();
    /*!
    * \brief Temat do którego są publikowane wiadomości MQTT.
    */
    const QString pub_topic = "chickencoop/door";
    /*!
    * \brief Wskaźnik na player do streamu.
    */
    QMediaPlayer *player;
    /*!
    * \brief Wskaźnik na Video Widget potrzebny do odtworzenia streamu.
    */
    QVideoWidget *videoWidget;
    /*!
    * \brief Wskaźnik na ustawienia z których pobierane jest ip oraz port stremu.
    */
    QSettings *settings;
    /*!
    * \brief Link do streamu.
    */
    QUrl link;

};

#endif // CHICKENCOOP_H
