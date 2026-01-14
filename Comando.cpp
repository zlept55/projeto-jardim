#include "Comando.h"

Comando::Comando(const std::string& linha) {
    std::istringstream iss(linha); // cria um “stream” da linha
    iss >> nome;                  // lê a primeira palavra (nome do comando)

    std::string temp;
    while (iss >> temp)
        args.push_back(temp);    // lê o resto (os parâmetros)
}

bool Comando::validar() {
    if (nome.empty()) {
        std::cout << "Comando vazio.\n";
        return false;
    }

    // Comandos válidos nesta fase
    std::vector<std::string> comandosValidos = {
        "jardim", "avanca", "planta", "colhe", "fim",
        "compra", "entra", "sai", "c", "b", "e", "d", "usa"  // novo comando para comprar ferramentas

        "compra"   // novo comando para comprar ferramentas
    };

    bool valido = false;
    for (auto& c : comandosValidos) {
        if (nome == c) {
            valido = true;
            break;
        }
    }

    if (!valido) {
        std::cout << "Comando desconhecido: " << nome << "\n";
        return false;
    }

    return true; // comando válido
}
