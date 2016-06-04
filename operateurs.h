#ifndef OPERATEURS_H_INCLUDED
#define OPERATEURS_H_INCLUDED
#include "litteraux.h"
#include "pile.h"
#include <typeinfo>

enum ErrOperateur{litteralNonCalculable,autreErreurOperateur};
class ExceptionOperateur : public Exception
{
    ErrOperateur id_erreur;
    public:
        ExceptionOperateur(const char* err, ErrOperateur idErr=autreErreurOperateur) : Exception(err), id_erreur(idErr) {}
        ErrOperateur getId() const { return id_erreur; }
};

class Computer;
class Operateur
{
    public:
        virtual Pile& operation(const Pile& P) = 0;
        virtual void appliquer(Computer& PM); // TEMPLATE METHOD
};

class OperateurNumerique : public  Operateur
{
    private:
        int arite;
    public:
        OperateurNumerique(int A): arite(A){} // L'arité sera définie dans la factory
        Pile& operation(const Pile &P); // ICI ON DEVRA PRENDRE EN COMPTE LES EXPRESSIONS
        virtual Litteral_calculable& calcul(Litteral_numerique** L_Tab) const = 0; // L
};


// OPERATEURS
class Additionner : public OperateurNumerique
{

    public:
        Additionner() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_numerique **L_Tab) const
        {
            Litteral_numerique *L1 = L_Tab[0];
            Litteral_numerique *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 + *L2;
            return Res;
        }
};

class Soustraire : public OperateurNumerique
{

    public:
        Soustraire() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_numerique **L_Tab) const
        {
            Litteral_numerique *L1 = L_Tab[0];
            Litteral_numerique *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 + *L2;
            return Res;
        }
};

class Multiplier : public OperateurNumerique
{

    public:
        Multiplier() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_numerique **L_Tab) const
        {
            Litteral_numerique *L1 = L_Tab[0];
            Litteral_numerique *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 + *L2;
            return Res;
        }
};

class Diviser : public OperateurNumerique
{

    public:
        Diviser() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_numerique **L_Tab) const
        {
            Litteral_numerique *L1 = L_Tab[0];
            Litteral_numerique *L2 = L_Tab[1];
            Litteral_calculable &Res = *L1 + *L2;
            return Res;
        }
};

class Dupliquer : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

#endif // OPERATEURS_H_INCLUDED
