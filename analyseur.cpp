#include "analyseur.h"
#include <iostream>
#include <string>
#include<list>

/*

list<string> Analyseur::setListe(){
    list<string> liste;
    liste.push_back("DUP");
    liste.push_back("DROP");
    liste.push_back("SWAP");
    liste.push_back("LASTOP");
    liste.push_back("LASTARGS");
    liste.push_back("UNDO");
    liste.push_back("REDO");
    liste.push_back("CLEAR");
    liste.push_back("DIV");
    liste.push_back("MOD");
    liste.push_back("NUM");
    liste.push_back("IM");
    liste.push_back("+");
    liste.push_back("-");
    liste.push_back("*");
    liste.push_back("/");
    liste.push_back("NEG");

}
*/
// METHODE DE LA CLASSE OPERATEURFACTORY

Operateur* Analyseur::creerOperateur(string ID)
{
    if(ID == "DUP")
    {
        return (new Dupliquer);
    }
 /*   else if(ID == "DROP")
    {
        return (new Drop);
    }
    else if(ID == "SWAP")
    {
        return (new Swap);
    }
    else if(ID == "LASTOP")
    {
        return (new Lastop);
    }
    else if(ID == "LASTARGS")
    {
        return (new Lastargs);
    }
    else if(ID == "UNDO")
    {
        return (new Undo);
    }
    else if(ID == "REDO")
    {
        return (new Redo);
    }
    else if(ID == "CLEAR")
    {
        return (new Clear);
    }
    else if(ID == "MOD")
    {
        return (new Mod);
    }
    else if(ID == "NEG")
    {
        return (new Neg);
    }
    else if(ID == "NUM")
    {
        return (new Num);
    }
    else if(ID == "IM")
    {
        return (new Im);
    }
    */
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
    else if(ID == "/")
    {
        return (new Diviser);
    }
    else
    {
        return operateurSupplementaire(ID);
    }
}
Litteral* Analyseur::evaluer(ConteneurOperande** exp, unsigned int taille)
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
        return &P.pop();
}


// METHODES DE LA CLASSE PILEMANAGER

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






Forme_fraction *Analyseur::creerUneLitteraleRationelle(const string &s){

    size_t place;
    place = s.find_first_of("\/");
    if(place != -1)
    {
    string numerateur;
    string denominateur;

    numerateur = s.substr(0, place);
    denominateur = s.substr(place+1);


    unsigned int i;
    bool pnum = true;
    bool pden = true;

    for(i=0; i<numerateur.size(); i++){

        if(numerateur[i]>'9'||numerateur[i]<'0')
            pnum = false;

    }

        for(i=0; i<denominateur.size(); i++){

        if(denominateur[i]>'9'||denominateur[i]<'0')
            pden = false;

    }

    if(pnum == true && pden == true){
            unsigned int *tab = getNumEtDen(s);
            Forme_fraction frac(tab[0], tab[1]);
            return &frac;

    }
    }

}


Forme_decimale *Analyseur::creerUneLitteraleReel(const string &s){
    size_t place;

    place = s.find_first_of("\.");
    if(place == -1){return false;}
    string partie_entiere;
    string partie_decimale;
    partie_entiere = s.substr(0, place);
    partie_decimale = s.substr(place+1);


    unsigned int i;
    bool pentiere = true;
    bool pdecimale = true;
    if((!partie_entiere.empty()) && (!partie_decimale.empty()))
    {
        for(i=0; i<partie_entiere.size(); i++)
        {
            if(partie_entiere[i]>'9'||partie_entiere[i]<'0')
            pentiere = false;
        }

        for(i=0; i<partie_decimale.size(); i++)
        {
            if(partie_decimale[i]>'9'||partie_decimale[i]<'0')
            pdecimale = false;
        }
        if(pentiere == true && pdecimale == true){

                float val = atof( s.c_str());
                Forme_decimale  f_dec(val);
                return &f_dec;
        }
    }

    else if(partie_entiere.empty() && !partie_decimale.empty())
    {

        partie_entiere == "0";
        for(i=0; i<partie_decimale.size(); i++)
        {
            if(partie_decimale[i]>'9'||partie_decimale[i]<'0')
            pdecimale = false;
        }
        if(pdecimale == true){

            string reel = partie_entiere + "\." + partie_decimale;
            float val = atof( reel.c_str());
            Forme_decimale f_dec(val);
            return &f_dec;
        }

    }
    else if(partie_decimale.empty() && !partie_entiere.empty())
    {
        for(i=0; i<partie_entiere.size(); i++)
        {
            if(partie_entiere[i]>'9'||partie_entiere[i]<'0')
            pentiere = false;
        }
        if(pentiere == true){

            int entier = atoi( partie_entiere.c_str());
            Forme_decimale f_ent(entier);
            return &f_ent;
        }

    }



}

