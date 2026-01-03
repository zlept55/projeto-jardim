#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Comando.h"
#include "Jardim.h"
#include "Jardineiro.h"

#include <map>
#include <string>

class Simulador {

private:
    Jardim* jardim;
    int instanteAtual;
    Jardineiro* jardineiro;

    // cópias de jardim associadas a um nome (para grava/recupera/apaga)
    std::map<std::string, Jardim*> backups;

    // função auxiliar para clonar um jardim (implementada em Simulador.cpp)
    Jardim* clonarJardim(const Jardim* origem);

public:
    Simulador(Jardim* j, Jardineiro* jard);
    ~Simulador();

    int getInstanteAtual() const;

    void avanca(int nInstantes);
    void processarComando(const Comando& cmd);
};

#endif
