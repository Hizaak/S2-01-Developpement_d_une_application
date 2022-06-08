#include "presentation.h"
#include "chifoumivue.h"

Presentation::Presentation(Chifoumi *m, QObject *parent) : QObject(parent), _leModele(m)
{
    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(majTimer()));
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

    timer->start(1000);
    valeurTimer = lgTimer;

    _laVue->MAJInterface(verificationFinPartie(),
                         _leModele->determinerGagnant(),
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine(),
                         valeurTimer);
}

void Presentation::deroulerUnTour(Chifoumi::UnCoup coupJoueur) {
    _leModele->setCoupJoueur(coupJoueur);
    _leModele->setCoupMachine(_leModele->genererUnCoup());

    // MAJ des scores
    _leModele->majScores(_leModele->determinerGagnant());

    _laVue->MAJInterface(verificationFinPartie(),
                         _leModele->determinerGagnant(),
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine(),
                         valeurTimer);
}

char Presentation::verificationFinPartie(){
    if (_leModele->getScoreJoueur() == pointMax) {
        timer->stop();
        return 'J';
    } else if (_leModele->getScoreMachine() == pointMax){
        timer->stop();
        return 'M';
    } else {
        return 'O';
    }
}

void Presentation::majTimer() {
    char gagnantPartie = 'O'; // "O" signifie que le timer n'est pas finis

    valeurTimer--;

    if (valeurTimer==0) {
        if (_leModele->getScoreJoueur() > _leModele->getScoreMachine()) {
            gagnantPartie = 'J';
        } else if (_leModele->getScoreJoueur() < _leModele->getScoreMachine()) {
            gagnantPartie = 'M';
        } else {
            gagnantPartie = 'N';
        }
        timer->stop();
    } else {
        timer->start(1000);
    }

    _laVue->MAJInterface(gagnantPartie,
                         'O',
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine(),
                         valeurTimer);
}

void Presentation::pauseTimer() {
     if (timer->isActive()) {
         timer->stop();
     } else {
         timer->start();
     }
}

bool Presentation::timerIsActive() {
    return timer->isActive();
}

unsigned int Presentation::getTempsEcoule() {
    return lgTimer - valeurTimer;
}

unsigned int Presentation::getTempsRestant() {
    return valeurTimer;
}

unsigned int Presentation::getLGTimer() {
    return lgTimer;
}

unsigned int Presentation::getPointMax() {
    return pointMax;
}

void Presentation::setLGTimer(unsigned int sec) {
    lgTimer = sec;
}

void Presentation::setPointMax(unsigned int point) {
    pointMax = point;
}