Forme_fraction *Analyseur::creerUneLitteraleEntiere(const string& s){
	unsigned int i;
	bool entier = true;
	for(i = 0; i< s.size(); i++)
    {
        if (s[i]>'9'||s[i]<'0') entier = false;
    }

    if (entier == true){
            int entier = atoi( s.c_str());
            Forme_fraction f_ent(entier);
            return &f_ent;
    }

}


Litteral_numerique *Analyseur::creerUneLitteraleComplexe(const string& s){
    string *type = new string[2];
    type = getReEtIm(s);
    int slash;
    int point;
    slash = s.find_first_of("\/");
    point = s.find_first_of("\.");
    Reel **reel = new Reel*[2];

    for(unsigned int i=0; i<2; i++){

        if(slash == -1&&point == -1){
                reel[i] = creerUneLitteraleEntiere(type[i]);
        }
        else if (slash != -1&&point == -1){

                reel[i] = creerUneLitteraleRationelle(type[i]);
        }
        else if (slash == -1 && point != -1){
                reel[i] = creerUneLitteraleReel(type[i]);
        }
        else
        throw ExceptionLitteral("Syntaxe invalide");

        for(i=0; i<2;i++){
            delete [] reel;
        }
    }
}


unsigned int *Analyseur::getNumEtDen(const string & fraction){

        size_t place;
        place = fraction.find_first_of("\/");
        unsigned int *tab = new unsigned int[2];
        unsigned int numerateur;
        unsigned int denominateur;

        if(place==-1){
            numerateur = atoi(fraction.c_str());
            denominateur = 1;
            tab[0] = numerateur;
            tab[1] = denominateur;
        }
        else{

        string num;
        string den;
        num = fraction.substr(0, place);
        den = fraction.substr(place+1);
        numerateur = atoi(num.c_str());
        denominateur = atoi(den.c_str());

        tab[0] = numerateur;
        tab[1] = denominateur;
        }
        return tab;
}


string *Analyseur::getReEtIm(const string & complexe){

        size_t place;
        place = complexe.find_first_of("\$");
        string pre;
        string pim;
        pre = complexe.substr(0, place);
        pim = complexe.substr(place+1);

        string *tab = new string[2];
        tab[0] = pre;
        tab[1] = pim;
        return tab;


}












//effectuer() permet d'appliquer les Operandes : Il empile si c'est un Literal ou effectue l'operation si c'est un operateur

