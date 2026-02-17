#ifndef AFD_BUILDER_H
#define AFD_BUILDER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>
#include "AFD_M.h"

template <typename Simbolo>
class AFDBuilder {
private:
    std::unordered_set<Estado> estados;
    std::unordered_set<Simbolo> alfabeto;
    std::vector<Transicion<Simbolo>> listaTransiciones;

    std::optional<Estado> estadoInicial;
    std::unordered_set<Estado> estadosFinales;

public:
    void agregarEstado(const Estado& e) {
        estados.insert(e);
    }

    void agregarSimbolo(const Simbolo& s) {
        alfabeto.insert(s);
    }

    void establecerInicial(const Estado& e) {
        if (!estados.count(e))
            throw InvalidStateException("No hay estados iniciales");
        estadoInicial = e;
    }

    void agregarFinal(const Estado& e) {
        if (!estados.count(e))
            throw InvalidStateException("No hay estados finales");
        estadosFinales.insert(e);
    }

    void agregarTransicion(const Transicion<Simbolo>& t) {
        listaTransiciones.push_back(t);
    }

    AFD<Simbolo> build() {

        if (!estadoInicial.has_value())
            throw InvalidStateException("No hay estados iniciales");

        std::unordered_map<
            Estado,
            std::unordered_map<Simbolo, Estado>
        > transiciones;

        //Construcción y validación del AFD
        for (const auto& t : listaTransiciones) {

            if (!estados.count(t.getOrigen()) ||
                !estados.count(t.getDestino()))
                throw InvalidStateException("Transición con estado inválido");

            if (!alfabeto.count(t.getSimbolo()))
                throw InvalidSymbolException("Cadena inválida");

            auto& mapa = transiciones[t.getOrigen()];

            if (mapa.count(t.getSimbolo()))
                throw NonDeterministicException("El AFD no es determinista");

            mapa.emplace(t.getSimbolo(), t.getDestino());
        }

        /*
        //Verificar si el AFD está completo
        bool completo = true;

        for (const auto& estado : estados) {
            for (const auto& simbolo : alfabeto) {
                if (!transiciones[estado].count(simbolo)) {
                    completo = false;
                    throw IncompleteAutomatonException("AFD incompleto");
                }
            }
        }
        */

        return AFD<Simbolo>(
            estados,
            alfabeto,
            transiciones,
            estadoInicial.value(),
            estadosFinales
        );
    }
};

#endif
