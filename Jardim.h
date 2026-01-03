#ifndef TP_JARDIM_H
#define TP_JARDIM_H

#include "Bloco.h"
#include "Jardineiro.h"
#include "Planta.h"
#include "Ferramenta.h"
#include <iostream>

class Jardim {
    int linhas, colunas;
    Bloco** grelha; // matriz dinâmica de blocos
    Jardineiro* jardineiro;
    int instanteAtual;

    bool posicaoValida(int l, int c) const;
    void verificarEspacoRoseiras();
    void tratarMultiplicacao();

public:
    Jardim(int linhas, int colunas);
    ~Jardim();

    void setJardineiro(Jardineiro* j);

    int getLinhas() const {return linhas;}
    int getColunas() const {return colunas;}
    int getInstante() const;

    void avancaInstante();
    bool querMult() const;
    void multiplicarRoseiras(int l, int c);
    bool roseiraSemEspaco(int l, int c) const;
    void multiplicarRoseira(int l, int c);

    Bloco* getBloco(int linha, int coluna) const;
    void mostrar(const Jardineiro& j) const;
    void atualizar();


    // --- meta 2 ---
    void adicionarPlanta(int l, int c, Planta* p);
    void adicionarFerramenta(int l, int c, Ferramenta* f);


};

#endif
