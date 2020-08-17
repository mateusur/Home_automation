#include "weather.h"
#include "ui_weather.h"



Weather::Weather(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    QNetworkRequest request(QUrl(QString("https://api.openweathermap.org/data/2.5/onecall?lat=50.907066&lon=16.653226&%20exclude=current,minutely,hourly&appid=66a44116b5639646b420fff27e0fb57b&units=metric&lang=pl")));
    //QNetworkRequest request(QUrl(QString("http://api.openweathermap.org/data/2.5/weather?lat=50.907066&lon=16.653226&appid=66a44116b5639646b420fff27e0fb57b&units=metric")));

    //request.setUrl(QUrl(QString("https://api.openweathermap.org/data/2.5/onecall?lat=50.907066&lon=16.653226&%20exclude=current,minutely,hourly&appid=66a44116b5639646b420fff27e0fb57b&units=metric&lang=pl")));
    //QNetworkReply *netReply =
    manager->get(request);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));

    QPixmap pixmap_return(":/Icons/left_48.png");
    QIcon ButtonIcon_return(pixmap_return);
    ui->return_button->setIcon(ButtonIcon_return);
    ui->return_button->setIconSize(pixmap_return.rect().size());
}

Weather::~Weather()
{
    qDebug() << "Destruktor weahter window";
    delete ui;
}

void Weather::managerFinished(QNetworkReply *reply)
{


    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jo = jsonDoc.object();
    QJsonValue val = jo.value("daily");
    QJsonArray array = val.toArray();
    for(auto day : array){
        auto object = day.toObject();
        v_feels_like.push_back(object["feels_like"].toObject()["day"].toDouble());
        v_rain.push_back( object["rain"].toDouble());
        v_pressure.push_back( object["pressure"].toInt());
        v_temp.push_back( object["temp"].toObject()["day"].toDouble());
        v_descrption.push_back( object["weather"].toArray()[0].toObject()["description"].toString());
        v_icon.push_back( object["weather"].toArray()[0].toObject()["icon"].toString());
    }

    for(auto temperatures :v_feels_like ){
        qDebug() << "====================================";
        qDebug() << temperatures;
    }

    //    QJsonObject jo = jsonDoc.object();
    //    QJsonObject main = jo["main"].toObject();
    //    feels_like = main["feels_like"].toDouble();
    //    humidity = main["humidity"].toInt();
    //    pressure = main["pressure"].toInt();
    //    temp          = main["temp"].toDouble();
    //    temp_max      = main["temp_max"].toDouble();
    //    temp_min      = main["temp_min"].toDouble();
    //    qDebug() << feels_like;
    //    qDebug() << humidity ;
    //    qDebug() << pressure ;
    //    qDebug() << temp      ;
    //    qDebug() << temp_max  ;
    //    qDebug() << temp_min  ;
    //    QJsonObject sys = jo["sys"].toObject();
    //    QTime sunrise_tmp(0,0,0), sunset_tmp(0,0,0);
    //    sunrise_tmp = sunrise_tmp.addSecs(int(sys["sunrise"].toInt()));
    //    sunset_tmp = sunset_tmp.addSecs(sys["sunset"].toInt());
    //    this->sunrise = sunrise_tmp;
    //    this->sunset = sunset_tmp;
    //    QJsonObject wind = jo["wind"].toObject();
    //    this->deg = wind["deg"].toInt();
    //    this->speed = wind["speed"].toDouble();
    //    QJsonArray weather = jo["weather"].toArray();
    //    this->description = weather.first()["description"].toString();
    //    this->icon = weather.first()["icon"].toString();
    //    this->name = jo["name"].toString();
       // qDebug() << "============================================================================================================";
}

void Weather::on_return_button_clicked()
{
    this->hide();
      emit change_window();
}
