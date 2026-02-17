#ifndef AFD_PARSER_H
#define AFD_PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "AFDBuilder.h"
#include "Exceptions.h"

template <typename Simbolo>
class AFDParser {
private:

    static std::string trim(const std::string& s) {
        size_t start = 0;
        while (start < s.size() && std::isspace(s[start])) start++;

        size_t end = s.size();
        while (end > start && std::isspace(s[end - 1])) end--;

        return s.substr(start, end - start);
    }

    static bool leeP(const std::string& s, const std::string& p){
        return s.rfind(p, 0) == 0;
    }
public:

    AFD<Simbolo> parseFromFile(const std::string& filename) {

        std::ifstream file(filename);
        if (!file)
            throw InvalidFormatException("Error al abrir el archivo");

        AFDBuilder<Simbolo> builder;

        enum class Section {
            NONE,
            ESTADOS,
            INICIAL,
            FINAL,
            ALFABETO,
            TRANSICIONES
        };

        Section current = Section::NONE;

        std::string line;

        while (std::getline(file, line)) {

            line = trim(line);

            if (line.empty()) continue;
            if (leeP(line, "#")) continue;
            if (line == "[ESTADOS]") {
                current = Section::ESTADOS;
                continue;
            }
            if (line == "[INICIAL]") {
                current = Section::INICIAL;
                continue;
            }
            if (line == "[FINAL]") {
                current = Section::FINAL;
                continue;
            }
            if (line == "[ALFABETO]") {
                current = Section::ALFABETO;
                continue;
            }
            if (line == "[TRANSICIONES]") {
                current = Section::TRANSICIONES;
                continue;
            }

            switch (current) {

                case Section::ESTADOS: {
                    builder.agregarEstado(Estado(line));
                    break;
                }

                case Section::INICIAL: {
                    builder.establecerInicial(Estado(line));
                    break;
                }

                case Section::FINAL: {
                    builder.agregarFinal(Estado(line));
                    break;
                }

                case Section::ALFABETO: {
                    if (line.size() != 1)
                        throw InvalidFormatException("Símbolo inválido en ALFABETO");

                    builder.agregarSimbolo(static_cast<Simbolo>(line[0]));
                    break;
                }

                case Section::TRANSICIONES: {

                    std::istringstream iss(line);
                    std::string origen, simboloStr, destino;

                    if (!(iss >> origen >> simboloStr >> destino))
                        throw InvalidFormatException("Error en la transición");

                    if (simboloStr.size() != 1)
                        throw InvalidFormatException("Símbolo inválido en transición");

                    builder.agregarTransicion(
                        Transicion<Simbolo>(
                            Estado(origen),
                            static_cast<Simbolo>(simboloStr[0]),
                            Estado(destino)
                        )
                    );

                    break;
                }

                default:
                    throw InvalidFormatException("Sección no definida antes de contenido");
            }
        }

        return builder.build();
    }
};

#endif
