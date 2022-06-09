#include "resultatfen.h"
#include "ui_resultatfen.h"

#include <database.h>
#include <QSqlQuery>
#include <QDebug>

ResultatFen::ResultatFen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultatFen)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    connect(ui->pBRetour,SIGNAL(clicked()),this,SLOT(close()));

    this->setWindowTitle("Résultat");

    QSqlQuery query;
    query.exec("SELECT * FROM informationPartieDMT "
               "WHERE `nbrPointJoueur`>`nbrPointMachine` "
               "ORDER BY `nbrPointJoueur`-`nbrPointMachine` DESC, `nbrPointJoueur` DESC "
               "LIMIT 10;");

    for(int i = 0; query.next(); i++) {
        for(int d = 0; d<6; d++) {
            QTableWidgetItem *item = ui->tableWidget->item(i, d);
            item = new QTableWidgetItem();
            ui->tableWidget->setItem(i,d,item);
            item->setText(query.value(d+1).toString());
        }
    }

    query.exec("SELECT COUNT(*) FROM informationPartieDMT");
    query.next();

    int NbrPartieTotal = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM informationPartieDMT WHERE `nbrPointJoueur`>`nbrPointMachine`");
    query.next();
    ui->labelPourcentInfo->setText(QString::number((query.value(0).toInt()*100)/NbrPartieTotal)+"%");
    ui->labelNbrpartieTInfo->setText(QString::number(NbrPartieTotal));

    query.exec("SELECT SUM(`nbrPointJoueur`)/SUM(`tempsEcoule`) FROM informationPartieDMT");
    query.next();
    ui->labelTpsMoyenSecInfo->setText(query.value(0).toString());

    query.exec("SELECT SUM(`nbrPointMachine`)/SUM(`tempsEcoule`) FROM informationPartieDMT");
    query.next();
    ui->labelTpsMoyenSecMachineInfo->setText(query.value(0).toString());
}

ResultatFen::~ResultatFen()
{
    delete ui;
}
