#ifndef OPERATEURS_H_INCLUDED
#define OPERATEURS_H_INCLUDED
#include "litteraux.h"
#include "pile.h"

class Operateur
{
    public:
        virtual Pile& operation(const Pile& P) = 0;
        virtual void appliquer(PileManager& PM);
};
class Dupliquer : public Operateur
{
    public:
        Pile& operation(const Pile& P);
};

class OperateurFactory
{
    public:
        Operateur* creerOperateur(string ID);
        virtual Operateur* operateurSupplementaire(string ID) { return 0; }
};
#endif // OPERATEURS_H_INCLUDED
