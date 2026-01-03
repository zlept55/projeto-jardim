#include "Planta.h"
#include "Bloco.h"
#include "Settings.h"

void Cacto::atualizar(Bloco& b) {
    if (!viva)
        return;

    int aguaSolo = b.getAgua();
    int nutrientesSolo = b.getNutrientes();

    int absorcaoAgua = aguaSolo * Settings::Cacto::absorcao_agua_percentagem / 100;
    int absorcaoNutrientes = Settings::Cacto::absorcao_nutrientes;

    absorcaoAgua = std::min(absorcaoAgua, aguaSolo);
    absorcaoNutrientes = std::min(absorcaoNutrientes, nutrientesSolo);

    agua += absorcaoAgua;
    nutrientes += absorcaoNutrientes;

    b.setAgua(aguaSolo - absorcaoAgua);
    b.setNutrientes(nutrientesSolo - absorcaoNutrientes);

    if (b.getAgua() > Settings::Cacto::morre_agua_solo_maior)
        instantesAguaAlta++;
    else
        instantesAguaAlta = 0;

    if (b.getNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor)
        instantesNutrientesBaixo++;
    else
        instantesNutrientesBaixo = 0;

    if (instantesAguaAlta >= Settings::Cacto::morre_agua_solo_instantes ||
        instantesNutrientesBaixo >= Settings::Cacto::morre_nutrientes_solo_instantes){
        morrer(b);
        return;
    }
    if (nutrientes > Settings::Cacto::multiplica_nutrientes_maior &&
        agua > Settings::Cacto::multiplica_agua_maior) {

        pedirMult = true;

        nutrientes /= 2;
        agua /= 2;
    }
}

void Cacto::morrer(Bloco& b) {
    viva = false;

    b.setNutrientes(b.getNutrientes() + nutrientes);

    nutrientes = 0;
    agua = 0;
}
void Roseira::atualizar(Bloco& b) {
    if (!viva)
        return;

    agua -= Settings::Roseira::perda_agua;
    nutrientes -= Settings::Roseira::perda_nutrientes;

    int aguaSolo = b.getAgua();
    int nutrientesSolo = b.getNutrientes();

    int absorcaoAgua = std::min(Settings::Roseira::absorcao_agua,aguaSolo);
    int absorcaoNutrientes = std::min(Settings::Roseira::absorcao_nutrientes, nutrientesSolo);

    agua += absorcaoAgua;
    nutrientes += absorcaoNutrientes;

    b.setAgua(aguaSolo - absorcaoAgua);
    b.setNutrientes(nutrientesSolo - absorcaoNutrientes);

    if (agua < Settings::Roseira::morre_agua_menor ||
        nutrientes < Settings::Roseira::morre_nutrientes_menor ||
        nutrientes > Settings::Roseira::morre_nutrientes_maior) {
        morrer(b);
        return;
    }
    pedirVerifEspaco = true;
    if (nutrientes > Settings::Roseira::multiplica_nutrientes_maior) {
        pedirMult = true;
    }

}
Planta* Roseira::clonar() const {
    Roseira* r = new Roseira();
    r->agua = agua / 2;
    r->nutrientes = Settings::Roseira::nutrientes_inicial;
    return r;
}

void Roseira::morrer(Bloco& b) {
    viva = false;

    b.setAgua(b.getAgua() + agua / 2);
    b.setNutrientes(b.getNutrientes() + nutrientes / 2);

    agua = 0;
    nutrientes = 0;
}

void Roseira::aposMultiplicacao() {
    agua /= 2;          // metade da água fica na mãe
    nutrientes = 100;   // regra do enunciado
}

