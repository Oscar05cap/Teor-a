#ifndef TRANSICION_H
#define TRANSICION_H

#include "Estado.h"

template <typename Simbolo>
class Transicion {
private:
    Estado origen;
    Simbolo simbolo;
    Estado destino;

public:
    Transicion(const Estado& o, const Simbolo& s, const Estado& d)
        : origen(o), simbolo(s), destino(d) {}

    const Estado& getOrigen() const { return origen; }
    const Simbolo& getSimbolo() const { return simbolo; }
    const Estado& getDestino() const { return destino; }
};

#endif
