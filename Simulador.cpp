#include "Simulador.h"
#include <iostream>
#include <cstdlib>

Simulador::Simulador(Jardim* j, Jardineiro* jard) {
    instanteAtual = 0;
    jardim = j;
    jardineiro = jard;
}

Simulador::~Simulador() {
    delete jardim;  // se o jardim existir, é libertado da memória
}

int Simulador::getInstanteAtual() const{
    return instanteAtual;
}

void Simulador::avanca(int nInstantes) {
    for (int i = 0; i < nInstantes; i++) {
        instanteAtual++;

        jardim->atualizar();



        std::cout << "[DEBUG] Instante " << instanteAtual << " concluído\n";
    }
}


void Simulador::processarComando(const Comando& cmd) {
    std::string nome = cmd.getNome();
    std::vector<std::string> args = cmd.getArgs();

    if (nome == "jardim") {
        if (args.size() != 2) {
            std::cout << "Erro: uso correto -> jardim <linhas> <colunas>\n";
            return;
        }

        int linhas = std::stoi(args[0]); // converte string para inteiro
        int colunas = std::stoi(args[1]);

        if (linhas <= 0 || colunas <= 0 || linhas > 26 || colunas > 26) {
            std::cout << "Erro: tamanhos inválidos (1–26)\n";
            return;
        }

        // se já existir um jardim anterior, apaga-o
        delete jardim;
        jardim = new Jardim(linhas, colunas);

        std::cout << "\nJardim criado com sucesso ("
                  << linhas << "x" << colunas << ")\n";
        jardim->mostrar(*jardineiro); // mostra o jardim criado
        return;
    }

    if (nome == "fim") {
        std::cout << "A terminar o simulador...\n";
        return;
    }

    std::cout << "Comando reconhecido mas ainda não implementado: " << nome << "\n";
}
