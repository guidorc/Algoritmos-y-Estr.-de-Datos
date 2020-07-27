#include "SistemaDeMensajes.h"

// Ejercício 1
SistemaDeMensajes::SistemaDeMensajes() {
    for(int i = 0; i < 4; i++){
        ConexionJugador* nuevo = new ConexionJugador("");
        _conns[i] = nuevo;
    }
}

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    delete(_conns[id]);
    ConexionJugador* registrar = new ConexionJugador(ip);
    _conns[id] = registrar;
}

void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    _conns[id] -> enviarMensaje(mensaje);
}

bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] -> ip() != "";
}

string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id] -> ip();
}

// Ejercício 2
SistemaDeMensajes::~SistemaDeMensajes() {
    for(int i = 0; i < 4; i++){
        delete(_conns[i]);
    }
    // Ejercício 5
    int tam = _proxys.size();
    for(int i= 0; i < tam ; i++ ){
        delete(_proxys[i]);
    }
}

// Ejercício 3
void SistemaDeMensajes::desregistrarJugador(int id) {
    delete(_conns[id]);
    ConexionJugador* vacio = new ConexionJugador("");
    _conns[id] = vacio;
}

// Ejercício 4
#if EJ == 4 || EJ == 5
Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    Proxy* nuevo = new Proxy(_conns[id]);
    _proxys.push_back(nuevo);
    return nuevo;
}
#endif

// Ejercício 6
#if EJ == 6
Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    ConexionJugador** puntero = new ConexionJugador*(_conns[id]); // ¿Que es esto?
    Proxy* nuevo = new Proxy(puntero);
    _proxys.push_back(nuevo);
    return nuevo;
}
#endif