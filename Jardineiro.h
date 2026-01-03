#ifndef TP_JARDINEIRO_H
#define TP_JARDINEIRO_H

#include <vector>
#include "Ferramenta.h"

class Jardim; // forward declaration

class Jardineiro {

private:
    bool noJardim;
    int linha;
    int coluna;

    // Inventário de ferramentas
    std::vector<Ferramenta*> ferramentas;
    Ferramenta* naMao = nullptr; // ferramenta ativa

public:
    Jardineiro();

    bool estaNoJardim() const;
    int getLinha() const;
    int getColuna() const;

    void entra(int l, int c);
    void sai();
    void paraCima();
    void paraBaixo();
    void paraEsquerda();
    void paraDireita();

    // Gestão de ferramentas
    void apanharFerramenta(Ferramenta* f); // adiciona ao inventário
    void largaFerramenta();                // tira a ferramenta da mão (continua no inventário)
    void escolheFerramenta(int id);        // escolhe por número de série

    // Aplicar a ferramenta atual na posição onde o jardineiro está
    void aplicarFerramentaAtual(Jardim& jardim);
};

#endif //TP_JARDINEIRO_H
