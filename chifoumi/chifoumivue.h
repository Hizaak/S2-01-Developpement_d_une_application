#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "chifoumi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

    ///* Une définition de type énuméré

public:
    ChifoumiVue(Chifoumi *m, QWidget *parent = nullptr);
    ~ChifoumiVue();

private slots:
    void reinitialiser();
    /*
     * BUT: Créer une nouvelle partie de chifoumi, et reinitialise la page.
     */

    void jouerPierre();
    /*
     * BUT: Deroule un tour avec comme choix du joueur la figure pierre.
     */

    void jouerCiseau();
    /*
     * BUT: Deroule un tour avec comme choix du joueur la figure ciseau.
     */

    void jouerPapier();
    /*
     * BUT: Deroule un tour avec comme choix du joueur la figure papier.
     */



private:
    // NOUVEAUX TYPES
    enum EtatsJeu {attenteLancementPartie, attenteCoupJoueur};

    // ATTRIBUTS
    Ui::ChifoumiVue *ui;

    QPixmap ressourcePierre = QPixmap(":png/pierre_115"); // ressource de l'image de la pierre
    QPixmap ressourceCiseau = QPixmap(":png/ciseau_115"); // ressource de l'image du ciseau
    QPixmap ressourcePapier = QPixmap(":png/papier_115"); // ressource de l'image du papier
    QPixmap ressourceRien = QPixmap(":png/rien_115");     // ressource de l'image de rien

    Chifoumi* partieDeChifoumi; // partie de chifoumi
    EtatsJeu etatDuJeu; // état du jeu

    // METHODES
    void choixJoueur(Chifoumi::UnCoup /* Coup du joueur*/);
    /*
     * BUT: Procedure qui affecte la valeur UnCoup à la classe Chifoumi et affiche l'image correspondante sur la fenetre.
     */

    void choixMachine();
    /*
     * BUT: Procedure qui genere UnCoup et l'affecte à la classe Chifoumi et affiche l'image correspondante sur la fenetre.
     */

    void determinerEtAfficherGagnant();
    /*
     * BUT: Determine le gagnant, et met à jour les points.
     *      Puis affiche les points, le gagnant et met à jour les couleurs.
     */

    void deroulerUnTour(Chifoumi::UnCoup /* Coup du joueur*/);
    /*
     * BUT: deroule un tour en fonction du parametre UnCoup du joueur, et met à jour la fenetre en fonction du resultat du tour.
     */

    void afficherPoint();
    /*
     * BUT: met à jour les points à l'affichage
     */

    void styleSheetMAJ();
    /*
     * BUT: met à jour la feuille de style.
     */

    void majCouleurGauche(QString);
    /*
     * BUT: modification de la propriété de chaque element du joueur gauche avec le QString passé en parametre.
     */

    void majCouleurDroit(QString);
    /*
     * BUT: modification de la propriété de chaque element du joueur droit avec le QString passé en parametre.
     */

    QPixmap pixmapDeCoup(Chifoumi::UnCoup);
    /*
     * BUT: determine le pixmap à utiliser à l'affichage en fonction du parametre UnCoup passé en parametre.
     */

};
#endif // CHIFOUMIVUE_H
