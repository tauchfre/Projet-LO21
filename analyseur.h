#ifndef ANALYSEUR_H_INCLUDED
#define ANALYSEUR_H_INCLUDED

#include "atomes.h"
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"
#include <iostream>
#include <string>
#include "atomes.h"
using namespace std;


class Analyseur
{
    ListeAtomes& atomes;
    map<string,Operateur&> operateurs;
    public:
        Analyseur();
        Analyseur(map<string,Operateur&> opSupp);


        Litteral_numerique* evaluer(ConteneurOperande** exp, unsigned int taille);
        Litteral_numerique* evaluer(string str);
        void effectuer(ConteneurOperande** exp, unsigned int nbOp, Computer &c);

        Operateur* creerOperateur(string ID);
        virtual Operateur* operateurSupplementaire(string ID) { return 0; }
        void addOperateursCourants();
        void addOperateur(string key, Operateur& op) { if(operateurs.find("key") == operateurs.end()) { operateurs.insert(  pair<string, Operateur&>(key,op)); }  }

        ListeAtomes& getAtomes() { return atomes; }

        ConteneurOperande** interpreter(const string &commande);
        Forme_fraction *creerUneLitteraleRationelle(const string &s);
        Forme_decimale *creerUneLitteraleReel(const string &s);
        Forme_fraction *creerUneLitteraleEntiere(const string& s);
        Litteral_numerique *creerUneLitteraleComplexe(const string& s);
        int *getNumEtDen(const string & fraction);
        string *getReEtIm(const string & fraction);

};

class Computer
{
    private:
        Pile* pileActuelle;
        int maxHistorique;
        Analyseur a;
        Pile** historiqueUndo;
        int undoDisponible;
        Pile** historiqueRedo;
        int redoDisponible;

    public:
        Computer(int T=500): a(), pileActuelle(new Pile),historiqueUndo(new Pile*[T]), maxHistorique(T), historiqueRedo(new Pile*[T]),redoDisponible(0),undoDisponible(0) {}
        Computer(map<string,Operateur&> opSupp, int T=500) : a(opSupp), pileActuelle(new Pile),historiqueUndo(new Pile*[T]), maxHistorique(T), historiqueRedo(new Pile*[T]),redoDisponible(0),undoDisponible(0) {}
        Pile& getPileActuelle() const { return *pileActuelle; }
        Litteral& pop();
        void push(Litteral& L);
        void afficherPile() { if(pileActuelle != 0) pileActuelle->afficher();};
        void setPileActuelle(Pile &P) { pileActuelle = &P; }

        void pushHistorique(Pile& P, bool isUndo=true);
        Pile& popHistorique(bool isUndo=true);
        void undo();
        void redo();

        Analyseur& getAnalyseur() { return a; }

        void effectuer(string commande); // Computer& c);
        void effectuer(ConteneurOperande** exp, unsigned int nbOp);// Computer& c);

};


#endif // ANALYSEUR_H_INCLUDED
