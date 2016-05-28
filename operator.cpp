#ifndef OPERATOR_CPP_INCLUDED
#define OPERATOR_CPP_INCLUDED
#include "operator.h"
#include "litteraux.h"
#include "pile.h"


///-------------------- Operateur Numerique --------------------------------------

  /*  void Operator::additioner(){
            PileManager pm = getpm();

        return res;
    };*/


   /* void operator-();
    void operator*();
    void operator/();
    void DIV();
    void MOD();
    void NEG();
    void NUM();
    void DEN();
    void operator$();
    Factorielle RE();
    Factorielle IM();
    void DUP();*/










void Operator::DUP(Pile *p){

    if(p->getTaille() > 0 )
    {
        Litteral *nvlit;
        *nvlit = p->top();
        p->push(*nvlit);
    }
}

void Operator::DROP(Pile * p){

p->pop();
}

void Operator::SWAP(Pile *p)
{
    if(p->getTaille()>1)
    {
        Litteral *nvlit1;
        Litteral *nvlit2;
        *nvlit1 = p->pop();
        *nvlit2 = p->pop();        p->push(*nvlit1);
        p->push(*nvlit2);
    }
}

/*
void Operator::LASTOP(){}
void Operator::LASTARGS(){}
void Operator::UNDO(){}
void Operator::REDO(){}

*/

void Operator::CLEAR(Pile *p){

    while(p->getTaille() > 0)
    {

        p->pop();
    }

}

 void Operator::LASTOP(){

 }

 void Operator::LASTARGS(){



 }

#endif // OPERATOR_CPP_INCLUDED
