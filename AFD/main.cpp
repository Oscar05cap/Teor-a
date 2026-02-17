#include <iostream>
#include <string>
#include <vector>
#include "AFDParser.h"

int main() {

    try {
        AFDParser<char> parser;

        //Se carga al automata desde el archivo
        auto afd = parser.parseFromFile("automata.txt");

        std::cout << "AFD cargado correctamente.\n";
        std::cout << "Escriba una cadena o 'exit' para salir):\n";

        std::string input;

        while (true) {

            std::cout << "> ";
            std::cin >> input;

            if (input == "exit")
                break;

            std::vector<char> cadena(input.begin(), input.end());

            bool aceptada = afd.acepta(cadena);

            if (aceptada)
                std::cout << "Cadena ACEPTADA\n";
            else
                std::cout << "Cadena RECHAZADA\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
