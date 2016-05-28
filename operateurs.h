#ifndef OPERATEURS_H_INCLUDED
#define OPERATEURS_H_INCLUDED
#include "litteraux.h"
#include "pile.h"
#include <typeinfo>

enum ErrOperateur{litteralNonCalculable,autre};
class ExceptionOperateur : public Exception
{
    ErrOperateur id_erreur;
    public:
        ExceptionOperateur(const char* err, ErrOperateur idErr=autre) : Exception(err), id_erreur(idErr) {}
        ErrOperateur getId() const { return id_erreur; }
};


class Operateur
{
    public:
        virtual Pile& operation(const Pile& P) = 0;
        virtual void appliquer(PileManager& PM);
};
class OperateurNumerique : public  Operateur
{
    private:
        int arite;
    public:
        OperateurNumerique(int A): arite(A){} // L'arité sera définie dans la factory
        Pile& operation(const Pile &P); // ICI ON DEVRA PRENDRE EN COMPTE LES EXPRESSIONS
        virtual Litteral_numerique& calcul(Litteral_numerique** L_Tab) const = 0; // L
};

class OperateurFactory
{
    public:
        Operateur* creerOperateur(string ID);
        virtual Operateur* operateurSupplementaire(string ID) { return 0; }
};


// OPERATEURS
class Additionner : public OperateurNumerique
{

    public:
        Additionner() : OperateurNumerique(2) {}
        Litteral_numerique& calcul(Litteral_numerique **L_Tab) const
        {
            Litteral_numerique L1 = *L_Tab[0];
            Litteral_numerique L2 = *L_Tab[1];
            Litteral_numerique &Res = L1+L2;
            return Res;
        }
};
class Dupliquer : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

#endif // OPERATEURS_H_INCLUDED
