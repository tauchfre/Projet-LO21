#include "operateurs.h"
#include <typeinfo>

// METHODE DE LA CLASSE OPERATEUR

void Operateur::appliquer(PileManager& PM)
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
    Litteral_numerique **L_tab = new Litteral_numerique*[arite];
    for(int i=arite-1;i>=0;i--) // On parcours la pile à l'envers
    {
        try
        {
            L_tab[i] = dynamic_cast<Litteral_numerique*> ( &(Res.pop()) );
        }
        catch (bad_cast& bc)
        {
            throw(ExceptionOperateur("Un des littéral n'est pas calculable", litteralNonCalculable));
        }
    }
    Litteral_numerique &L_Res = calcul(L_tab);
    Res.push(L_Res);
    return Res;
}
// METHODE DE LA CLASSE OPERATEURFACTORY

Operateur* OperateurFactory::creerOperateur(string ID)
{
    if(ID == "DUP")
    {
        return (new Dupliquer);
    }
    else if(ID == "+")
    {
        return (new Additionner);
    }
    else
    {
        return operateurSupplementaire(ID);
    }
}
p
// OPERATIONS DES OPERATEURS
Pile& Dupliquer::operation(const Pile& P)
{
    Pile &Res = * (new Pile(P));

    Litteral &L = Res.pop();
    Res.push(L);
    Res.push(L);
    return Res;
}
