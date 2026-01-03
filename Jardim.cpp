#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Jardim.h"
#include "Ferramenta.h"
#include "Planta.h"
#include "Jardineiro.h"

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    if (linhas <= 0 || colunas <= 0)
        throw std::invalid_argument("Dimensoes invalidas do jardim");
    grelha = new Bloco*[linhas];

    for (int i = 0; i < linhas; i++)
        grelha[i] = new Bloco[colunas];
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; i++) {
        delete[] grelha[i];
    }
    delete[] grelha;
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

    for (int l = 0; l < linhas; l++)
        for (int c = 0; c < colunas; c++) {
            Planta *p = grelha[l][c].getPlanta();
            if (p && p->getSimbolo() == 'k') {
                int direcoes[4][2] = {
                    {-1, 0},
                    { 1, 0},
                    { 0,-1},
                    { 0, 1}
                };

                for (int i = 0; i < 4; i++) {
                    int vizlinha = l + direcoes[i][0];
                    int vizcoluna = c + direcoes[i][1];

                    if (vizlinha >= 0 && vizlinha < linhas
                        && vizcoluna >= 0 && vizcoluna < colunas) {

                        Bloco &vizinho = grelha[vizlinha][vizcoluna];
                        Planta *vizPlanta = vizinho.getPlanta();

                        if (vizPlanta && vizPlanta->getSimbolo() == 'e') {
                            vizinho.setPlanta(nullptr);
                            delete vizPlanta;

                            dynamic_cast<Carnivora*>(p)->ganhaNutrientes(
                                Settings::Carnivora::ganha_nutrientes_feia);

                            std::cout << "A Planta Carnivora em (" << (char)('a'+l) << (char)('a'+c) << ") comeu erva daninha em (" << (char)('a'+vizlinha) << (char)('a'+vizcoluna) << ")!\n" << std::endl;
                        }
                    }
                }
            }
        }

    tratarMultiplicacao();
    verificarEspacoRoseiras();
}

void Jardim::avancaInstante() {
    instanteAtual++;
    atualizar();
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

                    if (dl == 0 && dc == 0)
                        continue;

                    int nl = l + dl;
                    int nc = c + dc;

                    if (!posicaoValida(nl, nc))
                        continue;

                    if (grelha[nl][nc].getPlanta() != nullptr)
                        continue;

                    // cria nova planta
                    Planta* nova = p->clonar();
                    grelha[nl][nc].setPlanta(nova);

                    // ajusta a planta original (roseira, cacto, etc.)
                    p->aposMultiplicacao();
                    p->resetMult();

                    return; // só multiplica uma vez por instante
                }
            }

            // não conseguiu multiplicar
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