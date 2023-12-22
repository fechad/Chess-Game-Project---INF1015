/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Pieces.h"
#include "Controleur.h"
#include "Case.h"
#include "Plateau.h"
#include <typeinfo>

/*Voir ReadMe pour la source des images et l'inspiration des méthodes setImage()*/

extern Interface::Controleur* jeu;

namespace Modele {
	
	Roi::Roi(QString couleur) {

		couleur_ = couleur;
		verifierNombreInstanceRoi();
		image = new QGraphicsPixmapItem();
		setImage();
		nombreDeRoi++;
	}
	void Roi::verifierNombreInstanceRoi() {
		
		if (nombreDeRoi > 2) {
			throw logic_error("On ne peut pas avoir plus de 2 Roi sur le plateu !!");
		}
	}

	void Roi::setImage() {

		if (couleur_ == "Blanc") {
			image->setPixmap(QPixmap("images/RoiB.png"));
		}
		else {
			image->setPixmap(QPixmap("images/RoiN.png"));
		}
	}
	
	Fou::Fou(QString couleur) {

		couleur_ = couleur;
		image = new QGraphicsPixmapItem();
		setImage();
	}

	void Fou::setImage() {

		if (couleur_ == "Blanc") {
			image->setPixmap(QPixmap("images/FouB.png"));
		}
		else {
			image->setPixmap(QPixmap("images/FouN.png"));
		}
	}

	Tour::Tour(QString couleur) {

		couleur_ = couleur;
		image = new QGraphicsPixmapItem();
		setImage();
	}

	void Tour::setImage() {

		if (couleur_ == "Blanc") {
			image->setPixmap(QPixmap("images/TourB.png"));
		}
		else {
			image->setPixmap(QPixmap("images/TourN.png"));
		}
	}

	Reine::Reine(QString couleur) {

		couleur_ = couleur;
		image = new QGraphicsPixmapItem();
		setImage();
	}

	void Reine::setImage() {

		if (couleur_ == "Blanc") {
			image->setPixmap(QPixmap("images/ReineB.png"));
		}
		else {
			image->setPixmap(QPixmap("images/ReineN.png"));
		}
	}

	Cavalier::Cavalier(QString couleur) {

		couleur_ = couleur;
		image = new QGraphicsPixmapItem();
		setImage();
	}

	void Cavalier::setImage() {

		if (couleur_ == "Blanc") {
			image->setPixmap(QPixmap("images/CavalierB.png"));
		}
		else {
			image->setPixmap(QPixmap("images/CavalierN.png"));
		}
	}

	Pion::Pion(QString couleur) {

		couleur_ = couleur;
		image = new QGraphicsPixmapItem();
		setImage();
		firstMove = true;
	}

	void Pion::setImage() {

		if (couleur_ == "Blanc") {
			image->setPixmap(QPixmap("images/PionB.png"));
		}
		else {
			image->setPixmap(QPixmap("images/PionN.png"));
		}
	}

