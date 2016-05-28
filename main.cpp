#include <iostream>
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"

using namespace std;

int main()
{
    try
    {
        Forme_decimale dec1 = 1.4, dec2 = 0.4;
        Litteral_numerique *L = new Litteral_numerique(dec1,dec2);
        Litteral_numerique L2 = *L;
        delete(L);
        Pile P;
        P.push(L2);
        P.push(L2);
        PileManager PM(3);
        PM.setPileActuelle(P);
        OperateurFactory OF;
        Operateur &D = *( OF.creerOperateur("DUP") );
        PM.getPileActuelle().afficher();
        D.appliquer(PM);
        cout << "-" << endl;
        PM.getPileActuelle().afficher();
    }
    catch(Exception e)
    {
        e.afficher();
    }
    return 0;
}
