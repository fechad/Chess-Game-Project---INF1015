/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Controleur.h"
#include <QPixmap>
#include <QDebug>
#include "Pieces.h"
#include "Bouttons.h"
#include "Plateau.h" 
namespace Interface {
    Controleur::Controleur(QWidget* parent) :QGraphicsView(parent) {

        QBrush brush;
        //pieceADeplacer = NULL;

        /*Interface Graphique*/
        interfaceGraphique_ = make_unique<QGraphicsScene>();
        interfaceGraphique_->setSceneRect(0, 0, 1400, 900);
        setFixedSize(1400, 900);
        setScene(interfaceGraphique_.get());
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkCyan);
        setBackgroundBrush(brush);


        /*Texte d'echec*/
        echec = make_unique<QGraphicsTextItem>();
        echec->setPos(1150, 375);
        echec->setFont(QFont("arial", 20));
        echec->setPlainText("Echec!");
        echec->setDefaultTextColor(Qt::red);
        echec->setVisible(false);
    }

    void Controleur::dessinerPlateau() {

        echequier_ = new Plateau();
        echequier_->lancerLaPartie();
        echequier_->dessinerCases(width() / 2 - 400, 50);
    }

    void Controleur::ajouter(QGraphicsItem* item) {

        interfaceGraphique_->addItem(item);
    }

    void Controleur::retirer(QGraphicsItem* item) {

        interfaceGraphique_->removeItem(item);
    }

    void Controleur::changerDeTour() {

        if (getTour() == "Noir") {
            setTour("Blanc");
            joeurActif_->setPlainText("C'est au tour des : Blanc");
        }
        else {
            setTour("Noir");
            joeurActif_->setPlainText("C'est au tour des : Noir");
        }
    }

    void Controleur::partieCommencee() {

        for (size_t i = 0; i < composantesGraphiques_.size(); i++)
            retirer(composantesGraphiques_[i]);

        redemarrage = false;

        /*joueur actif */
        joeurActif_ = make_unique<QGraphicsTextItem>();
        joeurActif_->setPos(width() / 2 - 150, 10);
        joeurActif_->setFont(QFont("arial", 16));
        joeurActif_->setPlainText("C'est au tour des : Blanc");
        joeurActif_->setDefaultTextColor(Qt::white);
        setTour("Blanc");

        joeurActif_->setVisible(true);
        ajouter(joeurActif_.get());
        ajouter(echec.get());
        dessinerPlateau();
        echequier_->dessinerPieces();

        /* Bouton "Abandonner" */
        Boutton* bouttonAbandonner = new Boutton("Abandonner");
        bouttonAbandonner->setPos(1150, 675);
        connect(bouttonAbandonner, SIGNAL(clicked()), this, SLOT(close()));
        ajouter(bouttonAbandonner);
        composantesGraphiques_.append(bouttonAbandonner);

        /* Bouton "Redemarrer" */
        Boutton* bouttonRedemarrer = new Boutton("Redemarrer");
        bouttonRedemarrer->setPos(1150, 775);
        connect(bouttonRedemarrer, SIGNAL(clicked()), this, SLOT(redemarrer()));
        ajouter(bouttonRedemarrer);
        composantesGraphiques_.append(bouttonRedemarrer);
    }

    void Controleur::redemarrer() {
        
        redemarrage = true;
        joeurActif_->setVisible(false);
        echec->setVisible(false);
        setTour("Blanc");
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete grille[i][j];
            }
        }
        delete echequier_;
        selectionCombinaison();
    }

    void Controleur::menuPrincipal(){

        /* Titre */
        QGraphicsTextItem* titre = new QGraphicsTextItem("ChessProject2021");
        QFont margeTitre("arial", 50);
        titre->setFont(margeTitre);
        int posX = width() / 2 - titre->boundingRect().width() / 2;
        titre->setPos(posX, 320);
        ajouter(titre);
        composantesGraphiques_.append(titre);

        /* Bouton "Lancer la Partie" */
        Boutton* bouttonLancerPartie = new Boutton("Lancer la partie");
        bouttonLancerPartie->resize(300, 50);
        posX = width() / 2 - bouttonLancerPartie->boundingRect().width() / 2;
        bouttonLancerPartie->setPos(posX, 600);
        connect(bouttonLancerPartie, SIGNAL(clicked()), this, SLOT(selectionCombinaison()));
        ajouter(bouttonLancerPartie);
        composantesGraphiques_.append(bouttonLancerPartie);

        /* Bouton "Quitter" */
        Boutton* quitButton = new Boutton("Quitter");
        int qxPos = width() / 2 - quitButton->boundingRect().width() / 2;
        int qyPos = 675;
        quitButton->setPos(qxPos, qyPos);
        connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
        ajouter(quitButton);
        //dessinerPlateau();
        composantesGraphiques_.append(quitButton);
    }

    void Controleur::selectionCombinaison() {
        for (size_t i = 0; i < composantesGraphiques_.size(); i++)
            retirer(composantesGraphiques_[i]);

        QGraphicsTextItem* titre = new QGraphicsTextItem("Choix de départ: ");
        QFont margeTitre("arial", 50);
        titre->setFont(margeTitre);
        int posX = width() / 2 - titre->boundingRect().width() / 2;
        titre->setPos(posX, 120);
        ajouter(titre);
        composantesGraphiques_.append(titre);

        /* Bouton "Classique" */
        Boutton* bouttonClassique = new Boutton("Classique");
        bouttonClassique->resize(300, 50);
        posX = width() / 2 - bouttonClassique->boundingRect().width() / 2;
        bouttonClassique->setPos(posX, 500);
        connect(bouttonClassique, SIGNAL(clicked()), this, SLOT(comfirmationCombinaisonClassique()));
        ajouter(bouttonClassique);
        composantesGraphiques_.append(bouttonClassique);

        /* Bouton "Combinaison A" */
        Boutton* bouttonCombinaisonA = new Boutton("Combinaison A");
        bouttonCombinaisonA->resize(300, 50);
        posX = width() / 2 - bouttonCombinaisonA->boundingRect().width() / 2;
        bouttonCombinaisonA->setPos(posX, 575);
        connect(bouttonCombinaisonA, SIGNAL(clicked()), this, SLOT(comfirmationCombinaisonA()));
        ajouter(bouttonCombinaisonA);
        composantesGraphiques_.append(bouttonCombinaisonA);

        /* Bouton "Combinaison B" */
        Boutton* bouttonCombinaisonB = new Boutton("Combinaison B");
        bouttonCombinaisonB->resize(300, 50);
        posX = width() / 2 - bouttonCombinaisonB->boundingRect().width() / 2;
        bouttonCombinaisonB->setPos(posX, 650);
        connect(bouttonCombinaisonB, SIGNAL(clicked()), this, SLOT(comfirmationCombinaisonB()));
        ajouter(bouttonCombinaisonB);
        composantesGraphiques_.append(bouttonCombinaisonB);

        /* Bouton "Quitter" */
        Boutton* quitButton = new Boutton("Quitter");
        int qxPos = width() / 2 - quitButton->boundingRect().width() / 2;
        int qyPos = 825;
        quitButton->setPos(qxPos, qyPos);
        connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
        ajouter(quitButton);
        //dessinerPlateau();
        composantesGraphiques_.append(quitButton);

        combinaisonDepart = " ";
    }

    void Controleur::comfirmationCombinaisonClassique() {

        for (size_t i = 0; i < composantesGraphiques_.size(); i++)
            retirer(composantesGraphiques_[i]);

        QGraphicsTextItem* titre = new QGraphicsTextItem("Combinaison Classique");
        QFont margeTitre("arial", 40);
        titre->setFont(margeTitre);
        int posX = width() / 2 - titre->boundingRect().width() / 2;
        titre->setPos(posX, 30);
        ajouter(titre);
        composantesGraphiques_.append(titre);

        /*Image de la combinaison*/
        QGraphicsPixmapItem* imageCombinaison = new  QGraphicsPixmapItem();
        imageCombinaison->setPixmap(QPixmap("images/combinaisonClassique.png"));
        imageCombinaison->setPos((posX*1.15), 120);
        ajouter(imageCombinaison);
        composantesGraphiques_.append(imageCombinaison);

        /* Bouton "Confirmer" */
        Boutton* bouttonConfirmer = new Boutton("Confirmer");
        bouttonConfirmer->resize(300, 50);
        posX = width() / 2 - bouttonConfirmer->boundingRect().width() / 2;
        bouttonConfirmer->setPos(posX, 750);
        connect(bouttonConfirmer, SIGNAL(clicked()), this, SLOT(partieCommencee()));
        ajouter(bouttonConfirmer);
        composantesGraphiques_.append(bouttonConfirmer);

        /* Bouton "Annuler" */
        Boutton* bouttonAnnuler = new Boutton("Annuler");
        posX = width() / 2 - bouttonAnnuler->boundingRect().width() / 2;
        bouttonAnnuler->setPos(posX, 825);
        connect(bouttonAnnuler, SIGNAL(clicked()), this, SLOT(selectionCombinaison()));
        ajouter(bouttonAnnuler);
        composantesGraphiques_.append(bouttonAnnuler);

        combinaisonDepart = "combinaison Classique";

    }

    void Controleur::comfirmationCombinaisonA() {
        for (size_t i = 0; i < composantesGraphiques_.size(); i++)
            retirer(composantesGraphiques_[i]);

        QGraphicsTextItem* titre = new QGraphicsTextItem("Combinaison A");
        QFont margeTitre("arial", 40);
        titre->setFont(margeTitre);
        int posX = width() / 2 - titre->boundingRect().width() / 2;
        titre->setPos(posX, 30);
        ajouter(titre);
        composantesGraphiques_.append(titre);

        /*Image de la combinaison*/
        QGraphicsPixmapItem* imageCombinaison = new  QGraphicsPixmapItem();
        imageCombinaison->setPixmap(QPixmap("images/combinaisonA.png"));
        imageCombinaison->setPos((posX/1.2), 120);
        ajouter(imageCombinaison);
        composantesGraphiques_.append(imageCombinaison);

        /* Bouton "Confirmer" */
        Boutton* bouttonConfirmer = new Boutton("Confirmer");
        bouttonConfirmer->resize(300, 50);
        posX = width() / 2 - bouttonConfirmer->boundingRect().width() / 2;
        bouttonConfirmer->setPos(posX, 750);
        connect(bouttonConfirmer, SIGNAL(clicked()), this, SLOT(partieCommencee()));
        ajouter(bouttonConfirmer);
        composantesGraphiques_.append(bouttonConfirmer);

        /* Bouton "Annuler" */
        Boutton* bouttonAnnuler = new Boutton("Annuler");
        posX = width() / 2 - bouttonAnnuler->boundingRect().width() / 2;
        bouttonAnnuler->setPos(posX, 825);
        connect(bouttonAnnuler, SIGNAL(clicked()), this, SLOT(selectionCombinaison()));
        ajouter(bouttonAnnuler);
        composantesGraphiques_.append(bouttonAnnuler);

        combinaisonDepart = "combinaison A";

    }

    void Controleur::comfirmationCombinaisonB() {
        for (size_t i = 0; i < composantesGraphiques_.size(); i++)
            retirer(composantesGraphiques_[i]);

        QGraphicsTextItem* titre = new QGraphicsTextItem("Combinaison B");
        QFont margeTitre("arial", 40);
        titre->setFont(margeTitre);
        int posX = width() / 2 - titre->boundingRect().width() / 2;
        titre->setPos(posX, 30);
        ajouter(titre);
        composantesGraphiques_.append(titre);

        /*Image de la combinaison*/
        QGraphicsPixmapItem* imageCombinaison = new  QGraphicsPixmapItem();
        imageCombinaison->setPixmap(QPixmap("images/combinaisonB.png"));
        imageCombinaison->setPos((posX/1.2 ), 120);
        ajouter(imageCombinaison);
        composantesGraphiques_.append(imageCombinaison);

        /* Bouton "Confirmer" */
        Boutton* bouttonConfirmer = new Boutton("Confirmer");
        bouttonConfirmer->resize(300, 50);
        posX = width() / 2 - bouttonConfirmer->boundingRect().width() / 2;
        bouttonConfirmer->setPos(posX, 750);
        connect(bouttonConfirmer, SIGNAL(clicked()), this, SLOT(partieCommencee()));
        ajouter(bouttonConfirmer);
        composantesGraphiques_.append(bouttonConfirmer);

        /* Bouton "Annuler" */
        Boutton* bouttonAnnuler = new Boutton("Annuler");
        posX = width() / 2 - bouttonAnnuler->boundingRect().width() / 2;
        bouttonAnnuler->setPos(posX, 825);
        connect(bouttonAnnuler, SIGNAL(clicked()), this, SLOT(selectionCombinaison()));
        ajouter(bouttonAnnuler);
        composantesGraphiques_.append(bouttonAnnuler);

        combinaisonDepart = "combinaison B";

    }
}