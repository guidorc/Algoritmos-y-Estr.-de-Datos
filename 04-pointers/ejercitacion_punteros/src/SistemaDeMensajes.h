#ifndef SISTEMADEMENSAJES_H
#define SISTEMADEMENSAJES_H

#include "vector"
#include "ConexionJugador.h"
#include "Proxy2.h"
#include <string>

#if EJ == 4 || EJ == 5
#include "Proxy.h"
#elif EJ == 6
#include "Proxy2.h"
#endif

using namespace std;

class SistemaDeMensajes {
  public:
    SistemaDeMensajes();
    // Pre: 0 <= id < 4
    void registrarJugador(int id, string ip);
    // Pre: 0 <= id < 4
    bool registrado(int id) const;

    // Pre: registrado(id)
    void enviarMensaje(int id, string mensaje);

    // Pre: registrado(id)
    string ipJugador(int id) const;

    ~SistemaDeMensajes();

    // Ejercício 3
    void desregistrarJugador(int id);

    // Ejercício 4
    Proxy* obtenerProxy(int id);

  private:
    ConexionJugador* _conns[4]; //array de punteros
    // Ejercício 5
    vector<Proxy*> _proxys; // Vector de punteros a Proxy
};

#endif
