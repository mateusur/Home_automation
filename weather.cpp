#include "weather.h"
#include "ui_weather.h"


Weather::Weather(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    data_changed();

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));

    QPixmap pixmap_return(":/Icons/left_48.png");
    QIcon ButtonIcon_return(pixmap_return);
    ui->return_button->setIcon(ButtonIcon_return);
    ui->return_button->setIconSize(pixmap_return.rect().size());

    QPixmap pixmap_refresh(":/Icons/Weather/refresh_30.png");
    QIcon ButtonIcon_refresh(pixmap_refresh);
    ui->pushButton_refresh->setIcon(ButtonIcon_refresh);
    ui->pushButton_refresh->setIconSize(pixmap_refresh.rect().size());

    ui->return_button->setToolTip(tr("Powrót do okna głównego"));
    ui->pushButton_refresh->setToolTip(tr("Odśwież dane"));
}

Weather::~Weather()
{
    qDebug() << "Destruktor weahter window";
    delete ui;
}

void Weather::data_changed()
{
    QSettings settings("PrivateApp", "Home_automation");
    QString latitude  = settings.value("latitude", "").toString();
    QString longitude = settings.value("longitude", "").toString();
    QString API_key = settings.value("API_key","").toString();
    QString language = settings.value("language","").toString();
    if(language == "Polish"){
        request.setUrl(QUrl(QString("https://api.openweathermap.org/data/2.5/onecall?lat="+latitude+"&lon="+longitude+"&%20exclude=current,minutely,hourly&appid="+API_key+"&units=metric&lang=pl")));
    }
    else{
        request.setUrl(QUrl(QString("https://api.openweathermap.org/data/2.5/onecall?lat="+latitude+"&lon="+longitude+"&%20exclude=current,minutely,hourly&appid="+API_key+"&units=metric&lang=en")));
    }
    manager->get(request);
}

void Weather::managerFinished(QNetworkReply *reply)
{

    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }
    v_feels_like.clear();
    v_rain.clear();
    v_pressure.clear();
    v_temp.clear();
    v_description.clear();
    v_icon.clear();
    v_time.clear();
    v_time_days.clear();
    v_clouds.clear();
    QString answer = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jo = jsonDoc.object();
    QJsonValue val = jo.value("daily");
    QJsonArray array = val.toArray();
    uint unixtimestamp;
    QDateTime myDateTime;
    QSettings settings("PrivateApp", "Home_automation");
    QString language = settings.value("language","").toString();
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
        if(language == "Polish"){
            QString tmp = myDateTime.toString("dddd");
              tmp[0] = tmp[0].toUpper();
            v_time.push_back(tmp);
            v_time_days.push_back(myDateTime.toString("dd.MM"));
        }
        else{
            QString tmp = myDateTime.toString("dddd");
              tmp[0] = tmp[0].toUpper();
              qDebug() << tmp;
              translate_day(tmp);
            v_time.push_back(tmp);
            v_time_days.push_back(myDateTime.toString("dd.MM"));
        }
        v_clouds.push_back(object["clouds"].toInt());
    }
    set_all_icons();
}

void Weather::on_return_button_clicked()
{
    this->hide();
    emit change_window();
}

void Weather::set_icon(QLabel *label,const QString& icon)
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
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(weather_pixmap.scaled(w,h,Qt::KeepAspectRatioByExpanding));
}

void Weather::set_temp(QLabel *label, const double& temp)
{
//    QString t = tr("Temp.: ").rightJustified(11);
    QString num = QString::number(temp,'f',1) ;
    //
//    QString unit = (" °C");
//    QString uf= unit.rightJustified(4);
    QString str = QString("%1 %2 %3")
            .arg(tr("Temp.:"), 11).arg(num,4).arg("°C",2);
    label->setText(str);
}

void Weather::set_feels(QLabel *label, const double& feels_like)
{
    QString num  = QString::number(feels_like,'f',1);
    QString str = QString("%1 %2 %3")
            .arg(tr("Odcz.:"), 11).arg(num,4).arg("°C",2);
    label->setText(str);
}

void Weather::set_rain(QLabel *label, const double& rain)
{
    QString num = QString::number(rain,'f',1);
    QString str = QString("%1 %2 %3").arg((tr("Opady:")), 11).arg(num,4).arg("mm",2);
    label->setText(str);
}

void Weather::set_clouds(QLabel *label, const int& cloudines)
{
    QString num = QString::number(cloudines);
    QString str = QString("%1 %2 %3")
            .arg(tr("Chmury:"), 11).arg(num,3).arg("%",1);
    label->setText(str);
}

