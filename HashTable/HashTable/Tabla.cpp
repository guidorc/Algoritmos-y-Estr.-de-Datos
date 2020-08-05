#include "Tabla.h"
#include <iostream>

using namespace std;

int Hash_Table::_funcionHash(int clave) {
    return clave % _grupos;
}

bool Hash_Table::esVacia() const {
    for(int i = 0; i < _grupos; i++){
        if(tabla[i].size() > 0){
            return false;
        }
    }
    return true;
}

string Hash_Table::buscar(const int &clave) {
    int pos = _funcionHash(clave);
    string res = "Clave no encontrada";
    for (auto& i : tabla[pos]) {
        if (i.first == clave) {
            res = i.second;
        }
    }
    return res;
}

void Hash_Table::insertar(const int &clave, const string &valor) {
    int pos = _funcionHash(clave);
    for(auto i : tabla[pos]) {      // Me fijo que no esté ya definida
        if(i.first == clave) {
            i.second = valor;
            return;
        }
    }
    tabla[pos].emplace_back(clave, valor);  // Si no está definida, la defino.
}

void Hash_Table::remover(const int &clave) {
    int pos = _funcionHash(clave);
    auto iterador = begin(tabla[pos]); // consigue un iterador al principio de la lista de esa posicion de la tabla
    for(; iterador != tabla[pos].end(); iterador++){
        if(iterador->first == clave){
            iterador = tabla[pos].erase(iterador); // Elimino el par clave/valor apuntado por el iterador. (La funcion erase devuelve un iterador, por eso lo asigno)
            return;
        }
    }
}

void Hash_Table::mostrar() {
    for(int i = 0; i < _grupos; i++) {
        if(tabla[i].size() == 0) continue;

        auto iterador = tabla[i].begin();
        for(; iterador != tabla[i].end(); iterador++) {
            cout << "[INFO] clave: " << iterador->first << " Valor: " << iterador->second << endl;
        }
    }
}










