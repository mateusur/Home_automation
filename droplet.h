#ifndef DROPLET_H
#define DROPLET_H
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPropertyAnimation>

class Droplet : public QLabel
{
    Q_OBJECT
public:
    Droplet(QLabel *label);
    ~Droplet();
    void pause();
    void resume();
private:
    QPixmap droplet_icon;
    QPropertyAnimation *animation;
};

#endif // DROPLET_H
