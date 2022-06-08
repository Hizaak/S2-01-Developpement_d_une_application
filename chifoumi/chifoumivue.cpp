#include "chifoumivue.h"
#include "presentation.h"
#include "ui_chifoumivue.h"

#include <QPixmap>
#include <iostream>
#include <QMessageBox>

using namespace std;

/// ================== METHODES PUBLIQUES ==================

// Constructeurs
ChifoumiVue::ChifoumiVue(Presentation *p, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
    , _laPresentation(p)
{
    ui->setupUi(this);

    this->setWindowTitle("SAE 2.01 - version 5");

    // Ouverture et affichage des images des figures dans les boutons.
    ui->boutonCiseau->setIcon(ressourceCiseau);
    ui->boutonPierre->setIcon(ressourcePierre);
    ui->boutonPapier->setIcon(ressourcePapier);

    // Connexion entre les differentes boutons et les slots à executer
    connect(ui->boutonCiseau, SIGNAL(clicked()), this,  SLOT(jouerCiseau()));
    connect(ui->boutonPapier, SIGNAL(clicked()), this, SLOT(jouerPapier()));
    connect(ui->boutonPierre, SIGNAL(clicked()), this, SLOT(jouerPierre()));
    connect(ui->boutonRejouer, SIGNAL(clicked()), this, SLOT(reinitialiser()));
    connect(ui->boutonPause, SIGNAL(clicked()), this, SLOT(pause()));

    connect(ui->action_Quitter, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(actionAPropos()));

    ui->boutonRejouer->setFocus();

    ui->labelGagnant->hide();
    ui->labelInfoJGagnant->hide();

    etatDuJeu = EtatsJeu::attenteLancementPartie;
}

// Destructeurs
ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}

// Accesseurs
Presentation *ChifoumiVue::getPresentation() {
    return _laPresentation;
}

// Mutateurs
void ChifoumiVue::setPresentation (Presentation *p) {
    _laPresentation = p;
}

// Affichage
void ChifoumiVue::MAJInterface(char victoirePartie,
                               char joueurGagnantRound,
                               Chifoumi::UnCoup coupJGauche,
                               Chifoumi::UnCoup coupJDroit,
                               unsigned int scoreJGauche,
                               unsigned int scoreJDroit,
                               unsigned int valeurTimer)
{
    afficherTemps(valeurTimer);
    afficherGagnantRound(joueurGagnantRound);
    afficherPoint(scoreJGauche, scoreJDroit);
    afficherCoup(coupJGauche, coupJDroit);
    afficherGagnantTotal(victoirePartie, scoreJGauche, scoreJDroit);
}

/// ================== SLOTS PRIVEE ==================

void ChifoumiVue::actionAPropos() {
    QMessageBox fenAPropos;
    fenAPropos.setWindowTitle("À propos");
    fenAPropos.setText("Version v5 du 01/06/2022\n\nFait par :\nAlexandre Maurice\nNicolas Dargazanli\nGuillaume Tritsch");
    fenAPropos.exec();
}

void ChifoumiVue::jouerPierre() {
    _laPresentation->deroulerUnTour(Chifoumi::UnCoup::pierre);
}

void ChifoumiVue::jouerCiseau() {
    _laPresentation->deroulerUnTour(Chifoumi::UnCoup::ciseau);
}

void ChifoumiVue::jouerPapier() {
    _laPresentation->deroulerUnTour(Chifoumi::UnCoup::papier);
}

void ChifoumiVue::reinitialiser() {

    // Redefinir le bouton du timer en actif
    if (!_laPresentation->timerIsActive()) {
        pause();
    }

    _laPresentation->reinitialiser();

    switch (etatDuJeu) {
    case EtatsJeu::attenteCoupJoueur:
        majCouleur("neutre", "neutre");

        break;

    case EtatsJeu::attenteLancementPartie:
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);
        ui->boutonPause->setEnabled(true);
        ui->boutonRejouer->setText("Relancer la partie");

        majCouleur("neutre", "neutre");


        etatDuJeu = EtatsJeu::attenteCoupJoueur;
        break;

    case EtatsJeu::finDePartie:
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);
        ui->boutonPause->setEnabled(true);

        ui->labelGagnant->hide();
        ui->labelInfoJGagnant->hide();

        majCouleur("neutre", "neutre");

        etatDuJeu = EtatsJeu::attenteCoupJoueur;
        break;

    }
}

void ChifoumiVue::pause() {
    _laPresentation->pauseTimer();
    if (_laPresentation->timerIsActive()) {
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);
        ui->boutonPause->setText(tr("&Pause"));
    } else {
        ui->boutonCiseau->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonPapier->setEnabled(false);
        ui->boutonPause->setText(tr("R&eprendre"));
    }
}

/// ================== METHODES PRIVEES ==================

void ChifoumiVue::afficherGagnantRound(char joueurGagnantRound) {

    switch (joueurGagnantRound) {
    case 'J':
        majCouleur("true", "false");
        break;
    case 'M':
        majCouleur("false", "true");
        break;
    case 'N':
        majCouleur("false", "false");
        break;
    case 'O':
        break;
    }
}

