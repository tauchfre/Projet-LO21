#ifndef ANALYSEUR_H_INCLUDED
#define ANALYSEUR_H_INCLUDED

#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"
#include <iostream>
#include <string>
#include<list>


class ConteneurOperande // Sert à exprimer des expression / suite d'opérandes
{
    private:
        Operateur* o;
        Litteral* l;
        bool trueIfLitteral;
    public:
        ConteneurOperande(Litteral& L) : o(0), l(&L), trueIfLitteral(true) {}
        ConteneurOperande(Operateur& O) : o(&O), l(0), trueIfLitteral(false) {}
        bool isLitteral() { return trueIfLitteral; }
        Operateur* getOperateur() { return o; }
        Litteral* getLitteral() { return l; }
};

class Analyseur // Contient les fonctions essentielles à l'analyse dans le controleur, peut être surchagé avec d'autres operateurs !
{
    unsigned int nbOperande;
    /*list<string> liste;*/

    public:
        /*list<string> setListe();*/
        Analyseur() : nbOperande(0)/* , liste(setListe())*/{} // idée = l'initialiser avec un objet qui rajoute des opérateurs ???  génius !!!!!
        // map<string,operateur>, utiliser dans creerOperateur un operateur de recopie :) !
        void effectuer(const string &commande, Computer& c);

        void effectuer(ConteneurOperande** exp, unsigned int nbOp, Computer& c);
        Litteral* evaluer(ConteneurOperande** exp, unsigned int taille);
        ConteneurOperande** interpreter(const string &commande);
        Operateur* creerOperateur(string ID);
        virtual Operateur* operateurSupplementaire(string ID) { return 0; }

        Forme_fraction *creerUneLitteraleRationelle(const string &s);
        Forme_decimale *creerUneLitteraleReel(const string &s);
        Forme_fraction *creerUneLitteraleEntiere(const string& s);
        Litteral_numerique *creerUneLitteraleComplexe(const string& s);

        unsigned int *getNumEtDen(const string & fraction);
        string *getReEtIm(const string & fraction);




};

class Computer
{
    private:
        Analyseur analyseur;
        Pile* pileActuelle;
        int maxHistorique;

        Pile** historiqueUndo;
        int undoDisponible;
        Pile** historiqueRedo;
        int redoDisponible;

    public:
        Computer(int T=50): analyseur(), pileActuelle(new Pile(50)),historiqueUndo(new Pile*[T]), maxHistorique(T), historiqueRedo(new Pile*[T]),redoDisponible(0),undoDisponible(0) {}
        Pile& getPileActuelle() const { return *pileActuelle; }
        Litteral& pop();
        void push(Litteral& L);
        void afficherPile() { if(pileActuelle != 0) pileActuelle->afficher();};
        void setPileActuelle(Pile &P) { pileActuelle = &P; }
        void pushHistorique(Pile& P, bool isUndo=true);
        Pile& popHistorique(bool isUndo=true);
        Analyseur *getAnalyseur(){ return &analyseur;}

};


#endif // ANALYSEUR_H_INCLUDED
