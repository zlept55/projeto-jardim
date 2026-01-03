#include "Bloco.h"
#include "Planta.h"
#include "Ferramenta.h"
#include "Settings.h"

#include <cstdlib>

Bloco::Bloco() {
    defValoresIniciais();
}

Bloco::~Bloco() {
    delete planta;
    delete ferramenta;
}

void Bloco::defValoresIniciais() {
    // Valores iniciais aleatórios com base no enunciado:
    // água entre 80 e 100, nutrientes entre 40 e 50 (usando Settings ou rand). [file:1][file:42]
    int minAgua = Settings::agua_inicial_solo_min;
    int maxAgua = Settings::agua_inicial_solo_max;
    int minNutr = Settings::nutrientes_inicial_solo_min;
    int maxNutr = Settings::nutrientes_inicial_solo_max;

    agua = minAgua + (std::rand() % (maxAgua - minAgua + 1));
    nutrientes = minNutr + (std::rand() % (maxNutr - minNutr + 1));
}

char Bloco::getSimbolo() const {
    if (planta)
        return planta->getSimbolo();
    if (ferramenta)
        return ferramenta->getSimbolo();
    return ' ';
}

void Bloco::mostrarInfo() const {
    std::cout << "Agua: " << agua
              << ", Nutrientes: " << nutrientes;

    if (planta) {
        std::cout << ", Planta: " << planta->getSimbolo();
    }
    if (ferramenta) {
        std::cout << ", Ferramenta: " << ferramenta->getSimbolo();
    }

    std::cout << "\n";
}

void Bloco::atualizar() {
    // Neste projeto, quem trata do comportamento das plantas é o Jardim,
    // chamando planta->atualizar(*this) diretamente. [file:31][file:38]
    // Mantém-se esta função para possível uso futuro.
}
