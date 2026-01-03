#include "Ferramenta.h"

void Ferramenta::mostrarInfo() const {
    std::cout << "[" << nome << " #" << id
              << "] simbolo='" << simbolo << "'\n";
}