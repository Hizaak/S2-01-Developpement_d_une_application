#include "chifoumivue.h"
#include "presentation.h"
#include "modele.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Chifoumi *m = new Chifoumi();
    // créer la présentation et lui associer le modèle
    Presentation *p = new Presentation(m);
    // créer la vue
    ChifoumiVue w(p);
    // associer la vue à la présentation
    p->setVue(&w);

    w.show();
    return a.exec();
}
