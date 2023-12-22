
#ifndef CONTROLEUR_H
#define CONTROLEUR_H
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QBrush>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <iterator>
#include <map>
#include <forward_list>
#include <numeric>
#include <limits>
#include <algorithm>
#include <sstream>
#include "cppitertools/range.hpp"
#include "cppitertools/enumerate.hpp"
#include "gsl/span"

using namespace std;
using namespace iter;
using namespace gsl;

#pragma endregion//}

#include "Case.h"
#include "PionVirtuel.hpp"
#include "Bouttons.h"
#include "Plateau.h"

/*voir ReadMe pour l'inspiration de cette classe*/

namespace Interface {
    using namespace Modele;
    class Controleur :public QGraphicsView
    {
        Q_OBJECT
    public:
        Controleur(QWidget* parent = 0);
        ~Controleur() {
            
            if (redemarrage == false) {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        delete grille[i][j];
                    }
                }
                delete echequier_;
            }
            for (int i = 0; i < composantesGraphiques_.length(); i++) {
                delete composantesGraphiques_[i];
            }

            //delete pieceADeplacer;
            exit(0);
        }
        void dessinerPlateau();
        void menuPrincipal();
        void ajouter(QGraphicsItem* item);
        void retirer(QGraphicsItem* item);

        PionVirtuel* pieceADeplacer;

        QString getTour() {
            return tour_;
        }
        void setTour(QString value) {
            tour_ = value;
        }
        void changerDeTour();

        Case* grille[8][8];
        unique_ptr<QGraphicsTextItem> echec;

        Plateau* getEchequier() {
            return echequier_;
        }
        int nbClick = 0;
        QString getCombinaisonDepart() {
            return combinaisonDepart;
        }
        QString combinaisonDepart;
        QList <QGraphicsItem*> getComposantes() { return composantesGraphiques_; }
        bool redemarrage = true;

    public slots:
        void partieCommencee();
        void redemarrer();
        void selectionCombinaison();
        void comfirmationCombinaisonClassique();
        void comfirmationCombinaisonA();
        void comfirmationCombinaisonB();

    private:
        QString tour_;
        Plateau* echequier_ = nullptr;
        unique_ptr<QGraphicsTextItem> joeurActif_;
        QList <QGraphicsItem*> composantesGraphiques_;
        unique_ptr<QGraphicsScene> interfaceGraphique_;
    };

}
#endif

