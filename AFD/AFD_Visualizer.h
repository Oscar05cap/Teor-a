#ifndef AFD_VISUALIZER_H
#define AFD_VISUALISER_H

#include <iomanip>
#include <iostream>
#include <string>
#include "AFDParser.h"
#include "AFD_M.h"

template <typename Simbolo>

class AFD_Visualizer{
    private: 
    const AFD<Simbolo>& afd;

    public: 

    AFD_Visualizer(const AFD<Simbolo>& automata) : afd(automata) {}

    void imprimirEnConsola() const{
        const auto& estados = afd.agregarEstado();
        const auto& alfabeto = afd.agregarSimbolo();
        const auto& transiciones = afd.agregarTransicion();
        const auto& estadoInicial = afd.establecerInicial();
        const auto& estadoAceptacion = afd.agregarFinal();

        std::cout << std::setw(10) << "Estado";
        for(const auto& simbolo : alfabeto){
            std::cout << std::setw(10) << simbolo;
        }
        std::cout << "\n";

        std::cout << std::string(10 + 10 * alfabeto.size(), '-') << "\n";

        for(const auto& estado : estados){
            std::string etiqueta = estado;

            if(estado == estadoInicial)
                etiqueta = "->" + etiqueta;
            
            if(estado == estadoAceptacion)
                etiqueta = "*" + etiqueta;

            std::cout << std::setw(10) << etiqueta;

            for(const auto& simbolo: alfabeto){
                if(transiciones.at(estado).count(simbolo))
                    std::cout << std::setw(10) << transiciones.at(estado).at(simbolo);
                else
                    std::cout << std::setw(10) << "-";
            }

            std::cout << "\n";
        }
            std::cout << "\n";
    }

    void imprimirDot(){

    }
};

#endif 