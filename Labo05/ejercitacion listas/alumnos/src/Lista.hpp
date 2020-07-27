#include "Lista.h"

Lista::Lista() : _primero(nullptr), _ultimo(nullptr), _length(0) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* temp = _primero;
    while(temp != nullptr){
        temp = temp -> sig;
        delete(_primero);
        _primero = temp;
    }
    _length = 0;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    /*
    for(Nat i = 0; i < _length; i++){  //Borro todos los elementos de la lista original
        this -> eliminar(0);
    }
    */
    Nodo* temp = _primero;
    while(temp != nullptr){ //Borro todos los elementos de la lista original
        temp = temp -> sig;
        delete(_primero);
        _primero = temp;
    }
    _length = 0;
    int tam = aCopiar.longitud();
    Nodo* iterador = aCopiar._primero;
    while(tam > 0){        //Agrego todos los elementos de la lista aCopiar
        int nuevo = iterador -> data;
        this -> agregarAtras(nuevo);
        iterador = iterador -> sig;
        tam--;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* first = new Nodo();   // Reservo memoria para el nodo a agregar
    first -> data = elem;
    first -> ant = nullptr;
    first -> sig = nullptr;
    if(_primero == nullptr){    //En caso de que la lista esté vacía
        _primero = first;
        _ultimo = first;
    }else{
        Nodo* temp = _primero;
        temp -> ant = first;
        first -> sig = _primero;
        _primero = first;
    }
    _length++;
}

void Lista::agregarAtras(const int& elem) {
    // Completar
    Nodo* last = new Nodo();    // Reservo espacio para el nodo a agregar
    last -> data = elem;
    last -> sig = nullptr;
    last -> ant = nullptr;
    if(_primero == nullptr){    // En caso de que la lista esté vacía
        _primero = last;
        _ultimo =last;
    }else{
        Nodo* temp = _ultimo;
        temp -> sig = last;
        last -> ant = _ultimo;
        _ultimo = last;
    }
    _length++;
}

void Lista::eliminar(Nat i) {
    // Completar
    Nodo* temp1 = _primero;
    if(i < _length) {
        if (_length == 1) { // Si la lista tiene un solo elemento
            delete (_primero);
            _primero = nullptr;
            _ultimo = nullptr;
        } else {
            if (i == 0) {   //Si quiero eliminar el primero
                _primero = temp1->sig;
                delete (temp1);
            } else {
                if (i == _length - 1) { //Si quiero eliminar el último
                    Nodo* ultimo = _ultimo;
                    _ultimo = ultimo->ant;
                    delete (ultimo);
                } else {    //Otro caso
                    for (int j = 0; j < i; j++) {
                        temp1 = temp1->sig;
                    }
                    Nodo *anterior = temp1->ant;
                    Nodo *siguiente = temp1->sig;
                    anterior->sig = siguiente;
                    siguiente->ant = anterior;
                    delete (temp1);
                }
            }
        }
        _length--;
    }
}

int Lista::longitud() const {
    return this -> _length;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* buscador = _primero;
    for(int j = 0; j < i; j++ ){
        buscador = buscador -> sig;
    }
    int& res = buscador->data;
    return res;
    assert(false);
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* buscador = _primero;
    for(int j = 0; j < i; j++ ){
        buscador = buscador -> sig;
    }
    int& res = buscador->data;
    return res;
    assert(false);
}

void Lista::mostrar(ostream& o) {
    // Completar
    for(int i = 0; i < _length; i++){
        o << _primero->data;
    }
}
