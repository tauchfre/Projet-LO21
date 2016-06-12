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

/**
 * ...\brief Classe abstraite de laquelle heritent les operateurs .
 */
class Operateur
{
    protected:
        Analyseur* a;
        bool estAnnulable;
    public:
        Operateur(Analyseur* pt_analyseur=0) : a(pt_analyseur), estAnnulable(true) {}
        Operateur(bool B, Analyseur* pt_analyseur=0) : a(pt_analyseur), estAnnulable(B) {}
        Analyseur* getAnalyseur() const { return a; }
        void setAnalyseur(Analyseur& newA) { a = &newA; }
        virtual Pile& operation(const Pile& P) = 0;
        virtual void appliquer(Computer& PM); // TEMPLATE METHOD
};

/**
 * ...\brief Classe abstraite de laquelle heritent les operateurs qui transforment <arite> Litteral_calculable en <1> Litteral_calculable.
 */
class OperateurNumerique : public  Operateur
{
    private:
        int arite;
    public:
        OperateurNumerique(int A, Analyseur* pt_analyseur=0): arite(A), Operateur(pt_analyseur) {} // L'arité sera définie dans la factory
        Pile& operation(const Pile &P); // ICI ON DEVRA PRENDRE EN COMPTE LES EXPRESSIONS
        virtual Litteral_calculable& calcul(Litteral_calculable** L_Tab) const = 0; // { throw(ExceptionOperateur("Cet opérateur ne peux pas s'appliquer aux littéraux non numérique")); }; // L
};



/**
 * ...\brief Stocke indifferement une Litterale ou un Operateur dont on saura le type.
 */
class ConteneurOperande // Sert à exprimer des expression / suite d'opérandes
{
    private:
        Operateur* o;
        Litteral* l;
        bool trueIfLitteral;
    public:
        ConteneurOperande(Litteral& L) : o(0), l(&L), trueIfLitteral(true) {}
        ConteneurOperande(Operateur& O) : o(&O), l(0), trueIfLitteral(false) {}
        bool isLitteral()  const{ return trueIfLitteral; }
        Operateur* getOperateur() const { return o; }
        Litteral* getLitteral() const { return l; }
};

#endif // OPERATEURS_H_INCLUDED
