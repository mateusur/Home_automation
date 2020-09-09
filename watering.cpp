#include "watering.h"
#include "ui_watering.h"

Watering::Watering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Watering)
{
    ui->setupUi(this);

    for(auto i=0; i<drop_count; i++){
        labels[i] = new QLabel(this);
    }
    for(auto i=0; i<drop_count; i++){
        droplets[i] = new Droplet(labels[i]);
    }
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    for(auto i=0; i<drop_count; i++){
        droplets[i]->pause();
    }
    for(auto i=0; i<drop_count; i++){
        labels[i]->hide();
    }

    QPixmap pixmap_return(":/Icons/left_48.png");
    QIcon ButtonIcon_return(pixmap_return);
    ui->return_button->setIcon(ButtonIcon_return);
    ui->return_button->setIconSize(pixmap_return.rect().size());

    ui->timeEdit->hide();

}

Watering::~Watering()
{
    qDebug() << "Destruktor garden window";

    for(auto i=0; i<drop_count; i++){
        delete droplets[i];
    }
    delete ui;
}

void Watering::message_handler(QByteArray message, QMqttTopicName topic)
{
    char msg[5] = "0000";
    for(int i=0; i<message.size(); ++i)
        msg[i]=(char)message[i];
    int op =(int)msg[0];
    int hh=(int)msg[1];
    int mm=(int)msg[2];
    int m=(int)msg[3];

    if(topic == topics_watering[0]){ //sunday
        if(op==1)
            ui->label_sunday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m) +" min");
        else
            ui->label_sunday->setText("");
    }
    else if(topic == topics_watering[1]){
        if(op==1)
            ui->label_monday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m)+" min");
        else
            ui->label_monday->setText("");
    }
    else if(topic == topics_watering[2]){
        if(op==1)
            ui->label_tuesday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m)+" min");
        else
            ui->label_tuesday->setText("");
    }
    else if(topic == topics_watering[3]){
        if(op==1)
            ui->label_wednesday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m)+" min");
        else
            ui->label_wednesday->setText("");
    }
    else if(topic == topics_watering[4]){
        if(op==1)
            ui->label_thursday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m)+" min");
        else
            ui->label_thursday->setText("");
    }
    else if(topic == topics_watering[5]){
        if(op==1)
            ui->label_friday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m)+" min");
        else
            ui->label_friday->setText("");
    }
    else if(topic == topics_watering[6]){
        if(op==1)
            ui->label_saturday->setText("Włącz o "+QString::number(hh)+":"+QString::number(mm)+"\nna " +QString::number(m)+" min");
        else
            ui->label_saturday->setText("");
    }
}

void Watering::on_return_button_clicked()
{
    this->hide();
    emit change_window();
}

void Watering::on_radioButton_once_clicked()
{
    if(ui->radioButton_once->isChecked()){
        ui->checkBox_monday->setEnabled(false);
        ui->checkBox_tuesday->setEnabled(false);
        ui->checkBox_wednesday->setEnabled(false);
        ui->checkBox_thursday->setEnabled(false);
        ui->checkBox_friday->setEnabled(false);
        ui->checkBox_saturday->setEnabled(false);
        ui->checkBox_sunday->setEnabled(false);
        ui->timeEdit->hide();
        ui->pushButton_turn_off->hide();
        ui->label_3->show();
        //ui->label_countdown->show();
        ui->label_countdown->setText("--:--");
        ui->label->setText("Włącz nawodnienie");
        ui->label_2->setText("na");
    }
    else{
        ui->checkBox_monday->setEnabled(true);
        ui->checkBox_tuesday->setEnabled(true);
        ui->checkBox_wednesday->setEnabled(true);
        ui->checkBox_thursday->setEnabled(true);
        ui->checkBox_friday->setEnabled(true);
        ui->checkBox_saturday->setEnabled(true);
        ui->checkBox_sunday->setEnabled(true);
        ui->timeEdit->show();
        ui->pushButton_turn_off->show();
        ui->label_3->hide();
        //ui->label_countdown->hide();
        ui->label_countdown->setText("");
        ui->label->setText("Włącz nawodnienie o");
        ui->label_2->setText("na");
    }

}

