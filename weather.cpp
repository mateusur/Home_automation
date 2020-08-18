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
    uint unixtimestamp;
    QDateTime myDateTime;
    for(auto day : array){
        auto object = day.toObject();
        v_feels_like.push_back(object["feels_like"].toObject()["day"].toDouble());
        v_rain.push_back( object["rain"].toDouble());
        v_pressure.push_back( object["pressure"].toInt());
        v_temp.push_back( object["temp"].toObject()["day"].toDouble());
        v_description.push_back( object["weather"].toArray()[0].toObject()["description"].toString());
        v_icon.push_back( object["weather"].toArray()[0].toObject()["icon"].toString());
        unixtimestamp = object["dt"].toInt();
        myDateTime.setTime_t(unixtimestamp);
        v_time.push_back(myDateTime.toString("dd.MM"));
        v_clouds.push_back(object["clouds"].toInt());
    }


    for(auto b: v_time)
        qDebug() << b;

    set_icon(ui->label_icon_day00,v_icon[0]);
    set_icon(ui->label_icon_day01,v_icon[1]);
    set_icon(ui->label_icon_day02,v_icon[2]);
    set_icon(ui->label_icon_day03,v_icon[3]);
    set_icon(ui->label_icon_day04,v_icon[4]);
    set_icon(ui->label_icon_day05,v_icon[5]);
    //set_icon(ui->label_day06,v_icon[6]);
    //set_icon(ui->label_day07,v_icon[7]);

    set_temp(ui->label_temp00,v_temp[0]);
    set_temp(ui->label_temp01,v_temp[1]);
    set_temp(ui->label_temp02,v_temp[2]);
    set_temp(ui->label_temp03,v_temp[3]);
    set_temp(ui->label_temp04,v_temp[4]);
    set_temp(ui->label_temp05,v_temp[5]);
    //set_temp(ui->label_temp06,v_temp[6]);
    //set_temp(ui->label_temp07,v_temp[7]);

    set_feels(ui->label_feels00,v_feels_like[0]);
    set_feels(ui->label_feels01,v_feels_like[1]);
    set_feels(ui->label_feels02,v_feels_like[2]);
    set_feels(ui->label_feels03,v_feels_like[3]);
    set_feels(ui->label_feels04,v_feels_like[4]);
    set_feels(ui->label_feels05,v_feels_like[5]);
    //set_feels(ui->label_feels06,v_feels_like[6]);
    //set_feels(ui->label_feels07,v_feels_like[7]);

    set_rain(ui->label_rain00,v_rain[0]);
    set_rain(ui->label_rain01,v_rain[1]);
    set_rain(ui->label_rain02,v_rain[2]);
    set_rain(ui->label_rain03,v_rain[3]);
    set_rain(ui->label_rain04,v_rain[4]);
    set_rain(ui->label_rain05,v_rain[5]);
    //set_rain(ui->label_rain06,v_rain[6]);
    //set_rain(ui->label_rain07,v_rain[7]);

    set_pressure(ui->label_pressure00,v_pressure[0]);
    set_pressure(ui->label_pressure01,v_pressure[1]);
    set_pressure(ui->label_pressure02,v_pressure[2]);
    set_pressure(ui->label_pressure03,v_pressure[3]);
    set_pressure(ui->label_pressure04,v_pressure[4]);
    set_pressure(ui->label_pressure05,v_pressure[5]);
    //set_pressure(ui->label_pressure06,v_pressure[6]);
    //set_pressure(ui->label_pressure07,v_pressure[7]);

    set_description(ui->label_description00,v_description[0]);
    set_description(ui->label_description01,v_description[1]);
    set_description(ui->label_description02,v_description[2]);
    set_description(ui->label_description03,v_description[3]);
    set_description(ui->label_description04,v_description[4]);
    set_description(ui->label_description05,v_description[5]);
    //set_description(ui->label_description06,v_description[6]);
    //set_description(ui->label_description07,v_description[7]);

    set_clouds(ui->label_clouds00,v_clouds[0]);
    set_clouds(ui->label_clouds01,v_clouds[1]);
    set_clouds(ui->label_clouds02,v_clouds[2]);
    set_clouds(ui->label_clouds03,v_clouds[3]);
    set_clouds(ui->label_clouds04,v_clouds[4]);
    set_clouds(ui->label_clouds05,v_clouds[5]);

    set_time(ui->label_day00,"Dzisiaj");
    set_time(ui->label_day01,"Jutro");
    set_time(ui->label_day02,v_time[2]);
    set_time(ui->label_day03,v_time[3]);
    set_time(ui->label_day04,v_time[4]);
    set_time(ui->label_day05,v_time[5]);


}

void Weather::on_return_button_clicked()
{
    this->hide();
    emit change_window();
}

void Weather::set_icon(QLabel *label, QString icon)
{
    QPixmap weather_pixmap;
    if(icon == "01d"  || icon == "01n")
        weather_pixmap.load(":/Icons/Weather/summer_96.png");
    else if (icon == "02d"  || icon == "02n")
        weather_pixmap.load(":/Icons/Weather/partly_cloudy_day_96.png");
    else if (icon == "03d"  || icon == "03n" || icon == "04d"  || icon == "04n")
        weather_pixmap.load(":/Icons/Weather/clouds_96.png");
    else if (icon == "09d"  || icon == "09n")
        weather_pixmap.load(":/Icons/Weather/light_rain_96.png");
    else if (icon == "10d"  || icon == "10n")
        weather_pixmap.load(":/Icons/Weather/heavy_rain_96.png");
    else if (icon == "11d"  || icon == "11n")
        weather_pixmap.load(":/Icons/Weather/storm_96.png");
    else if (icon == "13d"  || icon == "13n")
        weather_pixmap.load(":/Icons/Weather/snow_96.png");
    else if (icon == "50d"  || icon == "50n")
        weather_pixmap.load(":/Icons/Weather/haze_96.png");

    int w = label->width();
    int h = label->height();
    label->setPixmap(weather_pixmap.scaled(w,h,Qt::KeepAspectRatioByExpanding));
}

void Weather::set_temp(QLabel *label, double temp)
{

    label->setText("Temp: "+ QString::number(temp) + " °C");
}

void Weather::set_feels(QLabel *label, double feels_like)
{
    label->setText("Odczuwalna: "+ QString::number(feels_like) + " °C");
}

void Weather::set_rain(QLabel *label, double rain)
{
    label->setText("Opady: "+ QString::number(rain) + " mm");
}

void Weather::set_clouds(QLabel *label, int cloudines)
{
    label->setText("Chmury: "+ QString::number(cloudines) + " %");
}

void Weather::set_pressure(QLabel *label, int pressure)
{
    label->setText("Ciśnienie: "+ QString::number(pressure) + " hPa");
}

void Weather::set_description(QLabel *label, QString description)
{
    label->setText(description);
    label->setWordWrap(true);
}

void Weather::set_time(QLabel *label, QString time)
{
    label->setStyleSheet("font-weight: bold; font: 16pt");
    label->setAlignment(Qt::AlignCenter);
    label->setText(time);
}
