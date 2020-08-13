#ifndef CHICKENCOOP_H
#define CHICKENCOOP_H

#include <QDialog>

namespace Ui {
class Chickencoop;
}

class Chickencoop : public QDialog
{
    Q_OBJECT

public:
    explicit Chickencoop(QWidget *parent = nullptr);
    ~Chickencoop();

private:
    Ui::Chickencoop *ui;
};

#endif // CHICKENCOOP_H
