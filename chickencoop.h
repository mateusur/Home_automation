#ifndef CHICKENCOOP_H
#define CHICKENCOOP_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
#include <QRegExpValidator>
#include <QRegExp>
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

    void on_pushButton_stream_clicked();

signals:
    void change_window();
    void publish_msg(const QString &pub_topic,const QByteArray &msg);
private:
    Ui::Chickencoop *ui;
    void set_icons();
    const QString pub_topic = "chickencoop/door";
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QSettings *settings;
    QUrl link;

};

#endif // CHICKENCOOP_H
