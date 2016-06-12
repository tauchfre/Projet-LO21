

#include "analyseur.h"
#include "operateurs_instances.h"
#include <QTextStream>
#include <QString>
#include <cstdlib>

// METHODE DE LA CLASSE OPERATEURFACTORY


// METHODES DE LA CLASSE COMPUTER

void Computer::pushHistorique(Pile& P, bool isUndo)
{
    if(isUndo && undoDisponible < maxHistorique)
    {
        historiqueUndo[undoDisponible] = &P;
        undoDisponible++;
    }
    else if(!isUndo && redoDisponible < maxHistorique)
    {
        historiqueRedo[redoDisponible] = &P;
        redoDisponible++;
    }
    else
    {
        throw ExceptionPile("Taille de l'historique max atteinte");
    }
}
Pile& Computer::popHistorique(bool isUndo)
{
    if(isUndo && undoDisponible > 0)
    {
        undoDisponible--;
        return * (historiqueUndo[undoDisponible]);
    }
    else if(!isUndo && redoDisponible > 0)
    {
        redoDisponible--;
        return * (historiqueUndo[redoDisponible]);
    }
    else
    {
        throw ExceptionPile("Historique vide");
    }
}

Litteral& Computer::pop()
{
     pushHistorique(*pileActuelle, true);
     Pile newP(*pileActuelle);
     Litteral &res = newP.pop();
     pileActuelle = &newP;

     return res;
}
void Computer::push(Litteral& L)
{
     pushHistorique(*pileActuelle, true);
     Pile *newP = new Pile(*pileActuelle);
     newP->push(L);
     pileActuelle = newP;

}
void Computer::effectuer(ConteneurOperande** exp, unsigned int nbOp)
{
    a.effectuer(exp,nbOp,*this);
}
void Computer::effectuer(QString str)
{

    ConteneurOperande** commande = a.interpreter(str);

    unsigned int i;
    for(i = 0; commande != 0 && commande[i] != 0; i++ );
    effectuer(commande, i);

    modificationEtat();
}

// Analyseur
Litteral_numerique* Analyseur::evaluer(QString str)
{
    ConteneurOperande** commande = interpreter(str);
    unsigned int i;
    for(i = 0; commande != 0 && commande[i] != 0; i++ );
    return evaluer(commande, i);
}
void Analyseur::effectuer(ConteneurOperande** exp, unsigned int nbOp, Computer &c) {
    for(unsigned int i = 0; i < nbOp; i++)
    {
        if(exp[i]->isLitteral())
        {
            c.push(*exp[i]->getLitteral());
        }
        else
        {
            exp[i]->getOperateur()->appliquer(c);
        }
    }
}

Operateur* Analyseur::creerOperateur(QString ID) {
    if(ID == "DUP")
    {
        return (new Dupliquer);
    }
    else if(ID == "DROP")
    {
        return (new Drop);
    }
    else if(ID == "SWAP")
    {
        return (new Swap);
    }
    else if(ID == "CLEAR")
    {
        return (new Clear);
    }
    else if(ID == "+")
    {
        return (new Additionner);
    }
    else if(ID == "-")
    {
        return (new Soustraire);
    }
    else if(ID == "*")
    {
        return (new Multiplier);
    }
    else if(ID == "\/")
    {
        return (new Diviser);
    }
    else if(ID == "NEG")
    {
        return (new Neg);
    }
    else if(ID == "MOD")
    {
        return (new Mod);
    }
    else if(ID == "DIV")
    {
        return (new Div);
    }
   /* else if(ID == "UNDO")
    {
        return (new Undo);
    }
    else if(ID == "REDO")
    {
        return (new Redo);
    }*/
    else if(ID == "NUM")
    {
        return (new Num);
    }
    else if(ID == "DEN")
    {
        return (new Den);
    }
    else if(ID == "RE")
    {
        return (new Re);
    }
    else if(ID == "IM")
    {
        return (new Im);
    }
   else if(ID == "\$")
    {
        return (new creerComplexe);
    }
   else if(ID == "AND")
    {
        return (new And);
    }
   else if(ID == "OR")
    {
        return (new Or);
    }
   else if(ID == "NOT")
    {
        return (new Not);
    }
   else if(ID == "=")
    {
        return (new Egal);
    }
   else if(ID == "!=")
    {
        return (new Different);
    }
   else if(ID == "=<")
    {
        return (new InfOuEgal);
    }
   else if(ID == ">=")
    {
        return (new SupOuEgal);
    }
   else if(ID == "<")
    {
        return (new Inferieur);
    }
   else if(ID == ">")
    {
        return (new Superieur);
    }

/*
    else if(ID == "LASTOP")
    {
        return (new Lastop);
    }
    else if(ID == "LASTARGS")
    {
        return (new Lastargs);
    }*/
    else if(ID == "EVAL")
    {
        return (new Eval);
    }
    else if(ID == "STO")
    {
        return (new Sto(this));
    }
    else
    {
        return operateurSupplementaire(ID);
    }
}

