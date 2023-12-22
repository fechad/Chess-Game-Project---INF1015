#ifndef CASE_H
#define CASE_H
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "PionVirtuel.hpp"
#include "Controleur.h"
#include <QGraphicsRectItem>
#include <QBrush>

namespace Modele {
    struct Position {
        int i;
        int j;
        bool operator<(Position pos) noexcept {
            return i < pos.i;
        }
    };
    class Case :public QGraphicsRectItem
    {
    public:

        Case(QGraphicsItem* parent = 0);
        ~Case() { 
            delete positionCase_; 
            delete piece_; 
        }

        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        QColor getCouleurCase() { return pinceau_.color(); }
        void setCouleurPinceau(QColor color);
        void placerPiece(PionVirtuel* piece);
        void resetCouleur();
        void setCouleur(QColor couleur);
        bool getEstOccupe();
        void setEstOccupe(bool etat);
        QString getCouleurPiece();
        void setCouleurPiece(QString couleur);

        Position* positionCase_;
        PionVirtuel* piece_;
        
    private:
        QColor couleur_;
        bool estOccupe_;
        QString couleurDuPion_;
        QBrush pinceau_;
    };
}
#endif // !CASE_H