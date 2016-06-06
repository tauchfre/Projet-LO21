#include "pile.h"
#include "litteraux.h"


// METHODES DE LA CLASSE PILE
void Pile::afficher() const
{
    if(taille > 0)
    {
        cout << "Pile :" << endl;
        for(int i = taille-1; i>=0; i--) // On affiche à l'envers !
        {
            cout << "> ("<<i<<") " << *litteraux[i];
            cout << endl;
        }
    }
}
void Pile::push(Litteral& L)
{
    if(taille < tailleMax)
    {
        litteraux[taille] = &L.copie();
        taille++;
    }
    else
        throw ExceptionPile("Taille max atteinte");
}
Litteral& Pile::pop()
{
    if(taille>0)
    {
        taille--;
        return *litteraux[taille];
    }
    else
        throw ExceptionPile("Pas d'élement à dépiler");

}
Pile::Pile(const Pile& P) : litteraux(new Litteral*[P.getTailleMax()]),tailleMax(P.getTailleMax()),taille(0)
{
    P.copierDans(*this);
}
void Pile::copierDans(Pile& P) const
{
    for(int i = 0; i<taille; i++) // On parcours dans l'ordre d'ajout du plus vieux au plus récent
    {
        P.push(*litteraux[i]);
    }
}
