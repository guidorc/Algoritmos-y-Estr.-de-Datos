#include "Diccionario.h"

#ifndef SOLUCION_DICCIONARIO_HPP
#define SOLUCION_DICCIONARIO_HPP

using namespace::std;

#include <vector> 

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Diccionario() {
}

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Asociacion::Asociacion(Clave k, Valor v) : clave(k), valor(v) {
}

template<class Clave, class Valor>
void Diccionario<Clave, Valor>::definir(Clave k, Valor v) {
    if(!this->def(k)){
        this->_claves.push_back(k);
    }
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            _asociaciones[i].valor = v;
            return;
        }
    }
    _asociaciones.push_back(Asociacion(k, v));
}

template<class Clave, class Valor>
bool Diccionario<Clave, Valor>::def(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return true;
        }
    }
    return false;
}

template<class Clave, class Valor>
Valor Diccionario<Clave, Valor>::obtener(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return _asociaciones[i].valor;
        }
    }
    assert(false);
}

template<class Clave, class Valor>
vector<Clave> Diccionario<Clave, Valor>::claves() const{
    vector<Clave> v1 = this->_claves;
    vector<Clave> res;
    int tam = v1.size();
    for(int i = 0; i < tam; i++){
        Clave min = v1[0];
        int posMin = 0;
        for(int j = 1; j < v1.size(); j++){
            if(v1[j] < min){
                min = v1[j];
                posMin = j;
            }
        }
        //quitar minimo
        vector<Clave> aux;
        for(int m = posMin + 1; m < v1.size(); m++){
            aux.push_back(v1[m]);
        }
        for(int l = 0; l < posMin; l++){
            aux.push_back(v1[l]);
        }
        v1 = aux;
        // agregar el mínimo al nuevo vector;
        res.push_back(min);
    }
    return res;
}


#endif //SOLUCION_DICCIONARIO_HPP
