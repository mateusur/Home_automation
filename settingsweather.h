#ifndef SETTINGSWEATHER_H
#define SETTINGSWEATHER_H

#include <QDialog>
#include <QSettings>
#include <QRegExpValidator>
#include <QRegExp>
namespace Ui {
class SettingsWeather;
}

class SettingsWeather : public QDialog
{
    Q_OBJECT

public:
    /*!
    * \brief Konstruktor klasy SettingsWeather.
    *
    * Konstruktor klasy SettingsWeather odpowiedzialnej za zmiane ustawień położenia oraz klucza API.
    * \param[in] parent
    */
    explicit SettingsWeather(QWidget *parent = nullptr);
    ~SettingsWeather();

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
    Ui::SettingsWeather *ui;
    /*!
    * \brief Wskaźnik na klase ustawień.
    *
    * Wskaźnik na klase ustawień.
    */
    QSettings *settings;
};

#endif // SETTINGSWEATHER_H
