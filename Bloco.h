#ifndef TP_BLOCO_H
#define TP_BLOCO_H

#include <iostream>

class Planta;     // forward declaration
class Ferramenta; // forward declaration

class Bloco {
    Planta* planta = nullptr;        // ponteiro para planta ou nullptr
    Ferramenta* ferramenta = nullptr; // ponteiro para ferramenta ou nullptr
    int agua;                        // quantidade de água no bloco
    int nutrientes;                  // quantidade de nutrientes no bloco

public:
    Bloco();
    Bloco(int agua, int nutrientes) : planta(nullptr), ferramenta(nullptr),
                                      agua(agua), nutrientes(nutrientes) {}
    ~Bloco();

    void defValoresIniciais(); // define valores iniciais aleatórios de água/nutrientes

    char getSimbolo() const;   // carácter que representa a célula no jardim
    void mostrarInfo() const;  // imprime info detalhada (água, nutrientes, conteudo)

    // Getters
    Planta* getPlanta() const { return planta; }
    Ferramenta* getFerramenta() const { return ferramenta; }
    int getAgua() const { return agua; }
    int getNutrientes() const { return nutrientes; }

    // Setters
    void setPlanta(Planta* p) { planta = p; }
    void setFerramenta(Ferramenta* f) { ferramenta = f; }
    void setAgua(int a) { agua = a; }
    void setNutrientes(int n) { nutrientes = n; }

    void atualizar(); // chamada a cada instante (planta pode agir)
};

#endif //TP_BLOCO_H
