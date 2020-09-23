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
    * \param[in] parent
    */
    explicit SettingsMQTT(QWidget *parent = nullptr);
    ~SettingsMQTT();

private slots:
    /*!
    * \brief Metoda odpowiadająca za zapis danych.
    */
    void on_pushButton_save_clicked();
signals:
    /*!
    * \brief Sygnał zmiany danych.
    */
    void on_data_changed();
private:
    Ui::SettingsMQTT *ui;
    /*!
    * \brief Wskaźnik na klase ustawień.
    */
    QSettings *settings;

};

#endif // SETTINGSMQTT_H
