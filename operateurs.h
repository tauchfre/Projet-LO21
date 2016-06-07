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
    Analyseur* a;
    public:
        Operateur(Analyseur* pt_analyseur=0) : a(pt_analyseur) {}
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

class Div : public OperateurNumerique
{

    public:
        Div() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];
            string str1 = L1->toStr();
            string str2 = L2->toStr();
            Forme_fraction *f1 = nullptr;
            f1 = a->creerUneLitteraleEntiere(str1);
            Forme_fraction *f2 = nullptr;
            f2 = a->creerUneLitteraleEntiere(str2);
            if(f1 != nullptr && f2 != nullptr)
            {
                int i1 = f1->getNumerateur();
                int i2 = f2->getNumerateur();
                int res = i2/i1;
                Litteral_calculable *Res =  new Litteral_numerique(*(new Forme_fraction(res)), *(new Forme_fraction(0)));
                Return Res;
            }
            else
                throw ErrOperateur(" Erreur ce n'est pas des entiers ");
        }
};


class Mod : public OperateurNumerique
{

    public:
        Mod() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];
            string str1 = L1->toStr();
            string str2 = L2->toStr();
            Forme_fraction *f1 = nullptr;
            f1 = a->creerUneLitteraleEntiere(str1);
            Forme_fraction *f2 = nullptr;
            f2 = a->creerUneLitteraleEntiere(str2);
            if(f1 != nullptr && f2 != nullptr)
            {
                int i1 = f1->getNumerateur();
                int i2 = f2->getNumerateur();
                int res = i2%i1;
                Litteral_calculable *Res =  new Litteral_numerique(*(new Forme_fraction(res)), *(new Forme_fraction(0)));
                Return Res;
            }
            else
                throw ErrOperateur(" Erreur ce n'est pas des entiers ");
        }
};

class Neg : public OperateurNumerique
{

    public:
        Neg() : OperateurNumerique(1) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            Litteral_calculable *L1 =  new Litteral_numerique(*(new Forme_fraction(-1)), *(new Forme_fraction(0)));
            Litteral_calculable *L2 = L_Tab[0];
            Litteral_calculable *Res = *L1 * *L2;
            return Res;
        }
};

class Num : public OperateurNumerique
{

    public:
        Num() : OperateurNumerique(1) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            string s;
            Litteral_calculable *L = L_Tab[0];
            s = L.toStr();
            int place;
            place = s.find_first_of('/');
            Forme_fraction* f = nullptr;
            if(place != -1){
            f = a->creerUneLitteraleRationelle(s);
            }
            else f = a->creerUneLitteraleEntiere(s);

            if(f != nullptr )
            {
                cout <<"ici \n";
                int num = f->getNumerateur();
                Litteral_numerique *Res =  new Litteral_numerique(*(new Forme_fraction(num)), *(new Forme_fraction(0)));
                Return Res;
            }
            else
            {
                throw ErrOperateur('Litterale reele ou complexe');
            }

        }
};

class Den : public OperateurNumerique
{

    public:
        Den() : OperateurNumerique(1) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            string s;
            Litteral_calculable *L = L_Tab[0];
            s = L.toStr();
            int place;
            place = s.find_first_of('/');
            Forme_fraction* f = nullptr;
            if(place != -1){
            f = a->creerUneLitteraleRationelle(s);
            }
            else f = a->creerUneLitteraleEntiere("1");

            if(f != nullptr )
            {
                int den = f->getDenominateur();
                Litteral_numerique *Res =  new Litteral_numerique(*(new Forme_fraction(den)), *(new Forme_fraction(0)));
                Return Res;
            }
            else
            {
                throw ErrOperateur('Litterale reele ou complexe');
            }

        }
};

//OPERATEUR MANIPULATION PILE

class Dupliquer : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class Drop : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class Swap : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class Clear : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};


class Lastop : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class Lastargs : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class Undo : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class Redo : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};



#endif // OPERATEURS_H_INCLUDED
