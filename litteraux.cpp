#include "litteraux.h"
#include "analyseur.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <typeinfo>
using namespace std;

/* Méthodes sur les réels */
Reel& Reel::operator+(const Reel& terme) const
{
    if(type == decimal || terme.type==decimal)
        return *(new Forme_decimale(this->getValeur()+terme.getValeur()));
    else
    {
        const Forme_fraction& terme_frac = dynamic_cast<const Forme_fraction&>(terme);
        const Forme_fraction& reel_actuel = dynamic_cast<const Forme_fraction&>(*this);
        int n1 = reel_actuel.getNumerateur(), d1 = reel_actuel.getDenominateur(),
         n2 = terme_frac.getNumerateur(), d2 = terme_frac.getDenominateur();
        Forme_fraction *Res = new Forme_fraction(n1*d2+n2*d1,d1*d2);
        Res->simplifier();
        return *Res;
    }
}
Reel& Reel::operator-(const Reel& terme) const
{
    if(type == decimal || terme.type==decimal)
        return *(new Forme_decimale(this->getValeur()-terme.getValeur()));
    else
    {
        const Forme_fraction& terme_frac = dynamic_cast<const Forme_fraction&>(terme);
        const Forme_fraction& reel_actuel = dynamic_cast<const Forme_fraction&>(*this);
        int n1 = reel_actuel.getNumerateur(), d1 = reel_actuel.getDenominateur(),
         n2 = terme_frac.getNumerateur(), d2 = terme_frac.getDenominateur();
        Forme_fraction *Res = new Forme_fraction(n1*d2-n2*d1,d1*d2);
        Res->simplifier();
        return *Res;
    }
}
Reel& Reel::operator*(const Reel& terme) const
{
    if(type == decimal || terme.type==decimal)
        return *(new Forme_decimale(this->getValeur()-terme.getValeur()));
    else
    {
        const Forme_fraction& terme_frac = dynamic_cast<const Forme_fraction&>(terme);
        const Forme_fraction& reel_actuel = dynamic_cast<const Forme_fraction&>(*this);
        int n1 = reel_actuel.getNumerateur(), d1 = reel_actuel.getDenominateur(),
         n2 = terme_frac.getNumerateur(), d2 = terme_frac.getDenominateur();
        Forme_fraction *Res = new Forme_fraction(n1*n2,d1*d2);
        Res->simplifier();
        return *Res;
    }
}
Reel& Reel::operator/(const Reel& terme) const
{
    if(type == decimal || terme.type==decimal)
        return *(new Forme_decimale(this->getValeur()-terme.getValeur()));
    else
    {
        const Forme_fraction& terme_frac = dynamic_cast<const Forme_fraction&>(terme);
        const Forme_fraction& reel_actuel = dynamic_cast<const Forme_fraction&>(*this);
        int n1 = reel_actuel.getNumerateur(), d1 = reel_actuel.getDenominateur(),
         n2 = terme_frac.getNumerateur(), d2 = terme_frac.getDenominateur();
        if(d1*n2 == 0)
            throw(ExceptionLitteral("Division par 0"));
        Forme_fraction *Res =  new Forme_fraction(n1*d2,d1*n2);
        Res->simplifier();
        return *Res;
    }
}

/* Méthodes forme fraction */

