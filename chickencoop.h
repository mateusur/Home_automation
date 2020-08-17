#ifndef CHICKENCOOP_H
#define CHICKENCOOP_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Chickencoop;
}

class Chickencoop : public QDialog
{
    Q_OBJECT

public:
    explicit Chickencoop(QWidget *parent = nullptr);
    ~Chickencoop();

private slots:
    void on_return_button_clicked();
    void on_up_button_clicked();

    void on_down_button_clicked();

signals:
    void change_window();
    void publish_msg(QString topic, QByteArray msg);
private:
    Ui::Chickencoop *ui;
    void set_icons();

};

#endif // CHICKENCOOP_H
