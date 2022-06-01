#include "presentation.h"
#include "chifoumivue.h"

Presentation::Presentation(Chifoumi *m, QObject *parent) : QObject(parent), _leModele(m)
{

}

Chifoumi *Presentation::getModele()
{
    return _leModele;
}

ChifoumiVue *Presentation::getVue()
{
    return _laVue;
}

void Presentation::setModele(Chifoumi *m)
{
    _leModele = m;
}

void Presentation::setVue(ChifoumiVue *v)
{
    _laVue = v;
}


void Presentation::reinitialiser() {
    _leModele->initCoups();
    _leModele->initScores();

    _laVue->MAJInterface(_leModele->determinerGagnant(),
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine());
}

void Presentation::deroulerUnTour(Chifoumi::UnCoup coupJoueur) {
    _leModele->setCoupJoueur(coupJoueur);
    _leModele->setCoupMachine(_leModele->genererUnCoup());

    // MAJ des scores
    _leModele->majScores(_leModele->determinerGagnant());

    _laVue->MAJInterface(_leModele->determinerGagnant(),
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine());
}



