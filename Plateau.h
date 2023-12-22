#ifndef PLATEAU_H
#define PLATEAU_H
/*
* Groupe: 02
* Chatelier, Fedwin, 2104132
* Haidara, Mohamed, 2004322
* Yapmi Nji Monluh, Nemro, 2005582
*/
#include <QString>
#include <QList>
#include <QSet>
#include <set>

namespace Modele {
    class PionVirtuel;
    class Case;
    class Plateau
    {
    public:
        Plateau();
        ~Plateau() {

            for (int i = 0; i < corbeille_.length(); i++) {
                delete corbeille_[i];
            }
            for (int i = 0; i < pieces_.length(); i++) {
                pieces_.removeAt(i);
            }
        }
        void dessinerCases(int x, int y);
        void lancerLaPartie();
        void dessinerPieces();
        QList<QList<QString>> grille_;
        void tuer(Case* caseDuPion);
        void ajouterPiece(QString couleur, QString nom);
        void attaquerRoi();
        void verification(Case* caseAVerifier, Case* caseDepart, PionVirtuel* pion);
        void combinaisonB();
        void combinaisonA();

        QList <PionVirtuel*> pieces_;
        bool roiEnDanger;
        bool unsafe;
    private:
        QList<Case*> corbeille_;
    };
}
#endif // !PLATEAU_H