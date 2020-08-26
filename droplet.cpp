#include "droplet.h"

Droplet::Droplet(QLabel *label) : QLabel(label)
{
    //qDebug() << "Nowy obiekt";
    int pos = qrand()%800;
    int ypos = qrand()%500 - 500;
    int timess = 0.048*(-ypos)*1000;
    //int velocity = 10000+timess/(500-ypos);
    //qDebug() <<ypos << " " << 500 << " " << timess<< "Time: " << 10000+timess << "distance: " << 500-ypos << "velocity: " << velocity;
    droplet_icon.load(":/Icons/Watering/icons8-water-30.png");
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(droplet_icon);
    animation = new QPropertyAnimation(label,"geometry");
    animation->setDuration(10000+ timess);
    animation->setStartValue(QRect(pos, ypos, 100, 30));
    animation->setEndValue(QRect(pos, 500, 100, 30));
    //connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));
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
