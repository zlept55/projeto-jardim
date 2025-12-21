#include "Jardim.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // criar matriz de ponteiros
    grelha = new Bloco**[linhas];
    for (int i = 0; i < linhas; ++i) {
        grelha[i] = new Bloco*[colunas];
        for (int j = 0; j < colunas; ++j) {
            int aguaInicial = std::rand() % 21 + 80;        // 80–100
            int nutrientesIniciais = std::rand() % 11 + 40; // 40–50
            grelha[i][j] = new Bloco(aguaInicial, nutrientesIniciais);
        }
    }
}

Jardim::~Jardim() {
    // libertar cada Bloco e as linhas
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j)
            delete grelha[i][j];
        delete[] grelha[i];
    }
    delete[] grelha;
}

void Jardim::mostrar() const {
    std::cout << "  ";
    for (int j = 0; j < colunas; ++j)
        std::cout << static_cast<char>('A' + j);
    std::cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        std::cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < colunas; ++j)
            std::cout << grelha[i][j]->getSimbolo();
        std::cout << "\n";
    }
}

// --- Funções planeadas (meta 2) ---
/*
void Jardim::adicionarPlanta(int l, int c, Planta* p) {
    // TODO: validar limites e se já existe planta
    std::cout << "TODO: adicionar planta em (" << l << "," << c << ")\n";
}

void Jardim::adicionarFerramenta(int l, int c, Ferramenta* f) {
    // TODO: validar limites e se já existe ferramenta
    std::cout << "TODO: adicionar ferramenta em (" << l << "," << c << ")\n";
}

Bloco* Jardim::getBloco(int l, int c) const {
    // TODO: validar limites
    return &grelha[l][c];
}*/