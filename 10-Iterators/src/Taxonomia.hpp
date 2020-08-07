#include <sstream>
#include "Taxonomia.h"


// Métodos de Taxonomia (ya implementados por la cátedra):

template<class T>
int Taxonomia<T>::_espiarProximoCaracter(istream& is) const {
    int c = is.peek();
    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        is.get();
        c = is.peek();
    }
    return is.peek();
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::_leerDe(istream& is) {
    Taxonomia<T>::Nodo* nodo = new Taxonomia<T>::Nodo();
    is >> nodo->valor;
    if (_espiarProximoCaracter(is) == '{') {
        is.get();
        while (_espiarProximoCaracter(is) != '}') {
            nodo->hijos.push_back(_leerDe(is));
        }
        is.get();
    }
    return nodo;
}

template<class T>
Taxonomia<T>::Taxonomia(const string& input) {
    istringstream is(input);
    _raiz = _leerDe(is);
}

template<class T>
void Taxonomia<T>::_borrar(Taxonomia<T>::Nodo* nodo) {
    for (int i = 0; i < nodo->hijos.size(); i++) {
        _borrar(nodo->hijos[i]);
    }
    delete nodo;
}

template<class T>
Taxonomia<T>::~Taxonomia() {
    _borrar(_raiz);
}

template<class T>
void Taxonomia<T>::_identar(ostream& os, int tab) const {
    for (int i = 0; i < tab; i++) {
        os << "  ";
    }
}

template<class T>
void Taxonomia<T>::_mostrarEn(ostream& os, Taxonomia<T>::Nodo* nodo, int tab) const {
    _identar(os, tab);
    os << nodo->valor;
    if (nodo->hijos.size() == 0) {
        os << "\n";
    } else {
        os << " {\n";
        for (int i = 0; i < nodo->hijos.size(); i++) {
            _mostrarEn(os, nodo->hijos[i], tab + 1);
        }
        _identar(os, tab);
        os << "}\n";
    }
}

template<class T>
void Taxonomia<T>::mostrar(ostream& os) const {
    _mostrarEn(os, _raiz, 0);
}

////////////////////////////////////////

// Métodos para implementar el iterador de Taxonomia<T> (para completar)

// Devuelve un iterador válido al principio de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::begin() {
    return iterator(this->_raiz);
}

// Devuelve un iterador válido al final de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::end() {
    Nodo* f = new Nodo();
    return iterator(f);
}

// Constructor por defecto del iterador.
// (Nota: puede construir un iterador inválido).
template<class T>
Taxonomia<T>::iterator::iterator(Nodo* raiz): _actual(raiz){}

// Referencia mutable al nombre de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
T& Taxonomia<T>::iterator::operator*() const {
    return this->_actual->valor;
}

// Cantidad de subcategorías de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
int Taxonomia<T>::iterator::cantSubcategorias() const {
    return this->_actual->hijos.size();
}

// Ubica el iterador sobre la i-ésima subcategoría.
// Pre: el iterador está posicionado sobre una categoría
// y además 0 <= i < cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::subcategoria(int i) {
    this->_superCategorias.push(this->_actual);
    this->_actual = this->_actual->hijos[i];
}

// Devuelve true sii la categoría actual es la raíz. 
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
bool Taxonomia<T>::iterator::esRaiz() const {
    return this->_superCategorias.empty();
}

// Ubica el iterador sobre la supercategoría de la categoría
// actual.
// Pre: el iterador está posicionado sobre una categoría
// y además !esRaiz()
template<class T>
void Taxonomia<T>::iterator::supercategoria() {
    this->_actual = this->_superCategorias.top();
    this->_superCategorias.pop();
}

// Compara dos iteradores por igualdad.
// Pre: deben ser dos iteradores de la misma taxonomía.
template<class T>
bool Taxonomia<T>::iterator::operator==(const Taxonomia<T>::iterator& otro) const {
    return this->_actual->valor == otro._actual->valor;
}

// Ubica el iterador sobre la categoría siguiente a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la última categoría de la taxonomía,
// el iterador resultante debe ser igual al iterador end()
// de la taxonomía.
template<class T>
void Taxonomia<T>::iterator::operator++() {
    // Caso estoy en la raiz
    if (this->_superCategorias.empty()) {
        if (_actual->hijos.size() == 0) {
            _actual = nullptr;
        } else {
            this->_superCategorias.push(this->_actual);
            this->_actual = _actual->hijos[0];
        }
        return;
    }

    Nodo* padre = this->_superCategorias.top();
    int fin = padre->hijos.size() - 1;

    // Caso estoy en el fín de la taxonomia
    if (this->_superCategorias.size() == 1 && padre->hijos[fin] == this->_actual) {
        if ( this->_actual->hijos.size() != 0) {
            this->_superCategorias.push(this->_actual);
            this->_actual = this->_actual->hijos[0];
        } else {
            this->_actual = nullptr;
            this->_superCategorias.pop();
        }
        return;
    }

    int pos = 0;
    while (padre->hijos[pos]->valor != this->_actual->valor && pos <= fin) {
        pos++;
    }

    // Caso no estoy en el fin de la categoría actual
    if (pos < fin) {
        if ( this->_actual->hijos.size() != 0) {
            this->_superCategorias.push(this->_actual);
            this->_actual = this->_actual->hijos[0];
        } else {
            this->_actual = padre->hijos[pos + 1];
        }
        return;
    }

    // Caso estoy en el fin de la categoría actual
    if ( this->_actual->hijos.size() != 0) {
        this->_superCategorias.push(this->_actual);
        this->_actual = this->_actual->hijos[0];
    } else {
        this->_actual = padre;
        this->_superCategorias.pop();
        buscarCategoria(this->_actual, this->_superCategorias);
    }
}

