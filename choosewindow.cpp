#include "choosewindow.h"
#include "ui_choosewindow.h"

ChooseWindow::ChooseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);

    QPixmap pixmap(":/Icons/chicken_100.png");
    QIcon ButtonIcon(pixmap);
    //chickencoop_button->setIcon(ButtonIcon);
    //chickencoop_button->setIconSize(pixmap.rect().size());

}

ChooseWindow::~ChooseWindow()
{
    delete ui;
}




void ChooseWindow::on_chickencoop_button_clicked()
{
    qDebug() << "Hello";
}
