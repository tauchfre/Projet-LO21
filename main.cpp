#include <iostream>
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"
#include "analyseur.h"
#include "operateurs_instances.h"
#include "atomes.h"

using namespace std;
void boucle();
int main()
{
    boucle();
    return 0;
}
void boucle()
{
     try
    {
        Computer c;
        Additionner add;
        ConteneurOperande cAdd(add);
        Dupliquer dup;
        ConteneurOperande cDup(dup);
        Litteral_numerique L1 = Litteral_numerique(* new Forme_fraction(3,-4), * new Forme_fraction(17,144));
        Litteral_calculable &l_1 = L1;
        Litteral &l1 = L1;
        ConteneurOperande cL1(l1);

        Litteral_numerique L2 = Litteral_numerique(* new Forme_fraction(3), * new Forme_fraction(4));
        Litteral_calculable &l_2 = L2;
        Litteral &l2 = L2;
        ConteneurOperande cL2(l2);
        c.push(l1);
        c.push(l2);
        ConteneurOperande* cMul = new ConteneurOperande(* new Multiplier);;

        ConteneurOperande** commande = new ConteneurOperande*[5];
        commande[0] = &cL2;
        commande[1] = new ConteneurOperande(* new Diviser);
        commande[2] = &cAdd;
        commande[3] = &cDup;
        commande[4] = cMul;
        Analyseur a;
//       c.effectuer(commande, 5);
// NE FONCTIONNENT PAS
//      c.effectuer("1");
        c.afficherPile();
        //cout << endl << toRPN("-2/3 + 3/2")<< endl;
        string commande_user;
        getline(cin, commande_user);
        while(commande_user != "exit")
        {
            try {
            c.effectuer(commande_user); // EVAL");
            cout << endl << endl;
            c.afficherPile();
            cout << endl << endl << "---------------------------------" << endl << endl;
            getline(cin, commande_user);
            }
            catch(Exception e)
            {
                e.afficher();
                commande_user = "";
            }
        }
    }
    catch(Exception e)
    {
            e.afficher();
    }
}
