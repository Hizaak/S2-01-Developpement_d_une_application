#include "chifoumivue.h"
#include "presentation.h"
#include "ui_chifoumivue.h"

#include <QPixmap>
#include <iostream>
#include <QDebug>
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

    this->setWindowTitle("SAE 2.01 - version 4");

    // Ouverture et affichage des images des figures dans les boutons.
    ui->boutonCiseau->setIcon(QPixmap("F:/BUT/Semestre_2/R2-02/R202DevAplisAvecIHM/SAE2_01_v1/images/ciseau_115"));
    ui->boutonPierre->setIcon(QPixmap("F:/BUT/Semestre_2/R2-02/R202DevAplisAvecIHM/SAE2_01_v1/images/pierre_115"));
    ui->boutonPapier->setIcon(QPixmap("F:/BUT/Semestre_2/R2-02/R202DevAplisAvecIHM/SAE2_01_v1/images/papier_115"));

    // Connexion entre les differentes boutons et les slots à executer
    connect(ui->boutonCiseau, SIGNAL(clicked()), this,  SLOT(jouerCiseau()));
    connect(ui->boutonPapier, SIGNAL(clicked()), this, SLOT(jouerPapier()));
    connect(ui->boutonPierre, SIGNAL(clicked()), this, SLOT(jouerPierre()));
    connect(ui->boutonRejouer, SIGNAL(clicked()), this, SLOT(reinitialiser()));

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
                               unsigned int scoreJDroit)
{
    afficherGagnantRound(joueurGagnantRound);
    afficherPoint(scoreJGauche, scoreJDroit);
    afficherCoup(coupJGauche, coupJDroit);
    afficherGagnantTotal(victoirePartie);
}

/// ================== SLOTS PRIVEE ==================

void ChifoumiVue::actionAPropos() {
    QMessageBox fenAPropos;
    fenAPropos.setWindowTitle("À propos");
    fenAPropos.setText("Version v4 du 24/05/2022\n\nFait par :\nAlexandre Maurice\nNicolas Dargazanli\nGuillaume Tritsch");
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

    _laPresentation->reinitialiser();

    switch (etatDuJeu) {
    case EtatsJeu::attenteCoupJoueur:
        majCouleur("neutre", "neutre");

        break;

    case EtatsJeu::attenteLancementPartie:
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);
        ui->boutonRejouer->setText("Relancer la partie");

        majCouleur("neutre", "neutre");


        etatDuJeu = EtatsJeu::attenteCoupJoueur;
        break;

    case EtatsJeu::finDePartie:
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);

        ui->labelGagnant->hide();
        ui->labelInfoJGagnant->hide();

        majCouleur("neutre", "neutre");

        etatDuJeu = EtatsJeu::attenteCoupJoueur;
        break;

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
    }
}

void ChifoumiVue::afficherFenetreVictoire(QString nomGagnant) {
    QMessageBox FenVictoire;
    FenVictoire.setWindowTitle("Victoire !");
    FenVictoire.setText("Bravo, " + nomGagnant + " a gagné la partie");
    FenVictoire.exec();
}

void ChifoumiVue::afficherGagnantTotal(char joueurGagnant) {

    switch (joueurGagnant) {
    case 'J':
        ui->labelGagnant->show();
        ui->labelInfoJGagnant->show();

        ui->boutonCiseau->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonPapier->setEnabled(false);

        ui->labelInfoJGagnant->setText("Joueur");

        majCouleur("neutre", "neutre");

        afficherFenetreVictoire("le Joueur");

        etatDuJeu = EtatsJeu::finDePartie;
        break;
    case 'M':
        ui->labelGagnant->show();
        ui->labelInfoJGagnant->show();

        ui->boutonCiseau->setEnabled(false);
        ui->boutonPierre->setEnabled(false);
        ui->boutonPapier->setEnabled(false);

        ui->labelInfoJGagnant->setText("Machine");

        majCouleur("neutre", "neutre");

        afficherFenetreVictoire("la Machine");

        etatDuJeu = EtatsJeu::finDePartie;
        break;
    case 'N':
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
