#include <iostream>
#include<string>
#include<sstream>
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"
#include "analyseur.h"

using namespace std;

int main()
{
    /*
    try
    {

        Computer c;

        Additionner add;
        ConteneurOperande cAdd(add);
        Dupliquer dup;
        ConteneurOperande cDup(dup);

        Litteral_numerique L1 = Litteral_numerique(-2.3,2);
        Litteral_calculable &l_1 = L1;
        Litteral &l1 = L1;
        ConteneurOperande cL1(l1);

        Litteral_numerique L2 = Litteral_numerique(2.3);;
        Litteral_calculable &l_2 = L2;
        Litteral &l2 = L2;
        ConteneurOperande cL2(l2);

        c.push(l1);
        c.push(l2);

        ConteneurOperande** commande = new ConteneurOperande*[5];
        commande[0] = &cL2;
        commande[1] = &cAdd;
        commande[2] = &cAdd;
        commande[3] = &cDup;
        Analyseur a;
        c.afficherPile();
        cout << endl << endl;
        a.effectuer(commande, 4, c);
        c.afficherPile();
    }
    catch(Exception e)
    {
        e.afficher();
    }
*/

    Computer c;

    int k;
    string s;
    Analyseur a;
    cin >> s;
    a.effectuer(s,c);
    c.afficherPile();

    /*for(k=0; k<8; k++){

    cin >> s;
    c.getAnalyseur()->effectuer(s, c); */


    return 0;
}