Litteral_numerique* Analyseur::evaluer(ConteneurOperande** exp, unsigned int taille)
{
    Pile P;
    for(unsigned int i=0; i < taille; i++)
    {
        if(exp[i]->isLitteral())
        {
            P.push(*(exp[i]->getLitteral()));
        }
        else
        {
            P = exp[i]->getOperateur()->operation(P);
        }
    }
    if(P.getTaille() != 1)
        return 0;
    else
    {
        try
        {
            return dynamic_cast<Litteral_numerique*>(&(P.pop()));
        }
        catch(bad_cast e)
        {
            throw(ExceptionOperateur("EVAL n'évalue que les calculables"));
        }
    }
}

Forme_fraction *Analyseur::creerUneLitteraleRationelle(const QString &s){

    int place;
    QString slash = "\/";
    place = s.indexOf(slash);
    if(place != -1)
    {
    QString numerateur;
    QString denominateur;

    numerateur = s.mid(0, place);
    denominateur = s.mid(place+1);

    int i;
    bool pnum = true;
    bool pden = true;

    i = 0;
    if(numerateur[0]=='-'){i++;}
    for(i; i<numerateur.size(); i++){

        if(numerateur[i]>'9'||numerateur[i]<'0')
            pnum = false;

    }
        i = 0;
        if(denominateur[0]=='-'){i++;}
        for(i; i<denominateur.size(); i++){

        if(denominateur[i]>'9'||denominateur[i]<'0')
            pden = false;

    }

    if(pnum == true && pden == true){
            int *tab = getNumEtDen(s);
            Forme_fraction *frac = new Forme_fraction(tab[0], tab[1]);
            return frac;

        }
    }

}
Forme_decimale *Analyseur::creerUneLitteraleReel(const QString &s){
    int place;

    place = s.indexOf("\.");

    QString partie_entiere;
    QString partie_decimale;
    partie_entiere = s.mid(0, place);
    partie_decimale = s.mid(place+1);


    int i;
    bool pentiere = true;
    bool pdecimale = true;
    if((!partie_entiere.isEmpty()) && (!partie_decimale.isEmpty()))
    {
        i = 0;
        if(partie_entiere[0]=='-'){i++;}
        for(i; i<partie_entiere.size(); i++)
        {
            if(partie_entiere[i]>'9'||partie_entiere[i]<'0')
            pentiere = false;
        }

        i = 0;
        if(partie_decimale[0]=='-'){i++;}
        for(i; i<partie_decimale.size(); i++)
        {
            if(partie_decimale[i]>'9'||partie_decimale[i]<'0')
            pdecimale = false;
        }
        if(pentiere == true && pdecimale == true){

                float val =  s.toFloat();
                Forme_decimale *f_dec = new Forme_decimale(val);
                return f_dec;
        }
    }

    else if(partie_entiere.isEmpty() && !partie_decimale.isEmpty())
    {

        partie_entiere == "0";
        i = 0;
        if(partie_decimale[0]=='-'){i++;}
        for(i; i<partie_decimale.size(); i++)
        {
            if(partie_decimale[i]>'9'||partie_decimale[i]<'0')
            pdecimale = false;
        }
        if(pdecimale == true){

            QString reel = partie_entiere + "\." + partie_decimale;

            float val =  s.toFloat();
            Forme_decimale *f_dec = new Forme_decimale(val);
            return f_dec;
        }

    }
    else if(partie_decimale.isEmpty() && !partie_entiere.isEmpty())
    {

        partie_decimale == "0";
        i = 0;
        if(partie_entiere[0]=='-'){i++;}
        for(i; i<partie_entiere.size(); i++)
        {
            if(partie_entiere[i]>'9'||partie_entiere[i]<'0')
            pentiere = false;
        }
        if(pentiere == true){
            QString reel = partie_entiere + "\." + partie_decimale;
            float val =  s.toFloat();
            Forme_decimale *f_dec = new Forme_decimale(val);
            return f_dec;
        }


    }
}

Forme_fraction *Analyseur::creerUneLitteraleEntiere(const QString& s){
    int i = 0;
	bool entier = true;
	if(s[0]=='-'){i++;}
    for(i; i< s.size(); i++)
    {
        if (s[i]>'9'||s[i]<'0') entier = false;
    }

    if (entier == true){
            int entier = s.toInt();
            Forme_fraction *f_ent = new Forme_fraction(entier);
            return f_ent;
    }



}