template<class T>
void Taxonomia<T>::iterator::buscarCategoria(Nodo* a, stack<Nodo*>& p) {
    // Caso estoy en el último elemento de la taxonomía
    if (p.empty()){
        this->_actual = _final;
        return;
    }

    int fin = p.top()->hijos.size() - 1;
    int pos = 0;
    while (p.top()->hijos[pos]->valor != a->valor && pos <= fin) {
        pos++;
    }

    // caso estoy en el fin de la categoria actual
    if (pos == fin) {
        this->_actual = p.top();
        this->_superCategorias.pop();
        buscarCategoria(this->_actual, this->_superCategorias);
    } else { // caso no estoy en el fin de la categoria actual;
        this->_actual = p.top()->hijos[pos + 1];
    }
    return;
}

// Ubica el iterador sobre la categoría anterior a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la raíz de la taxonomía el iterador
// resultante debe ser igual al iterador end() de la taxonomía.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
void Taxonomia<T>::iterator::operator--() {
    // Caso estoy en la raiz
    if (this->_superCategorias.empty()) {
        this->_actual = nullptr;
        this->_superCategorias.pop();
        return;
    }

    Nodo* padre = this->_superCategorias.top();

    // Caso caso es el minimo de su subcategoría
    if (this->_actual == padre->hijos[0]) {
        this->_actual = padre;
        this->_superCategorias.pop();
        return;
    }

    int pos = 0;
    while (padre->hijos[pos]->valor != this->_actual->valor) {
        pos++;
    }

    int nuevaPos = pos - 1;
    if ((padre->hijos[nuevaPos])->hijos.size() > 0) {
        this->_superCategorias.push(padre->hijos[nuevaPos]);
        buscarMaximo(padre->hijos[nuevaPos]);
    } else {
        this->_actual = padre->hijos[nuevaPos];
    }
}

template<class T>
void Taxonomia<T>::iterator::buscarMaximo(Nodo *a) {
    if (a->hijos.size() == 0) {
        this->_actual = a;
        return;
    }
    int fin = a->hijos.size() - 1;
    if ( a->hijos[fin]->hijos.size() > 0){
        this->_superCategorias.push(a->hijos[fin]);
    }
    buscarMaximo(a->hijos[fin]);
}

// Inserta una subcategoría con el nombre indicado
// en el lugar i-ésimo.
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores.
// Pre: el iterador está posicionado sobre una categoría,
// y además 0 <= i <= cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::insertarSubcategoria(int i, const T& nombre) {
    Nodo* nuevo = new(Nodo);
    nuevo->valor = nombre;
    int fin = _actual->hijos.size();
    _actual->hijos.push_back(nuevo);
    // Caso agrego al final
    if (fin == i) {
        return;
    }else{
        while(fin != i) {
            swap(_actual->hijos[fin], _actual->hijos[fin - 1]);
            fin--;
        }
    }
}

// Elimina la categoría actual de la taxonomía
// (y todas sus subcategorías).
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores. Debe encargarse de
// liberar la memoria.
// Pre: el iterador está posicionado sobre una categoría,
// y además !esRaiz().
template<class T>
void Taxonomia<T>::iterator::eliminarCategoria() {
    for (int i = 0; i < _actual->hijos.size(); i++) {
        eliminarAux(_actual->hijos[i]);
    }
    int pos = 0;
    Nodo* padre = _superCategorias.top();
    while (padre->hijos[pos] != _actual) {
        pos++;
    }
    int fin = padre->hijos.size() - 1;
    while (pos != fin) {
        swap(padre->hijos[pos], padre->hijos[pos + 1]);
        pos++;
    }
    padre->hijos.pop_back();
    delete(_actual);
    _actual = padre;
}

template<class T>
void Taxonomia<T>::iterator::eliminarAux(Nodo* a) {
    for (int i = 0; i < a->hijos.size(); i++) {
        eliminarAux(a->hijos[i]);
    }
    delete(a);
}



