#ifndef CONTROLEUR_H_INCLUDED
#define CONTROLEUR_H_INCLUDED
#include "pile.h"
#include "interpreteur.h"


class Controleur {
    Interpreteur interp;
	PileManager& pileMng;
	Pile& pileAff;
public:
	Controleur(PileManager& pm, Pile& p):
		pileMng(pm), pileAff(p){}
	void commande(const string& c);
	void executer();
};

#endif // CONTROLEUR_H_INCLUDED
