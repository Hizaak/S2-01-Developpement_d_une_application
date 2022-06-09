#include "presentation.h"
#include "chifoumivue.h"

#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlRecord>
#include <QVariant>
#include <QSqlError>

/// Constructeur

Presentation::Presentation(Chifoumi *m, QObject *parent) : QObject(parent), _leModele(m)
{

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS informationPartieDMT ("
               "id INTEGER(4) PRIMARY KEY, "
               "horodatage DATETIME, "
               "nomJoueurHumain VARCHAR(80), "
               "nbrPointJoueur INTEGER(255), "
               "nbrPointMachine INTEGER(255), "
               "tempsEcoule INTEGER(255), "
               "typeVictoire VARCHAR(5) "
               "CHECK (typeVictoire in ('temps','point')));");

    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(majTimer()));
}

/// Get

Chifoumi *Presentation::getModele()
{
    return _leModele;
}

ChifoumiVue *Presentation::getVue()
{
    return _laVue;
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

/// Set

void Presentation::setModele(Chifoumi *m)
{
    _leModele = m;
}

void Presentation::setVue(ChifoumiVue *v)
{
    _laVue = v;
}

void Presentation::setLGTimer(unsigned int sec) {
    lgTimer = sec;
}

void Presentation::setPointMax(unsigned int point) {
    pointMax = point;
}

/// Autre

void Presentation::insertGameInformation(QString nomJoueur, unsigned int ptJoueur, unsigned int ptMachine, unsigned int tpsEcoule, QString typeVictoire) {

    // Obtention du nombre d'enregistrement de la table informationPartieDMT
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM informationPartieDMT;");

    // Obtention de la prochaine clef primaire à utiliser
    query.next();
    int id = query.value(0).toInt();

    query.exec("INSERT INTO informationPartieDMT VALUES ("+QString::number(id)+", CURRENT_TIMESTAMP  , '"+nomJoueur+"',"+QString::number(ptJoueur)+","+QString::number(ptMachine)+","+QString::number(tpsEcoule)+",'"+typeVictoire+"');");
}

void Presentation::reinitialiser() {
    // Réinitialisation des scores et des coups
    _leModele->initCoups();
    _leModele->initScores();

    // Réinitialisation du timer
    timer->start(1000);
    valeurTimer = lgTimer;

    // Mise à jour de la vue
    _laVue->MAJInterface(verificationFinPartie(),
                         _leModele->determinerGagnant(),
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine(),
                         valeurTimer);
}

void Presentation::deroulerUnTour(Chifoumi::UnCoup coupJoueur) {
    // Transmission au modele des coups
    _leModele->setCoupJoueur(coupJoueur);
    _leModele->setCoupMachine(_leModele->genererUnCoup());

    // Mise à jour des scores
    _leModele->majScores(_leModele->determinerGagnant());

    // Mise à jour de la vue
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
        // Arret du timer
        timer->stop();

        // Enregistrement des infos de la partie dans la base de données
        insertGameInformation(_laVue->getNomJoueur(), _leModele->getScoreJoueur(), _leModele->getScoreMachine(),getTempsEcoule(), "point");
        return 'J';
    } else if (_leModele->getScoreMachine() == pointMax){
        // Arret du timer
        timer->stop();

        // Enregistrement des infos de la partie dans la base de données
        insertGameInformation(_laVue->getNomJoueur(), _leModele->getScoreJoueur(), _leModele->getScoreMachine(),getTempsEcoule(), "point");
        return 'M';
    } else {
        return 'O'; // "O" signifie que le timer n'est pas finis
    }
}

void Presentation::majTimer() {
    char gagnantPartie = 'O'; // "O" signifie que le timer n'est pas finis

    valeurTimer--;

    if (valeurTimer==0) {
        // Determiner le gagnant
        if (_leModele->getScoreJoueur() > _leModele->getScoreMachine()) {
            gagnantPartie = 'J';
        } else if (_leModele->getScoreJoueur() < _leModele->getScoreMachine()) {
            gagnantPartie = 'M';
        } else {
            gagnantPartie = 'N';
        }

        // Enregistrement des infos de la partie dans la base de données
        insertGameInformation(_laVue->getNomJoueur(), _leModele->getScoreJoueur(), _leModele->getScoreMachine(),getTempsEcoule(), "temps");

        // Arret du timer
        timer->stop();
    } else {
        timer->start(1000);
    }

    // Mise à jour de la vue
    _laVue->MAJInterface(gagnantPartie,
                         'O',
                         _leModele->getCoupJoueur(),
                         _leModele->getCoupMachine(),
                         _leModele->getScoreJoueur(),
                         _leModele->getScoreMachine(),
                         valeurTimer);
}

void Presentation::pauseTimer() {
    // Changement d'état du timer
     if (timer->isActive()) {
         timer->stop();
     } else {
         timer->start();
     }
}

bool Presentation::timerIsActive() {
    // Indique si le timer est actif
    return timer->isActive();
}

