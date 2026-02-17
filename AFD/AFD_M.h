#ifndef AFD_M_H
#define AFD_M_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>
#include "Estado.h"
#include "Transicion.h"
#include "Exceptions.h"

template <typename Simbolo>
class AFD 
{
private:
    std::unordered_set<Estado> estados;
    std::unordered_set<Simbolo> alfabeto;

    std::unordered_map<
        Estado,
        std::unordered_map<Simbolo, Estado>
    > transiciones;

    Estado estadoInicial;
    std::unordered_set<Estado> estadosFinales;

public:
    AFD(
        const std::unordered_set<Estado>& estados,
        const std::unordered_set<Simbolo>& alfabeto,
        const std::unordered_map<
            Estado,
            std::unordered_map<Simbolo, Estado>
        >& transiciones,
        const Estado& estadoInicial,
        const std::unordered_set<Estado>& estadosFinales
    )
        : estados(estados),
          alfabeto(alfabeto),
          transiciones(transiciones),
          estadoInicial(estadoInicial),
          estadosFinales(estadosFinales)
    {}

    bool acepta(const std::vector<Simbolo>& cadena) const{
        Estado actual = estadoInicial;

        for (const auto& simbolo : cadena) {

            if (!alfabeto.count(simbolo)) {
                throw InvalidSymbolException("Símbolo fuera del alfabeto");
            }

            const auto& mapa = transiciones.at(actual);
            actual = mapa.at(simbolo);
        }

        return estadosFinales.count(actual) > 0;
    }

};

#endif
