#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "modele.h"

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

    void MAJInterface(char joueurGagnant,
                      Chifoumi::UnCoup coupJGauche,
                      Chifoumi::UnCoup coupJDroit,
                      unsigned int scoreJGauche,
                      unsigned int scoreJDroit);

    Presentation *getPresentation();

    void setPresentation (Presentation *p);

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


private:

    // NOUVEAUX TYPES
    enum EtatsJeu {attenteLancementPartie, attenteCoupJoueur};

    // ATTRIBUTS
    Ui::ChifoumiVue *ui;

    Presentation *_laPresentation;

    QPixmap ressourcePierre = QPixmap(":png/pierre_115"); // ressource de l'image de la pierre
    QPixmap ressourceCiseau = QPixmap(":png/ciseau_115"); // ressource de l'image du ciseau
    QPixmap ressourcePapier = QPixmap(":png/papier_115"); // ressource de l'image du papier
    QPixmap ressourceRien = QPixmap(":png/rien_115");     // ressource de l'image de rien

    EtatsJeu etatDuJeu; // état du jeu

    // METHODES

    void afficherGagnant(char joueurGagnant);
    /*
     * BUT: Affiche au centre de l'écran le gagnant du precedent tour.
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

};
#endif // CHIFOUMIVUE_H
