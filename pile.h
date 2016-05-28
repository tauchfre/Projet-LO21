#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#include "litteraux.h"
class ExceptionPile: public Exception
{
    public:
        ExceptionPile(const char* err) :  Exception(err) {}
        void afficher() { cout << "Erreur avec une pile :" << erreur; }
};

class Pile
{
    private:
        Litteral** litteraux;
        int tailleMax;
        int taille;
    public:
        Pile(int T = 50):litteraux(new Litteral*[T]),tailleMax(T),taille(0){}
        Pile(const Pile& P);
        void afficher() const;
        void copierDans(Pile& P) const;
        void push(Litteral& L);
        int getTailleMax() const { return tailleMax; }
        int getTaille() const { return taille; }
        Litteral& pop();
        Litteral& top();
};

class PileManager
{
    private:
        Pile* pileActuelle;

        Pile** historiqueUndo;
        int undoDisponible;
        Pile** historiqueRedo;
        int redoDisponible;

        void addLitteral(Litteral& liter);

    public:
        PileManager(): pileActuelle(0),historiqueUndo(0), historiqueRedo(0),redoDisponible(0),undoDisponible(0) {}
        Litteral& pop();
        void push(Litteral& L);
};


#endif // PILE_H_INCLUDED
