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
                Litteral_calculable &Res =  *(new Litteral_numerique(*(new Forme_fraction(res)), *(new Forme_fraction(0))));
                return Res;
            }
            else
                throw ErrOperateur();
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
                Litteral_calculable &Res =  *(new Litteral_numerique(*(new Forme_fraction(res)), *(new Forme_fraction(0))));
                return Res;
            }
            else
                throw ErrOperateur();
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
            Litteral_calculable &Res = *L1 * *L2;
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
            s = L->toStr();
            int place;
            int dollar;
            dollar = s.find_first_of('$');
            place = s.find_first_of('/');
            Forme_fraction* f = nullptr;
            if(place != -1&& dollar == -1){
            f = a->creerUneLitteraleRationelle(s);
            }
            else if(place == -1 && dollar == -1)f = a->creerUneLitteraleEntiere(s);

            if(f != nullptr )
            {
                int num = f->getNumerateur();
                Litteral_numerique &Res =  *(new Litteral_numerique(*(new Forme_fraction(num)), *(new Forme_fraction(0))));
                return Res;
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
            s = L->toStr();
            int place;
            int dollar;
            place = s.find_first_of('/');
            dollar = s.find_first_of('$');
            Forme_fraction* f = nullptr;
            if(place != -1 && dollar ==-1){
            f = a->creerUneLitteraleRationelle(s);
            }
            else if (place == -1 && dollar ==-1) f = a->creerUneLitteraleEntiere("1");

            if(f != nullptr )
            {
                int den = f->getDenominateur();
                Litteral_numerique &Res =  *(new Litteral_numerique(*(new Forme_fraction(den)), *(new Forme_fraction(0))));
                return Res;
            }
            else
            {
                throw ErrOperateur('Litterale reele ou complexe');
            }

        }
};


class Re : public OperateurNumerique
{

    public:
        Re() : OperateurNumerique(1) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            string s;
            Litteral_calculable *L = L_Tab[0];
            s = L->toStr();
            int dollar;
            int point;
            int slash;
            dollar = s.find_first_of('$');


            if(dollar != -1)
            {
                string *tab = new string[2];
                tab = a->getReEtIm(s);
                point = tab[0].find_first_of("\.");
                slash = tab[0].find_first_of("\/");
                if(point == -1&&slash == -1)
                {
                    Forme_fraction* ln = nullptr;
                    ln = a->creerUneLitteraleEntiere(tab[0]);
                    if(ln != nullptr )
                    {
                        Litteral_calculable &Res = *(new Litteral_numerique((*ln), *(new Forme_fraction(0))));
                        return Res;
                    }
                    else
                    {
                        throw ErrOperateur('Erreur');
                    }
                }
                else if(point == -1&&slash != -1)
                {
                    Forme_fraction* ln = nullptr;
                    ln = a->creerUneLitteraleRationelle(tab[0]);
                    if(ln != nullptr )
                    {
                        Litteral_calculable &Res = *(new Litteral_numerique((*ln), *(new Forme_fraction(0))));
                        return Res;
                    }
                    else
                    {
                        throw ErrOperateur('Erreur');
                    }
                }
                else
                {
                    Forme_decimale* ln = nullptr;
                    ln = a->creerUneLitteraleReel(tab[0]);
                    if(ln != nullptr )
                    {
                        Litteral_calculable &Res = *(new Litteral_numerique((*ln), *(new Forme_fraction(0))));
                        return Res;
                    }
                    else
                    {
                        throw ErrOperateur('Erreur');
                    }
                }

            }
            else
            {

                        Litteral_calculable &Res = *L;
                        return Res;

            }


        }
};

class Im : public OperateurNumerique
{

    public:
        Im() : OperateurNumerique(1) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {

            string s;
            Litteral_calculable *L = L_Tab[0];
            s = L->toStr();
            int dollar;
            int point;
            int slash;
            dollar = s.find_first_of('$');


            if(dollar != -1)
            {
                string *tab = new string[2];
                tab = a->getReEtIm(s);
                point = tab[1].find_first_of("\.");
                slash = tab[1].find_first_of("\/");

                if(point == -1 && slash == -1)
                {
                    Forme_fraction* ln = nullptr;
                    ln = a->creerUneLitteraleEntiere(tab[1]);

                    if(ln != nullptr )
                    {

                        Litteral_calculable &Res = *(new Litteral_numerique((*ln), *(new Forme_fraction(0))));

                        return Res;

                    }
                    else
                    {
                        throw ErrOperateur('Erreur');
                    }
                }
                if(point == -1 && slash != -1)
                {
                    Forme_fraction* ln = nullptr;
                    ln = a->creerUneLitteraleRationelle(tab[1]);

                    if(ln != nullptr )
                    {

                        Litteral_calculable &Res = *(new Litteral_numerique((*ln), *(new Forme_fraction(0))));

                        return Res;

                    }
                    else
                    {
                        throw ErrOperateur('Erreur');
                    }
                }
                else
                {
                    Forme_decimale* ln = nullptr;
                    ln = a->creerUneLitteraleReel(tab[1]);
                    if(ln != nullptr )
                    {
                        Litteral_calculable &Res = *(new Litteral_numerique((*ln), *(new Forme_fraction(0))));
                        return Res;
                    }
                    else
                    {
                        throw ErrOperateur('Erreur');
                    }
                }

            }
            else
            {

                        Litteral_calculable &Res = *(new Litteral_numerique(*(new Forme_fraction(0)), *(new Forme_fraction(0))));
                        return Res;

            }


        }
};

class creerComplexe : public OperateurNumerique
{

    public:
        creerComplexe() : OperateurNumerique(2) {}
        Litteral_calculable& calcul(Litteral_calculable **L_Tab) const
        {


            Litteral_calculable *L1 = L_Tab[0];
            Litteral_calculable *L2 = L_Tab[1];

            int dollar1;
            int dollar2;
            dollar1 = L1->toStr().find_first_of('$');
            dollar2 = L2->toStr().find_first_of('$');
            if(dollar1 == -1 && dollar2 == -1){
            string complexe = L2->toStr()+"$"+L1->toStr();
            Litteral_numerique *Ln = nullptr;
            Ln = a->creerUneLitteraleComplexe(complexe);

            if(Ln != nullptr){
                Litteral_calculable &Res = *(new Litteral_numerique(*Ln));
                return Res;
            }
            else
                throw ErrOperateur('Syntaxe invalide');
            }
            else
                throw ErrOperateur('Ne peut etre transforme en complexe');

        }
};

//OPERATEUR MANIPULATION PILE


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
