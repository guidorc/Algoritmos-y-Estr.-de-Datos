
template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
    _cardinal = 0;
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
    _cardinal = 0;
}

template <class T>
void Conjunto<T>::destruir(Nodo* n) {
    if(n != nullptr){
        destruir(n->izq);
        destruir(n->der);
        delete(n);
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* iterador = _raiz;
    while(iterador != nullptr){
        if(iterador->valor == clave){
            return true;
        }else{
            if(iterador->valor > clave){
                iterador = iterador->izq;
            }else{
                iterador = iterador->der;
            }
        }
    }
    return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!(pertenece(clave))) {
        Nodo *iterador = _raiz;
        Nodo *nuevo = new Nodo(clave);
        if (_raiz == nullptr) { //es el conjunto vacío
            _raiz = nuevo;
        } else {
            while (iterador != nullptr) {
                if (iterador->valor > clave) {
                    if (iterador->izq == nullptr) {
                        iterador->izq = nuevo;
                        break;
                    } else {
                        iterador = iterador->izq;
                    }
                } else {
                    if (iterador->der == nullptr) {
                        iterador->der = nuevo;
                        break;
                    } else {
                        iterador = iterador->der;
                    }
                }
            }
        }
        _cardinal++;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(pertenece(clave)) {
        Nodo* padre = nullptr;
        Nodo* actual = _raiz;
        while(actual != nullptr) {
            if(actual->valor == clave) {
                if(actual->der == nullptr && actual->izq == nullptr) { // Caso 1: El nodo a eliminar no tiene hijos
                    if(padre != nullptr) {
                        if(actual->valor > padre->valor) padre->der = nullptr;
                        else padre->izq = nullptr;
                    } else { // Quiero borrar la raíz
                        _raiz = nullptr;
                    }
                    _cardinal--;
                    delete(actual);
                } else if(actual->izq == nullptr) { // Caso 2.1: Tiene un solo hijo (el derecho)
                    Nodo* nuevo = actual->der;
                    if(padre != nullptr) {
                        if(nuevo->valor > padre->valor){
                            padre->der = nuevo;
                        }else{
                            padre->izq = nuevo;
                        }
                    } else { // Quiero borrar la raíz
                        _raiz = nuevo;
                    }
                    _cardinal--;
                    delete(actual);
                } else if(actual->der == nullptr) { // Caso 2.2: Tiene un solo hijo (el izquierdo)
                    Nodo* nuevo = actual->izq;
                    if(padre != nullptr){
                        if(nuevo->valor > padre->valor){
                            padre->der = nuevo;
                        }else{
                            padre->izq = nuevo;
                        }
                    } else { // Quiero borrar la raíz
                        _raiz = nuevo;
                    }
                    _cardinal--;
                    delete(actual);
                } else { // Caso 3 : Tiene dos hijos
                    T siguiente = this->siguiente(clave);
                    this->remover(siguiente);
                    actual->valor = siguiente;
                }
                return;
            } else if(actual->valor > clave) {
                padre = actual;
                actual = actual->izq;
            } else {
                padre = actual;
                actual = actual->der;
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* iterador = _raiz;
    Nodo* buscado = nullptr;
    while(iterador != nullptr){ // Busco el Nodo que contiene al parámetro
        if(iterador->valor == clave){
            buscado = iterador;
            break;
        }else if(clave < iterador->valor){
            iterador = iterador->izq;
        }else{
            iterador = iterador->der;
        }
    }
    if(buscado->der != nullptr){ // Caso 1: el nodo buscado tiene subarbol derecho
        iterador = buscado->der;
        while(iterador->izq != nullptr){
            iterador = iterador->izq;
        }
        return iterador->valor;
    }else{ //caso 2: el nodo buscado no tiene subarbol derecho
        Nodo* res = nullptr;
        Nodo* padre = _raiz;
        while(padre != buscado){
            if(buscado->valor < padre->valor){
                res = padre; //Nodo más profundo con el nodo actual a la izquierda
                padre = padre->izq;
            }else{
                padre = padre->der;
            }
        }
        return res->valor;
    }
}


template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* iterador = _raiz;
    while(iterador->izq != nullptr){
        iterador = iterador->izq;
    }
    return iterador->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* iterador = _raiz;
    while(iterador->der != nullptr){
        iterador = iterador->der;
    }
    return iterador->valor;
}


template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