Forme_fraction& Forme_fraction::fraction_simple() const
{
    int pgcd = PGCD(numerateur, denominateur);
    return *(new Forme_fraction(numerateur / pgcd, denominateur / pgcd));
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

// Methodes sur les litteraux calculables

ostream& Litteral_numerique::concat(ostream& f) const
{
    if(0==partie_imaginaire.getValeur())
    {
         return f << partie_reele;
    }
    else if(partie_imaginaire.getValeur() > 0)
        return f << partie_reele << " + " << partie_imaginaire << "i";
    else
        return f << partie_reele << " - " << partie_imaginaire.negatif() << "i";
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
Litteral* Litteral_expression::eval(Computer &c) const
{
    string new_exp = toRPN(exp);
    Litteral* Res = c.getAnalyseur().evaluer(new_exp);
    c.popHistorique(true);
    if(Res != 0)
        return  Res;
    else
        throw(ExceptionLitteral("Erreur dans l'évaluation de l'expression"));
}
Litteral_calculable& Litteral_calculable::operator/(const Litteral_calculable& L) const
{
    if(getType() == expression || L.getType() == expression)
    {
        ostringstream os;
        os << "(" << this->toStr() << ")/(" << L.toStr() << ")";
        return * ( new Litteral_expression(os.str()));
    }
    else
    {
        try
        {
            const Litteral_numerique* L_actuel = dynamic_cast<const Litteral_numerique*>(this);
            const Litteral_numerique& L_num = dynamic_cast<const Litteral_numerique&>(L);
            Reel &re1 = L_actuel->getRe(), &im1 = L_actuel->getIm(), &re2 = L_num.getRe(), &im2 = L_num.getIm();
            return *(new Litteral_numerique((im1*im2 + re1*re2)/(im2*im2 + re2*re2), (im1*re2 - im2*re1)/(im2*im2 + re2*re2)));
        }
        catch(std::bad_cast& e)
        {
            throw ExceptionLitteral("Le littéral n'est pas de type connu");
        }
    }
}
Litteral_calculable& Litteral_calculable::operator+(const Litteral_calculable& L) const
{
    if(getType() == expression || L.getType() == expression)
    {
        ostringstream os;
        os << "(" << this->toStr() << ")+(" << L.toStr() << ")";
        return * ( new Litteral_expression(os.str()));
    }
    else
    {
        try
        {
            const Litteral_numerique* L_actuel = dynamic_cast<const Litteral_numerique*>(this);
            const Litteral_numerique& L_num = dynamic_cast<const Litteral_numerique&>(L);
            Reel& p_reele = L_actuel->getRe() + L_num.getRe();
            Reel& p_imag = L_actuel->getIm() + L_num.getIm();
            return *(new Litteral_numerique(p_reele, p_imag));
        }
        catch(std::bad_cast& e)
        {
            throw ExceptionLitteral("Le littéral n'est pas de type connu");
        }
    }
}
Litteral_calculable& Litteral_calculable::operator-(const Litteral_calculable& L) const
{
    if(getType() == expression || L.getType() == expression)
    {
        ostringstream os;
        os << "(" << this->toStr() << ")-(" << L.toStr() << ")";
        return * ( new Litteral_expression(os.str()));
    }
    else
    {
        try
        {
            const Litteral_numerique* L_actuel = dynamic_cast<const Litteral_numerique*>(this);
            const Litteral_numerique& L_num = dynamic_cast<const Litteral_numerique&>(L);
            Reel& p_reele = L_actuel->getRe() - L_num.getRe();
            Reel& p_imag = L_actuel->getIm() - L_num.getIm();
            return *(new Litteral_numerique(p_reele, p_imag));
        }
        catch(std::bad_cast& e)
        {
            throw ExceptionLitteral("Le littéral n'est pas de type connu");
        }
    }
}
Litteral_calculable& Litteral_calculable::operator*(const Litteral_calculable& L) const
{
    if(getType() == expression || L.getType() == expression)
    {
        ostringstream os;
        os << "(" << this->toStr() << ")*(" << L.toStr() << ")";
        return * ( new Litteral_expression(os.str()));
    }
    else
    {
         try
        {
            const Litteral_numerique* L_actuel = dynamic_cast<const Litteral_numerique*>(this);
            const Litteral_numerique& L_num = dynamic_cast<const Litteral_numerique&>(L);
            Reel &re1 = L_actuel->getRe(), &im1 = L_actuel->getIm(), &re2 = L_num.getRe(), &im2 = L_num.getIm();
            return *(new Litteral_numerique(re1*re2 - im1*im2, re1 * im2 + im1 * re2));
        }
        catch(std::bad_cast& e)
        {
            throw ExceptionLitteral("Le littéral n'est pas de type connu");
        }
    }
}

Litteral& Litteral_expression::copie() const
{
    return *( new Litteral_expression(*this) ); // Appel du constructeur de recopie
}


string toRPN(string exp) // Exp sans espace => expression en RPN; tout chaine inconnue est transformée en littérale
{
    bool analysingLitteral = false,analysingOpUnaire = false;
    string *str= new string[50];
    string carac;
    string lastcarac = "";
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
            if(carac == "*" || carac == "+" || carac == "(" || carac == ")" || (lastcarac == " " && ( carac == "/" || carac == "-" )))
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
            lastcarac = "";
            lastcarac.push_back(exp[i]);
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
    output.erase(output.size() - 1);
    return output;

}
// FONCTIONS LITTERALES PROGRAMMES
Litteral* Litteral_programme::eval(Computer &c) const
{
    try
    {
        c.effectuer(commande);
        c.popHistorique(true);
        return 0;
    }
    catch(Exception e)
    {
        throw(ExceptionLitteral("Programme mal défini"));
    }
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
