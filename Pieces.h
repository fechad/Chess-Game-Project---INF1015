#ifndef PIECES_H
#define PIECES_H
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include "Controleur.h"
#include "PionVirtuel.hpp"
namespace Modele {
    using namespace Interface;
    class Case;

    class Roi :public PionVirtuel
    {
    public:
        Roi(QString couleur);
        ~Roi() override { nombreDeRoi-=1;}
        void setImage() override;
        void seDeplacer(Case* newPos, bool pretend) override;
        void verifierNombreInstanceRoi();
        inline static int nombreDeRoi = 0;
    };

    class Reine :public PionVirtuel
    {
    public:
        Reine(QString couleur);
        void setImage() override;
        void seDeplacer(Case* newPos, bool pretend) override;
    };

    class Fou :public PionVirtuel
    {
    public:
        Fou(QString couleur);
        void setImage() override;
        void seDeplacer(Case* newPos, bool pretend) override;
    };

    class Tour :public PionVirtuel
    {
    public:
        Tour(QString couleur);
        void setImage() override;
        void seDeplacer(Case* newPos, bool pretend) override;
    };

    class Cavalier :public PionVirtuel
    {
    public:
        Cavalier(QString couleur);
        void setImage() override;
        void seDeplacer(Case* newPos, bool pretend) override;
    };

    class Pion :public PionVirtuel
    {
    public:
        Pion(QString couleur);
        void setImage() override;
        void seDeplacer(Case* newPos, bool pretend) override;
    };
}
#endif // !PIECES_H