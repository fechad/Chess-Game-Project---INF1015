/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Controleur.h"
#include "Case.h"
#include "PionVirtuel.hpp"
#include "Plateau.h"
#include "Pieces.h"
#include <QDebug>
#include <typeinfo>

extern Interface::Controleur* jeu;
namespace Modele {
	PionVirtuel::PionVirtuel(QString couleur) {

		couleur_ = couleur;
		estVivant_ = true;
		firstMove = true;
	}

	Case* PionVirtuel::getCase() {

		return caseActuel_;
	}
}

