#ifndef AUTHOR_H
#define AUTHOR_H

#include <QDialog>

namespace Ui {
class Author;
}
/*!
 * \brief Klasa Author
 * Klasa implementuje okno pomocnicze, które zawiera kontakt do autora oraz licencje wykorzystanych ikon.
 */
class Author : public QDialog
{
    Q_OBJECT

public:
    explicit Author(QWidget *parent = nullptr);
    ~Author();

private:
    Ui::Author *ui;
};

#endif // AUTHOR_H
