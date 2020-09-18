#ifndef SETTINGSWEATHER_H
#define SETTINGSWEATHER_H

#include <QDialog>
#include <QSettings>
namespace Ui {
class SettingsWeather;
}

class SettingsWeather : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWeather(QWidget *parent = nullptr);
    ~SettingsWeather();

private slots:
    void on_pushButton_save_clicked();
signals:
    void on_data_changed();
private:
    Ui::SettingsWeather *ui;
    QSettings *settings;
};

#endif // SETTINGSWEATHER_H
