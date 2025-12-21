#ifndef TP_PLANTA_H
#define TP_PLANTA_H

#include <string>
#include <iostream>

class Planta {
protected:
    std::string nome;
    char simbolo;
    int agua;
    int nutrientes;
    bool viva = true;

public:
    Planta(std::string nome, char simbolo, int agua, int nutrientes)
        : nome(std::move(nome)), simbolo(simbolo), agua(agua), nutrientes(nutrientes) {}

    virtual ~Planta() = default;

    // --- Métodos virtuais previstos ---
    virtual void atualizar() = 0;        // TODO: comportamento em cada instante
    virtual void mostrarInfo() const;    // imprime informação sobre a planta
    virtual char getSimbolo() const { return simbolo; }

    // --- Métodos auxiliares ---
    bool estaViva() const { return viva; }
    std::string getNome() const { return nome; }
    int getAgua() const { return agua; }
    int getNutrientes() const { return nutrientes; }

    // --- Planeamento de funções futuras ---
    virtual void morrer();               // TODO: comportamento ao morrer
    virtual void multiplicar();          // TODO: criar nova planta vizinha
};

// === Classes derivadas ===

class Cacto : public Planta {
public:
    Cacto() : Planta("Cacto", 'c', 0, 0) {}
    void atualizar() override { /* TODO: comportamento do cacto */ }
    void mostrarInfo() const override {
        std::cout << "[Cacto] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

class Roseira : public Planta {
public:
    Roseira() : Planta("Roseira", 'r', 25, 25) {}
    void atualizar() override { /* TODO: comportamento da roseira */ }
    void mostrarInfo() const override {
        std::cout << "[Roseira] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

class ErvaDaninha : public Planta {
public:
    ErvaDaninha() : Planta("Erva Daninha", 'e', 5, 5) {}
    void atualizar() override { /* TODO: comportamento da erva daninha */ }
    void mostrarInfo() const override {
        std::cout << "[Erva Daninha] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

class Exotica : public Planta {
public:
    Exotica() : Planta("Exótica", 'x', 10, 10) {}
    void atualizar() override { /* TODO: comportamento da planta exótica */ }
    void mostrarInfo() const override {
        std::cout << "[Exótica] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

#endif //TP_PLANTA_H
