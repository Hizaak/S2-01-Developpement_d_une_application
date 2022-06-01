/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe métier (= modèle) Chifoumi-v1
 **************************************************************/
#include "modele.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MODèLE ---------------------------

Chifoumi::Chifoumi()
{
    //ctor
    // partie modèle
    initCoups();
    initScores();
}

Chifoumi::~Chifoumi()
{
    //dtor
}

        /// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
    return (*this).coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return (*this).coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return (*this).scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return (*this).scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner='N';


    // avant de commencer : match nul
    if (coupJoueur==pierre && coupMachine==papier){gagnantARetourner = 'M';}
    else if (coupMachine==pierre && coupJoueur==papier){gagnantARetourner = 'J';}

    else if (coupJoueur==pierre && coupMachine==ciseau){gagnantARetourner = 'J';}
    else if (coupMachine==pierre && coupJoueur==ciseau){gagnantARetourner = 'M';}

    else if (coupJoueur==papier && coupMachine==ciseau){gagnantARetourner = 'M';}
    else if (coupMachine==papier && coupJoueur==ciseau){gagnantARetourner = 'J';}

    else {gagnantARetourner = 'N';}

    return gagnantARetourner;
}

         ///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max){
    /* pré-condition : min<max ;
       Le nbre aléatoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    int numCoup;

    numCoup = randMinMax(0,3);

    switch (numCoup) {
    case 0:
        valeurGeneree = ciseau;
        break;
    case 1:
        valeurGeneree = pierre;
        break;
    case 2:
        valeurGeneree = papier;
        break;
    }
    return valeurGeneree;
}

        /// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    (*this).coupJoueur = p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    (*this).coupMachine = p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    (*this).scoreJoueur = p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    (*this).scoreMachine = p_score;
}

void Chifoumi::majScores(char p_gagnant) {
    switch (p_gagnant) {
        case 'J':
            (*this).scoreJoueur ++;
            break;
        case 'M':
            (*this).scoreMachine ++;
            break;
    }
}

void Chifoumi::initScores() {
    (*this).scoreJoueur = 0;
    (*this).scoreMachine = 0;
}

void Chifoumi::initCoups() {
    (*this).coupMachine = rien;
    (*this).coupJoueur = rien;
}
