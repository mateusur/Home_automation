#ifndef CHICKENCOOP_H
#define CHICKENCOOP_H

#include <QDialog>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
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
    void publish_msg(const QString &pub_topic,const QByteArray &msg);
private:
    Ui::Chickencoop *ui;
    void set_icons();
    const QString pub_topic = "chickencoop/door";
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    const QUrl link = QUrl("http://0.0.0.0:8080/stream/video.h264");
};

#endif // CHICKENCOOP_H
