#include<string>
#include"Templates.hpp"
using namespace std;
template<class T>

// Ejercicio 1: Pasar a templates
T cuadrado(T x) {
  return x * x;
}

// Ejercicio 2: Pasar a templates
template<class Contenedor, class Elem>
bool contiene(Contenedor s, Elem c) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == c) {
      return true;
    }
  }
  return false;
}

// Ejercicio 3: Funcion es prefijo con un template contenedor
template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    bool menor = a.size() < b.size();
    bool prefijo = true;
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            prefijo = false;
        }
    }
    return menor && prefijo;
}
// Ejercicio 4: Función maximo con un template contenedor y uno elemento
template<class Contenedor, class Elem>
Elem maximo(Contenedor c){
    Elem parcial = c[0];
    for(int i = 0; i < c.size() ; i++){
        if(c[i] > parcial){
            parcial = c[i];
        }
    }
    return parcial;
}