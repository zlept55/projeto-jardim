#include "Bloco.h"
#include "Planta.h"
#include "Settings.h"
#include "Ferramenta.h"
#include <iostream>
#include <cstdlib>


Bloco::Bloco() {
    defValoresIniciais();
}

// destrutor — liberta memória se existirem planta ou ferramenta
Bloco::~Bloco() {
    delete planta;
    delete ferramenta;
}

// define valores iniciais de água e nutrientes (aleatórios)
void Bloco::defValoresIniciais() {
    agua = Settings::agua_inicial_solo_min +
           rand() % (Settings::agua_inicial_solo_max - Settings::agua_inicial_solo_min + 1);

    nutrientes = Settings::nutrientes_inicial_solo_min +
                 rand() % (Settings::nutrientes_inicial_solo_max - Settings::nutrientes_inicial_solo_min + 1);

    planta = nullptr;
    ferramenta = nullptr;
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

void Bloco::atualizar() {
    if (planta)
        planta->atualizar(*this);
}