void ErvaDaninha::atualizar(Bloco& b) {
    if (!viva)
        return;

    instantesVivos++;
    if (instantesVivos >= Settings::ErvaDaninha::morre_instantes) {
        morrer(b);
        return;
    }

    int aguaSolo = b.getAgua();
    int nutrientesSolo = b.getNutrientes();

    int absorcaoAgua = std::min(Settings::ErvaDaninha::absorcao_agua,aguaSolo);
    int absorcaoNutrientes = std::min(Settings::ErvaDaninha::absorcao_nutrientes, nutrientesSolo);

    agua += absorcaoAgua;
    nutrientes += absorcaoNutrientes;

    b.setAgua(aguaSolo - absorcaoAgua);
    b.setNutrientes(nutrientesSolo - absorcaoNutrientes);

    if (nutrientesSolo > Settings::ErvaDaninha::multiplica_nutrientes_maior) {
        instantesDesdeMult++;

        if (instantesDesdeMult >= Settings::ErvaDaninha::multiplica_instantes) {
            pedirMult = true;
            instantesDesdeMult = 0;
        }
    } else
        instantesDesdeMult = 0;
}

void ErvaDaninha::morrer(Bloco& b) {
    viva = false;

    agua = 0;
    nutrientes = 0;
}

/*void Planta::multiplicar() {

} */

void Carnivora::atualizar(Bloco& b) {
    if (!viva)
        return;

    agua -= Settings::Carnivora::perda_agua;
    nutrientes -= Settings::Carnivora::perda_nutrientes;

    int aguaSolo = b.getAgua();
    int nutrientesSolo = b.getNutrientes();

    int absorcaoAgua = std::min(Settings::Carnivora::absorcao_agua,aguaSolo);
    int absorcaoNutrientes = std::min(Settings::Carnivora::absorcao_nutrientes,nutrientesSolo);

    agua += absorcaoAgua;
    nutrientes += absorcaoNutrientes;

    b.setAgua(aguaSolo - absorcaoAgua);
    b.setNutrientes(nutrientesSolo - absorcaoNutrientes);

    if (agua < Settings::Carnivora::morre_agua_menor ||
        nutrientes < Settings::Carnivora::morre_nutrientes_menor ||
        nutrientes > Settings::Carnivora::morre_nutrientes_maior) {
        morrer(b);
        return;
        }

    if (nutrientes > Settings::Carnivora::morre_nutrientes_maior)
        pedirMult = true;
}

Planta *Carnivora::clonar() const {
    Carnivora* k = new Carnivora();
    k->agua = Settings::Carnivora::agua_inicial;
    k->nutrientes = Settings::Roseira::nutrientes_inicial;
    return k;
}

void Carnivora::morrer(Bloco &b) {
    viva = false;

    b.setAgua(b.getAgua() + agua);
    b.setNutrientes(b.getNutrientes() + nutrientes);

    agua = 0;
    nutrientes = 0;
}

// Implementações mínimas das funções virtuais puras de Planta
Planta::~Planta() {}  // Destrutor virtual

Planta *Planta::clonar() const {
    return nullptr;  // Não usado diretamente, só nas subclasses
}

void Planta::morrerBloco(Bloco &b) {
    // Implementação padrão (subclasses override)
    viva = false;
}

void Planta::atualizarBloco(Bloco &b) {
    // Comportamento padrão vazio
    if (agua < Settings::Carnivora::morre_agua_menor ||
        nutrientes < Settings::Carnivora::morre_nutrientes_menor ||
        nutrientes > Settings::Carnivora::morre_nutrientes_maior) {
        morrer(b);
        return;
    }

    if (nutrientes > Settings::Carnivora::morre_nutrientes_maior)
        pedirMult = true;
}

Planta *Carnivora::clonar() const {
    Carnivora* k = new Carnivora();
    k->agua = Settings::Carnivora::agua_inicial;
    k->nutrientes = Settings::Roseira::nutrientes_inicial;
    return k;
}

void Carnivora::morrer(Bloco &b) {
    viva = false;

    b.setAgua(b.getAgua() + agua);
    b.setNutrientes(b.getNutrientes() + nutrientes);

    agua = 0;
    nutrientes = 0;
}


void Planta::mostrarInfo() const {
    std::cout << nome
              << " | Água = " << agua
              << " | Nutrientes = " << nutrientes
              << " | Viva = " << (viva ? "Sim" : "Não")
              << "\n";
}
