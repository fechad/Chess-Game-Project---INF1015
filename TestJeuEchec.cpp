#define CATCH_CONFIG_MAIN
#include "Case.h"
#include "Controleur.h"
#include "Pieces.h"
#include "PionVirtuel.hpp"
#include <QColor>
#include <QApplication>
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

using namespace Modele;
using namespace Interface;

extern Interface::Controleur* jeu;

TEST(Echec, DeplacementRoi) {

	jeu->dessinerPlateau();
	
	Case *pos = new Case();
	PionVirtuel* roi = new Roi("Blanc");
	pos->positionCase_->i = 7;
	pos->positionCase_->j = 4;
	pos->setEstOccupe(true);
	roi->setCase(pos);

	Case* pos1 = new Case();
	pos1->positionCase_->i = 7;
	pos1->positionCase_->j = 3;
	pos1->setEstOccupe(false);
	
	jeu->pieceADeplacer = roi;
	jeu->getEchequier()->roiEnDanger = false;
	jeu->grille[7][4]->setEstOccupe(true);
	jeu->grille[7][3]->setEstOccupe(false);

	roi->seDeplacer(pos1, false);

	EXPECT_EQ(roi->getCase() , pos1);

	delete pos;
	delete pos1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete jeu->grille[i][j];
		}
	}
	for (int i = 0; i < jeu->getEchequier()->pieces_.length(); i++) {
		delete jeu->getEchequier()->pieces_[i];
	}
	delete jeu->getEchequier();
	jeu->pieceADeplacer = nullptr;
}
TEST(Echec, DeplacementCavalier) {

	jeu->dessinerPlateau();
	
	Case *pos = new Case();
	PionVirtuel* cavalier = new Cavalier("Blanc");
	pos->positionCase_->i = 7;
	pos->positionCase_->j = 4;
	pos->setEstOccupe(true);
	cavalier->setCase(pos);

	Case* pos1 = new Case();
	pos1->positionCase_->i = 5;
	pos1->positionCase_->j = 5;
	pos1->setEstOccupe(false);
	
	jeu->pieceADeplacer = cavalier;
	jeu->getEchequier()->roiEnDanger = false;
	jeu->grille[7][4]->setEstOccupe(true);
	jeu->grille[5][5]->setEstOccupe(false);

	cavalier->seDeplacer(pos1, false);

	EXPECT_EQ(cavalier->getCase() , pos1);

	delete pos;
	delete pos1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete jeu->grille[i][j];
		}
	}
	for (int i = 0; i < jeu->getEchequier()->pieces_.length(); i++) {
		delete jeu->getEchequier()->pieces_[i];
	}
	delete jeu->getEchequier();
	jeu->pieceADeplacer = nullptr;
}

TEST(Echec, DeplacementReine) {

	jeu->dessinerPlateau();
	
	Case *pos = new Case();
	PionVirtuel* reine = new Reine("Blanc");
	pos->positionCase_->i = 7;
	pos->positionCase_->j = 4;
	pos->setEstOccupe(true);
	reine->setCase(pos);

	Case* pos1 = new Case();
	pos1->positionCase_->i = 6;
	pos1->positionCase_->j = 5;
	pos1->setEstOccupe(false);
	
	jeu->pieceADeplacer = reine;
	jeu->getEchequier()->roiEnDanger = false;
	jeu->grille[7][4]->setEstOccupe(true);
	jeu->grille[6][5]->setEstOccupe(false);

	reine->seDeplacer(pos1, false);

	EXPECT_EQ(reine->getCase() , pos1);

	delete pos;
	delete pos1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete jeu->grille[i][j];
		}
	}
	for (int i = 0; i < jeu->getEchequier()->pieces_.length(); i++) {
		delete jeu->getEchequier()->pieces_[i];
	}
	delete jeu->getEchequier();
	jeu->pieceADeplacer = nullptr;
}
TEST(Echec, DeplacementPion) {

	jeu->dessinerPlateau();
	
	Case *pos = new Case();
	PionVirtuel* pion = new Pion("Blanc");
	pos->positionCase_->i = 7;
	pos->positionCase_->j = 4;
	pos->setEstOccupe(true);
	pion->setCase(pos);

	Case* pos1 = new Case();
	pos1->positionCase_->i = 6;
	pos1->positionCase_->j = 4;
	pos1->setEstOccupe(false);
	
	jeu->pieceADeplacer = pion;
	jeu->getEchequier()->roiEnDanger = false;
	jeu->grille[7][4]->setEstOccupe(true);
	jeu->grille[6][4]->setEstOccupe(false);

	pion->seDeplacer(pos1, false);

	EXPECT_EQ(pion->getCase() , pos1);

	delete pos;
	delete pos1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete jeu->grille[i][j];
		}
	}
	for (int i = 0; i < jeu->getEchequier()->pieces_.length(); i++) {
		delete jeu->getEchequier()->pieces_[i];
	}
	delete jeu->getEchequier();
	jeu->pieceADeplacer = nullptr;
}

TEST(Echec, DeplacementFou) {

	jeu->dessinerPlateau();

	Case* pos = new Case();
	PionVirtuel* fou = new Fou("Blanc");
	pos->positionCase_->i = 7;
	pos->positionCase_->j = 4;
	pos->setEstOccupe(true);
	fou->setCase(pos);

	Case* pos1 = new Case();
	pos1->positionCase_->i = 5;
	pos1->positionCase_->j = 6;
	pos1->setEstOccupe(false);

	jeu->pieceADeplacer = fou;
	jeu->getEchequier()->roiEnDanger = false;
	jeu->grille[7][4]->setEstOccupe(true);
	jeu->grille[5][6]->setEstOccupe(false);

	fou->seDeplacer(pos1, false);

	EXPECT_EQ(fou->getCase(), pos1);

	delete pos;
	delete pos1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete jeu->grille[i][j];
		}
	}
	for (int i = 0; i < jeu->getEchequier()->pieces_.length(); i++) {
		delete jeu->getEchequier()->pieces_[i];
	}
	delete jeu->getEchequier();
	jeu->pieceADeplacer = nullptr;
}

TEST(Echec, DeplacementTour) {

	jeu->dessinerPlateau();
	
	Case *pos = new Case();
	PionVirtuel* tour = new Tour("Blanc");
	pos->positionCase_->i = 7;
	pos->positionCase_->j = 4;
	pos->setEstOccupe(true);
	tour->setCase(pos);

	Case* pos1 = new Case();
	pos1->positionCase_->i = 1;
	pos1->positionCase_->j = 4;
	pos1->setEstOccupe(false);
	
	jeu->pieceADeplacer = tour;
	jeu->getEchequier()->roiEnDanger = false;
	jeu->grille[7][4]->setEstOccupe(true);
	jeu->grille[1][4]->setEstOccupe(false);

	tour->seDeplacer(pos1, false);

	EXPECT_EQ(tour->getCase() , pos1);

	delete pos;
	delete pos1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete jeu->grille[i][j];
		}
	}
	for (int i = 0; i < jeu->getEchequier()->pieces_.length(); i++) {
		delete jeu->getEchequier()->pieces_[i];
	}
	delete jeu->getEchequier();
	jeu->pieceADeplacer = nullptr;
}
#endif;