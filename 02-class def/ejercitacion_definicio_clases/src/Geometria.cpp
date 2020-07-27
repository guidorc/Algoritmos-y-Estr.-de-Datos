#include <iostream>

using namespace std;

using uint = unsigned int;

// Ejercicio 1

class Rectangulo {
    public:
        Rectangulo(uint alto, uint ancho);
        uint alto();
        uint ancho();
        float area();

    private:
        uint alto_;
        uint ancho_;

};

Rectangulo::Rectangulo(uint alto, uint ancho) : alto_(alto), ancho_(ancho) {};

uint Rectangulo::alto() {
    return alto_;
}

uint Rectangulo::ancho(){
    return ancho_;
}

float Rectangulo::area(){
    return alto() * ancho();
}

// Ejercicio 2

class Elipse {
    public:
        Elipse(uint a, uint b);
        uint r_a();
        uint r_b();
        float area();
        float PI = 3.14;
    private:
        uint r_a_;
        uint r_b_;
};

Elipse::Elipse(uint a, uint b) : r_a_(a), r_b_(b) {};

uint Elipse::r_a(){
    return r_a_;
}

uint Elipse::r_b(){
    return r_b_;
}

float Elipse::area(){
    return r_a() * r_b() * PI;
}

// Ejercicio 3

class Cuadrado {
    public:
        Cuadrado(uint lado);
        uint lado();
        float area();

    private:
        Rectangulo r_;
};

Cuadrado::Cuadrado(uint lado): r_(lado, lado) {}

uint Cuadrado::lado() {
    return r_.alto();
}

float Cuadrado::area() {
    return r_.alto() * r_.ancho();
}

// Ejercicio 4

class Circulo {
    public:
        Circulo(uint radio);
        uint radio();
        float area();
    private:
        Elipse radio_;
};

Circulo::Circulo(uint r) : radio_(r, r) {}

uint Circulo::radio() {
    return radio_.r_a();
}

float Circulo::area() {
    return radio_.r_a() * radio_.r_b() * radio_.PI;
}

// Ejercicio 5

ostream& operator<<(ostream& os, Rectangulo r) {
    os << "Rect(" << r.alto() << ", " << r.ancho() << ")";
    return os;
}

ostream& operator<<(ostream& os, Elipse e) {
    os << "Elipse(" << e.r_a() << ", " << e.r_b() << ")";
    return os;
}

// Ejercicio 6

ostream& operator<<(ostream& os, Circulo circulo) {
    os << "Circ(" << circulo.radio() << ")";
    return os;
}

ostream& operator<<(ostream& os, Cuadrado cuadrado) {
    os << "Cuad(" << cuadrado.lado() << ")";
    return os;
}