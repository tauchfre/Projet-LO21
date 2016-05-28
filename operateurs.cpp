#include "operateurs.h"
#include "litteraux.h"
#include "pile.h"

// METHODE DE LA CLASSE OPERATEUR

void Operateur::appliquer(PileManager& PM)
{
    Pile &pileActuelle = PM.getPileActuelle();
    Pile &ResOp = this->operation(pileActuelle);
    PM.pushHistorique(pileActuelle);
    PM.setPileActuelle(ResOp);
}

// METHODE DE LA CLASSE OPERATEURFACTORY

Operateur* OperateurFactory::creerOperateur(string ID)
{
    if(ID == "DUP")
    {
        return (new Dupliquer);
    }
    else
    {
        return operateurSupplementaire(ID);
    }
}

// OPERATIONS DES OPERATEURS
Pile& Dupliquer::operation(const Pile& P)
{
    Pile &Res = * (new Pile(P));

    Litteral &L = Res.pop();
    Res.push(L);
    Res.push(L);
    return Res;
}
