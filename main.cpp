#include "choosewindow.h"
#include "chickencoop.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseWindow w;
    w.show();

    Chickencoop c;
    c.show();
    return a.exec();
}
