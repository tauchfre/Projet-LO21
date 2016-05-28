#ifndef OPERATOR_H_INCLUDED
#define OPERATOR_H_INCLUDED
#include<cstring>
#include<iostream>
#include<stack>
#include "pile.h"


using namespace std;

class Operator{
/*
string derniereOperation;
PileManager *pileMng
*/
public :

  //  string getDernierOp()const {return derniereOperation;}

/// operateurs numerique

    Litteral& additioner();
    void operator-();
    void operator*();
 /*  void operator/();
    void DIV();
    void MOD();
    void NEG();
    void NUM();
    void DEN();
    void operator$();
    Litteral& RE();
    Litteral& IM();
    void DUP();
/*

/// operateurs logiques

    void operator=();
    void operator!=();    void operator=<();
    void operator>=();
    void operator<();
    void operator>();

/// operateurs pour les litterales expressions

*/

/// operateurs de manipulation de pile

    void DUP(Pile *p);
    void DROP(Pile *p);
    void SWAP(Pile *p);
    void LASTOP();
    void LASTARGS();
    void UNDO();
    void REDO();
    void CLEAR(Pile *p);

};



#endif // OPERATOR_H_INCLUDED