void Watering::on_pushButton_accept_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setText("Musisz zaznaczyc regularność nawadniania.");

    if(ui->radioButton_once->isChecked()){
        //qDebug() << ui->doubleSpinBox_interval->value();
        double minutes = ui->doubleSpinBox_interval->value();
        QByteArray databuf = QByteArray::number(minutes, 'f', 0);
        emit publish_msg(topics_watering[7],databuf);
        timer->start(1000);
        countdown.setHMS(0,minutes,0);
        ui->pushButton_accept->setEnabled(false);
        for(auto i=0; i<drop_count; i++){
            droplets[i]->resume();
        }
        for(auto i=0; i<drop_count; i++){
            labels[i]->show();
        }
        ui->radioButton_once->setEnabled(false);

    }else if( ui->checkBox_monday->isChecked() || ui->checkBox_tuesday->isChecked() || ui->checkBox_wednesday->isChecked()
              || ui->checkBox_thursday->isChecked() || ui->checkBox_friday->isChecked() || ui->checkBox_saturday->isChecked() || ui->checkBox_sunday->isChecked()){
        char op = 1;
        char hh = ui->timeEdit->time().hour();
        char mm = ui->timeEdit->time().minute();
        char tt = ui->doubleSpinBox_interval->value();
        char dd[] = "0000";
        dd[0] = op;
        dd[1] = hh;
        dd[2] = mm;
        dd[3] = tt;

        QByteArray databuf;
        databuf = QByteArray((char*)dd, 4);
        if(ui->checkBox_sunday->isChecked())
            emit publish_msg(topics_watering[0],databuf);
        if(ui->checkBox_monday->isChecked())
            emit publish_msg(topics_watering[1],databuf);
        if(ui->checkBox_tuesday->isChecked())
            emit publish_msg(topics_watering[2],databuf);
        if(ui->checkBox_wednesday->isChecked())
            emit publish_msg(topics_watering[3],databuf);
        if(ui->checkBox_thursday->isChecked())
            emit publish_msg(topics_watering[4],databuf);
        if(ui->checkBox_friday->isChecked())
            emit publish_msg(topics_watering[5],databuf);
        if(ui->checkBox_saturday->isChecked())
            emit publish_msg(topics_watering[6],databuf);
    }
    else
        msgBox.exec();
}



void Watering::updateCountdown()
{
    if(QObject::sender() == timer){
        countdown = countdown.addSecs(-1);
        ui->label_3->setText("Pozostały czas nawadniania:");
        ui->label_countdown->setText( countdown.toString("mm:ss"));
        if(countdown <= QTime(0,0,0,0)){
            timer->stop();
            ui->label_countdown->setText("-- --");
            countdown.setHMS(0,cooldown_time,0);
            timer2->start(1000);
            for(auto i=0; i<drop_count; i++){
                droplets[i]->pause();
            }
            for(auto i=0; i<drop_count; i++){
                labels[i]->hide();
            }
            ui->radioButton_once->setEnabled(false);
        }
    }
    else{
        countdown = countdown.addSecs(-1);
        ui->label_3->setText("Pozostały czas schładzania:");
        ui->label_countdown->setText( countdown.toString("mm:ss"));
        if(countdown <= QTime(0,0,0,0)){
            timer2->stop();
            ui->label_countdown->setText("-- --");
            ui->pushButton_accept->setEnabled(true);

        }
    }

}

void Watering::on_pushButton_turn_off_clicked()
{
    char dd[] = "0000";
    QByteArray databuf;
    databuf = QByteArray((char*)dd, 4);
    if(ui->checkBox_sunday->isChecked())
        emit publish_msg(topics_watering[0],databuf);
    if(ui->checkBox_monday->isChecked())
        emit publish_msg(topics_watering[1],databuf);
    if(ui->checkBox_tuesday->isChecked())
        emit publish_msg(topics_watering[2],databuf);
    if(ui->checkBox_wednesday->isChecked())
        emit publish_msg(topics_watering[3],databuf);
    if(ui->checkBox_thursday->isChecked())
        emit publish_msg(topics_watering[4],databuf);
    if(ui->checkBox_friday->isChecked())
        emit publish_msg(topics_watering[5],databuf);
    if(ui->checkBox_saturday->isChecked())
        emit publish_msg(topics_watering[6],databuf);
}
