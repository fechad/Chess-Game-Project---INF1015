#ifndef BOUTTONS_H
#define BOUTTONS_H
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

/*voir ReadMe pour l'inspiration de cette classe*/

namespace Interface {
    class Boutton :public QObject, public QGraphicsRectItem
    {
        Q_OBJECT
    public:

        Boutton(QString name, QGraphicsItem* parent = NULL);
        ~Boutton() { delete nom; }
        void resize(int longueur, int largeur);
        void mousePressEvent(QGraphicsSceneMouseEvent* event) {
            if (event) {
                emit clicked();
            }
        }
    signals:
        void clicked();
    private:
        QGraphicsTextItem* nom = nullptr;
    };
}
#endif // BOUTTONS_H
