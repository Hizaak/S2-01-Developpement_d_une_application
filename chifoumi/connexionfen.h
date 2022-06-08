#ifndef CONNEXIONFEN_H
#define CONNEXIONFEN_H

#include <QDialog>
#include "database.h"
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
    bool getConnexionValidation();
    Database *getDatabase();

private slots:
    void connexion();
    void quitter();


private:
    Ui::ConnexionFen *ui;
    Database * db;


    bool connexionReussie;
};

#endif // CONNEXIONFEN_H
