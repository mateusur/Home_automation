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
    * \param[in] parent
    */
    explicit SettingsWeather(QWidget *parent = nullptr);
    ~SettingsWeather();

private slots:
    /*!
    * \brief Metoda odpowiadająca za zapis danych.
    */
    void on_pushButton_save_clicked();
signals:
    /*!
    * \brief Sygnał zmiany danych.
    */
    void data_changed();
private:
    Ui::SettingsWeather *ui;
    /*!
    * \brief Wskaźnik na klase ustawień.
    */
    QSettings *settings;
};

#endif // SETTINGSWEATHER_H
