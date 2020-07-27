
#include "string_map.h"

template <typename T>
string_map<T>::string_map(){
    raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    _size = d._size;
    if(d.raiz != nullptr) {
        Nodo *nuevaRaiz = new(Nodo);
        if (d.raiz->definicion != nullptr) {
            T *nuevaDef = new(T);
            T nuevo = *d.raiz->definicion;
            *nuevaDef = nuevo;
            nuevaRaiz->definicion = nuevaDef;
        } else {
            nuevaRaiz->definicion = nullptr;
        }
        vector<Nodo *> nuevosSiguientes(256, nullptr);
        for (int i = 0; i < 256; i++) {
            if (d.raiz->siguientes[i] != nullptr) {
                Nodo *nuevo = new(Nodo);
                copy(nuevo, d.raiz->siguientes[i]);
                nuevosSiguientes[i] = nuevo;
            }
        }
        nuevaRaiz->siguientes = nuevosSiguientes;
        raiz = nuevaRaiz;
    }else{
        raiz = nullptr;
    }
}

template<typename T>
void string_map<T>::copy(string_map::Nodo* actual, const string_map::Nodo* aCopiar) {
    if(aCopiar->definicion != nullptr){
        T* nuevaDef = new(T);
        T nuevo = *aCopiar->definicion;
        *nuevaDef = nuevo;
        actual->definicion = nuevaDef;
    }else{
        actual->definicion = nullptr;
    }
    vector<Nodo*> nuevosSiguientes(256, nullptr);
    for(int i = 0; i < 256; i++){
        if(aCopiar->siguientes[i] != nullptr){
            Nodo* nuevo = new(Nodo);
            copy(nuevo,  aCopiar->siguientes[i]);
            nuevosSiguientes[i] = nuevo;
        }
    }
    actual->siguientes = nuevosSiguientes;
}

template <typename T>
string_map<T>::~string_map(){
    if(raiz != nullptr) {
        borrar(raiz);
        _size = 0;
        raiz = nullptr;
    }
}

template<typename T>
void string_map<T>::borrar(string_map::Nodo* actual) {
    for(int i = 0; i < actual->siguientes.size(); i++){
        if(actual->siguientes[i] != nullptr){
            borrar(actual->siguientes[i]);
            actual->siguientes[i] = nullptr;
        }
    }
    if(actual->definicion != nullptr){
        delete(actual->definicion);
        actual->definicion = nullptr;
    }
    delete(actual);
}

template<typename T>
void string_map<T>::insert(const pair<string, T> & clave_valor) {
    if(raiz == nullptr){
        Nodo* nuevo = new(Nodo);
        raiz = nuevo;
    }
    Nodo* actual = raiz;
    char iterador = 0;
    while(iterador < clave_valor.first.size()){
        int ascii = int(clave_valor.first[iterador]);
        if(actual->siguientes[ascii] == nullptr){
            Nodo* nuevo = new(Nodo);
            actual->siguientes[ascii] = nuevo;
            actual = actual->siguientes[ascii];
        }else{
            actual = actual->siguientes[ascii];
        }
        iterador++;
    }
    T significado = clave_valor.second;
    if(actual->definicion == nullptr){
        T* nuevo = new(T);
        actual->definicion = nuevo;
    }
    *actual->definicion = significado;
    _size++;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
    if(raiz == nullptr){
        Nodo* nuevo = new(Nodo);
        raiz = nuevo;
    }
    if (this->count(clave) == 0) {
        Nodo *actual = raiz;
        char iterador = 0;
        while (iterador < clave.size()) {
            int ascii = int(clave[iterador]);
            if (actual->siguientes[ascii] == nullptr) {
                Nodo *nuevo = new(Nodo);
                actual->siguientes[ascii] = nuevo;
                actual = actual->siguientes[ascii];
            } else {
                actual = actual->siguientes[ascii];
            }
            iterador++;
        }
        T *nuevo = new(T);
        actual->definicion = nuevo;
        _size++;
        return *nuevo;
    } else {
        Nodo *actual = raiz;
        char iterador = 0;
        while (iterador < clave.size()) {
            int ascii = int(clave[iterador]);
            actual = actual->siguientes[ascii];
            iterador++;
        }
        return *actual->definicion;
    }
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    int contador = 0;
    if(raiz == nullptr){
        contador = 0;
    }else {
        Nodo *actual = raiz;
        char iterador = 0;
        while(iterador < clave.size()){
            int ascii = int(clave[iterador]);
            if(actual->siguientes[ascii] == nullptr){
                return 0;
            }else{
                actual = actual->siguientes[ascii];
                iterador++;
            }
        }
        if(actual->definicion != nullptr){
            contador = 1;
        }
    }
    return contador;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    int iterador = 0;
    Nodo* actual = raiz;
    while(iterador < clave.size()){
        int ascii = int(clave[iterador]);
        actual = actual->siguientes[ascii];
        iterador++;
    }
    return *actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    int iterador = 0;
    Nodo* actual = raiz;
    while(iterador < clave.size()){
        int ascii = int(clave[iterador]);
        actual = actual->siguientes[ascii];
        iterador++;
    }
    return *actual->definicion ;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = raiz;
    Nodo* ultNodo = actual;
    int ultLetra = 0;
    int iterador = 0;
    while(iterador < clave.size()){
        bool tieneSignificado = actual->definicion != nullptr;
        int nroDeHijos = 0;
        for(int i = 0; i < actual->siguientes.size(); i++){
            if(actual->siguientes[i] != nullptr){
                nroDeHijos++;
            }
        }
        if(tieneSignificado || nroDeHijos > 1){
            ultNodo = actual;
            ultLetra = iterador;
        }
        int ascii = int(clave[iterador]);
        actual = actual->siguientes[ascii];
        iterador++;
    }
    delete(actual->definicion);
    actual->definicion = nullptr;
    _size--;
    int hijosDeActual = 0;
    for(int i = 0; i < actual->siguientes.size(); i++){
        if(actual->siguientes[i] != nullptr){
            hijosDeActual++;
        }
    }
    if(hijosDeActual == 0) {
        Nodo *siguiente = ultNodo->siguientes[int(clave[ultLetra])];
        ultNodo->siguientes[int(clave[ultLetra])] = nullptr;
        ultLetra++;
        ultNodo = siguiente;
        while (ultLetra < clave.size()) {
            siguiente = ultNodo->siguientes[int(clave[ultLetra])];
            delete (ultNodo);
            ultNodo = siguiente;
            ultLetra++;
        }
        delete (ultNodo);
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}




