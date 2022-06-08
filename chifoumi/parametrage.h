#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H

#include <QDialog>

namespace Ui {
class parametrageVue;
}

class parametrageVue : public QDialog
{
    Q_OBJECT

public:
    explicit parametrageVue(QString pseudoActuel, unsigned int point, unsigned int lgTimer, QWidget *parent = nullptr);
    ~parametrageVue();


    unsigned int getLgTimer();
    /*
     * BUT : Retourne la valeur du le spin box dédié au timer
     */

    unsigned int getPointMax();
    /*
     * BUT : Retourne la valeur du le spin box dédié au point
     */

    QString getNomJoueur();
    /*
     * BUT : Retourne le text du widget lineEdit
     */

    bool getValidite();
    /*
     * BUT : Retourne la validité des données
     */

private slots:
    void valider();
    /*
     * BUT : Lorsque l'utilisateur clique sur le bouton valider. Vérification du pseudo et validation
     */

    void annuler();
    /*
     * BUT : Fermeture de la fenetre sans validation
     */

private:
    Ui::parametrageVue *ui;

    bool informationValide = false;
    /*
     * BUT : Indique si les données son valide
     */

};

#endif // PARAMETRAGE_H
