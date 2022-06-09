#ifndef RESULTATFEN_H
#define RESULTATFEN_H

#include <QDialog>
#include <database.h>

namespace Ui {
class ResultatFen;
}

class ResultatFen : public QDialog
{
    Q_OBJECT

public:
    explicit ResultatFen(QWidget *parent = nullptr);
    ~ResultatFen();

private:
    Ui::ResultatFen *ui;
};

#endif // RESULTATFEN_H
