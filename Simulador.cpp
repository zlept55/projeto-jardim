#include "Simulador.h"

#include <iostream>
#include <vector>

#include "Ferramenta.h"

Simulador::Simulador(Jardim* j, Jardineiro* jard) {
    instanteAtual = 0;
    jardim = j;
    jardineiro = jard;
}

Simulador::~Simulador() {
    delete jardim; // se o jardim existir, é libertado da memória
}

int Simulador::getInstanteAtual() const {
    return instanteAtual;
}

void Simulador::avanca(int nInstantes) {
    if (!jardim) {
        std::cout << "Erro: ainda nao existe jardim.\n";
        return;
    }

    for (int i = 0; i < nInstantes; i++) {
        instanteAtual++;

        jardim->atualizar();



        std::cout << "[DEBUG] Instante " << instanteAtual << " concluído\n";
        jardim->avancaInstante();   // avanço interno do jardim (plantas, etc.)
        std::cout << "[DEBUG] Instante " << instanteAtual << " concluido\n";
    }

    jardim->mostrar(*jardineiro);
}

void Simulador::processarComando(const Comando& cmd) {
    std::string nome = cmd.getNome();
    std::vector<std::string> args = cmd.getArgs();

    // comando jardim <linhas> <colunas>
    if (nome == "jardim") {
        if (args.size() != 2) {
            std::cout << "Erro: uso correto -> jardim <linhas> <colunas>\n";
            return;
        }

        int linhas = std::stoi(args[0]); // converte string para inteiro
        int colunas = std::stoi(args[1]);

        if (linhas <= 0 || colunas <= 0 || linhas > 26 || colunas > 26) {
            std::cout << "Erro: tamanhos invalidos (1–26)\n";
            return;
        }

        // se já existir um jardim anterior, apaga-o
        delete jardim;
        jardim = new Jardim(linhas, colunas);

        // ligar jardineiro ao jardim
        jardim->setJardineiro(jardineiro);

        std::cout << "\nJardim criado com sucesso ("
                  << linhas << "x" << colunas << ")\n";
        jardim->mostrar(*jardineiro); // mostra o jardim criado
        return;
    }

    // comando avanca [n]
    if (nome == "avanca") {
        int n = 1;
        if (!args.empty())
            n = std::stoi(args[0]);

        if (n <= 0) {
            std::cout << "Erro: numero de instantes deve ser positivo.\n";
            return;
        }

        avanca(n);
        return;
    }

    // comando compra <g|a|t|z>
    if (nome == "compra") {
        if (args.size() != 1) {
            std::cout << "Erro: uso correto -> compra <g|a|t|z>\n";
            return;
        }

        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }

        char tipo = args[0][0];
        Ferramenta* f = nullptr;

        switch (tipo) {
            case 'g': f = new Regador();     break;
            case 'a': f = new Adubo();       break;
            case 't': f = new Tesoura();     break;
            case 'z': f = new FerramentaZ(); break;
            default:
                std::cout << "Erro: tipo de ferramenta invalido (use g, a, t ou z).\n";
                return;
        }

        std::cout << "Comprada ferramenta " << f->getNome()
                  << " #" << f->getId() << "\n";

        // Por agora, coloca a ferramenta na posicao (0,0) se estiver livre
        if (jardim->getBloco(0, 0) && jardim->getBloco(0, 0)->getFerramenta() == nullptr) {
            jardim->adicionarFerramenta(0, 0, f);
        } else {
            std::cout << "Ainda nao foi definido onde guardar ferramentas compradas.\n";
        }

        jardim->mostrar(*jardineiro);
        return;
    }

    if (nome == "fim") {
        std::cout << "A terminar o simulador...\n";
        return;
    }

    std::cout << "Comando reconhecido mas ainda nao implementado: " << nome << "\n";
}