void Analyseur::effectuer(ConteneurOperande** exp, unsigned int nbOp, Computer& c)
{

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



ConteneurOperande** Analyseur::interpreter(const string &commande){

    unsigned int i, occEsp =0, occProg = 0;
    char cEsp =' ';
    char cExp ='\'';
    char cProg1 = '\[';
    char cProg2 = '\]';
    bool expression = true;
    bool programme = true;


    for(i=0; i<commande.size(); i++)
    {

        if(commande[i]== cProg1 ) programme = false;
        else if(commande[i]== cProg2 ) programme = true;

        if(commande[i]== cExp && expression == true) expression = false;
        else if(commande[i]== cExp && expression == false) expression = true;

        if(commande[i]==cEsp && expression == true && programme == true)
        {
        occEsp++;
        }

    }

    unsigned int nb1=0;
    unsigned int nb2=0;
    for(i=0; i<commande.size(); i++)
    {

        if(commande[i]== cProg1 ) nb1++;
        if(commande[i]== cProg2 ) nb2++;

    }
    if (nb1==nb2){
        occProg = nb1;
    }
    else
        cout << "Erreur" << "\n";

   // cout << "Espace :"<<occEsp<<"\n";

    string *tab = new string[occEsp+1];

    unsigned int occtab=0;
//    unsigned int j;
    unsigned int k = 0;

    while(k<commande.size())
    {

        if(commande[k]==cEsp){k++;}

        else if(commande[k]== cProg1 )
        {
            unsigned int tour = 0;
            do
            {
                if(commande[k]==cProg2){tour++;}
                tab[occtab] = tab[occtab] + commande[k];
                k++;


            }while((commande[k]!=cProg2||tour <occProg-1)&& k<commande.size());
            tab[occtab] = tab[occtab] + commande[k];
            k++;            occtab++;
        }


        else if (commande[k]== cExp)
        {
            unsigned int conditionFin = 0;
            do
            {
                if(commande[k]==cExp){conditionFin++;}
                tab[occtab] = tab[occtab] + commande[k];
                k++;

            } while(commande[k]!=cExp && conditionFin <=1 && k<commande.size());
            tab[occtab] = tab[occtab] + commande[k];
            k++;
            occtab++;
        }

        else
        {
            while (commande[k]!=cEsp&&k< commande.size())
            {

                tab[occtab] = tab[occtab] + commande[k];
                k++;
            }            occtab++;
        }


    }

    ConteneurOperande **newtab = new ConteneurOperande*[occtab];

    //On a tab qui contient les Operande en string maintenant nous allons Implementer le tableau d'operande.

    unsigned int numOp;
    for(numOp=0; numOp < occtab; numOp++ ){
        int slash;
        int point;
        int dollar;
        int quote;
        int crochet;

        slash = tab[numOp].find_first_of("\/");
        point = tab[numOp].find_first_of("\.");
        dollar = tab[numOp].find_first_of("\$");
        quote = tab[numOp].find_first_of("\'");
        crochet = tab[numOp].find_first_of("\[");


        if(slash ==-1&&point==-1&&dollar==-1&&quote==-1&&crochet==-1){

            Forme_fraction *frac1 = creerUneLitteraleEntiere(tab[numOp]);
            Forme_fraction *frac2 = creerUneLitteraleEntiere("0/1");
            Litteral_numerique *Lit = new Litteral_numerique(*frac1, *frac2);
            ConteneurOperande *cL = new ConteneurOperande(*Lit);
            newtab[numOp] = cL;


        }
        else if(slash !=-1&&point==-1&&dollar==-1&&quote==-1&&crochet==-1){
            Forme_fraction *reel1 = creerUneLitteraleRationelle(tab[numOp]);
            Forme_fraction *reel2 = creerUneLitteraleRationelle("0/1");
            Litteral_numerique *Lit = new Litteral_numerique(*reel1, *reel2);
            ConteneurOperande *cL = new ConteneurOperande(*Lit);
            newtab[numOp] = cL;

        }
        else if(point!=-1&&slash ==-1&&dollar==-1&&quote==-1&&crochet==-1){
            Forme_decimale *dec1 = creerUneLitteraleReel(tab[numOp]);
            Forme_decimale *dec2 = creerUneLitteraleReel("0");
            Litteral_numerique *Lit = new Litteral_numerique(*dec1, *dec2);
            ConteneurOperande *cL= new ConteneurOperande(*Lit);
            newtab[numOp] = cL;

        }
        else if(dollar==-1&&quote==-1&&crochet==-1){

            Litteral_numerique *Lit = creerUneLitteraleComplexe(tab[numOp]);
            ConteneurOperande *cL= new ConteneurOperande(*Lit);
            newtab[numOp] = cL;
        }/*
        else
        {
                Operateur* Op = creerOperateur(tab[numOp]);
                ConteneurOperande oP(*Op);
                newtab[numOp] = &oP;
        }

        */
       /* else{


            bool inListe = false;
            list<string>::iterator it;
            for(it = liste.begin(); it!=liste.end(); it++)
            {
                if(tab[numOp] ==*(it))
                {
                    inListe = true;
                }
            }
            if(inListe == true)
            {
                Operateur* Op = creerOperateur(tab[numOp]);
                ConteneurOperande oP(*Op);
                newtab[numOp] = &oP;
            }

            else
                throw ExceptionLitteral("Syntaxe invalide");
                */
        }
        nbOperande = occtab;
        return newtab;




    }


void Analyseur::effectuer(const string& commande, Computer& c){

    ConteneurOperande** exp = interpreter(commande);
    effectuer(exp, nbOperande, c);
}





