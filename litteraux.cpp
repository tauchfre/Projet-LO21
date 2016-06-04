#include "litteraux.h"
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

/* Méthodes forme décimale */
Reel& Forme_decimale::operator+(const Reel& terme) const
{
    return *(new Forme_decimale(valeur+terme.getValeur()));
}
Reel& Forme_decimale::operator-(const Reel& terme) const
{
    return *(new Forme_decimale(valeur-terme.getValeur()));
}
Reel& Forme_decimale::operator/(const Reel& terme) const
{
    return *(new Forme_decimale(valeur/terme.getValeur()));
}
Reel& Forme_decimale::operator*(const Reel& terme) const
{
    return *(new Forme_decimale(valeur*terme.getValeur()));
}


/* Méthodes forme fraction */

Forme_fraction& Forme_fraction::fraction_simple() const
{
    int pgcd = PGCD(numerateur, denominateur);
    return *(new Forme_fraction(numerateur / pgcd, denominateur / pgcd));
}
Reel& Forme_fraction::operator+(const Forme_fraction& terme) const
{
    int n1 = numerateur, d1 = denominateur, n2 = terme.getNumerateur(), d2 = terme.getDenominateur();
    Forme_fraction *Res = new Forme_fraction(n1*d2+n2*d1,d1*d2);
    Res->simplifier();
    return *Res;
}
Reel& Forme_fraction::operator-(const Forme_fraction& terme) const
{
    int n1 = numerateur, d1 = denominateur, n2 = terme.getNumerateur(), d2 = terme.getDenominateur();
    Forme_fraction *Res = new Forme_fraction(n1*d2-n2*d1,d1*d2);
    Res->simplifier();
    return *Res;
}
Reel& Forme_fraction::operator*(const Forme_fraction& terme) const
{
    int n1 = numerateur, d1 = denominateur, n2 = terme.getNumerateur(), d2 = terme.getDenominateur();
    Forme_fraction *Res = new Forme_fraction(n1*n2,d1*d2);
    Res->simplifier();
    return *Res;
}
Reel& Forme_fraction::operator/(const Forme_fraction& terme) const
{
    int n1 = numerateur, d1 = denominateur, n2 = terme.getNumerateur(), d2 = terme.getDenominateur();
    Forme_fraction *Res = new Forme_fraction(n1*d2,d1*n2);
    Res->simplifier();
    return *Res;
}
bool operator==(const Forme_fraction &f1, const Forme_fraction &f2)
{
     Forme_fraction f1_simple = f1.fraction_simple();
     Forme_fraction f2_simple = f2.fraction_simple();
     return (f1_simple.getNumerateur()==f2_simple.getNumerateur())&&(f1_simple.getDenominateur()==f2_simple.getDenominateur());
}
bool operator!=(const Forme_fraction& f1, const Forme_fraction& f2)
{
    return !(f1==f2);
}


/* Méthode littéral numérique */
Litteral_calculable& Litteral_numerique::operator+(const Litteral_numerique& L) const
{
    cout << "L_n + L_n -> L_c" << endl;
    Reel& p_reele = partie_reele + L.getRe();
    Reel& p_imag = partie_imaginaire + L.getIm();
    return *(new Litteral_numerique(p_reele, p_imag));
}
Litteral_calculable& Litteral_numerique::operator-(const Litteral_numerique& L) const
{
    Reel& p_reele = partie_reele - L.getRe();
    Reel& p_imag = partie_imaginaire - L.getIm();
    return *(new Litteral_numerique(p_reele, p_imag));
}
Litteral_calculable& Litteral_numerique::operator*(const Litteral_numerique& L) const
{
    Reel &re1 = partie_reele, &im1 = partie_imaginaire, &re2 = L.getRe(), &im2 = L.getIm();
    return *(new Litteral_numerique(re1*re2 - im1*im2, re1 * im2 + im1 * re2));

}
Litteral_calculable& Litteral_numerique::operator/(const Litteral_numerique& L) const
{
    Reel &re1 = partie_reele, &im1 = partie_imaginaire, &re2 = L.getRe(), &im2 = L.getIm();
    return *(new Litteral_numerique((im1*im2 + re1*re2)/(im2*im2 + re2*re2), (im1*re2 - im2*re1)/(im2*im2 + re2*re2)));
}

ostream& Litteral_numerique::concat(ostream& f) const
{

    if(partie_imaginaire.getValeur()==0)
    {

         return f << partie_reele;
    }
    else if(partie_imaginaire.getValeur() > 0)
        return f << partie_reele << " + " << partie_imaginaire << " i";
    else
        return f << partie_reele << " - " << partie_imaginaire.negatif() << " i";
}
ostream& operator<<(ostream& f, const Litteral& L)
{
    return L.concat(f);
}
ostream& operator<<(ostream& f, const Reel& reel)
{
    return reel.concat(f);
}

// METHODES LITTERALE EXPRESSIOn

