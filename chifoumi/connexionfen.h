#ifndef CONNEXIONFEN_H
#define CONNEXIONFEN_H

#include <QDialog>
#include "presentation.h"

namespace Ui {
class ConnexionFen;
}

class ConnexionFen : public QDialog
{
    Q_OBJECT

public:
    explicit ConnexionFen(QWidget *parent = nullptr);
    ~ConnexionFen();

    void insertNewUser(QString pseudo, QString mdp);
    /*
     * BUT : Création d'un nouvelle utilisateur si l'identifiant est libre
     */

    bool getConnexionValidation();
    /*
     * BUT : Retourne true si la connexion est valide
     */

private slots:
    void connexion();
    void quitter();


private:
    Ui::ConnexionFen *ui;

    bool connexionReussie;
    /*
     * BUT : Indicateur si la connexion est valide
     */
};

#endif // CONNEXIONFEN_H
