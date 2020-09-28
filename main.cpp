#include "choosewindow.h"
#include "chickencoop.h"
#include <QApplication>
//TODO: Wprowadzic poprawki do ponizszego opisu

/*! \mainpage Dokumentacja aplikacji Home automation
 * \section Wprowadzenie
 * Program kontrolujący nawodnienie ogrodu oraz działanie kurnika przy użyciu protokołu MQTT. Pozwala na wysyłanie oraz odbieranie danych
 *  z różnych czujników (nodeMCU, Raspberry pi) oraz pobieranie danych pogodowych z OpenWeather.
 * \section Interface_window Główne okno
 * Główne okno aplikacji, po lewej stronie zawiera aktualne dane o kącie, statusie silników oraz przyciski pozwalające na interakcje z robotem.
 * W środkowej części umieszczono wykresy. Po prawej stronie znajduję się wizualizacja odchylenia robota od pionu. Klasa implementująca okno:\ref InterfaceWindow
 * \section Connect_window Okno łączenia
 * W oknie connect window zawarta jest implementacja narzędzi potrzebnych do połączenia się z robotem. Klasa implementująca okno:\ref ConnectWindow
 * \section Dokumentacja Dokumentacja
 * Dokumentacja została wygenerowana za pomocą aplikacji Doxygen.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseWindow w;
    w.show();




    return a.exec();
}
