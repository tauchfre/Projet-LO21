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
        PM.setPileActuelle(ResOp);
        if(estAnnulable == false)
            PM.popHistorique(true);
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
    int taille_P = P.getTaille();
    bool expressionFound = false;
    for(int i= taille_P - 1;i >= taille_P - arite;i--) // On parcours la pile à l'envers
    {
        try
        {
            L_tab[taille_P - 1 - i] = dynamic_cast<Litteral_calculable*> ( &(Res.pop()) );
            if( L_tab[taille_P - 1 - i]->getType() == expression )
                expressionFound = true;
        }
        catch (bad_cast& bc)
        {
            throw(ExceptionOperateur("Un des littéral n'est pas calculable", litteralNonCalculable));
        }
    }
    if(expressionFound && getAnalyseur() != 0)
    {
        ostringstream os;
        cout << arite << endl;
        map<string,Operateur&> operateurs = getAnalyseur()->getOperateurs();
        for(map<string,Operateur&>::iterator It = operateurs.begin(); It != operateurs.end(); It++)
        {
            if(this == &It->second)
                os << It->first;
        }
        os << "(";
        if(arite > 1)
        {
            os << L_tab[0]->toStr();
            for(int i = 1; i < arite - 1; i++)
            {
                os << "," << L_tab[i]->toStr();
            }
            os << "," << L_tab[arite-1]->toStr();
        }
        else if(arite == 1)
            os << L_tab[0]->toStr();
        os << ")";
        Res.push( * new Litteral_expression(os.str()));

    }
    else
    {
        Litteral_calculable &L_Res = calcul(L_tab);
        Res.push(L_Res);
    }
    return Res;
}

