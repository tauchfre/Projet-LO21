#ifndef OPERATEURS_INSTANCES_H_INCLUDED
#define OPERATEURS_INSTANCES_H_INCLUDED
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"
#include "analyseur.h"
#include <algorithm>

// OPERATEURS
class Additionner : public OperateurNumerique
{

    public:
        Additionner() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {
            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 + *L2;
            return Res;
        }
};
class Soustraire : public OperateurNumerique
{

    public:
        Soustraire() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {
            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 - *L2;
            return Res;
        }
};
class Multiplier : public OperateurNumerique
{
    public:
        Multiplier() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {
            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 * *L2;
            return Res;
        }
};
class Diviser : public OperateurNumerique
{

    public:
        Diviser() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {
            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 / *L2;
            return Res;
        }
};
/*class Eval : public Operateur
{
    public:
        Eval(Analyseur* A) : Operateur(A) {}
    /*    Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {
            Litteral_calculable *L1 = L_Tab[0];
            string pre_exp = L1->toStr();
            string exp = toRPN(pre_exp);
            Litteral_calculable* Res = getAnalyseur()->evaluer(exp);
            if(Res != 0)
                    return  *Res;
            else
                throw(ExceptionOperateur("Ce littéral n'est pas évaluable"));
        }
        virtual Pile& operation(const Pile& P);
        virtual void appliquer(Computer& PM);
}; */
class Eval : public Operateur
{
    public:
        Eval(Analyseur* pt_analyseur=0) : Operateur(pt_analyseur) {}
        Analyseur* getAnalyseur() const { return a; }
        void setAnalyseur(Analyseur& newA) { a = &newA; }
        Pile& operation(const Pile& P)  { }
        void appliquer(Computer& C);
};
class Dupliquer : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

#endif // OPERATEURS_INSTANCES_H_INCLUDED
