#include"Templates.h"

template<class T>
Generico<T>::Generico(T t1) {
    _t1(t1);
}

template<class T>
T Generico<T>::t1() const {
    return _t1;
}


