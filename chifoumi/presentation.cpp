#include "presentation.h"
#include "chifoumivue.h"
#include "database.h"

#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlRecord>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Presentation::Presentation(Chifoumi *m, Database *db, QObject *parent) : QObject(parent), _leModele(m), db(db)
{
    db->openDataBase();

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

void Presentation::insertGameInformation(QString nomJoueur, unsigned int ptJoueur, unsigned int ptMachine, unsigned int tpsEcoule, QString typeVictoire) {
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM informationPartieDMT;");

    query.next();
    int id = query.value(0).toInt();

    query.exec("INSERT INTO informationPartieDMT VALUES ("+QString::number(id)+", CURRENT_TIMESTAMP  , '"+nomJoueur+"',"+QString::number(ptJoueur)+","+QString::number(ptMachine)+","+QString::number(tpsEcoule)+",'"+typeVictoire+"');");
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
        insertGameInformation(_laVue->getNomJoueur(), _leModele->getScoreJoueur(), _leModele->getScoreMachine(),getTempsEcoule(), "point");
        return 'J';
    } else if (_leModele->getScoreMachine() == pointMax){
        timer->stop();
        insertGameInformation(_laVue->getNomJoueur(), _leModele->getScoreJoueur(), _leModele->getScoreMachine(),getTempsEcoule(), "point");
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
        insertGameInformation(_laVue->getNomJoueur(), _leModele->getScoreJoueur(), _leModele->getScoreMachine(),getTempsEcoule(), "temps");
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