void Weather::set_pressure(QLabel *label, const int& pressure)
{
    QString num = QString::number(pressure);
    QString str = QString("%1 %2 %3")
            .arg(tr("Ciśnienie:"), 11).arg(num,5).arg("hPa",3);
    label->setText(str);
}

void Weather::set_description(QLabel *label, const QString& description)
{
    label->setText(description);
    label->setWordWrap(true);
}

void Weather::set_time(QLabel *label, const QString& time)
{
    label->setStyleSheet("font-weight: bold; font: 12pt");
    label->setAlignment(Qt::AlignCenter);
    label->setText(time);
}

void Weather::set_all_icons()
{
    set_icon(ui->label_icon_day00,v_icon[0]);
    set_icon(ui->label_icon_day01,v_icon[1]);
    set_icon(ui->label_icon_day02,v_icon[2]);
    set_icon(ui->label_icon_day03,v_icon[3]);
    set_icon(ui->label_icon_day04,v_icon[4]);
    set_icon(ui->label_icon_day05,v_icon[5]);

    set_temp(ui->label_temp00,v_temp[0]);
    set_temp(ui->label_temp01,v_temp[1]);
    set_temp(ui->label_temp02,v_temp[2]);
    set_temp(ui->label_temp03,v_temp[3]);
    set_temp(ui->label_temp04,v_temp[4]);
    set_temp(ui->label_temp05,v_temp[5]);

    set_feels(ui->label_feels00,v_feels_like[0]);
    set_feels(ui->label_feels01,v_feels_like[1]);
    set_feels(ui->label_feels02,v_feels_like[2]);
    set_feels(ui->label_feels03,v_feels_like[3]);
    set_feels(ui->label_feels04,v_feels_like[4]);
    set_feels(ui->label_feels05,v_feels_like[5]);

    set_rain(ui->label_rain00,v_rain[0]);
    set_rain(ui->label_rain01,v_rain[1]);
    set_rain(ui->label_rain02,v_rain[2]);
    set_rain(ui->label_rain03,v_rain[3]);
    set_rain(ui->label_rain04,v_rain[4]);
    set_rain(ui->label_rain05,v_rain[5]);

    set_pressure(ui->label_pressure00,v_pressure[0]);
    set_pressure(ui->label_pressure01,v_pressure[1]);
    set_pressure(ui->label_pressure02,v_pressure[2]);
    set_pressure(ui->label_pressure03,v_pressure[3]);
    set_pressure(ui->label_pressure04,v_pressure[4]);
    set_pressure(ui->label_pressure05,v_pressure[5]);

    set_description(ui->label_description00,v_description[0]);
    set_description(ui->label_description01,v_description[1]);
    set_description(ui->label_description02,v_description[2]);
    set_description(ui->label_description03,v_description[3]);
    set_description(ui->label_description04,v_description[4]);
    set_description(ui->label_description05,v_description[5]);

    set_clouds(ui->label_clouds00,v_clouds[0]);
    set_clouds(ui->label_clouds01,v_clouds[1]);
    set_clouds(ui->label_clouds02,v_clouds[2]);
    set_clouds(ui->label_clouds03,v_clouds[3]);
    set_clouds(ui->label_clouds04,v_clouds[4]);
    set_clouds(ui->label_clouds05,v_clouds[5]);

    set_time(ui->label_day00,tr("Dzisiaj"));
    set_time(ui->label_day01,tr("Jutro"));
    set_time(ui->label_day02,v_time[2]);
    set_time(ui->label_day03,v_time[3]);
    set_time(ui->label_day04,v_time[4]);
    set_time(ui->label_day05,v_time[5]);

    set_time(ui->label_day00_2,v_time_days[0]);
    set_time(ui->label_day01_2,v_time_days[1]);
    set_time(ui->label_day02_2,v_time_days[2]);
    set_time(ui->label_day03_2,v_time_days[3]);
    set_time(ui->label_day04_2,v_time_days[4]);
    set_time(ui->label_day05_2,v_time_days[5]);


}

void Weather::translate_day(QString &day)
{
    if(day=="Poniedziałek"){day =tr("Poniedziałek");}
    else if(day=="Wtorek"){day =tr("Wtorek");}
    else if(day == "Środa"){day =tr("Środa");}
    else if(day == "Czwartek"){day =tr("Czwartek");}
    else if(day == "Piątek"){day =tr("Piątek");}
    else if(day == "Sobota"){day =tr("Sobota");}
    else if(day == "Niedziela"){day =tr("Niedziela");}
    else{day = tr("Błąd");}

}

void Weather::on_pushButton_refresh_clicked()
{
    manager->get(request);
}
