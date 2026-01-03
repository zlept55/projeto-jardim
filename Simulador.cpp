#include "Simulador.h"

#include <iostream>
#include <vector>
#include <fstream>   // <-- novo

#include "Ferramenta.h"
#include "Bloco.h"
#include "Planta.h"

// === função auxiliar para clonar um jardim ===
Jardim* Simulador::clonarJardim(const Jardim* origem) {
    if (!origem) return nullptr;

    int linhas = origem->getLinhas();
    int colunas = origem->getColunas();

    Jardim* copia = new Jardim(linhas, colunas);

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            Bloco* bOrig = origem->getBloco(l, c);
            Bloco* bDest = copia->getBloco(l, c);
            if (!bOrig || !bDest) continue;

            // copiar solo
            bDest->setAgua(bOrig->getAgua());
            bDest->setNutrientes(bOrig->getNutrientes());

            // copiar planta (usando clonar())
            if (bOrig->getPlanta()) {
                bDest->setPlanta(bOrig->getPlanta()->clonar());
            }

            // copiar ferramenta (criando novo objeto com o mesmo simbolo)
            if (bOrig->getFerramenta()) {
                Ferramenta* fOrig = bOrig->getFerramenta();
                Ferramenta* fNova = nullptr;
                char s = fOrig->getSimbolo();
                switch (s) {
                    case 'g': fNova = new Regador(); break;
                    case 'a': fNova = new Adubo();   break;
                    case 't': fNova = new Tesoura(); break;
                    case 'z': fNova = new FerramentaZ(); break;
                    default: break;
                }
                if (fNova)
                    bDest->setFerramenta(fNova);
            }
        }
    }

    return copia;
}

Simulador::Simulador(Jardim* j, Jardineiro* jard) {
    instanteAtual = 0;
    jardim = j;
    jardineiro = jard;
}

Simulador::~Simulador() {
    delete jardim;
    for (auto& par : backups)
        delete par.second;
}

int Simulador::getInstanteAtual() const {
    return instanteAtual;
}

