// Implementacion simple de guía telefónica usando una tabla de hash.

#ifndef HASHTABLE_TABLA_H
#define HASHTABLE_TABLA_H

#include <iostream>
#include <list>
using namespace std;

class Hash_Table{
    public:
        bool esVacia() const;
        void insertar(const int& clave, const string& valor);
        void remover(const int& clave);
        string buscar(const int& clave);
        void mostrar();

    private:
        static const int _grupos = 10;
        int _funcionHash(int clave);
        list<pair<int, string>> tabla[_grupos]; // tabla es un array de listas
};

#endif //HASHTABLE_TABLA_H