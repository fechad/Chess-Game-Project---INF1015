/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Controleur.h"
#include "Bouttons.h"
#include <QGraphicsTextItem>
#include <QBrush>

namespace Interface {
    Boutton::Boutton(QString name, QGraphicsItem* parent) : QGraphicsRectItem(parent) {
        setRect(0, 0, 200, 50);
        QBrush pinceau;
        pinceau.setStyle(Qt::SolidPattern);
        pinceau.setColor(Qt::darkBlue);
        setBrush(pinceau);

        nom = new QGraphicsTextItem(name, this);
        nom->setDefaultTextColor(Qt::white);
        int x = rect().width() / 2 - nom->boundingRect().width() / 2;
        int y = rect().height() / 2 - nom->boundingRect().height() / 2;
        nom->setPos(x, y);
    }
    void Boutton::resize(int longueur, int largeur) {

        setRect(0, 0, longueur, largeur);
        int x = rect().width() / 2 - nom->boundingRect().width() / 2;
        int y = rect().height() / 2 - nom->boundingRect().height() / 2;
        nom->setPos(x, y);
    }
}


