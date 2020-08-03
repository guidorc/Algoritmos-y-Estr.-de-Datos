
#include "ColaPrior.h"

template<class T>
ColaPrior<T>::ColaPrior() {
}

template<class T>
int ColaPrior<T>::tam() const {
	return _heap.size();
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
	_heap.push_back(elem);
	int n = tam() - 1;
	siftUp(n);
}

template<class T>
const T& ColaPrior<T>::proximo() const {
	return _heap[0];
}

template<class T>
void ColaPrior<T>::desencolar() {
    int n = tam() - 1;
	swap(_heap[0], _heap[n]);
	_heap.pop_back();
	siftDown(0);
}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems) {
	// COMPLETAR
	for(int i = 0; i < elems.size(); i++){
	    _heap.push_back(elems[i]);
	}
	int n = tam();
	for(int i = n/2; i >= 0; i--){
	    siftDown(i);
	}
}

template<class T>
Nat ColaPrior<T>::padre(Nat i) {
    return floor((i - 1) / 2);
}

template<class T>
Nat ColaPrior<T>::hijo_der(Nat i) {
    return (2*i) + 2;
}

template<class T>
Nat ColaPrior<T>::hijo_izq(Nat i) {
    return (2*i) + 1;
}

template<class T>
void ColaPrior<T>::siftUp(Nat i) {
    if(i != 0 && _heap[i] > _heap[padre(i)]){
        swap(_heap[i], _heap[padre(i)]);
        siftUp(padre(i));
    }
}

template<class T>
void ColaPrior<T>::siftDown(Nat i) {
    if (!esHoja(i)) {
        int indice = hijo_izq(i);
        T m = _heap[hijo_izq(i)];
        if (hijo_der(i) < tam()) {
            if (_heap[hijo_izq(i)] < _heap[hijo_der(i)]) {
                indice = hijo_der(i);
                m = _heap[hijo_der(i)];
            }
        }

        if (m > _heap[i]) {
            swap(_heap[indice], _heap[i]);
            siftDown(indice);
        }
    }
}

template<class T>
bool ColaPrior<T>::esHoja(Nat i) {
    return (hijo_der(i) >= tam() && hijo_izq(i) >= tam());
}