void ChifoumiVue::afficherFenetreVictoire(TypeVictoire victoire, QString nomGagnant, unsigned int nbrPointGagnant) {
    QMessageBox FenVictoire;
    FenVictoire.setWindowTitle("Victoire !");

    int valeurTimer = _laPresentation->getTempsEcoule();

    switch (victoire) {
    case TypeVictoire::point:
        FenVictoire.setText("Bravo, " + nomGagnant + " a gagné la partie apres "+QString::number(valeurTimer)+" de jeu.");
        break;
    case TypeVictoire::temps:
        if (nomGagnant == "Aucun") {
            FenVictoire.setText("Helas chers joueurs, le temps de jeu est fini ! Il n'y a malheuresement aucun gagnant.");
        } else {
            FenVictoire.setText("Helas chers joueurs, le temps de jeu est fini ! Toutefois, "+nomGagnant+" gagne avec "+ QString::number(nbrPointGagnant) +" points.");
        }
        break;
    }
    FenVictoire.exec();
}

void ChifoumiVue::afficherGagnantTotal(char joueurGagnant, unsigned int scoreJGauche, unsigned int scoreJDroit) {

    switch (joueurGagnant) {
    case 'J':
        ui->labelGagnant->show();
        ui->labelInfoJGagnant->show();

        ui->boutonCiseau->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonPapier->setEnabled(false);
        ui->boutonPause->setEnabled(false);

        ui->labelInfoJGagnant->setText("Joueur");

        majCouleur("neutre", "neutre");

        if (_laPresentation->getTempsRestant()==0) {
            afficherFenetreVictoire(temps, "le Joueur", scoreJGauche);
        } else {
            afficherFenetreVictoire(point, "le Joueur", scoreJGauche);
        }

        etatDuJeu = EtatsJeu::finDePartie;
        break;
    case 'M':
        ui->labelGagnant->show();
        ui->labelInfoJGagnant->show();

        ui->boutonCiseau->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonPapier->setEnabled(false);
        ui->boutonPause->setEnabled(false);

        ui->labelInfoJGagnant->setText("Machine");

        majCouleur("neutre", "neutre");

        if (_laPresentation->getTempsRestant()==0) {
            afficherFenetreVictoire(temps, "la Machine", scoreJDroit);
        } else {
            afficherFenetreVictoire(point, "la Machine", scoreJDroit);
        }

        etatDuJeu = EtatsJeu::finDePartie;
        break;
    case 'N':
        ui->labelGagnant->show();
        ui->labelInfoJGagnant->show();

        ui->boutonCiseau->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonPapier->setEnabled(false);
        ui->boutonPause->setEnabled(false);

        ui->labelInfoJGagnant->setText("Aucun");

        majCouleur("neutre", "neutre");

        if (_laPresentation->getTempsRestant()==0) {
            afficherFenetreVictoire(temps, "Aucun");
        } else {
            afficherFenetreVictoire(point, "Aucun");
        }

        etatDuJeu = EtatsJeu::finDePartie;
        break;
    case 'O': // 'O' signifie que le timer n'est pas encore à 0 ou qu'il n'y a pas encore de gagnant
        break;
    }
}

void ChifoumiVue::afficherPoint(unsigned int jGauche, unsigned int jDroit) {
    ui->labelPointJGauche->setText(QString::number(jGauche));
    ui->labelPointJDroit->setText(QString::number(jDroit));
}

void ChifoumiVue::majCouleur(QString valeurJGauche, QString valeurJDroit) {
    ui->labelJGauche->setProperty("victoire", valeurJGauche);
    ui->frameJGauche->setProperty("victoire", valeurJGauche);
    ui->labelPointJGauche->setProperty("victoire", valeurJGauche);

    ui->labelJDroit->setProperty("victoire", valeurJDroit);
    ui->frameJDroit->setProperty("victoire", valeurJDroit);
    ui->labelPointJDroit->setProperty("victoire", valeurJDroit);

    this->setStyleSheet(this->styleSheet());
}


void ChifoumiVue::afficherCoup(Chifoumi::UnCoup coupJGauche, Chifoumi::UnCoup coupJDroit)
{
    ui->imageJGauche->setPixmap(pixmapDeCoup(coupJGauche));
    ui->imageJDroit->setPixmap(pixmapDeCoup(coupJDroit));
}

QPixmap ChifoumiVue::pixmapDeCoup(Chifoumi::UnCoup coup) {
    QPixmap ressource;

    switch (coup) {
    case Chifoumi::UnCoup::ciseau:
        ressource = ressourceCiseau;
        break;
    case Chifoumi::UnCoup::pierre:
        ressource = ressourcePierre;
        break;
    case Chifoumi::UnCoup::papier:
        ressource = ressourcePapier;
        break;
    case Chifoumi::UnCoup::rien:
        ressource = ressourceRien;
        break;
    }

    return ressource;
}

void ChifoumiVue::afficherTemps(unsigned int temps) {
    ui->labelTempsRestantInfo->setText(QString::number(temps));
}
