#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "modele.h"
#include "parametrage.h"
#include "connexionfen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class Presentation;
class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

    ///* Une définition de type énuméré

public:
    ChifoumiVue(Presentation *p, QWidget *parent = nullptr);
    ~ChifoumiVue();

    // METHODES

    void MAJInterface(char victoirePartie,
                      char joueurGagnantRound,
                      Chifoumi::UnCoup coupJGauche,
                      Chifoumi::UnCoup coupJDroit,
                      unsigned int scoreJGauche,
                      unsigned int scoreJDroit,
                      unsigned int valeurTimer);

    Presentation *getPresentation();

    void setPresentation (Presentation *p);

    QString getNomJoueur();

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

    void actionAPropos() ;
    /*
     * BUT: Ouvre une fenetre "A propos..."
     */

    void pause() ;
    /*
     * BUT: Indique à la presentation de mettre en pause le timer
     */

    void actionParametrerPartie();
    /*
     * BUT: Ouvre une fenetre de dialogue pour permettre au joueur de parametrer la partie
     */

    void actionResultat();
    /*
     * BUT: Ouvre une fenetre de dialogue qui indique les informations sur les meilleurs parties de chifoumi
     *
     */

private:

    // NOUVEAUX TYPES
    enum EtatsJeu {attenteLancementPartie, attenteCoupJoueur, finDePartie};
    enum TypeVictoire {point, temps};

    // ATTRIBUTS
    Ui::ChifoumiVue *ui;

    Presentation *_laPresentation;

    QPixmap ressourcePierre = QPixmap(":png/pierre_115"); // ressource de l'image de la pierre
    QPixmap ressourceCiseau = QPixmap(":png/ciseau_115"); // ressource de l'image du ciseau
    QPixmap ressourcePapier = QPixmap(":png/papier_115"); // ressource de l'image du papier
    QPixmap ressourceRien = QPixmap(":png/rien_115");     // ressource de l'image de rien

    EtatsJeu etatDuJeu; // état du jeu

    QString pseudoJoueur = "Le Joueur";

    parametrageVue * fenParametrage;

    // METHODES

    void demanderConnexion();
    /*
     * BUT: Ouvre une page de connexion, si la connexion échoue, le programme s'arrete.
     */

    void afficherGagnantTotal(char joueurGagnant, unsigned int scoreJGauche, unsigned int scoreJDroit);
    /*
     * BUT: Affiche au centre de l'écran le gagnant du precedent tour et ouvre une fenetre avec un message pouvant comporter le score du gagnant si il gagne au temps.
     */

    void afficherGagnantRound(char joueurGagnant);
    /*
     * BUT: Mise a jou des couleurs de chaque joueur
     */

    void afficherPoint(unsigned int jGauche, unsigned int jDroit);
    /*
     * BUT: met à jour les points à l'affichage.
     */

    void afficherCoup(Chifoumi::UnCoup coupJGauche, Chifoumi::UnCoup coupJDroit);
    /*
     * BUT: affiche les coups de chaques joueurs.
     */

    void majCouleur(QString propJGauche, QString propJDroit);
    /*
     * BUT: modification de la propriété de chaque elements graphiques des joueurs avec le QString passé en parametre.
     */

    QPixmap pixmapDeCoup(Chifoumi::UnCoup);
    /*
     * BUT: determine le pixmap à utiliser à l'affichage en fonction du parametre UnCoup passé en parametre.
     */

    void afficherFenetreVictoire(TypeVictoire victoire, QString joueur, unsigned int nbrPointGagnant = 0);
    /*
     * BUT: affichage de la fenetre de la victoire de la variable joueur et du type de la victoire.
     */

    void afficherTemps(unsigned int temps);
    /*
     * BUT: afficher le temps en fonction de la variable temps
     */

};
#endif // CHIFOUMIVUE_H
