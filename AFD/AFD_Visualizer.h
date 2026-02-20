#ifndef AFD_VISUALISER_H
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
        const auto& estados = afd.getEstados();
        const auto& alfabeto = afd.getAlfabeto();
        const auto& transiciones = afd.getTransiciones();
        const auto& estadoInicial = afd.getEstadoInicial();
        const auto& estadoAceptacion = afd.getEstadoAceptacion();

        std::cout << std::setw(10) << "Estado";
        for(const auto& simbolo : alfabeto){
            std::cout << std::setw(10) << simbolo;
        }
        std::cout << "\n";

        std::cout << std::string(10 + 10 * alfabeto.size(), '-') << "\n";

        for(const auto& estado : estados){
            std::string etiqueta = estado;

            if(estado == INICIAL)
                etiqueta = '->' + etiqueta;
            
            if(estado == FINAL)
                etiqueta = '*' + etiqueta;

            std::cout << std::setw(10) << etiqueta;

            for(const auto& simbolo: alfabeto){
                if(transiciones.at(estado).count(simbolo))
                    std::cout << std::setw(10) << transiciones.at(estado).at(simbolo)
                else
                    std::cout << std::setw(10) << "-";
            }

            std::cout << "\n";
        }
            std::cout << "\n"
    }

    void imprimirDot(){

    }
};

#endif AFD_VISUALISER_H