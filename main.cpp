#include <QTextStream>
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"
#include "analyseur.h"
#include "operateurs_instances.h"
#include "atomes.h"
#include <QApplication>
#include "qanalyseur.h"



int main(int argc, char* argv[]){


    QApplication app(argc, argv);
    QComputer fenetre;
    fenetre.show();
    return app.exec();


}
