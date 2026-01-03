#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Comando.h"
#include "Jardim.h"
#include "Jardineiro.h"

class Simulador {
private:
    Jardim* jardim;
    int instanteAtual;
    Jardineiro* jardineiro;

public:
    Simulador(Jardim* j, Jardineiro* jard);
    ~Simulador();

    int getInstanteAtual() const;
    void avanca(int nInstantes);

    void processarComando(const Comando& cmd);
};

#endif
