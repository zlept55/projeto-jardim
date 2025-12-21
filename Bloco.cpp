#include "Bloco.h"
#include "Planta.h"
#include "Ferramenta.h"
#include <iostream>
#include <cstdlib>

// destrutor — liberta memória se existirem planta ou ferramenta
Bloco::~Bloco() {
    delete planta;
    delete ferramenta;
}

// define valores iniciais de água e nutrientes (aleatórios)
void Bloco::defValoresIniciais() {
    // TODO: estes valores deverão vir de Settings na versão final
    agua = rand() % 21 + 80;        // 80–100
    nutrientes = rand() % 11 + 40;  // 40–50
}

// retorna o símbolo a imprimir no jardim
char Bloco::getSimbolo() const {
    // ordem de prioridade de visualização:
    // jardineiro (no futuro) > planta > ferramenta > solo
    if (planta)
        return planta->getSimbolo();
    if (ferramenta)
        return ferramenta->getSimbolo();
    return ' '; // solo vazio
}

// mostra informação detalhada sobre o bloco
void Bloco::mostrarInfo() const {
    std::cout << "Água: " << agua << " | Nutrientes: " << nutrientes;

    if (planta)
        std::cout << " | Planta: " << "Presente";
    else
        std::cout << " | Planta: Nenhuma";

    if (ferramenta)
        std::cout << " | Ferramenta: " << "Presente";
    else
        std::cout << " | Ferramenta: Nenhuma";

    std::cout << "\n";
}

// atualiza o estado do bloco (planeado para meta 2)
void Bloco::atualizar() {
    // TODO: neste método, as plantas e ferramentas poderão agir a cada instante.
    // Exemplo futuro:
    // - Planta absorve água/nutrientes
    // - Ferramenta ativa altera o bloco
    // - Atualizar condições do solo
}
