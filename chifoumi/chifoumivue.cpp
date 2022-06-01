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

    this->setWindowTitle("SAE 2.01 - version 2");

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
void ChifoumiVue::MAJInterface(char joueurGagnant,
                               Chifoumi::UnCoup coupJGauche,
                               Chifoumi::UnCoup coupJDroit,
                               unsigned int scoreJGauche,
                               unsigned int scoreJDroit)
{
    afficherGagnant(joueurGagnant);
    afficherPoint(scoreJGauche, scoreJDroit);
    afficherCoup(coupJGauche, coupJDroit);
}

/// ================== SLOTS PRIVEE ==================

void ChifoumiVue::actionAPropos() {
    QMessageBox fenAPropos;
    fenAPropos.setWindowTitle("À propos");
    fenAPropos.setText("Version v3 du 24/05/2022\n\nFait par :\nAlexandre Maurice\nNicolas Dargazanli\nGuillaume Tritsch");
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

        ui->labelInfoJGagnant->setText("Aucun");
        break;

    case EtatsJeu::attenteLancementPartie:
        ui->boutonCiseau->setEnabled(true);
        ui->boutonPierre->setEnabled(true);
        ui->boutonPapier->setEnabled(true);
        ui->boutonRejouer->setText("Relancer la partie");

        majCouleur("neutre", "neutre");

        ui->labelInfoJGagnant->setText("Aucun");

        etatDuJeu = EtatsJeu::attenteCoupJoueur;
        break;
    }
}

/// ================== METHODES PRIVEES ==================

void ChifoumiVue::afficherGagnant(char joueurGagnant) {
    switch (joueurGagnant) {
    case 'J':
        ui->labelInfoJGagnant->setText("Joueur");
        majCouleur("true", "false");
        break;
    case 'M':
        ui->labelInfoJGagnant->setText("Machine");
        majCouleur("false", "true");
        break;
    case 'N':
        ui->labelInfoJGagnant->setText("Nul");
        majCouleur("false", "false");
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
