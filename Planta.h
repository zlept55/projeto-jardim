#ifndef TP_PLANTA_H
#define TP_PLANTA_H

#include <string>
#include <iostream>
#include "Bloco.h"
#include "Settings.h"
#include "Settings.h"


class Planta {
protected:
    std::string nome;
    char simbolo;
    int agua;
    int nutrientes;

    bool viva = true;
    bool pedirMult = false;
    bool pedirMorte = false;

public:
    Planta(std::string nome, char simbolo, int agua, int nutrientes)
        : nome(std::move(nome)), simbolo(simbolo), agua(agua), nutrientes(nutrientes) {}

    virtual ~Planta() = default;

    virtual Planta* clonar() const = 0;
    virtual void atualizar(Bloco& b) = 0;
    virtual void mostrarInfo() const;
    virtual char getSimbolo() const { return simbolo; }


    bool querMult() const { return pedirMult; }
    void resetMult() {pedirMult = false;}
    bool estaViva() const { return viva; }

    int getAgua() const { return agua; }
    int getNutrientes() const { return nutrientes; }

    void setAgua(int a) {agua = a;}
    void setNutrientes(int n) {nutrientes = n;}

    void limparPedidos();

    virtual void morrer(Bloco& b) = 0;
};

// === Classes derivadas ===

class Cacto : public Planta {
    int instantesAguaAlta = 0;
    int instantesNutrientesBaixo = 0;
public:
    Cacto() : Planta("Cacto", 'c', 0, 0) {}
    void atualizar(Bloco& b) override;
    void morrer(Bloco& b);
    Planta* clonar() const override {return new Cacto(*this);}
    void mostrarInfo() const override {
        std::cout << "[Cacto] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

class Roseira : public Planta {
private:
    bool pedirVerifEspaco = false;
public:
    Roseira() : Planta("Roseira", 'r', Settings::Roseira::agua_inicial, Settings::Roseira::nutrientes_inicial) {}
    void atualizar(Bloco& b) override;
    void morrer(Bloco& b);
    Planta* clonar() const override;
    void mostrarInfo() const override {
        std::cout << "[Roseira] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

class ErvaDaninha : public Planta {
private:
    int instantesVivos = 0;
    int instantesDesdeMult = 0;
public:
    ErvaDaninha() : Planta("Erva Daninha", 'e', Settings::ErvaDaninha::agua_inicial, Settings::ErvaDaninha::nutrientes_inicial) {}
    void atualizar(Bloco& b) override;
    Planta* clonar() const override;
    void morrer(Bloco& b);
    void mostrarInfo() const override {
        std::cout << "[Erva Daninha] água=" << agua << ", nutrientes=" << nutrientes << "\n";
    }
};

class Exotica : public Planta {
private:
    int instantesSemComer = 0;

public:
    Exotica()
        : Planta("Carnivora", 'x',
                 Settings::Exotica::agua_inicial,
                 Settings::Exotica::nutrientes_inicial) {}

    void atualizar(Bloco& b) override;
    Planta* clonar() const override { return new Exotica(*this); }
    void morrer(Bloco& b) override;

    void mostrarInfo() const override {
        std::cout << "[Carnivora] agua=" << agua
                  << ", nutrientes=" << nutrientes
                  << ", instantesSemComer=" << instantesSemComer << "\n";
    }
};



#endif //TP_PLANTA_H
