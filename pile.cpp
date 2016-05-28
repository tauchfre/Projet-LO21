#include "pile.h"
#include "litteraux.h"


// METHODES DE LA CLASSE PILE
void Pile::afficher() const
{
    if(taille > 0)
    {
        for(int i = taille-1; i>=0; i--) // On affiche à l'envers !
        {
            cout << *litteraux[i] << endl ;
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

// METHODES DE LA CLASSE PILEMANAGER

void PileManager::pushHistorique(Pile& P, bool isUndo)
{
    if(isUndo && undoDisponible < maxHistorique)
    {
        historiqueUndo[undoDisponible] = &P;
        undoDisponible++;
    }
    else if(!isUndo && redoDisponible < maxHistorique)
    {
        historiqueRedo[redoDisponible] = &P;
        redoDisponible++;
    }
    else
    {
        throw ExceptionPile("Taille de l'historique max atteinte");
    }
}
Pile& PileManager::popHistorique(bool isUndo)
{
    if(isUndo && undoDisponible > 0)
    {
        undoDisponible--;
        return * (historiqueUndo[undoDisponible]);
    }
    else if(!isUndo && redoDisponible > 0)
    {
        redoDisponible--;
        return * (historiqueUndo[redoDisponible]);
    }
    else
    {
        throw ExceptionPile("Historique vide");
    }
}
