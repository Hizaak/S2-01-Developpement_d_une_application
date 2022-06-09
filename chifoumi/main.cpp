/*
 * Nom : Jeu du Chifoumi - version 8
 * Objectif : Jeu du chifoumi dans le cadre de la sae 2.01
 * Date : 06/06/2022
 * Auteur : Nicolas Dargazanli
 *          Alexandre Maurice
 *          Guillaume Tritsch
 */

#include "chifoumivue.h"
#include "presentation.h"
#include "modele.h"
#include "connexionfen.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Ouverture de la base de donnée
    Database * db = new Database();
    db->openDataBase();

    // Demande de connexion
    ConnexionFen * fenConnexion = new ConnexionFen();
    fenConnexion->exec();

    if (fenConnexion->getConnexionValidation()) {
        Chifoumi *m = new Chifoumi();
        // créer la présentation et lui associer le modèle
        Presentation *p = new Presentation(m);
        // créer la vue
        ChifoumiVue w(p);
        // associer la vue à la présentation
        p->setVue(&w);

        w.show();
        return a.exec();
    } else {
        return 0;
    }
}
