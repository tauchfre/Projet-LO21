#ifndef ATOMES_H_INCLUDED
#define ATOMES_H_INCLUDED
#include "operateurs.h"
#include "litteraux.h"
#include <map>
using namespace std;

enum TypeAtome{var,progg,NIL};
class ListeAtomes
{
    private:
        map<string,Litteral_calculable&> variables;
        map<string,Litteral_programme&> programmes;
    public:
        class iterator_var : public map<string,Litteral_calculable&>::iterator
        {
            public:
                iterator_var(typename map<string,Litteral_calculable&>::iterator I) : map<string,Litteral_calculable&>::iterator(I) {}
                void operator++() { map<string,Litteral_calculable&>::iterator::operator++(); }
        };
        iterator_var begin_var() { return iterator_var(variables.begin()); }
        iterator_var end_var() { return iterator_var(variables.end()); }

        class iterator_prog : public map<string,Litteral_programme&>::iterator
        {
            public:
                iterator_prog(typename map<string,Litteral_programme&>::iterator I) : map<string,Litteral_programme&>::iterator(I) {}
                void operator++() { map<string,Litteral_programme&>::iterator::operator++(); }
        };
        iterator_prog begin_prog() { return iterator_prog(programmes.begin()); }
        iterator_prog end_prog() { return iterator_prog(programmes.end()); }

        TypeAtome atomeExiste(string str);
        Litteral& traduireAtome(string str);
        void ajouterAtome(string key, const Litteral& L);
        ConteneurOperande* interpreter(string str);
};
#endif // ATOMES_H_INCLUDED