Litteral_numerique *Analyseur::creerUneLitteraleComplexe(const QString& s){
    QString *type = new QString[2];
    type = getReEtIm(s);
    int *slash = new int[2];
    int *point = new int[2];
    slash[0] = type[0].indexOf("\/");
    slash[1] = type[1].indexOf("\/");
    point[0] = type[0].indexOf("\.");
    point[1] = type[1].indexOf("\.");
    Reel **reel = new Reel*[2];

    for(unsigned int i=0; i<2; i++){

        if(slash[i] == -1 && point[i] == -1){

                reel[i] = creerUneLitteraleEntiere(type[i]);
        }
        else if (slash[i] != -1 && point[i] == -1){

                reel[i] = creerUneLitteraleRationelle(type[i]);
        }
        else if (slash[i] == -1 && point[i] != -1){
                reel[i] = creerUneLitteraleReel(type[i]);
        }
        else
        throw ExceptionLitteral("Syntaxe invalide");
    }
        Litteral_numerique* Lit = new Litteral_numerique(*reel[0], *reel[1]);
        return Lit;

}
 int *Analyseur::getNumEtDen(const QString & fraction) {
        int place;
        place = fraction.indexOf("\/");
        int *tab = new int[2];
        int numerateur;
        int denominateur;

        if(place==-1){
            numerateur =fraction.toInt();
            denominateur = 1;
            tab[0] = numerateur;
            tab[1] = denominateur;
        }
        else{

        QString num;
        QString den;
        num = fraction.mid(0, place);
        den = fraction.mid(place+1);
        numerateur = num.toInt();
        denominateur = den.toInt();

        tab[0] = numerateur;
        tab[1] = denominateur;
        }
        return tab;
}
QString *Analyseur::getReEtIm(const QString & complexe) {
        int place;
        place = complexe.indexOf("\$");
        QString pre;
        QString pim;
        pre = complexe.mid(0, place);
        pim = complexe.mid(place+1);

        QString *tab = new QString[2];
        tab[0] = pre;
        tab[1] = pim;
        return tab;
}

