#ifndef DROPLET_H
#define DROPLET_H
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPropertyAnimation>

/*!
 * \brief Klasa Droplet implementuje animacje kropli deszczu
 */
class Droplet : public QLabel
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy Droplet
     * \param label - wskaźnik na etykiete
     */
    Droplet(QLabel *label);
    ~Droplet();
    /*!
     * \brief Pauza animacji
     * Metoda odpowiedzialna za pauze animacji
     */
    void pause();
    /*!
     * \brief Wznawianie animacji
     * Metoda odpowiedzialna za wznowienie animacji
     */
    void resume();
private:
    /*!
     * \brief Pixmapa kropli deszczu
     */
    QPixmap droplet_icon;
    /*!
     * \brief Wskaźnik na animacje
     */
    QPropertyAnimation *animation;
};

#endif // DROPLET_H
