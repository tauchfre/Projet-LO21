#ifndef LITTERAUX_H_INCLUDED
#define LITTERAUX_H_INCLUDED


#include <iostream>
#include <cstring>

using namespace std;
// GESTION DES EXCEPTION

class Exception
{
    protected:
        string erreur;
    public:
        Exception(const char* err) : erreur((string)err) {}
        Exception(string err) : erreur(err) {}
        virtual  void afficher() { cout << erreur; }
};
class ExceptionLitteral : public Exception
{
    public:
        ExceptionLitteral(const char* err) :  Exception(err) {}
        void afficher() { cout << "Erreur avec les littéraux :" << erreur; }
};


class Litteral
{
    public:
        virtual ostream& concat(ostream& f) const { throw ExceptionLitteral("Pas de concat pour ce littéral"); }
        virtual Litteral& copie() const = 0;
};
class Litteral_calculable : public Litteral
{
};



// GESTION DES REELS

class Reel
{
    public:
        // On définit une concaténation avec un flux ostream&
        virtual ostream& concat(ostream& f) const=0;

        // On définit les opérateurs principaux sinon on envoie une exception
        virtual Reel& operator+(const Reel& terme) const { throw ExceptionLitteral("Pas d'opérateur + défini pour ce type de Réel"); }
        virtual Reel& operator-(const Reel& terme) const { throw ExceptionLitteral("Pas d'opérateur - défini pour ce type de Réel"); }
        virtual Reel& operator*(const Reel& terme) const { throw ExceptionLitteral("Pas d\'opérateur * défini pour ce type de Réel"); }
        virtual Reel& operator/(const Reel& terme) const { throw ExceptionLitteral("Pas d\'opérateur / défini pour ce type de Réel"); }
        virtual Reel& negatif() const { throw ExceptionLitteral("Pas de négation définie pour ce type de Réel"); }

        // On définit une fonction qui permet d'obtenir une valeur flottante du réel
        virtual float getValeur() const = 0;

        // On définit des opérations par défaut basées sur cette valeur flottante
        virtual bool operator==(const Reel& R) const
        {
            return R.getValeur() == (*this).getValeur();
        }
        virtual bool operator!=(const Reel& R) const
        {
            return R.getValeur() != (*this).getValeur();
        }

};

/* Fonctionnement des opérations
decimal (opération) réel donne un décimal
fraction (opération) fraction donne une fraction
fraction (opération) décimal  donne un décimal
*/

class Forme_decimale : public Reel
{
    private:
        float valeur;
    public:
        Forme_decimale(float v) : valeur(v){}
        ostream& concat(ostream& f) const { return f << valeur;}
        float getValeur() const { return valeur;}
        Reel& negatif() const { return * (new Forme_decimale(-valeur)) ; }
        Reel& operator+(const Reel& terme) const;
        Reel& operator-(const Reel& terme) const;
        Reel& operator*(const Reel& terme) const;
        Reel& operator/(const Reel& terme) const;
};

int PGCD(int a, int b);
class Forme_fraction : public Reel
{
    private:
        int numerateur;
        int denominateur;
    public:
        Forme_fraction(int a, int b=1) : numerateur(a), denominateur(b){ (*this).simplifier();}
        ostream& concat(ostream& f) const { if(denominateur != 1) return f << numerateur << "/" << denominateur; else return f << numerateur;}
        Forme_fraction& fraction_simple() const;
        void simplifier() { int pgcd = PGCD(numerateur, denominateur);  numerateur /= pgcd; denominateur /= pgcd;}
        int getNumerateur() const { return numerateur;}
        int getDenominateur() const { return denominateur;}
        float getValeur() const { return (float)numerateur/(float)denominateur;}

        Reel& negatif() const { return * (new Forme_fraction(-numerateur, denominateur)) ; }

        Reel& operator+(const Forme_decimale& terme) const {return terme+(*this);}
        Reel& operator-(const Forme_decimale& terme) const {return terme-(*this);}
        Reel& operator*(const Forme_decimale& terme) const {return terme*(*this);}
        Reel& operat,or/(const Forme_decimale& terme) const {return terme/(*this);}

        Reel& operator+(const Forme_fraction& terme) const;
        Reel& operator-(const Forme_fraction& terme) const;
        Reel& operator*(const Forme_fraction& terme) const;
        Reel& operator/(const Forme_fraction& terme) const;
};
bool operator==(const Forme_fraction &f1, const Forme_fraction &f2);
bool operator!=(const Forme_fraction &f1, const Forme_fraction &f2);


// GESTION DES LITTERAUX NUMERIQUES

class Litteral_numerique : public Litteral_calculable
{
    private:
        Reel& partie_reele;
        Reel& partie_imaginaire;
    public:
        Litteral_numerique(Reel& re, Reel& im) : partie_reele(re), partie_imaginaire(im) {}
        Litteral_numerique(float re, float im=0) : partie_reele(*(new Forme_decimale(re))), partie_imaginaire(*(new Forme_decimale(im))) {}
        Litteral_numerique(const Litteral_numerique& L) : partie_reele(L.getRe()), partie_imaginaire(L.getIm()) { }
         // On redéfinit le constructeur de recopie car on traite des membres références. Celui ci utilise les constructeur de recopie des classes rééles et derivées de réeles
        Reel& getRe() const{return partie_reele;}
        Reel& getIm() const{return partie_imaginaire;}
        ostream& concat(ostream& f) const;
        Litteral_numerique& operator+(const Litteral_numerique& L) const;
        Litteral_numerique& operator-(const Litteral_numerique& L) const;
        Litteral_numerique& operator*(const Litteral_numerique& L) const;
        Litteral_numerique& operator/(const Litteral_numerique& L) const;
        Litteral& copie() const{ return * (new Litteral_numerique(*this));}
};

ostream& operator<<(ostream& f, const Reel& reel);
ostream& operator<<(ostream& f, const Litteral& L);



void test();
#endif // LITTERAUX_H_INCLUDED
