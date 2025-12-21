#ifndef TP_JARDIM_H
#define TP_JARDIM_H

#include "Bloco.h"
#include <iostream>

class Jardim {
    int linhas, colunas;
    Bloco*** grelha = nullptr; // matriz dinâmica de blocos

public:
    Jardim(int l, int c);
    ~Jardim();

    void mostrar() const;

    // --- meta 2 ---
    void adicionarPlanta(int l, int c, Planta* p);
    void adicionarFerramenta(int l, int c, Ferramenta* f);
    Bloco* getBloco(int l, int c) const;
};

#endif
