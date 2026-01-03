//
// Created by rochi on 22/12/2025.
//

#ifndef TP_JARDINEIRO_H
#define TP_JARDINEIRO_H

class Jardineiro {
private:
    bool noJardim;
    int linha;
    int coluna;
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
};
#endif //TP_JARDINEIRO_H