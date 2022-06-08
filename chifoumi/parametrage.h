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
    unsigned int getPointMax();
    QString getNomJoueur();
    bool getValidite();

private slots:
    void valider();

    void annuler();

private:
    Ui::parametrageVue *ui;

    bool informationValide = false;
};

#endif // PARAMETRAGE_H
