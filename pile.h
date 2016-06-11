#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#include "litteraux.h"
class ExceptionPile: public Exception
{
    public:
        ExceptionPile(const char* err) :  Exception(err) {}
        void afficher() { cout << "Erreur avec une pile :" << erreur; }
};

class Pile
{
    private:
        Litteral** litteraux;
        int tailleMax;
        int taille;
    public:
        Pile(int T = 50):litteraux(new Litteral*[T+1]),tailleMax(T),taille(0){}
        Pile(const Pile& P);
        void afficher() const;
        void copierDans(Pile& P) const;
        void push(Litteral& L);
        int getTailleMax() const { return tailleMax; }
        int getTaille() const { return taille; }
        void setTaille(int T) { taille = T; }
        Litteral& pop();
        Litteral& top() { return *litteraux[taille-1]; }

        class iterator {
            Litteral** current;
            iterator(Litteral** u):current(u){}
            friend class Pile;
        public:
            iterator():current(0){}
            Litteral& operator*() const { return **current; }
            bool operator!=(iterator it) const { return current!=it.current; }
            iterator& operator++(){ ++current; return *this; }
        };
        iterator begin() { return iterator(litteraux); }
        iterator end() { return iterator(litteraux + taille); }


        class const_iterator {
            Litteral** current;
            const_iterator(Litteral** u):current(u){}
            friend class Pile;
        public:
            const_iterator():current(0){}
            Litteral& operator*() const { return **current; }
            bool operator!=(const_iterator it) const { return current!=it.current; }
            const_iterator& operator++(){ ++current; return *this; }
        };
        const_iterator begin() const { return const_iterator(litteraux); }
        const_iterator end() const { return const_iterator(litteraux + taille); }

};



#endif // PILE_H_INCLUDED
