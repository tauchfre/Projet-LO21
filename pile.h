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
        void setTaille(int T) { taille = T; }
        Litteral& pop();
};

class PileManager
{
    private:
        Pile* pileActuelle;

        int maxHistorique;

        Pile** historiqueUndo;
        int undoDisponible;
        Pile** historiqueRedo;
        int redoDisponible;

    public:
        PileManager(int T=50): pileActuelle(0),historiqueUndo(new Pile*[T]), maxHistorique(T), historiqueRedo(new Pile*[T]),redoDisponible(0),undoDisponible(0) {}
        Pile& getPileActuelle() const { return *pileActuelle; }
        void setPileActuelle(Pile &P) { pileActuelle = &P; }
        void pushHistorique(Pile& P, bool isUndo=true);
        Pile& popHistorique(bool isUndo=true);
};


#endif // PILE_H_INCLUDED
