/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Controleur.h"
#include "Case.h"
#include "Plateau.h"
#include "PionVirtuel.hpp"
#include "Pieces.h"
#include <QDebug>

using namespace Interface;
extern Interface::Controleur* jeu;

namespace Modele {

    Case::Case(QGraphicsItem* parent) : QGraphicsRectItem(parent)
    {
        setRect(0, 0, 100, 100);
        pinceau_.setStyle(Qt::SolidPattern);
        setEstOccupe(false);
        setCouleurPiece(" ");
        positionCase_ = new Position();
        piece_ = NULL;
    }

    void Case::mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if ((jeu->nbClick < 2) && (this->getEstOccupe() == true) && (jeu->getEchequier()->roiEnDanger == false)) {
            if (jeu->getTour() != this->getCouleurPiece()) {
                return;
            }
        }
        if ((jeu->getEchequier()->roiEnDanger == true) &&(jeu->nbClick < 2)) {
            if (this->brush() != Qt::yellow) {
                return;
            }
        }
        if (this->getEstOccupe()) {
            jeu->nbClick += 1;
        }
        if ((!jeu->pieceADeplacer) && (this->getEstOccupe())) {
            jeu->pieceADeplacer = this->piece_;
            this->setCouleurPinceau(Qt::green);
            jeu->nbClick += 1;
            return;
        }
        if (jeu->nbClick >= 2) {
            
            jeu->getEchequier()->verification(this, jeu->pieceADeplacer->getCase(), jeu->pieceADeplacer);
            if (jeu->getEchequier()->unsafe == true) {
                jeu->getEchequier()->unsafe = false;
                jeu->nbClick = 0;
                jeu->pieceADeplacer = NULL;
                return;
            }
            jeu->pieceADeplacer->seDeplacer(this, false);
            if (this->getEstOccupe()) {
                if (this->piece_ == jeu->pieceADeplacer) {
                    jeu->pieceADeplacer->getCase()->resetCouleur();
                }
                if (jeu->pieceADeplacer->getCase() == this) {
                    jeu->changerDeTour();
                }
                jeu->pieceADeplacer = NULL;
                jeu->getEchequier()->attaquerRoi();
                if (jeu->echec->isVisible()) {
                    jeu->getEchequier()->roiEnDanger = true;
                }
            }
            jeu->nbClick = 0;
        }
        else if ((this->piece_ == jeu->pieceADeplacer) && (jeu->nbClick != 0)) {
            if (!jeu->pieceADeplacer) { return; }
            jeu->pieceADeplacer->getCase()->resetCouleur();
            jeu->nbClick = 0;
            jeu->pieceADeplacer = NULL;
            return;
        }
    }

    void Case::placerPiece(PionVirtuel* piece)
    {
        int x = this->x() + 50 - piece->image->pixmap().width() / 2;
        int y = this->y() + 50 - piece->image->pixmap().width() / 2;
        piece->image->setPos(x, y);
        this->piece_ = piece;
        piece->setCase(this);
        this->setEstOccupe(true);
    }

    QString Case::getCouleurPiece() {
        return piece_->getCouleur();
    }

    void Case::setCouleurPiece(QString couleur) {
        couleurDuPion_ = couleur;
    }

    void Case::setCouleur(QColor couleur) {
        couleur_ = couleur;
        setCouleurPinceau(couleur_);
    }

    void Case::setCouleurPinceau(QColor color) {
        pinceau_.setColor(color);
        setBrush(color);
    }

    void Case::resetCouleur() {
        setCouleurPinceau(couleur_);
    }
    bool Case::getEstOccupe() {
        return estOccupe_;
    }
    void Case::setEstOccupe(bool etat) {
        estOccupe_ = etat;
    }
}