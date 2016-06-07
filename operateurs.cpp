#include "operateurs.h"
#include "analyseur.h"
#include <typeinfo>

// METHODE DE LA CLASSE OPERATEUR

void Operateur::appliquer(Computer& PM)
{
    Pile &pileActuelle = PM.getPileActuelle();
    try
    {
        Pile &ResOp = this->operation(pileActuelle);
        PM.pushHistorique(pileActuelle);
        PM.setPileActuelle(ResOp);
    }
    catch(ExceptionOperateur e)
    {
        e.afficher();
    }
}

// METHODE DE LA CLASSE OPERATEUR NUMERIQUE
Pile& OperateurNumerique::operation(const Pile &P)
{
    Pile &Res = * (new Pile(P));
    Litteral_calculable **L_tab = new Litteral_calculable*[arite];
    for(int i=arite-1;i>=0;i--) // On parcours la pile à l'envers
    {
        try
        {
            L_tab[i] = dynamic_cast<Litteral_calculable*> ( &(Res.pop()) );
        }
        catch (bad_cast& bc)
        {
            throw(ExceptionOperateur("Un des littéral n'est pas calculable", litteralNonCalculable));
        }
    }
    Litteral_calculable &L_Res = calcul(L_tab);
    Res.push(L_Res);
    return Res;
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

Pile& Drop::operation(const Pile& P)
{
    Pile &Res = * (new Pile(P));

    Litteral &L = Res.pop();
    return Res;
}

Pile& Swap::operation(const Pile& P)
{
    Pile &Res = * (new Pile(P));

    Litteral &L1 = Res.pop();
    Litteral &L2 = Res.pop();
    Res.push(L1);
    Res.push(L2);
    return Res;
}

Pile& Clear::operation(const Pile& P)
{
    Pile &Res = * (new Pile(P));
    unsigned int i;
    while (Res.getTaille()>0)
    {
        Res.pop();
        Res.setTaille(Res.getTaille()-1);

    }
    return Res;
}

Pile& Lastop::operation(const Pile& P)
{
    Pile &Res = *(new Pile(P));

    return Res;
}

Pile& Lastargs::operation(const Pile& P)
{
    Pile &Res = *(new Pile(P));

    return Res;
}

Pile& Undo::operation(const Pile& P)
{
    Pile &Res = *(new Pile(P));

    return Res;
}

Pile& Redo::operation(const Pile& P)
{
    Pile &Res = *(new Pile(P));

    return Res;
}





