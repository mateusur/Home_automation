#ifndef WATERING_H
#define WATERING_H

#include <QDialog>

namespace Ui {
class Watering;
}

class Watering : public QDialog
{
    Q_OBJECT

public:
    explicit Watering(QWidget *parent = nullptr);
    ~Watering();

private:
    Ui::Watering *ui;
};

#endif // WATERING_H
