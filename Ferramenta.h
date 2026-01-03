#ifndef TP_FERRAMENTA_H
#define TP_FERRAMENTA_H

#include <string>
#include <iostream>

class Ferramenta {
protected:
    std::string nome;
    char simbolo;
    int id;
    inline static int contador = 1; // número de série único

public:
    Ferramenta(std::string nome, char simbolo)
        : nome(std::move(nome)), simbolo(simbolo), id(contador++) {}

    virtual ~Ferramenta() = default;

    // --- Métodos virtuais previstos ---
    // usar(): a ação concreta sobre o solo/planta é tratada fora desta classe.
    virtual void usar() = 0;

    // Informação genérica; as derivadas podem sobrepor.
    virtual void mostrarInfo() const;

    // --- Getters ---
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    char getSimbolo() const { return simbolo; }
};

// === Classes derivadas ===

class Regador : public Ferramenta {
    int capacidade; // unidades de água
public:
    Regador()
        : Ferramenta("Regador", 'g'),
          capacidade(200) {} // 200 unidades como no enunciado [file:1]

    void usar() override {
        // Cada uso consome 10 unidades de água, se houver.
        if (capacidade >= 10)
            capacidade -= 10;
        else
            capacidade = 0;
        // O efeito no solo (aumentar água) é feito pelo código que chama usar().
    }

    void mostrarInfo() const override {
        std::cout << "[Regador #" << id << "] capacidade=" << capacidade << "\n";
    }

    int getCapacidade() const { return capacidade; }
};

class Adubo : public Ferramenta {
    int quantidade; // unidades de nutrientes
public:
    Adubo()
        : Ferramenta("Adubo", 'a'),
          quantidade(100) {} // 100 unidades como no enunciado [file:1]

    void usar() override {
        // Cada uso consome 10 unidades de nutrientes, se houver.
        if (quantidade >= 10)
            quantidade -= 10;
        else
            quantidade = 0;
        // O efeito no solo (aumentar nutrientes) é feito pelo código que chama usar().
    }

    void mostrarInfo() const override {
        std::cout << "[Adubo #" << id << "] quantidade=" << quantidade << "\n";
    }

    int getQuantidade() const { return quantidade; }
};

class Tesoura : public Ferramenta {
public:
    Tesoura()
        : Ferramenta("Tesoura", 't') {} // símbolo t [file:1]

    void usar() override {
        // Não se desgasta; efeito (eliminar plantas feias) é tratado fora.
    }

    void mostrarInfo() const override {
        std::cout << "[Tesoura #" << id << "] ferramenta permanente\n";
    }
};

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ()
        : Ferramenta("FerramentaZ", 'z') {} // símbolo z [file:1]

    void usar() override {
        // Comportamento especial definido pelo grupo, aplicado fora desta classe.
    }

    void mostrarInfo() const override {
        std::cout << "[FerramentaZ #" << id << "] efeito especial\n";
    }
};

#endif // TP_FERRAMENTA_H