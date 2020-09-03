#include "droplet.h"

Droplet::Droplet(QLabel *label) : QLabel(label)
{
    int xpos = qrand()%800;
    int ypos = qrand()%800 - 800;
    int timess = 0.048*(-ypos)*1000;
    droplet_icon.load(":/Icons/Watering/icons8-water-30.png");
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(droplet_icon);
    animation = new QPropertyAnimation(label,"geometry");
    animation->setDuration(10000+ timess);
    animation->setStartValue(QRect(xpos, ypos, 100, 30));
    animation->setEndValue(QRect(xpos, 500, 100, 30));
    animation->setLoopCount(-1);
    animation->start();
}

Droplet::~Droplet()
{
    delete animation;
}

void Droplet::pause()
{
    animation->pause();
}

void Droplet::resume()
{
    animation->resume();
}
