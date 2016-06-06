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
class Analyseur;
class Operateur
{
    protected:
        Analyseur* a;
    public:
        Operateur(Analyseur* pt_analyseur=0) : a(pt_analyseur) {}
        Analyseur* getAnalyseur() const { return a; }
        void setAnalyseur(Analyseur& newA) { a = &newA; }
        virtual Pile& operation(const Pile& P) = 0;
        virtual void appliquer(Computer& PM); // TEMPLATE METHOD
};

class OperateurNumerique : public  Operateur
{
    private:
        int arite;
    public:
        OperateurNumerique(int A, Analyseur* pt_analyseur=0): arite(A), Operateur(pt_analyseur) {} // L'arité sera définie dans la factory
        Pile& operation(const Pile &P); // ICI ON DEVRA PRENDRE EN COMPTE LES EXPRESSIONS
        virtual Litteral_calculable& calcul(Litteral_calculable** L_Tab) const = 0; // { throw(ExceptionOperateur("Cet opérateur ne peux pas s'appliquer aux littéraux non numérique")); }; // L
};




#endif // OPERATEURS_H_INCLUDED
