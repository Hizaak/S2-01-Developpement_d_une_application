#include "connexionfen.h"
#include "ui_connexionfen.h"
#include "database.h"
#include "presentation.h"
#include <QSqlQuery>
#include <QSqlError>

ConnexionFen::ConnexionFen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionFen)
{
    ui->setupUi(this);

    this->setWindowTitle("Connexion au jeu du chifoumi");

    db = new Database();
    db->openDataBase();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS connexionChifoumiDMT (identifiant VARCHAR(45) PRIMARY KEY, motDePasse VARCHAR(90));");

    insertNewUser("monId","monMDP");

    connexionReussie = false;

    connect(ui->pBConnexion, SIGNAL(clicked()), this, SLOT(connexion()));
    connect(ui->pBQuitter, SIGNAL(clicked()), this, SLOT(quitter()));
}

ConnexionFen::~ConnexionFen()
{
    delete ui;
}

void ConnexionFen::insertNewUser(QString pseudo, QString mdp) {
    QSqlQuery query;
    query.exec("SELECT * FROM connexionChifoumiDMT;");

    bool existeDeja = false;
    for(int i = 0; query.next(); i++){
        if (query.value(0).toString() == pseudo) {
            existeDeja = true;
        }
    }

    if (!existeDeja) {
        query.exec("INSERT INTO connexionChifoumiDMT VALUES ('"+pseudo+"','"+mdp+"');");
    }
}

void ConnexionFen::connexion() {
    QSqlQuery query;
    query.exec("SELECT * FROM connexionChifoumiDMT;");

    while (query.next()) {
        if (query.value(0).toString() == ui->lEIdentifiant->text() && query.value(1).toString() == ui->lEMDP->text()) {
            connexionReussie = true;
            close();
            break;
        }
    }

    if (!connexionReussie) {
        ui->labelErreur->setText("L'identifiant ou le mot de passe est invalide");
    }

}

bool ConnexionFen::getConnexionValidation() {
    return connexionReussie;
}

void ConnexionFen::quitter() {
    close();
}
