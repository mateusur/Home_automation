#ifndef SETTINGSMQTT_H
#define SETTINGSMQTT_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
namespace Ui {
class SettingsMQTT;
}

class SettingsMQTT : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsMQTT(QWidget *parent = nullptr);
    ~SettingsMQTT();

private slots:
    void on_pushButton_save_clicked();
signals:
    void on_data_changed();
private:
    Ui::SettingsMQTT *ui;

    QSettings *settings;

};

#endif // SETTINGSMQTT_H
