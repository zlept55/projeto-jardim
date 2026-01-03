#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "Jardim.h"
#include "Ferramenta.h"
#include "Planta.h"
#include "Jardineiro.h"

Jardim::Jardim(int l, int c) : linhas(l), colunas(c), jardineiro(nullptr), instanteAtual(0) {
    if (linhas <= 0 || colunas <= 0)
        throw std::invalid_argument("Dimensoes invalidas do jardim");

    grelha = new Bloco*[linhas];
    for (int i = 0; i < linhas; i++)
        grelha[i] = new Bloco[colunas];
}

void Jardim::setJardineiro(Jardineiro* j) {
    jardineiro = j;
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; i++) {
        delete[] grelha[i];
    }
    delete[] grelha;
}

int Jardim::getLinhas() const {
    return linhas;
}

int Jardim::getColunas() const {
    return colunas;
}

int Jardim::getInstante() const {
    return instanteAtual;
}

Bloco* Jardim::getBloco(int l, int c) const {
    if (l < 0 || l >= linhas || c < 0 || c >= colunas)
        return nullptr;
    return &grelha[l][c];
}

bool Jardim::posicaoValida(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

void Jardim::atualizar() {
    for (int l = 0; l < linhas; l++)
        for (int c = 0; c < colunas; c++)
            if (grelha[l][c].getPlanta())
                grelha[l][c].getPlanta()->atualizar(grelha[l][c]);

    tratarMultiplicacao();
    verificarEspacoRoseiras();
}

void Jardim::avancaInstante() {
    instanteAtual++;

    atualizar(); // plantas

    // se existir jardineiro, aplica a ferramenta que estiver na mão
    if (jardineiro) {
        jardineiro->aplicarFerramentaAtual(*this);
    }

    verificarEspacoRoseiras();
}

void Jardim::tratarMultiplicacao() {
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            Planta* p = grelha[l][c].getPlanta();
            if (!p || !p->querMult())
                continue;

            for (int dl = -1; dl <= 1; dl++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dl == 0 && dc == 0) continue;

                    int nl = l + dl;
                    int nc = c + dc;
                    if (!posicaoValida(nl, nc)) continue;
                    if (grelha[nl][nc].getPlanta()) continue;

                    // Criar nova planta
                    grelha[nl][nc].setPlanta(p->clonar());

                    // Ajustes específicos da roseira
                    if (p->getSimbolo() == 'r') {
                        p->setAgua(p->getAgua() / 2);
                        p->setNutrientes(100);
                    }

                    p->resetMult();
                    return;
                }
            }

            p->resetMult();
        }
    }
}

void Jardim::mostrar(const Jardineiro& j) const {
    std::cout << "  ";
    for (int c = 0; c < colunas; c++) {
        std::cout << char('A' + c);
    }
    std::cout << "\n";

    for (int l = 0; l < linhas; l++) {
        std::cout << char('A' + l) << " ";
        for (int c = 0; c < colunas; c++) {
            const Bloco& b = grelha[l][c];

            if (j.estaNoJardim() &&
                j.getLinha() == l &&
                j.getColuna() == c) {
                std::cout << "*";
            }
            else if (b.getPlanta() != nullptr) {
                std::cout << b.getPlanta()->getSimbolo();
            }
            else if (b.getFerramenta() != nullptr) {
                std::cout << b.getFerramenta()->getSimbolo();
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << " " << char('A' + l) << "\n";
    }

    std::cout << "  ";
    for (int c = 0; c < colunas; c++) {
        std::cout << char('A' + c);
    }
    std::cout << "\n";
}

void Jardim::multiplicarRoseira(int l, int c) {
    Planta* p = grelha[l][c].getPlanta();
    if (!p || p->getSimbolo() != 'r')
        return;

    for (int dl = -1; dl <= 1; dl++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dl == 0 && dc == 0)
                continue;

            int nl = l + dl;
            int nc = c + dc;
            if (!posicaoValida(nl,nc))
                continue;

            if (grelha[nl][nc].getPlanta() == nullptr) {
                Planta* nova = p->clonar();
                grelha[nl][nc].setPlanta(nova);
                p->resetMult();
                return;
            }
        }
    }
}

bool Jardim::roseiraSemEspaco(int l, int c) const {
    Planta* p = grelha[l][c].getPlanta();
    if (!p || p->getSimbolo() != 'r')
        return false;

    for (int dl = -1; dl <= 1; dl++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dl == 0 && dc == 0)
                continue;

            int nl = l + dl;
            int nc = c + dc;
            if (!posicaoValida(nl, nc))
                continue;

            if (grelha[nl][nc].getPlanta() == nullptr)
                return false;
        }
    }
    return true;
}

void Jardim::verificarEspacoRoseiras() {
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            Planta* p = grelha[l][c].getPlanta();
            if (p && p->getSimbolo() == 'r') {
                if (roseiraSemEspaco(l, c)) {
                    p->morrer(grelha[l][c]);
                }
            }
        }
    }
}

// --- meta 2 ---

void Jardim::adicionarPlanta(int l, int c, Planta* p) {
    if (!posicaoValida(l, c) || p == nullptr)
        return;

    Bloco* b = getBloco(l, c);
    if (!b)
        return;

    if (b->getPlanta() != nullptr)
        return; // já existe planta nessa posição

    b->setPlanta(p);
}

void Jardim::adicionarFerramenta(int l, int c, Ferramenta* f) {
    if (!posicaoValida(l, c) || f == nullptr)
        return;

    Bloco* b = getBloco(l, c);
    if (!b)
        return;

    if (b->getFerramenta() != nullptr)
        return; // já existe ferramenta nessa posição

    b->setFerramenta(f);
}
