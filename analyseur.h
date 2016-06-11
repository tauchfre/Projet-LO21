#ifndef ANALYSEUR_H_INCLUDED
#define ANALYSEUR_H_INCLUDED

#include "atomes.h"
#include "litteraux.h"
#include "pile.h"
#include "operateurs.h"

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "qanalyseur.h"



class Analyseur
{
    ListeAtomes& atomes;
    QString message;
    public:

        void setMessage(const QString & mess){message = mess; }
        QString getMessage(){return message;}
        Analyseur() : atomes(* new ListeAtomes) {}
        ListeAtomes& getAtomes() { return atomes; }
        Litteral_numerique* evaluer(ConteneurOperande** exp, unsigned int taille);
        Litteral_numerique* evaluer(QString str);
        Operateur* creerOperateur(QString ID);
        virtual Operateur* operateurSupplementaire(QString ID) { return 0; }

        void effectuer(ConteneurOperande** exp, unsigned int nbOp, Computer &c);

        ConteneurOperande** interpreter(const QString &commande);
        Forme_fraction *creerUneLitteraleRationelle(const QString &s);
        Forme_decimale *creerUneLitteraleReel(const QString &s);
        Forme_fraction *creerUneLitteraleEntiere(const QString& s);
        Litteral_numerique *creerUneLitteraleComplexe(const QString& s);

        int *getNumEtDen(const QString & fraction);
        QString *getReEtIm(const QString & fraction);
};

class Computer : public QObject
{
	Q_OBJECT

    private:
        Pile* pileActuelle;
        int maxHistorique;
        Analyseur a;
        Pile** historiqueUndo;
        int undoDisponible;
        Pile** historiqueRedo;
        int redoDisponible;
        int nbAfficher;




    public:
        Computer(int T=50): a(), pileActuelle(new Pile),historiqueUndo(new Pile*[T]), maxHistorique(T), historiqueRedo(new Pile*[T]),redoDisponible(0),undoDisponible(0) {}
        Pile& getPileActuelle() const { return *pileActuelle; }
        Litteral& pop();
        void push(Litteral& L);
        void setPileActuelle(Pile &P) { pileActuelle = &P; }
        void pushHistorique(Pile& P, bool isUndo=true);
        Pile& popHistorique(bool isUndo=true);
        Analyseur& getAnalyseur() { return a; }
        void setNbAfficher(int nb){nbAfficher = nb;}
        int getNbAfficher(){return nbAfficher;}
		
        void effectuer(QString commande); // Computer& c);
        void effectuer(ConteneurOperande** exp, unsigned int nbOp);// Computer& c);
		
        signals:
             void modificationEtat();

};


#endif // ANALYSEUR_H_INCLUDED
