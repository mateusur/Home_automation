#ifndef WATERING_H
#define WATERING_H

#include <QDialog>
#include "droplet.h"
#include <QDebug>
namespace Ui {
class Watering;
}

class Watering : public QDialog
{
    Q_OBJECT

public:
    explicit Watering(QWidget *parent = nullptr);
    ~Watering();

private slots:
    void on_return_button_clicked();
signals:
    void change_window();

private:
    Ui::Watering *ui;
    static const int drop_count = 15;
    QLabel *labels[drop_count];
    Droplet *droplets[drop_count];
};

#endif // WATERING_H
