#include "choosewindow.h"
#include "chickencoop.h"
#include <QApplication>
#include <QSettings>
#include <QInputDialog>

/*! \mainpage Dokumentacja aplikacji Home automation
 * \section Wprowadzenie
 * Program kontrolujący nawodnienie ogrodu oraz działanie kurnika przy użyciu protokołu MQTT. Pozwala na wysyłanie oraz odbieranie danych
 *  z różnych czujników (nodeMCU, Raspberry pi) oraz pobieranie danych pogodowych z OpenWeather. Użyte ikony: <a href=https://icons8.com>link</a>.
 * \section ChooseWindow Główne okno
 * Główne okno aplikacji, z tego okna możemy przechodzić do wszystkich pozostałych okien oraz ustawień. Klasa implementująca okno:\ref ChooseWindow
 * \section Chickencoop Okno kurnika
 * Okno kurnika pozwala na odtwarzanie streamu z kamery podłączonej do Raspberry pi, otwieranie oraz zamykanie drzwiczek kurnika. Klasa implementująca okno:\ref Chickencoop
 * \section Watering Okno nawadniania
 * Okno nawadniania pozwala na właczenie pojedynczej sesji nawadniania oraz na ustawienie regularnych sesji poprzez wybranie godziny oraz czasu nawadniania. Klasa implementująca okno:\ref Watering
 * \section Weather Okno pogody
 * Okno pogody wyświetla aktualnie pobraną pogodę dla współrzędnych podanych w oknie ustawień \ref SettingsWeather. Klasa implementująca okno:\ref Weather
 * \section SettingsWeather Okno ustawień pogody
 * Okno ustawień pogody pozwala na wprowadzenie współrzędnych dla jakich ma być pobrana pogoda. Wymagany jest także OpenWeather klucz API. Klasa implementująca okno:\ref SettingsWeather
 * \section SettingsMQTT Okno ustawień klienta MQTT
 * Okno ustawień klienta MQTT pozwala na skonfigurowanie klienta MQTT. Klasa implementująca okno:\ref SettingsMQTT
 * \section Author Okno informacji o autorze
 * Okno o autorze wyświetla infomacje kontaktowe autora oraz wymaganą licencję. Klasa implementująca okno:\ref Author
 *  \section Dokumentacja Dokumentacja
 * Dokumentacja została wygenerowana za pomocą aplikacji Doxygen.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings("PrivateApp", "Home_automation");
    QString langugage  = settings.value("Language", "").toString();
    QTranslator t;// = new QTranslator(&a);
    if(langugage == "English"){
        t.load(":/english.qm");
    }
    if(langugage != "Polish"){
       // a.removeTranslator(&t);
        a.installTranslator(&t);
    }

    ChooseWindow w;
    w.show();




    return a.exec();
}
