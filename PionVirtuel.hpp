#ifndef PIONVIRTUEL_H
#define PIONVIRTUEL_H
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
namespace Modele {
    class Case;

    class PionVirtuel
    {
    public:
        PionVirtuel(QString couleur = "");
        virtual ~PionVirtuel(){delete image;} 
        virtual void setImage() = 0;
        virtual void seDeplacer(Case* newPos, bool pretend) = 0;

        Case* getCase();
        void setCase(Case* pos) {
            caseActuel_ = pos;
        }     
        bool getEtatPion() {
            return estVivant_;
        }
        void setEtatPionMort() {
            estVivant_ = false;
        }
        QString getCouleur() {
            return couleur_; 
        }

        bool firstMove;

        QGraphicsPixmapItem* image;

    protected:
        QString couleur_;
        bool estVivant_;
        Case* caseActuel_;
        
    };
}
#endif // PIONVIRTUEL_H