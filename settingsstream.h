#ifndef SETTINGSSTREAM_H
#define SETTINGSSTREAM_H

#include <QDialog>
#include <QSettings>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>

namespace Ui {
class SettingsStream;
}

class SettingsStream : public QDialog
{
    Q_OBJECT

public:
    /*!
    * \brief Konstruktor klasy SettingsStream.
    *
    * Konstruktor klasy SettingsStream odpowiedzialnej za zmiane ustawień dotyczących streamu.
    * \param[in] parent
    */
    explicit SettingsStream(QWidget *parent = nullptr);
    ~SettingsStream();

private slots:
    /*!
    * \brief Metoda odpowiedzialna za zaktualizowanie zmiany IP oraz portu z którego jest nadawny stream.
    *
    * Metoda odpowiedzialna za zaktualizowanie zmiany IP oraz portu z którego jest nadawny stream uv4l.
    */
    void on_pushButton_save_clicked();

private:
    Ui::SettingsStream *ui;
    /*!
    * \brief Wskaźnik na ustawienia z których pobierane jest IP, port stremu oraz format.
    *
    * Wskaźnik na ustawienia dzięki, którym jest możliwość zapisywania oraz odczytywania raz wprowadzonego IP serwera,numeru portu oraz formatu.
    */
    QSettings *settings;
};

#endif // SETTINGSSTREAM_H
