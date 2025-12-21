cmake_minimum_required(VERSION 4.0)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP main.cpp
        Bloco.h
        Bloco.cpp
        Jardim.h
        Jardim.cpp
        Simulador.cpp
        Simulador.h
        Comando.h
        Comando.cpp
        Planta.h
        Ferramenta.h)
