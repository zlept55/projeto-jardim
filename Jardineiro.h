#ifndef TP_JARDINEIRO_H
#define TP_JARDINEIRO_H

#include <vector>
#include "Ferramenta.h"
#include "Settings.h"

class Jardim; // forward declaration

class Jardineiro {

private:
    bool noJardim;
    int linha;
    int coluna;

    // Inventário de ferramentas
    std::vector<Ferramenta*> ferramentas;
    Ferramenta* naMao = nullptr; // ferramenta ativa

    // Contadores por turno
    int movimentosFeitos = 0;
    int entradasSaidasFeitas = 0;
    int plantasPlantadas = 0;
    int plantasColhidas = 0;

public:
    Jardineiro();

    bool estaNoJardim() const;
    int getLinha() const;
    int getColuna() const;

    void entra(int l, int c);
    void sai();
    void paraCima(int maxLinhas);
    void paraBaixo(int maxLinhas);
    void paraEsquerda(int maxColunas);
    void paraDireita(int maxColunas);

    // Gestão de ferramentas
    void apanharFerramenta(Ferramenta* f); // adiciona ao inventário
    void largaFerramenta();                // tira a ferramenta da mão (continua no inventário)
    void escolheFerramenta(int id);        // escolhe por número de série

    // Aplicar a ferramenta atual na posição onde o jardineiro está
    void aplicarFerramentaAtual(Jardim& jardim);

    // --- gestão de contadores de turno ---
    void resetTurno();
    bool podeMover() const;
    bool podeEntrarSair() const;
    bool podePlantar() const;
    bool podeColher() const;

    void registarMovimento();
    void registarEntradaSaida();
    void registarPlantacao();
    void registarColheita();

    // Listagem de ferramentas
    void listarFerramentas() const;
};

#endif //TP_JARDINEIRO_H
