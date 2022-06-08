#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QTimer>
#include <QObject>
#include "modele.h"

class ChifoumiVue;
class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(Chifoumi *m, QObject *parent = nullptr);


    void deroulerUnTour(Chifoumi::UnCoup /* Coup du joueur*/);
    /*
     * BUT: deroule un tour en fonction du parametre UnCoup du joueur, et met à jour la fenetre en fonction du resultat du tour.
     */

    void reinitialiser();
    /*
     * BUT: Créer une nouvelle partie de chifoumi, et reinitialise la page.
     */

    void pauseTimer();
    /*
     * BUT: Met en pause le timer
     */

    unsigned int getTempsEcoule();
    /*
     * BUT: Retourne le temps deja écoulé
     */

    unsigned int getTempsRestant();
    /*
     * BUT: Retourne le temps restant
     */

    Chifoumi* getModele();
    ChifoumiVue* getVue();
    void setModele(Chifoumi *m);
    void setVue(ChifoumiVue *v);

    bool timerIsActive();
    /*
     * BUT: Indique si le timer est actif (true si actif)
     */

    void insertGameInformation(QString nomJoueur, unsigned int ptJoueur, unsigned int ptMachine, unsigned int tpsEcoule, QString typeVictoire);
    /*
     * BUT: Insertion des informations d'une partie de chifoumi dans la base de donnée
     */

    unsigned int getLGTimer();
    unsigned int getPointMax();
    void setLGTimer(unsigned int sec);
    void setPointMax(unsigned int point);

private slots:
    void majTimer();

private:
    Chifoumi *_leModele;
    ChifoumiVue *_laVue;
    QTimer* timer;

    unsigned int lgTimer = 30; // Durée total d'une partie (30 sec par défaut)
    unsigned int valeurTimer; // Valeur actuelle du timer
    unsigned int pointMax=5; // Point maximum (5 par défaut)

    char verificationFinPartie();

};

#endif // PRESENTATION_H
