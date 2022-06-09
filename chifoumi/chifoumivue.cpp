#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include <QPixmap>
#include <QShortcut>
#include <QDebug>

ChifoumiVue::ChifoumiVue(Chifoumi *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
    , partieDeChifoumi(m)
{
    ui->setupUi(this);

    this->setWindowTitle("SAE 2.01 - version 1");

    // Ouverture et affichage des images des figures dans les boutons.
    ui->boutonCiseau->setIcon(ressourceCiseau);
    ui->boutonPierre->setIcon(ressourcePierre);
    ui->boutonPapier->setIcon(ressourcePapier);

    // Connexion entre les differentes boutons et les slots à executer
    connect(ui->boutonCiseau, SIGNAL(clicked()), this,  SLOT(jouerCiseau()));
    connect(ui->boutonPapier, SIGNAL(clicked()), this, SLOT(jouerPapier()));
    connect(ui->boutonPierre, SIGNAL(clicked()), this, SLOT(jouerPierre()));
    connect(ui->boutonRejouer, SIGNAL(clicked()), this, SLOT(reinitialiser()));

    ui->boutonRejouer->setFocus();

    etatDuJeu = EtatsJeu::attenteLancementPartie;
}

//SLOTS de jeu
void ChifoumiVue::jouerPierre() {
    deroulerUnTour(Chifoumi::UnCoup::pierre);
}

void ChifoumiVue::jouerCiseau() {
    deroulerUnTour(Chifoumi::UnCoup::ciseau);
}

void ChifoumiVue::jouerPapier() {
    deroulerUnTour(Chifoumi::UnCoup::papier);
}

void ChifoumiVue::deroulerUnTour(Chifoumi::UnCoup coupJoueur) {
    choixJoueur(coupJoueur);
    choixMachine();
    determinerEtAfficherGagnant();
}

void ChifoumiVue::choixJoueur(Chifoumi::UnCoup coupJoueur) {
    partieDeChifoumi->setCoupJoueur(coupJoueur);
    ui->imageJGauche->setPixmap(pixmapDeCoup(coupJoueur));
}

void ChifoumiVue::choixMachine() {
   Chifoumi::UnCoup coupMachine;

   coupMachine = partieDeChifoumi->genererUnCoup();

   partieDeChifoumi->setCoupMachine(coupMachine);
   ui->imageJDroit->setPixmap(pixmapDeCoup(coupMachine));
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

void ChifoumiVue::determinerEtAfficherGagnant() {
    char joueurGagnant;
    joueurGagnant = partieDeChifoumi->determinerGagnant();
    partieDeChifoumi->majScores(joueurGagnant);

    switch (joueurGagnant) {
    case 'J':
        ui->labelInfoJGagnant->setText("Joueur");
        majCouleurDroit("false");
        majCouleurGauche("true");
        break;
    case 'M':
        ui->labelInfoJGagnant->setText("Machine");
        majCouleurDroit("true");
        majCouleurGauche("false");
        break;
    case 'N':
        ui->labelInfoJGagnant->setText("Nul");
        majCouleurDroit("false");
        majCouleurGauche("false");
        break;
    }

    this->afficherPoint();
    styleSheetMAJ();
}


void ChifoumiVue::reinitialiser() {

    switch (etatDuJeu) {
    case EtatsJeu::attenteCoupJoueur:

        partieDeChifoumi->initCoups();
        partieDeChifoumi->initScores();

        this->afficherPoint();

        ui->labelInfoJGagnant->setText("Aucun");
        ui->imageJDroit->setPixmap(ressourceRien);
        ui->imageJGauche->setPixmap(ressourceRien);

        majCouleurDroit("neutre");
        majCouleurGauche("neutre");

        styleSheetMAJ();
        break;

    case EtatsJeu::attenteLancementPartie:

        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);

        ui->boutonRejouer->setText("Relancer la partie");

        partieDeChifoumi->initCoups();
        partieDeChifoumi->initScores();

        this->afficherPoint();

        ui->labelInfoJGagnant->setText("Aucun");
        ui->imageJDroit->setPixmap(ressourceRien);
        ui->imageJGauche->setPixmap(ressourceRien);

        majCouleurDroit("neutre");
        majCouleurGauche("neutre");

        styleSheetMAJ();

        etatDuJeu = EtatsJeu::attenteCoupJoueur;
        break;
    }
}

void ChifoumiVue::afficherPoint() {
    ui->labelPointJGauche->setText(QString::number(partieDeChifoumi->getScoreJoueur()));
    ui->labelPointJDroit->setText(QString::number(partieDeChifoumi->getScoreMachine()));
}

void ChifoumiVue::styleSheetMAJ() {
    this->setStyleSheet(this->styleSheet());
}

void ChifoumiVue::majCouleurGauche(QString valeur) {
    ui->labelJGauche->setProperty("victoire", valeur);
    ui->frameJGauche->setProperty("victoire", valeur);
    ui->labelPointJGauche->setProperty("victoire", valeur);
}

void ChifoumiVue::majCouleurDroit(QString valeur) {
    ui->labelJDroit->setProperty("victoire", valeur);
    ui->frameJDroit->setProperty("victoire", valeur);
    ui->labelPointJDroit->setProperty("victoire", valeur);
}

ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}

