#ifndef TP_BLOCO_H
#define TP_BLOCO_H

#include <iostream>

class Planta; // criar class para a(s) plantas
class Ferramenta; // criar class para a(s) ferramentas

class Bloco {
    Planta* planta = nullptr; // ponteiro para planta ou nullptr (caso não tenha valor)
    Ferramenta* ferramenta = nullptr; // ponteiro para ferramenta ou nullptr (caso não tenha valor)
    int agua; // quantidade de água no bloco atual
    int nutrientes; // quantidade de nutrientes no bloco atual

public:
    Bloco(int agua, int nutrientes) : agua(agua), nutrientes(nutrientes){};
    ~Bloco();
    void defValoresIniciais(); // TODO: funcao que define os valores iniciais (aleatórios) de água e nutrientes
    char getSimbolo() const; // função que devolve o caráter que representa a determinada célula no jardim
    void mostrarInfo() const; // função auxiliar que imprime informação detalhada (valor da água/nutrientes)

    // Getters
    Planta* getPlanta() const { return planta; }
    Ferramenta* getFerramenta() const { return ferramenta; }
    int getAgua() const { return agua; }
    int getNutrientes() const { return nutrientes; }

    // Setters
    void setPlanta(Planta* p) { planta = p; }            // TODO: validar posição
    void setFerramenta(Ferramenta* f) { ferramenta = f; }
    void setAgua(int a) { agua = a; }
    void setNutrientes(int n) { nutrientes = n; }

    // TODO: comportamento futuro
    void atualizar(); // chamada a cada instante (planta/ferramenta podem agir)
};


#endif //TP_BLOCO_H