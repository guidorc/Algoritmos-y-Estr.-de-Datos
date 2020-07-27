

#ifndef SOLUCION_MULTICONJUNTO_HPP
#define SOLUCION_MULTICONJUNTO_HPP

#include "Diccionario.hpp"

template<class T>
class Multiconjunto{
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x) const;

private:
    Diccionario<T, int> _dicc;
};

template<class T>
Multiconjunto<T>::Multiconjunto() {}

template<class T>
void Multiconjunto<T>::agregar(T x) {
    if(_dicc.def(x)){
        // Tendría que borrar la definicion anterior
        // y agregar una nueva donde
        // el significado sea la cantidad de apariciones + 1
        int apariciones = _dicc.obtener(x) + 1;
        _dicc.definir(x, apariciones);
    }else{
        _dicc.definir(x, 1);
    }
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) const {
    if(_dicc.def(x)){
        return _dicc.obtener(x);
    }else{
        return 0;
    }
}

#endif //SOLUCION_MULTICONJUNTO_HPP
