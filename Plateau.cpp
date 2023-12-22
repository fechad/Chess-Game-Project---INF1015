/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Plateau.h"
#include "Case.h"
#include "Controleur.h"
#include "Pieces.h"
#include "PionVirtuel.hpp"
#include <QColor>

extern Interface::Controleur* jeu;

namespace Modele {
   
    Plateau::Plateau()
    {
        for (int i = 0; i < 8; i++) {
            QList<QString> row;
            for (int j = 0; j < 8; j++) {
                row.append("0");
            }
            grille_.push_back(row);
        }
    }

    void Plateau::dessinerCases(int x, int y) {
        int SHIFT = 100;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Case* carreau = new Case();
                carreau->positionCase_->i = i;
                carreau->positionCase_->j = j;
                carreau->setPos(x + SHIFT * j, y + SHIFT * i);
                if ((i + j) % 2 != 0) {
                    carreau->setCouleur(Qt::darkGreen);
                }
                else {
                    carreau->setCouleur(Qt::lightGray);
                }
                jeu->grille[i][j] = carreau;
                jeu->ajouter(jeu->grille[i][j]);
            }
        }
    }

    void Plateau::ajouterPiece(QString couleur, QString nom) {
        Case* pos = new Case();
        if (couleur == "Blanc") {
            if (nom == "ROI") {
                try {
                    PionVirtuel* roi = new Roi(couleur);
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 4;
                    pos->setEstOccupe(true);
                    roi->setCase(pos);
                    pieces_.append(roi);
                    grille_[roi->getCase()->positionCase_->i][roi->getCase()->positionCase_->j] = nom;
                }
                catch (logic_error& error) {
                    cout << "Erreur : " << error.what() << endl;
                }
            }
            else if (nom == "FOU") {
                PionVirtuel* fou = new Fou(couleur);
                pos->setEstOccupe(true);
                if (grille_[7][5] == "0") {
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 5;
                    fou->setCase(pos);
                }
                else {
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 2;
                    fou->setCase(pos);
                }
                pieces_.append(fou);
                grille_[fou->getCase()->positionCase_->i][fou->getCase()->positionCase_->j] = nom;
            }
            else if (nom == "TOUR") {
                PionVirtuel* tour = new Tour(couleur);
                pos->setEstOccupe(true);
                if (grille_[7][0] == "0") {
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 0;
                    tour->setCase(pos);
                }
                else {
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 7;
                    tour->setCase(pos);
                }
                pieces_.append(tour);
                grille_[tour->getCase()->positionCase_->i][tour->getCase()->positionCase_->j] = nom;
            }
            else if (nom == "PION") {
                PionVirtuel* pion = new Pion(couleur);
                for (int j = 0; j < grille_.size(); j++) {
                    if (grille_[6][j] == "0") {
                        pos->positionCase_->i = 6;
                        pos->positionCase_->j = j;
                        pos->setEstOccupe(true);
                        pion->setCase(pos);
                        pieces_.append(pion);
                        grille_[pion->getCase()->positionCase_->i][pion->getCase()->positionCase_->j] = nom;
                        break;
                    }
                }
            }
            else if (nom == "CAVALIER") {
                PionVirtuel* caval = new Cavalier(couleur);
                pos->setEstOccupe(true);
                if (grille_[7][1] == "0") {
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 1;
                    caval->setCase(pos);
                }
                else {
                    pos->positionCase_->i = 7;
                    pos->positionCase_->j = 6;
                    caval->setCase(pos);
                }
                pieces_.append(caval);
                grille_[caval->getCase()->positionCase_->i][caval->getCase()->positionCase_->j] = nom;
            }
            else if (nom == "REINE") {
                PionVirtuel* reine = new Reine(couleur);
                pos->positionCase_->i = 7;
                pos->positionCase_->j = 3;
                pos->setEstOccupe(true);
                reine->setCase(pos);
                pieces_.append(reine);
                grille_[reine->getCase()->positionCase_->i][reine->getCase()->positionCase_->j] = nom;
            }
        }
        else {
            if (nom == "ROI") {
                try  {
                    PionVirtuel* roi = new Roi(couleur);
                    pieces_.append(roi);
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 4;
                    pos->setEstOccupe(true);
                    roi->setCase(pos);
                    grille_[roi->getCase()->positionCase_->i][roi->getCase()->positionCase_->j] = nom;
                }
                catch (logic_error& error) {
                    cout << "Erreur : " << error.what() << endl;
                }
            }
            else if (nom == "FOU") {
                PionVirtuel* fou = new Fou(couleur);
                pos->setEstOccupe(true);
                if (grille_[0][5] == "0") {
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 5;
                    fou->setCase(pos);
                }
                else {
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 2;
                    fou->setCase(pos);
                }
                pieces_.append(fou);
                grille_[fou->getCase()->positionCase_->i][fou->getCase()->positionCase_->j] = nom;
            }
            else if (nom == "TOUR") {
                PionVirtuel* tour = new Tour(couleur);
                pos->setEstOccupe(true);
                if (grille_[0][0] == "0") {
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 0;
                    tour->setCase(pos);
                }
                else {
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 7;
                    tour->setCase(pos);
                }
                pieces_.append(tour);
                grille_[tour->getCase()->positionCase_->i][tour->getCase()->positionCase_->j] = nom;
            }
            else if (nom == "PION") {
                PionVirtuel* pion = new Pion(couleur);
                for (int j = 0; j < grille_.size(); j++) {
                    if (grille_[1][j] == "0") {
                        pos->positionCase_->i = 1;
                        pos->positionCase_->j = j;
                        pos->setEstOccupe(true);
                        pion->setCase(pos);
                        pieces_.append(pion);
                        grille_[pion->getCase()->positionCase_->i][pion->getCase()->positionCase_->j] = nom;
                        break;
                    }
                }
            }
            else if (nom == "CAVALIER") {
                PionVirtuel* caval = new Cavalier(couleur);
                pos->setEstOccupe(true);
                if (grille_[0][1] == "0") {
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 1;
                    caval->setCase(pos);
                }
                else {
                    pos->positionCase_->i = 0;
                    pos->positionCase_->j = 6;
                    caval->setCase(pos);
                }
                pieces_.append(caval);
                grille_[caval->getCase()->positionCase_->i][caval->getCase()->positionCase_->j] = nom;
            }
            else if (nom == "REINE") {
                PionVirtuel* reine = new Reine(couleur);
                pos->positionCase_->i = 0;
                pos->positionCase_->j = 3;
                pos->setEstOccupe(true);
                reine->setCase(pos);
                pieces_.append(reine);
                grille_[reine->getCase()->positionCase_->i][reine->getCase()->positionCase_->j] = nom;
            }
        }
        corbeille_.append(pos);
    }

    void Plateau::combinaisonB() {
        for (auto piece : pieces_) {
            if (dynamic_cast<Pion*>(piece)) {
                if (piece->getCouleur() == "Blanc") {
                    piece->getCase()->positionCase_->i = 4;
                    piece->firstMove = false;
                }
                else if (piece->getCouleur() == "Noir") {
                    piece->getCase()->positionCase_->i = 3;
                    piece->firstMove = false;
                }
            }
        }
    }

    void Plateau::combinaisonA() {
        
        /*reineB*/
        pieces_[1]->getCase()->positionCase_->i = 6;

        /*fouB2*/
        pieces_[3]->getCase()->positionCase_->i = 6;
        pieces_[3]->getCase()->positionCase_->j = 1;
        
        /*tourB1 */
        pieces_[4]->getCase()->positionCase_->i = 5;
        pieces_[4]->getCase()->positionCase_->j = 6;

        /*cavB1*/
        pieces_[6]->getCase()->positionCase_->i = 5;
        pieces_[6]->getCase()->positionCase_->j = 0;

        /*pionB2*/
        pieces_[9]->getCase()->positionCase_->i = 4;
        pieces_[9]->getCase()->positionCase_->j = 1;
        pieces_[9]->firstMove = false;

        /*pionB3*/
        pieces_[10]->getCase()->positionCase_->i = 5;
        pieces_[10]->getCase()->positionCase_->j = 2;
        pieces_[10]->firstMove = false;

        /*pionB4*/
        pieces_[11]->getCase()->positionCase_->i = 4;
        pieces_[11]->getCase()->positionCase_->j = 3;
        pieces_[11]->firstMove = false;

        /*reineN*/
        pieces_[17]->getCase()->positionCase_->i = 2;
        pieces_[17]->getCase()->positionCase_->j = 1;

        /*cavN1*/
        pieces_[22]->getCase()->positionCase_->i = 1;
        pieces_[22]->getCase()->positionCase_->j = 3;

        /*cavN1*/
        pieces_[23]->getCase()->positionCase_->i = 2;
        pieces_[23]->getCase()->positionCase_->j = 7;

        /*pionN4*/
        pieces_[27]->getCase()->positionCase_->i = 3;
        pieces_[27]->getCase()->positionCase_->j = 3;
        pieces_[27]->firstMove = false;

        /*pionN5*/
        pieces_[28]->getCase()->positionCase_->i = 4;
        pieces_[28]->getCase()->positionCase_->j = 4;
        pieces_[28]->firstMove = false;

        /*pionN7*/
        pieces_[30]->getCase()->positionCase_->i = 2;
        pieces_[30]->getCase()->positionCase_->j = 6;
        pieces_[30]->firstMove = false;
    }

    void Plateau::dessinerPieces() {
        for (auto i : pieces_) {
            Case* box = jeu->grille[i->getCase()->positionCase_->i][i->getCase()->positionCase_->j];
            box->placerPiece(i);
            jeu->grille[i->getCase()->positionCase_->i][i->getCase()->positionCase_->j] = box;
            jeu->ajouter(i->image);
        }
    }
    void Plateau::lancerLaPartie()
    {
        /*Combinaison Classique*/

        ajouterPiece("Blanc", "ROI");
        ajouterPiece("Blanc", "REINE");
        ajouterPiece("Blanc", "FOU");
        ajouterPiece("Blanc", "FOU");
        ajouterPiece("Blanc", "TOUR");
        ajouterPiece("Blanc", "TOUR");
        ajouterPiece("Blanc", "CAVALIER");
        ajouterPiece("Blanc", "CAVALIER");
        for (int pB = 0; pB < 8; pB++)
            ajouterPiece("Blanc", "PION");

        ajouterPiece("Noir", "ROI");
        ajouterPiece("Noir", "REINE");
        ajouterPiece("Noir", "FOU");
        ajouterPiece("Noir", "FOU");
        ajouterPiece("Noir", "TOUR");
        ajouterPiece("Noir", "TOUR");
        ajouterPiece("Noir", "CAVALIER");
        ajouterPiece("Noir", "CAVALIER");
        for (int pN = 0; pN < 8; pN++)
            ajouterPiece("Noir", "PION");

        /*Combinaison A*/
        if (jeu->getCombinaisonDepart() == "combinaison A") {
            combinaisonA();
        }

        /*Combinaison B*/
        if (jeu->getCombinaisonDepart() == "combinaison B") {
            combinaisonB();
        }
    }

    void Plateau::verification(Case* caseAVerifier, Case* caseDepart, PionVirtuel* pion) {
        
        pion->seDeplacer(caseAVerifier, false);
        if (pion->getCase() == caseAVerifier) {
            attaquerRoi();
            if (jeu->echec->isVisible()) {
                unsafe = true;
                jeu->echec->setVisible(false);
                for (auto piece : pieces_) {
                    if (dynamic_cast<Roi*>(piece)) {
                        if ((piece->getCase()->getCouleurCase() == Qt::yellow) && (!dynamic_cast<Roi*>(pion))) {
                            if (pion->getCouleur() != piece->getCouleur()) {
                                unsafe = false;
                            }
                        }
                        piece->getCase()->resetCouleur();
                    }
                }
                caseDepart->placerPiece(pion);
                if (!dynamic_cast<Pion*>(pion)) {
                    caseAVerifier->setEstOccupe(false);
                    caseAVerifier->piece_ = NULL;
                }
                else if(caseDepart->positionCase_->j == caseAVerifier->positionCase_->j){
                    caseAVerifier->setEstOccupe(false);
                    caseAVerifier->piece_ = NULL;
                }
                caseAVerifier->resetCouleur();
                caseDepart->resetCouleur();
            }
        }
    }

    void Plateau::attaquerRoi() {
        for (auto pieceCible : pieces_) {
            if (dynamic_cast<Roi*>(pieceCible)) {
                for (auto piece : pieces_) {
                    if (piece->getCase() != pieceCible->getCase()) {
                        piece->seDeplacer(pieceCible->getCase(), true);
                    }
                }
            }
        }
    }

    void Plateau::tuer(Case* caseDuPion) {
        int i = 0;
        for (auto piece : pieces_) {
            if (piece->getCase() == caseDuPion) {
                piece->getCase()->setEstOccupe(false);
                piece->getCase()->piece_ = NULL;
                jeu->retirer(piece->image);
                piece->setEtatPionMort();
                pieces_.removeAt(i);
                delete piece;
            }
            i++;
        }
    }
    
}
