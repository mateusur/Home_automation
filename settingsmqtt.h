#ifndef SETTINGSMQTT_H
#define SETTINGSMQTT_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <QRegExpValidator>
#include <QRegExp>

namespace Ui {
class SettingsMQTT;
}

class SettingsMQTT : public QDialog
{
    Q_OBJECT

public:
    /*!
    * \brief Konstruktor klasy SettingsMQTT.
    *
    * Konstruktor klasy SettingsMQTT odpowiedzialnej za zmiane ustawień IP serwera, portu oraz danych logowania użytkownika.
    * \param[in] parent
    */
    explicit SettingsMQTT(QWidget *parent = nullptr);
    ~SettingsMQTT();

private slots:
    /*!
    * \brief Metoda odpowiadająca za zapis danych.
    *
    * Metoda pobierająca dane z formularzy wypełnionych przez użytkownika i zapisująca je do pliku z ustawieniami.
    */
    void on_pushButton_save_clicked();
signals:
    /*!
    * \brief Sygnał zmiany danych.
    *
    * Sygnał zmiany danych, informujący, że należy nawiązać nowe połączenie z zaktualizowanymi ustawieniami.
    */
    void data_changed();
private:
    Ui::SettingsMQTT *ui;
    /*!
    * \brief Wskaźnik na klase ustawień.
    *
    * Wskaźnik na klase ustawień.
    */
    QSettings *settings;

};

#endif // SETTINGSMQTT_H
