#include <iostream>
#include <ctime>
#include "Simulador.h"
#include "Comando.h"

int main() {
    Jardim* jardim = nullptr;
    Jardineiro* jardineiro = new Jardineiro();
    std::srand(time(nullptr)); // inicializa os números aleatórios

    std::cout << "=== Simulador de Jardim ===\n";

    Simulador sim(jardim, jardineiro);
    std::string linha;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, linha);

        Comando cmd(linha);

        if (!cmd.validar())
            continue;

        if (cmd.getNome() == "fim")
            break;

        sim.processarComando(cmd);
    }

    std::cout << "Programa terminado.\n";
    delete jardineiro;
    return 0;
}
