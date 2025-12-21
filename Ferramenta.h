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
    virtual void usar() = 0;          // TODO: ação sobre o bloco
    virtual void mostrarInfo() const; // imprime informação da ferramenta

    // --- Getters ---
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    char getSimbolo() const { return simbolo; }
};

// === Classes derivadas ===

class Regador : public Ferramenta {
    int capacidade = 200; // unidades de água
public:
    Regador() : Ferramenta("Regador", 'g') {}
    void usar() override { /* TODO: aumentar água no solo */ }
    void mostrarInfo() const override {
        std::cout << "[Regador #" << id << "] capacidade=" << capacidade << "\n";
    }
};

class Adubo : public Ferramenta {
    int quantidade = 100; // unidades de nutrientes
public:
    Adubo() : Ferramenta("Adubo", 'a') {}
    void usar() override { /* TODO: aumentar nutrientes no solo */ }
    void mostrarInfo() const override {
        std::cout << "[Adubo #" << id << "] quantidade=" << quantidade << "\n";
    }
};

class Tesoura : public Ferramenta {
public:
    Tesoura() : Ferramenta("Tesoura", 't') {}
    void usar() override { /* TODO: eliminar plantas feias */ }
    void mostrarInfo() const override {
        std::cout << "[Tesoura #" << id << "] ferramenta permanente\n";
    }
};

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ() : Ferramenta("FerramentaZ", 'z') {}
    void usar() override { /* TODO: comportamento personalizado */ }
    void mostrarInfo() const override {
        std::cout << "[FerramentaZ #" << id << "] efeito especial\n";
    }
};

#endif //TP_FERRAMENTA_H
