#ifndef COMANDO_H
#define COMANDO_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Comando {
    std::string nome;                 // nome do comando (ex: "jardim")
    std::vector<std::string> args;    // lista de argumentos (ex: ["5", "7"])

public:
    Comando(const std::string& linha); // construtor que recebe a linha de texto
    bool validar();                    // valida a estrutura do comando

    std::string getNome() const { return nome; }
    std::vector<std::string> getArgs() const { return args; }
};

#endif
