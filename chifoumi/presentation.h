#ifndef PRESENTATION_H
#define PRESENTATION_H

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

    Chifoumi* getModele();
    ChifoumiVue* getVue();
    void setModele(Chifoumi *m);
    void setVue(ChifoumiVue *v);

private:
    Chifoumi *_leModele; // partie de chifoumi
    ChifoumiVue *_laVue; // partie de chifoumi

};

#endif // PRESENTATION_H