Litteral& Litteral_expression::copie() const
{

    return *( new Litteral_expression(*this) ); // Appel du constructeur de recopie
}
Litteral_calculable& Litteral_expression::operator+(const Litteral_calculable& L) const
{
    cout << "L_e + L_e -> L_c" << endl;
    ostringstream os;
    os << "(" << this->toStr() << ")+(" << L.toStr() << ")";
    return * ( new Litteral_expression(os.str()));
}
Litteral_calculable& Litteral_expression::operator-(const Litteral_calculable& L) const
{
    ostringstream os;
    os << "(" << this->toStr() << ")-(" << L.toStr() << ")";
    return * ( new Litteral_expression(os.str()));
}
Litteral_calculable& Litteral_expression::operator*(const Litteral_calculable& L) const
{
    ostringstream os;
    os << "(" << this->toStr() << ")*(" << L.toStr() << ")";
    return * ( new Litteral_expression(os.str()));
}
Litteral_calculable& Litteral_expression::operator/(const Litteral_calculable& L) const
{
    ostringstream os;
    os << "(" << this->toStr() << ")/(" << L.toStr() << ")";
    return * ( new Litteral_expression(os.str()));
}



string toRPN(string exp) // Exp sans espace => expression en RPN; tout chaine inconnue est transformée en littérale
{
    bool analysingLitteral = false,analysingOpUnaire = false;
    string *str= new string[50];
    string carac;
    string opUnaire = "";
    int nbStr=0, j=0;
    for(int i =0; i < exp.size(); i++) // Cette boucle transforme une expression en une suite de string
    {
        carac = "";
        if(exp[i] != ' ')
            carac.push_back(exp[i]);

        if(carac == "(" && analysingOpUnaire)
        {
            analysingLitteral = false;
            str[nbStr] = opUnaire + carac;
            nbStr++;
            opUnaire = "";
            analysingOpUnaire = false;
        }
        else if((int)exp[i]>=(int)'A' && (int)exp[i]<=(int)'Z')
        {
            opUnaire += carac;
            analysingOpUnaire = true;
            analysingLitteral = false;
        }
        else
        {
            if(analysingOpUnaire)
            {
                analysingOpUnaire = false;
                analysingLitteral = true;
                str[nbStr] = opUnaire;
                opUnaire = "";
                nbStr++;
            }
            if(carac == "*" || carac == "+" || carac == "/" || carac == "-" || carac == "(" || carac == ")")
            {
                analysingLitteral = false;
                str[nbStr] = carac;
                nbStr++;
            }
            else if(!analysingLitteral)
            {
                str[nbStr] = carac;
                analysingLitteral = true;
                analysingOpUnaire = false;
                opUnaire = "";
                nbStr++;
            }
            else
            {
                str[nbStr-1] = str[nbStr-1] + carac ;
            }
        }
    }
    string output = "";
    stack<string> opstack;
    for(j = 0; j < nbStr; j++) // cette boucle analyse une suite de string formée de litterales et d'opérateurs
    {
        if(str[j] == "*" || str[j] == "/" || str[j] == "(" || (str[j][0] <= 'Z' && str[j][0] >= 'A' && *str[j].rbegin() == '('))
        {
            opstack.push(str[j]);
        }
        else if(str[j] == "-" || str[j] == "+")
        {
            while(!opstack.empty() && opstack.top() != "(" && !( opstack.top()[0] <= 'Z' && opstack.top()[0] >= 'A' && *opstack.top().rbegin() == '('))
               {
                output  += opstack.top() + " ";
                opstack.pop();
            }
            opstack.push(str[j]);
        }
        else if(str[j] == ")")
        {
            while(!opstack.empty() && opstack.top() != "("  && !( opstack.top()[0] <= 'Z' && opstack.top()[0] >= 'A' && *opstack.top().rbegin() == '('))
            {
                output  += opstack.top() + " ";
                opstack.pop();
            }
            if(!opstack.empty() && opstack.top() == "(")
                opstack.pop();
            else if(!opstack.empty())
            {
                output += opstack.top().erase(opstack.top().size() - 1) + " ";
                opstack.pop();
            }
        }
        else
        {
            output += str[j] + " ";
        }
    }
    while(!opstack.empty())
    {
        output  += opstack.top() + " ";
        opstack.pop();
    }
    return output;

}

/* Fonctions annexes */

int PGCD(int a, int b)
{
    bool negatif = false;
    if(a<0)
    {
        a = -a;
        negatif = !negatif;
    }
    if(b<0)
    {
        b = -b;
        negatif = !negatif;
    }
    while(a != 0 && b != 0)
    {
        if(a>b)
        {
            a = a-b;
        }
        else
        {
            b = b-a;
        }
    }
    int facteur;
    if(negatif)
        facteur = -1;
    else
        facteur = 1;
    if(a==0)
        return facteur*b;
    else
        return facteur*a;
}
