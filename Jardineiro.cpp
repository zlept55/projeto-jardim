#include "Jardineiro.h"

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