ConteneurOperande** Analyseur::interpreter(const QString &commande) {

    int i, occEsp =0 ;
    char cEsp = ' ';
    char cExp ='\'';
    char cProg1 = '\[';
    char cProg2 = '\]';
    bool expression = true;
    bool programme = true;

    unsigned int prog = 0;
    for(i=0; i<commande.size(); i++)
    {

        if(commande[i]== cProg1 ) {prog++; programme = false;}
        else if(commande[i]== cProg2 && prog==0 ) programme = true;

        if(commande[i]== cExp && expression == true) expression = false;
        else if(commande[i]== cExp && expression == false) expression = true;

        if(commande[i]==cEsp && expression == true && programme == true)
        {
        occEsp++;
        }

    }



    QString *tab = new QString[occEsp+1];


    unsigned int occtab=0;

    unsigned int k = 0;

    while(k<commande.size())
    {
        // Si c'est un espace
        if(commande[k]==cEsp)
        {
            k++;

        }
        //Si c'est un programme
        else if(commande[k]== cProg1 )
        {
            tab[occtab] = tab[occtab] + commande[k];
            k++;
            unsigned int fin = 1;
            do
            {
                if(commande[k]==cProg1)
                {
                    tab[occtab] = tab[occtab] + commande[k];
                    fin++;
                    k++;
                }
                else if(commande[k]==cProg2&&fin!=0){
                    tab[occtab] = tab[occtab] + commande[k];
                    fin--;
                    k++;

                }
                else if(commande[k]==cProg2&&fin>0){
                    tab[occtab] = tab[occtab] + commande[k];
                    k++;

                }
                else{
                tab[occtab] = tab[occtab] + commande[k];
                k++;
                }


            }while(fin > 0 && k<commande.size());
            tab[occtab] = tab[occtab] + commande[k];
            k++;
            occtab++;
        }

        //Si c'est une expression
        else if (commande[k]== cExp)
        {
            unsigned int conditionFin = 0;
            do
            {
                if(commande[k]==cExp){conditionFin++;}
                tab[occtab] = tab[occtab] + commande[k];
                k++;

            } while(conditionFin <=1 && k<commande.size()-1);
            tab[occtab] = tab[occtab] + commande[k];
            k++;

           occtab++;
        }
        //pour le reste
        else
        {
            while (k< commande.size())
            {

                tab[occtab] = tab[occtab] + commande[k];
                k++;

            }
            occtab++;
        }


    }

    ConteneurOperande **newtab = new ConteneurOperande*[occtab+1];

    //On a tab qui contient les Operande en QString maintenant nous allons Implementer le tableau d'operande.

    unsigned int numOp;
    int slash;
    int point;
    int dollar;
    int quote;
    int crochet;
    int alphabet;
    for(numOp=0; numOp < occtab; numOp++ ){


        slash = tab[numOp].indexOf("\/");
        point = tab[numOp].indexOf("\.");
        dollar = tab[numOp].indexOf("\$");
        quote = tab[numOp].indexOf("\'");
        crochet = tab[numOp].indexOf("\[");
        alphabet = 26 + 25;
        for(char i='A'; i <= 'Z'; i++)
            alphabet += tab[numOp].indexOf(i);
        for(char i='a'; i <= 'z'; i++)
            alphabet += tab[numOp].indexOf(i);
        Operateur* Op = creerOperateur(tab[numOp]);
        if(Op)
        {

                ConteneurOperande *oP = new ConteneurOperande(*Op);
                newtab[numOp] = oP;
        }
        else
        {
            //Si c'est un entier
            if(alphabet<0&&slash ==-1&&point==-1&&dollar==-1&&quote==-1&&crochet==-1)
            {

                Forme_fraction *frac1 = creerUneLitteraleEntiere(tab[numOp]);
                Forme_fraction *frac2 = creerUneLitteraleEntiere("0");
                Litteral_numerique *Lit = new Litteral_numerique(*frac1, *frac2);
                ConteneurOperande *cL = new ConteneurOperande(*Lit);
                newtab[numOp] = cL;

            }
            //SI c'est un rationelle
            else if(slash !=-1&&point==-1&&dollar==-1&&quote==-1&&crochet==-1){

                Forme_fraction *reel1 = creerUneLitteraleRationelle(tab[numOp]);
                Forme_fraction *reel2 = creerUneLitteraleRationelle("0/1");
                Litteral_numerique *Lit = new Litteral_numerique(*reel1, *reel2);
                ConteneurOperande *cL = new ConteneurOperande(*Lit);
                newtab[numOp] = cL;

            }
            //Si c'est un réel
            else if(point!=-1&&slash ==-1&&dollar==-1&&quote==-1&&crochet==-1){

                Forme_decimale *dec1 = creerUneLitteraleReel(tab[numOp]);
                Forme_decimale *dec2 = creerUneLitteraleReel("0.0");
                Litteral_numerique *Lit = new Litteral_numerique(*dec1, *dec2);
                ConteneurOperande *cL= new ConteneurOperande(*Lit);
                newtab[numOp] = cL;

            }
            //SI c'est un Complexe
            else if(dollar!=-1&&quote==-1&&crochet==-1){


                Litteral_numerique *Lit = creerUneLitteraleComplexe(tab[numOp]);

                ConteneurOperande *cL= new ConteneurOperande(*Lit);
                newtab[numOp] = cL;
            }
            //Si c'est une Expression
            else if(quote != -1 && crochet == -1){
                tab[numOp].remove(0,1);
                tab[numOp].remove(tab[numOp].size() - 1);
                Litteral_expression *exp = new Litteral_expression(tab[numOp]);
                ConteneurOperande *cL = new ConteneurOperande(*exp);
                newtab[numOp] = cL;
            }
            // SI c'est un programme
            else if(quote == -1 && crochet != -1){

                tab[numOp].remove(0,1);
                tab[numOp].remove(tab[numOp].size() - 2);
                Litteral_programme *prog = new Litteral_programme(tab[numOp]);
                ConteneurOperande *cL = new ConteneurOperande(*prog);
                newtab[numOp] = cL;
            }
            else
            {
                TypeAtome existenceAtome = getAtomes().atomeExiste(tab[numOp]);
                if(existenceAtome == NIL)
                {
                    Litteral_expression *exp = new Litteral_expression(tab[numOp]);
                    ConteneurOperande *cL = new ConteneurOperande(*exp);
                    newtab[numOp] = cL;
                }
                else if(existenceAtome == prog)
                {
                    ConteneurOperande** ops = atomes.interpreter(tab[numOp]);
                    newtab[numOp] = ops[0];
//                    numOp++;
  //                  newtab[numOp] = ops[1];
                }
                else
                {
                    ConteneurOperande** ops = atomes.interpreter(tab[numOp]);
                    newtab[numOp] = ops[0];
                }
            }
//      throw ExceptionLitteral("Syntaxe invalide");

        }
    }
        newtab[occtab] = 0;
        return newtab;
    }
