#include <iostream>
#include <string>

#include "Simulador.h"
#include "Comando.h"
#include "Jardim.h"
#include "Jardineiro.h"

int main() {
    Jardim* jardim = nullptr;
    Jardineiro* jardineiro = new Jardineiro();

    Simulador sim(jardim, jardineiro);

    std::string linha;

    std::cout << "Simulador de Jardim (POO)\n";
    std::cout << "Escreva comandos (fim para sair).\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, linha))
            break;

        if (linha.empty())
            continue;

        Comando cmd(linha);
        if (!cmd.validar())
            continue;

        if (cmd.getNome() == "fim") {
            sim.processarComando(cmd);
            break;
        }

        sim.processarComando(cmd);
    }

    delete jardineiro;
    // jardim é destruído no destrutor de Simulador

    return 0;
}
