#include "Jardineiro.h"
#include "Jardim.h"
#include "Bloco.h"

#include <algorithm>

Jardineiro::Jardineiro() {
    noJardim = false;
    linha = -1;
    coluna = -1;
}

bool Jardineiro::estaNoJardim() const {
    return noJardim;
}

int Jardineiro::getLinha() const {
    return linha;
}

int Jardineiro::getColuna() const {
    return coluna;
}

void Jardineiro::entra(int l, int c) {
    noJardim = true;
    linha = l;
    coluna = c;
}

void Jardineiro::sai() {
    noJardim = false;
    linha = -1;
    coluna = -1;
}

void Jardineiro::paraCima() {
    if (noJardim)
        linha--;
}

void Jardineiro::paraBaixo() {
    if (noJardim)
        linha++;
}

void Jardineiro::paraEsquerda() {
    if (noJardim)
        coluna--;
}

void Jardineiro::paraDireita() {
    if (noJardim)
        coluna++;
}

// --- gestão de ferramentas ---

void Jardineiro::apanharFerramenta(Ferramenta* f) {
    if (!f) return;
    ferramentas.push_back(f);
    if (!naMao)
        naMao = f; // se não houver nenhuma ativa, passa a ser esta
}

void Jardineiro::largaFerramenta() {
    naMao = nullptr;
}

void Jardineiro::escolheFerramenta(int id) {
    for (auto* f : ferramentas) {
        if (f->getId() == id) {
            naMao = f;
            return;
        }
    }
}

// --- aplicar ferramenta atual ---

void Jardineiro::aplicarFerramentaAtual(Jardim& jardim) {
    if (!noJardim || !naMao)
        return;

    Bloco* b = jardim.getBloco(linha, coluna);
    if (!b)
        return;

    char s = naMao->getSimbolo();

    if (s == 'g') { // Regador
        auto* reg = dynamic_cast<Regador*>(naMao);
        if (reg && reg->getCapacidade() >= 10) {
            // aumenta água no solo em 10
            b->setAgua(b->getAgua() + 10);
            reg->usar();

            if (reg->getCapacidade() == 0) {
                // regador vazio sai do simulador
                std::cout << "Regador #" << reg->getId() << " esgotou e saiu do simulador.\n";
                ferramentas.erase(std::remove(ferramentas.begin(), ferramentas.end(), reg), ferramentas.end());
                if (naMao == reg)
                    naMao = nullptr;
                delete reg;
            }
        }
    } else if (s == 'a') { // Adubo
        auto* ad = dynamic_cast<Adubo*>(naMao);
        if (ad && ad->getQuantidade() >= 10) {
            // aumenta nutrientes no solo em 10
            b->setNutrientes(b->getNutrientes() + 10);
            ad->usar();

            if (ad->getQuantidade() == 0) {
                std::cout << "Adubo #" << ad->getId() << " esgotou e saiu do simulador.\n";
                ferramentas.erase(std::remove(ferramentas.begin(), ferramentas.end(), ad), ferramentas.end());
                if (naMao == ad)
                    naMao = nullptr;
                delete ad;
            }
        }
    } else if (s == 't') { // Tesoura
        // Tesoura elimina plantas "feias": aqui assumimos erva daninha (simbolo 'e')
        if (b->getPlanta() && b->getPlanta()->getSimbolo() == 'e') {
            std::cout << "Tesoura eliminou erva daninha em posicao "
                      << char('a' + linha) << char('a' + coluna) << "\n";
            b->getPlanta()->morrer(*b);
            b->setPlanta(nullptr);
        }
        naMao->usar(); // não gasta nada, mas mantém a chamada
    } else if (s == 'z') {
        // FerramentaZ: comportamento personalizado (por agora, só mensagem)
        std::cout << "FerramentaZ #" << naMao->getId()
                  << " aplicada em " << char('a' + linha) << char('a' + coluna) << "\n";
        naMao->usar();
    }
}