	void Roi::seDeplacer(Case* newPos, bool pretend) {
		
		int row = this->getCase()->positionCase_->i;
		int col = this->getCase()->positionCase_->j;
		QString team = this->getCouleur();
		bool possible = false;

		if (-1 <= (newPos->positionCase_->i - row) && (newPos->positionCase_->i - row) <= 1) {
			if (-1 <= (newPos->positionCase_->j - col) && (newPos->positionCase_->j - col) <= 1) {
				if (newPos->getEstOccupe() == false ) {
					if (pretend == true) {
						jeu->echec->setVisible(true);
						newPos->setCouleurPinceau(Qt::yellow);
						return;
					}
					possible = true;
				}
				if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->piece_->getCouleur() != this->couleur_) {
						possible = true;
						if (pretend == false) { jeu->getEchequier()->tuer(newPos); }
					}
					else { possible = false; }
				}
			}
			if ((possible == true) && (pretend == false)) {
				jeu->pieceADeplacer->getCase()->setEstOccupe(false);
				jeu->pieceADeplacer->getCase()->piece_ = NULL;
				jeu->pieceADeplacer->getCase()->resetCouleur();
				newPos->placerPiece(jeu->pieceADeplacer);
				if (jeu->getEchequier()->roiEnDanger == true) {
					jeu->getEchequier()->roiEnDanger = false;
					jeu->echec->setVisible(false);
				}
			}
		}
		if ((pretend == false) && (possible == false )) {
			jeu->pieceADeplacer->getCase()->setCouleurPinceau(Qt::darkRed);
		}
	}

	void Reine::seDeplacer(Case* newPos, bool pretend) {

		int row = this->getCase()->positionCase_->i;
		int col = this->getCase()->positionCase_->j;
		QString team = this->getCouleur();
		bool possible = true;
		bool tuer = false;

		int i = newPos->positionCase_->i;
		int j = newPos->positionCase_->j;


		if (i == row) {//si position de départ est sur la même ligne que la positin finale 
			if (col < j) {
				for (int k = col + 1; k <= j; k++) {
					if ((k != j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						if (jeu->grille[i][k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}

				}
			}
			else {
				for (int k = col - 1; k >= j; k--) {
					if ((k != j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						if (jeu->grille[i][k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}
				}
			}

		}
		else if (i < row) {// si position de départ est n'est pas sur la même ligne qe la position final et le déplacement est vertical vers le haut
			if (j == col) {
				for (int k = row - 1; k >= i; k--) {
					if ((k != i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						if (jeu->grille[k][j]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}

				}
			}
			else if (j - col > 0) {//deplacement diagonale secondaire vers le haut
				int k = 0;
				while (true) {
					++k;
					//--w;
					if ((col + k != j) && (jeu->grille[row - k][col + k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((col + k == j) && (jeu->grille[row - k][col + k]->getEstOccupe() == true)) {
						if (jeu->grille[row-k][col+k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}
					else if ((col + k) >= j) { break; }//on sort de la boucle si on a dépassé la limite
				}
			}
			else {//déplacement diagonale principale vers le haute  col > j

				int k = 0;
				while (true) {
					++k;
					if ((col - k != j) && (jeu->grille[row - k][col - k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((col - k == j) && (jeu->grille[row - k][col - k]->getEstOccupe() == true)) {
						if (jeu->grille[row-k][col-k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}
					else if ((col - k) <= j) { break; }//on sort de la boucle si on a dépassé la limite
				}
			}
		}
		else if (i > row) {// si position de départ est n'est pas sur la même ligne qe la position final et le déplacement est vertical vers le bas
			if (j == col) {
				for (int k = row + 1; k <= i; k++) {
					if ((k != i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						if (jeu->grille[k][j]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}
				}
			}
			else if (j - col > 0) {//deplacement diagonale principale vers le bas   j > col
				int k = 0;
				while (true) {
					++k;
					//--w;
					if ((col + k != j) && (jeu->grille[row + k][col + k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((col + k == j) && (jeu->grille[row + k][col + k]->getEstOccupe() == true)) {
						if (jeu->grille[row + k][col + k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}
					else if ((col + k) >= j) { break; }//on sort de la boucle si on a dépassé la limite
				}
			}
			else {//déplacement diagonale secondaire vers le bas  col > j

				int k = 0;
				while (true) {
					++k;
					if ((col - k != j) && (jeu->grille[row + k][col - k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((col - k == j) && (jeu->grille[row + k][col - k]->getEstOccupe() == true)) {
						
						if (jeu->grille[row + k][col - k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						else { possible = false; }
						break;
					}
					else if ((col - k) >= j) { break; }//on sort de la boucle si on a dépassé la limite
				}
			}
		}

		if ((abs(i - row) != abs(j - col)) && i != row && j != col) //si le déplacement n'est ni diogonal ni vertical, ni horizontal
			possible = false;

		if ((pretend == true) && (possible == true) && (team != newPos->getCouleurPiece())) {
			jeu->echec->setVisible(true);
			newPos->setCouleurPinceau(Qt::yellow);
			return;
		}
		else if (((tuer == true)||(possible == true)) && (pretend == false)) {

			if(tuer == true){ jeu->getEchequier()->tuer(newPos); }

			jeu->pieceADeplacer->getCase()->setEstOccupe(false);
			jeu->pieceADeplacer->getCase()->piece_ = NULL;
			jeu->pieceADeplacer->getCase()->resetCouleur();
			newPos->placerPiece(jeu->pieceADeplacer);

		}
		if (pretend == false && possible == false) {
			jeu->pieceADeplacer->getCase()->setCouleurPinceau(Qt::darkRed);
		}
	}

	void Fou::seDeplacer(Case* newPos, bool pretend) {

		bool possible = true;
		bool tuer = false;
		int row = this->getCase()->positionCase_->i;
		int col = this->getCase()->positionCase_->j;
		QString team = this->getCouleur();

		if ((row == newPos->positionCase_->i) || (col == newPos->positionCase_->j)) {
			possible = false;
		}
		else if ((row - newPos->positionCase_->i) != -(col - newPos->positionCase_->j)) {

			possible = false;
		}
		if ((row - newPos->positionCase_->i) == (col - newPos->positionCase_->j)) {

			possible = true;
		}
		if ((possible == true) || (row - newPos->positionCase_->i) == (col - newPos->positionCase_->j)) {
			if (row < newPos->positionCase_->i) {
				for (int i = (row + 1); i < newPos->positionCase_->i; i++) {
					if (col < newPos->positionCase_->j) {
						int j = (col + 1);
						if (jeu->grille[i][j]->getEstOccupe() == true) {
							possible = false;
						}
						col += 1;
					}
					else if (col > newPos->positionCase_->j) {
						int j = (col - 1);
						if (jeu->grille[i][j]->getEstOccupe() == true) {
							possible = false;
						}
						col -= 1;
					}
				}
			}
			else if (row > newPos->positionCase_->i) {
				for (int i = (row - 1); i > newPos->positionCase_->i; i--) {
					if (col < newPos->positionCase_->j) {
						int j = (col + 1);
						if (jeu->grille[i][j]->getEstOccupe() == true) {
							possible = false;
						}
						col += 1;
					}
					else if (col > newPos->positionCase_->j) {
						int j = (col - 1);
						if (jeu->grille[i][j]->getEstOccupe() == true) {
							possible = false;
						}
						col -= 1;
					}
				}
			}
			if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
				if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->piece_->getCouleur() != this->couleur_) {
					tuer = true;
					if ((pretend == false) && (possible == true)) { jeu->getEchequier()->tuer(newPos); }
				}
				else { possible = false; }
			}
			if ((pretend == true) && (possible == true ) && (tuer == true)) {
				jeu->echec->setVisible(true);
				newPos->setCouleurPinceau(Qt::yellow);
				return;
			}
		}
		if ((possible == true) && (pretend == false)) {
			jeu->pieceADeplacer->getCase()->setEstOccupe(false);
			jeu->pieceADeplacer->getCase()->piece_ = NULL;
			jeu->pieceADeplacer->getCase()->resetCouleur();
			newPos->placerPiece(jeu->pieceADeplacer);
		}
		else if ((pretend == false)&&(possible == false)) {
			jeu->pieceADeplacer->getCase()->setCouleurPinceau(Qt::darkRed);
		}
	}
	
	void Tour::seDeplacer(Case* newPos, bool pretend) {

		int row = this->getCase()->positionCase_->i;
		int col = this->getCase()->positionCase_->j;
		QString team = this->getCouleur();
		bool possible = true;
		bool tuer = false;

		int i = newPos->positionCase_->i;
		int j = newPos->positionCase_->j;


		if (i == row) {//si position de départ est sur la même ligne que la positin finale 
			if (col < j) {
				for (int k = col + 1; k <= j; k++) {
					if ((k != j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						if (jeu->grille[i][k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						break;
					}

				}
			}
			else {
				for (int k = col - 1; k >= j; k--) {
					if ((k != j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == j) && (jeu->grille[i][k]->getEstOccupe() == true)) {
						if (jeu->grille[i][k]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						break;
					}
				}
			}

		}
		else if (i < row) {// si position de départ est n'est pas sur la même ligne qe la position final et le déplacement est vertical vers le haut
			if (j == col) {
				for (int k = row - 1; k >= i; k--) {
					if ((k != i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						if (jeu->grille[k][j]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						break;
					}

				}
			}
		}
		else if (i > row) {// si position de départ est n'est pas sur la même ligne qe la position final et le déplacement est vertical vers le bas
			if (j == col) {
				for (int k = row + 1; k <= i; k++) {
					if ((k != i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						possible = false;
						break;
					}
					else if ((k == i) && (jeu->grille[k][j]->getEstOccupe() == true)) {
						if (jeu->grille[k][j]->piece_->getCouleur() != this->couleur_) {
							tuer = true;
						}
						break;
					}
				}
			}
		}

		if (i != row && j != col) //si le déplacement ni vertical, ni horizontal
			possible = false;
		if ((newPos->getEstOccupe() == true) &&(tuer == false) && (jeu->grille[i][j]->piece_->getCouleur() == this->couleur_))
			possible = false;

		if ((pretend == true) && (possible == true)) {
			jeu->echec->setVisible(true);
			newPos->setCouleurPinceau(Qt::yellow);
			return;
		}
		else if ((possible == true) && (pretend == false)) {

			if (tuer == true) { jeu->getEchequier()->tuer(newPos); }

			jeu->pieceADeplacer->getCase()->setEstOccupe(false);
			jeu->pieceADeplacer->getCase()->piece_ = NULL;
			jeu->pieceADeplacer->getCase()->resetCouleur();
			newPos->placerPiece(jeu->pieceADeplacer);

		}
		if (pretend == false && possible == false) {
			jeu->pieceADeplacer->getCase()->setCouleurPinceau(Qt::darkRed);
		}

	}

	void Cavalier::seDeplacer(Case* newPos, bool pretend) {

		bool possible = false;
		int row = this->getCase()->positionCase_->i;
		int col = this->getCase()->positionCase_->j;

		if (((col + 2 < 8) || (col - 2 >= 0) || (col + 1 < 8) || (col - 1 >= 0))
			&&
			((row + 2 < 8) || (row - 2 >= 0) || (col + 1 < 8) || (row - 1 >= 0)))
		{
			int i = newPos->positionCase_->i;
			int j = newPos->positionCase_->j;
			if (((col + 2 == j) && (row - 1 == i || row + 1 == i))
				|| ((col - 2 == j) && (row - 1 == i || row + 1 == i))
				|| ((col + 1 == j) && (row - 2 == i || row + 2 == i))
				|| ((col - 1 == j) && (row - 2 == i || row + 2 == i)))
			{

				if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == false) {
					possible = true;
				}
				if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->piece_->getCouleur() != this->couleur_) {
						possible = true;
						if (pretend == true) {
							jeu->echec->setVisible(true);
							newPos->setCouleurPinceau(Qt::yellow);
							return;
						}
						if (pretend == false) { jeu->getEchequier()->tuer(newPos); }
					}
					else { possible = false; }
				}
			}
			
		}
		if ((possible == true) && (pretend == false)) {

			jeu->pieceADeplacer->getCase()->setEstOccupe(false);
			jeu->pieceADeplacer->getCase()->piece_ = NULL;
			jeu->pieceADeplacer->getCase()->resetCouleur();
			newPos->placerPiece(jeu->pieceADeplacer);
		}
		if ((pretend == false) && (possible == false)) {
			jeu->pieceADeplacer->getCase()->setCouleurPinceau(Qt::darkRed);
		}

	}

	void Pion::seDeplacer(Case* newPos, bool pretend) {

		bool possible = false;
		int row = this->getCase()->positionCase_->i;
		int col = this->getCase()->positionCase_->j;
		QString team = this->getCouleur();
		bool tuer = false;
		int i = newPos->positionCase_->i;
		int j = newPos->positionCase_->j;

		if ((firstMove == true) && (col == j) && ((row - i == 2) || (i - row == 2))) {
			
			if ((col == newPos->positionCase_->j)) {
				if ((row - newPos->positionCase_->i == 1) || (row - newPos->positionCase_->i == 2)) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == false) {
						possible = true;
					}
				}
				else if ((row - newPos->positionCase_->i == -1) || (row - newPos->positionCase_->i == -2)) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == false) {
						possible = true;
					}
				}
			}
			else if (((newPos->positionCase_->j - col == 1) || (newPos->positionCase_->j - col == -1))) {
				if (((newPos->positionCase_->i - row == 1) || (newPos->positionCase_->i - row == -1))) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
						tuer = true;
					}
				}
			}
			if ((team == "Blanc")&&(pretend == false) && (jeu->grille[i + 1][j]->getEstOccupe() == false)) {
				possible = true;
			}
			else if ((team == "Noir") && (pretend == false) && (jeu->grille[i - 1][j]->getEstOccupe() == false)) {
				possible = true;
			}
			else { possible = false; }
		}
		else {
			if (getCouleur() == "Noir") {
				if ((col == newPos->positionCase_->j) && (row - newPos->positionCase_->i == -1)) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == false) {
						possible = true;
					}
				}
				else if (((newPos->positionCase_->j - col == 1) || (newPos->positionCase_->j - col == -1))) {
					if ((row - newPos->positionCase_->i == -1)) {
						if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
							tuer = true;
						}
					}
				}
			}
			else {
				if ((col == newPos->positionCase_->j) && (row - newPos->positionCase_->i == 1)) {
					if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == false) {
						possible = true;
					}
				}
				else if (((newPos->positionCase_->j - col == 1) || (newPos->positionCase_->j - col == -1))) {
					if ((row - newPos->positionCase_->i == 1)) {
						if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
							tuer = true;
						}
					}
				}
			}
		}
		
		if (tuer == true) {
			if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->getEstOccupe() == true) {
				if (jeu->grille[newPos->positionCase_->i][newPos->positionCase_->j]->piece_->getCouleur() != this->couleur_) {
					possible = true;
					if (pretend == false) { jeu->getEchequier()->tuer(newPos); }
				}
				else { possible = false; }
			}
		}
		if ((pretend == true) && (possible == true)) {
			if (team == newPos->getCouleurPiece()) { return; }
			jeu->echec->setVisible(true);
			newPos->setCouleurPinceau(Qt::yellow);
			return;
		}
		if (((possible == true) || (tuer == true)) && (pretend == false)) {
			if(this->caseActuel_ != newPos) {
				firstMove = false;
			}
			jeu->pieceADeplacer->getCase()->setEstOccupe(false);
			jeu->pieceADeplacer->getCase()->piece_ = NULL;
			jeu->pieceADeplacer->getCase()->resetCouleur();
			newPos->placerPiece(jeu->pieceADeplacer);
		}
		if (pretend == false && possible == false) {
			jeu->pieceADeplacer->getCase()->setCouleurPinceau(Qt::darkRed);
		}
	}

}