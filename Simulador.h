#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Comando.h"
#include "Jardim.h"
#include <memory>  // para usar ponteiros inteligentes (opcional)

class Simulador {
    Jardim* jardim = nullptr;  // Ponteiro para o jardim atual (pode estar vazio)

public:
    Simulador() = default;
    ~Simulador();

    void processarComando(const Comando& cmd);
};

#endif