void Simulador::avanca(int nInstantes) {
    if (!jardim) {
        std::cout << "Erro: ainda nao existe jardim.\n";
        return;
    }

    // reset aos contadores de turno
    if (jardineiro)
        jardineiro->resetTurno();

    for (int i = 0; i < nInstantes; i++) {
        instanteAtual++;
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

    // comando planta <l><c> <tipo>
    if (nome == "planta") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }

        if (!jardineiro->podePlantar()) {
            std::cout << "Ja atingiu o limite de plantacoes neste turno.\n";
            return;
        }

        if (args.size() != 2 || args[0].size() != 2 || args[1].size() != 1) {
            std::cout << "Erro: uso correto -> planta <lc> <tipo> (ex: planta fb c)\n";
            return;
        }

        char linChar = args[0][0];
        char colChar = args[0][1];
        int l = linChar - 'a';
        int c = colChar - 'a';

        if (l < 0 || l >= jardim->getLinhas() || c < 0 || c >= jardim->getColunas()) {
            std::cout << "Erro: posicao fora do jardim.\n";
            return;
        }

        Bloco* b = jardim->getBloco(l, c);
        if (!b) return;

        if (b->getPlanta() != nullptr) {
            std::cout << "Erro: ja existe planta nessa posicao.\n";
            return;
        }

        char tipo = args[1][0];
        Planta* p = nullptr;

        switch (tipo) {
            case 'c': case 'C':
                p = new Cacto();
                break;
            case 'r': case 'R':
                p = new Roseira();
                break;
            case 'e': case 'E':
                p = new ErvaDaninha();
                break;
            case 'x': case 'X':
                p = new Exotica();
                break;
            default:
                std::cout << "Erro: tipo de planta invalido (usa C, R, E, X).\n";
                return;
        }

        jardineiro->registarPlantacao();
        jardim->adicionarPlanta(l, c, p);
        std::cout << "Plantada planta do tipo " << tipo
                  << " em " << linChar << colChar << "\n";

        jardim->mostrar(*jardineiro);
        return;
    }

    // comando colhe <l><c>
    if (nome == "colhe") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }

        if (!jardineiro->podeColher()) {
            std::cout << "Ja atingiu o limite de colheitas neste turno.\n";
            return;
        }

        if (args.size() != 1 || args[0].size() != 2) {
            std::cout << "Erro: uso correto -> colhe <lc> (ex: colhe fb)\n";
            return;
        }

        char linChar = args[0][0];
        char colChar = args[0][1];
        int l = linChar - 'a';
        int c = colChar - 'a';

        if (l < 0 || l >= jardim->getLinhas() || c < 0 || c >= jardim->getColunas()) {
            std::cout << "Erro: posicao fora do jardim.\n";
            return;
        }

        Bloco* b = jardim->getBloco(l, c);
        if (!b) return;

        Planta* p = b->getPlanta();
        if (!p) {
            std::cout << "Nao existe planta nessa posicao.\n";
            return;
        }

        jardineiro->registarColheita();
        delete p;
        b->setPlanta(nullptr);

        std::cout << "Planta colhida em " << linChar << colChar << "\n";

        jardim->mostrar(*jardineiro);
        return;
    }

    // entra <l><c>  (ex: entra ab)
    if (nome == "entra") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }

        if (!jardineiro->podeEntrarSair()) {
            std::cout << "Ja atingiu o limite de entradas/saidas neste turno.\n";
            return;
        }

        if (args.size() != 1 || args[0].size() != 2) {
            std::cout << "Erro: uso correto -> entra <lc> (ex: entra ab)\n";
            return;
        }

        char linChar = args[0][0];
        char colChar = args[0][1];

        int l = linChar - 'a';
        int c = colChar - 'a';

        if (l < 0 || l >= jardim->getLinhas() || c < 0 || c >= jardim->getColunas()) {
            std::cout << "Erro: posicao fora do jardim.\n";
            return;
        }

        jardineiro->entra(l, c);
        jardim->mostrar(*jardineiro);
        return;
    }

    // sai
    if (nome == "sai") {
        if (!jardineiro->podeEntrarSair()) {
            std::cout << "Ja atingiu o limite de entradas/saidas neste turno.\n";
            return;
        }

        jardineiro->sai();
        if (jardim)
            jardim->mostrar(*jardineiro);
        return;
    }

    // movimento: c (cima), b (baixo), e (esquerda), d (direita)
    if (nome == "c" || nome == "b" || nome == "e" || nome == "d") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }

        if (!jardineiro->estaNoJardim()) {
            std::cout << "Erro: jardineiro nao esta no jardim.\n";
            return;
        }

        int maxL = jardim->getLinhas();
        int maxC = jardim->getColunas();

        if (nome == "c")
            jardineiro->paraCima(maxL);
        else if (nome == "b")
            jardineiro->paraBaixo(maxL);
        else if (nome == "e")
            jardineiro->paraEsquerda(maxC);
        else if (nome == "d")
            jardineiro->paraDireita(maxC);

        jardim->mostrar(*jardineiro);
        return;
    }

    // lferr
    if (nome == "lferr") {
        std::cout << "Ferramentas do jardineiro:\n";
        jardineiro->listarFerramentas();
        return;
    }

    // larga
    if (nome == "larga") {
        jardineiro->largaFerramenta();
        std::cout << "Ferramenta largada (nenhuma na mao).\n";
        return;
    }

    // pega <id>
    if (nome == "pega") {
        if (args.size() != 1) {
            std::cout << "Erro: uso correto -> pega <id>\n";
            return;
        }
        int id = std::stoi(args[0]);
        jardineiro->escolheFerramenta(id);
        std::cout << "Ferramenta selecionada (se existir com esse id).\n";
        return;
    }

    // lsolo <lc> [n]
    if (nome == "lsolo") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }
        if (args.size() < 1 || args.size() > 2 || args[0].size() != 2) {
            std::cout << "Erro: uso correto -> lsolo <lc> [n]\n";
            return;
        }

        char linChar = args[0][0];
        char colChar = args[0][1];
        int l0 = linChar - 'a';
        int c0 = colChar - 'a';

        if (l0 < 0 || l0 >= jardim->getLinhas() || c0 < 0 || c0 >= jardim->getColunas()) {
            std::cout << "Erro: posicao fora do jardim.\n";
            return;
        }

        int raio = 0;
        if (args.size() == 2)
            raio = std::stoi(args[1]);

        int lIni = std::max(0, l0 - raio);
        int lFim = std::min(jardim->getLinhas() - 1, l0 + raio);
        int cIni = std::max(0, c0 - raio);
        int cFim = std::min(jardim->getColunas() - 1, c0 + raio);

        for (int l = lIni; l <= lFim; ++l) {
            for (int c = cIni; c <= cFim; ++c) {
                Bloco* b = jardim->getBloco(l, c);
                if (!b) continue;

                std::cout << char('a' + l) << char('a' + c)
                          << ": agua=" << b->getAgua()
                          << ", nutr=" << b->getNutrientes();

                if (b->getPlanta()) {
                    std::cout << ", planta=" << b->getPlanta()->getSimbolo();
                } else {
                    std::cout << ", planta=nenhuma";
                }

                if (b->getFerramenta()) {
                    std::cout << ", ferr=" << b->getFerramenta()->getSimbolo()
                              << " #" << b->getFerramenta()->getId();
                } else {
                    std::cout << ", ferr=nenhuma";
                }
                std::cout << "\n";
            }
        }
        return;
    }

    // larea
    if (nome == "larea") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }

        int linhas = jardim->getLinhas();
        int colunas = jardim->getColunas();

        for (int l = 0; l < linhas; ++l) {
            for (int c = 0; c < colunas; ++c) {
                Bloco* b = jardim->getBloco(l, c);
                if (!b) continue;

                bool temPlanta = b->getPlanta() != nullptr;
                bool temFerramenta = b->getFerramenta() != nullptr;

                // totalmente vazia = sem planta e sem ferramenta
                if (!temPlanta && !temFerramenta)
                    continue;

                std::cout << char('a' + l) << char('a' + c)
                          << ": agua=" << b->getAgua()
                          << ", nutr=" << b->getNutrientes();

                if (temPlanta) {
                    std::cout << ", planta=" << b->getPlanta()->getSimbolo();
                } else {
                    std::cout << ", planta=nenhuma";
                }

                if (temFerramenta) {
                    std::cout << ", ferr=" << b->getFerramenta()->getSimbolo()
                              << " #" << b->getFerramenta()->getId();
                } else {
                    std::cout << ", ferr=nenhuma";
                }
                std::cout << "\n";
            }
        }
        return;
    }

    // grava <nome>
    if (nome == "grava") {
        if (!jardim) {
            std::cout << "Erro: ainda nao existe jardim.\n";
            return;
        }
        if (args.size() != 1) {
            std::cout << "Erro: uso correto -> grava <nome>\n";
            return;
        }
        std::string n = args[0];

        auto it = backups.find(n);
        if (it != backups.end()) {
            delete it->second;
            backups.erase(it);
        }

        Jardim* copia = clonarJardim(jardim);
        backups[n] = copia;

        std::cout << "Gravada copia do jardim com o nome '" << n << "'.\n";
        return;
    }

    // recupera <nome>
    if (nome == "recupera") {
        if (args.size() != 1) {
            std::cout << "Erro: uso correto -> recupera <nome>\n";
            return;
        }
        std::string n = args[0];

        auto it = backups.find(n);
        if (it == backups.end()) {
            std::cout << "Nao existe copia com o nome '" << n << "'.\n";
            return;
        }

        delete jardim;
        jardim = it->second;
        backups.erase(it);

        jardim->setJardineiro(jardineiro);

        std::cout << "Copia '" << n << "' recuperada.\n";
        jardim->mostrar(*jardineiro);
        return;
    }

    // apaga <nome>
    if (nome == "apaga") {
        if (args.size() != 1) {
            std::cout << "Erro: uso correto -> apaga <nome>\n";
            return;
        }
        std::string n = args[0];

        auto it = backups.find(n);
        if (it == backups.end()) {
            std::cout << "Nao existe copia com o nome '" << n << "'.\n";
            return;
        }

        delete it->second;
        backups.erase(it);

        std::cout << "Copia '" << n << "' apagada.\n";
        return;
    }

    // executa <ficheiro>
    if (nome == "executa") {
        if (args.size() != 1) {
            std::cout << "Erro: uso correto -> executa <ficheiro>\n";
            return;
        }

        std::ifstream f(args[0]);
        if (!f) {
            std::cout << "Erro: nao foi possivel abrir o ficheiro '" << args[0] << "'.\n";
            return;
        }

        std::string linha;
        while (std::getline(f, linha)) {
            if (linha.empty())
                continue;

            Comando c(linha);
            processarComando(c);
        }

        return;
    }

    if (nome == "fim") {
        std::cout << "A terminar o simulador...\n";
        return;
    }

    std::cout << "Comando reconhecido mas ainda nao implementado: " << nome << "\n";
}
