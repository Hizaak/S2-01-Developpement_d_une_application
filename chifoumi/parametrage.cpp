#include "parametrage.h"
#include "ui_parametrage.h"

parametrageVue::parametrageVue(QString pseudoActuel, unsigned int point, unsigned int lgTimer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parametrageVue)
{
    ui->setupUi(this);

    ui->lEPseudo->setText(pseudoActuel);
    ui->sBPointVictoire->setValue(point);
    ui->sBTimerFinPartie->setValue(lgTimer);

    connect(ui->pBValider, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->pBAnnuler, SIGNAL(clicked()), this, SLOT(annuler()));
}

parametrageVue::~parametrageVue()
{
    delete ui;
}

unsigned int parametrageVue::getLgTimer() {
    return ui->sBTimerFinPartie->value();
}

unsigned int parametrageVue::getPointMax() {
    return ui->sBPointVictoire->value();
}

QString parametrageVue::getNomJoueur() {
    return ui->lEPseudo->text();
}

bool parametrageVue::getValidite() {
    return informationValide;
}

void parametrageVue::valider() {
    if (getNomJoueur() != "" && getNomJoueur().toUpper() != "LA MACHINE") {
        informationValide = true;
        this->close();
    }
}

void parametrageVue::annuler() {
    this->close();
}
