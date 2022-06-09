#include "chifoumivue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chifoumi *m;
    m = new Chifoumi();
    ChifoumiVue w(m);
    w.show();
    return a.exec();
}
