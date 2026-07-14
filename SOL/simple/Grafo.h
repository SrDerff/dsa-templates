#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

template<typename T>
class Grafo {
public:
    struct Arista {
        int destino;  // indice del vertice destino en vertices[]
        int peso;
    };

private:
    std::vector<T> vertices;
    std::vector<std::vector<Arista>> adyacencia;

public:
    Grafo(){}

    // Genera el grafo aleatoriamente.
    //
    // numVertices   : cantidad de vertices a crear
    // generarVertice: funcion que retorna el valor de un vertice
    // generarGrado  : funcion que retorna cuantas aristas tendra un vertice
    // generarPeso   : funcion que retorna el peso de una arista
    //
    // Garantiza que NINGUN vertice exceda el grado devuelto por generarGrado(),
    // verificando tanto el origen como el destino al crear cada arco.
    void registroAleatorio(
        int numVertices,
        T(*generarVertice)(),
        int (*generarGrado)(),
        int (*generarPeso)()
    ) {
        vertices.clear();
        adyacencia.clear();

        for (int i = 0; i < numVertices; i++)
            vertices.push_back(generarVertice());
        adyacencia.resize(numVertices);

        std::vector<int> gradoObjetivo(numVertices);
        for (int i = 0; i < numVertices; i++)
            gradoObjetivo[i] = generarGrado();

        for (int i = 0; i < numVertices; i++) {
            for (int intentos = 0; intentos < gradoObjetivo[i] * 5; intentos++) {
                if ((int)adyacencia[i].size() >= gradoObjetivo[i]) break;
                int dest = rand() % numVertices;
                if (dest == i) continue;
                if ((int)adyacencia[dest].size() >= gradoObjetivo[dest]) continue;

                bool existe = false;
                for (const auto& a : adyacencia[i])
                    if (a.destino == dest) { existe = true; break; }
                if (existe) continue;

                int peso = generarPeso();
                adyacencia[i].push_back({ dest, peso });
                adyacencia[dest].push_back({ i, peso });
            }
        }
    }

    // Muestra el grafo no dirigido: valor, salida y llegada de cada vertice
    void mostrar(
        void (*procesarVertice)(const T&, int gradoSalida, int gradoLlegada),
        void (*procesarAristaSalida)(const T&, int peso),
        void (*procesarAristaLlegada)(const T&, int peso)
    ) const {
        for (int i = 0; i < (int)vertices.size(); i++) {
            int gradoLlegada = 0;
            for (int j = 0; j < (int)vertices.size(); j++) {
                if (j == i) continue;
                for (const auto& a : adyacencia[j])
                    if (a.destino == i) gradoLlegada++;
            }

            procesarVertice(vertices[i], (int)adyacencia[i].size(), gradoLlegada);

            if (!adyacencia[i].empty()) {
                std::cout << "\n  Salida:";
                for (const auto& a : adyacencia[i])
                    procesarAristaSalida(vertices[a.destino], a.peso);
            }

            if (gradoLlegada > 0) {
                std::cout << "\n  Llegada:";
                for (int j = 0; j < (int)vertices.size(); j++) {
                    if (j == i) continue;
                    for (const auto& a : adyacencia[j])
                        if (a.destino == i)
                            procesarAristaLlegada(vertices[j], a.peso);
                }
            }
        }
    }
};