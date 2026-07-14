#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

/*
#include "FIJAS/graph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(nullptr));

    Grafo<char> g([](const char& a, const char& b) { return a < b; });

    // registroAleatorio: 6 vertices, valores A-F, grado 0-3, peso 5-50
    g.registroAleatorio(6,
        [](int i) -> char { return 'A' + i; },
        [](int) -> int { return rand() % 4; },
        [](int, int) -> int { return 5 + rand() % 46; }
    );

    // Mostrar con indices (ej: "A[0] → B[1] peso=23")
    g.mostrar(
        [](const char& v, int) {
            std::cout << v << " conecta a: ";
        },
        [](const char& dest, int peso) {
            std::cout << dest << "(peso:" << peso << ") ";
        }
    );

    // BFS desde el indice 0 (vertice A)
    std::cout << "\nBFS: ";
    g.BFS(0, [](const char& v) { std::cout << v << " "; });
}
*/

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
    bool (*comp)(const T&, const T&);

    int _buscarIndice(const T& v) const {
        for (int i = 0; i < (int)vertices.size(); i++)
            if (!comp(vertices[i], v) && !comp(v, vertices[i]))
                return i;
        return -1;
    }

    void _DFS(int u, std::vector<bool>& visitado, void (*procesar)(const T&)) const {
        visitado[u] = true;
        procesar(vertices[u]);
        for (const auto& arista : adyacencia[u])
            if (!visitado[arista.destino])
                _DFS(arista.destino, visitado, procesar);
    }

public:
    Grafo(bool (*c)(const T&, const T&)) : comp(c) {}

    // Agrega un vertice y retorna su indice
    int agregarVertice(const T& v) {
        int idx = _buscarIndice(v);
        if (idx != -1) return idx;  // ya existe
        idx = vertices.size();
        vertices.push_back(v);
        adyacencia.push_back({});
        return idx;
    }

    // Agrega arista NO dirigida entre origen y destino con un peso
    // Retorna false si los indices son invalidos
    bool agregarArista(int origen, int destino, int peso) {
        if (origen < 0 || origen >= (int)vertices.size()) return false;
        if (destino < 0 || destino >= (int)vertices.size()) return false;
        adyacencia[origen].push_back({destino, peso});
        adyacencia[destino].push_back({origen, peso});  // no dirigido
        return true;
    }

    // Busca un vertice por su valor, retorna indice o -1
    int buscarVertice(const T& v) const {
        return _buscarIndice(v);
    }

    // Elimina arista entre origen y destino (en ambos sentidos)
    // Retorna false si no se encuentra
    bool eliminarArista(int origen, int destino) {
        if (origen < 0 || origen >= (int)vertices.size()) return false;
        if (destino < 0 || destino >= (int)vertices.size()) return false;
        auto it = std::remove_if(adyacencia[origen].begin(), adyacencia[origen].end(),
                                 [destino](const Arista& a) { return a.destino == destino; });
        adyacencia[origen].erase(it, adyacencia[origen].end());
        it = std::remove_if(adyacencia[destino].begin(), adyacencia[destino].end(),
                            [origen](const Arista& a) { return a.destino == origen; });
        adyacencia[destino].erase(it, adyacencia[destino].end());
        return true;
    }

    // Elimina un vertice y todas sus aristas
    // Retorna false si no existe
    bool eliminarVertice(const T& v) {
        int idx = _buscarIndice(v);
        if (idx == -1) return false;
        vertices.erase(vertices.begin() + idx);
        adyacencia.erase(adyacencia.begin() + idx);
        for (auto& lista : adyacencia)
            for (auto it = lista.begin(); it != lista.end(); )
                if (it->destino == idx) it = lista.erase(it);
                else if (it->destino > idx) { it->destino--; it++; }
                else it++;
        return true;
    }

    // DFS desde un vertice (por indice)
    void DFS(int inicio, void (*procesar)(const T&)) const {
        if (inicio < 0 || inicio >= (int)vertices.size()) return;
        std::vector<bool> visitado(vertices.size(), false);
        _DFS(inicio, visitado, procesar);
    }

    // BFS desde un vertice (por indice)
    void BFS(int inicio, void (*procesar)(const T&)) const {
        if (inicio < 0 || inicio >= (int)vertices.size()) return;
        std::vector<bool> visitado(vertices.size(), false);
        std::queue<int> cola;
        visitado[inicio] = true;
        cola.push(inicio);
        while (!cola.empty()) {
            int u = cola.front(); cola.pop();
            procesar(vertices[u]);
            for (const auto& arista : adyacencia[u])
                if (!visitado[arista.destino]) {
                    visitado[arista.destino] = true;
                    cola.push(arista.destino);
                }
        }
    }

    // Genera el grafo aleatoriamente.
    //
    // numVertices   : cantidad de vertices a crear
    // generarVertice: funcion que recibe el indice i y retorna el valor del vertice i
    // generarGrado  : funcion que recibe el indice i y retorna cuantas aristas tendra el vertice i
    // generarPeso   : funcion que recibe (origen, destino) y retorna el peso de la arista
    //
    // Los arcos se crean hacia vertices aleatorios (distintos de si mismo)
    // y evitando duplicados.
    void registroAleatorio(
        int numVertices,
        T  (*generarVertice)(int),
        int (*generarGrado)(int),
        int (*generarPeso)(int, int)
    ) {
        vertices.clear();
        adyacencia.clear();

        for (int i = 0; i < numVertices; i++)
            vertices.push_back(generarVertice(i));
        adyacencia.resize(numVertices);

        for (int i = 0; i < numVertices; i++) {
            int grado = generarGrado(i);
            for (int intentos = 0; intentos < grado * 3; intentos++) {
                if ((int)adyacencia[i].size() >= grado) break;
                int dest = rand() % numVertices;
                if (dest == i) continue;

                bool existe = false;
                for (const auto& a : adyacencia[i])
                    if (a.destino == dest) { existe = true; break; }
                if (existe) continue;

                int peso = generarPeso(i, dest);
                adyacencia[i].push_back({dest, peso});
                adyacencia[dest].push_back({i, peso});
            }
        }
    }

    int cantidadVertices() const { return vertices.size(); }

    const T& obtenerVertice(int idx) const { return vertices[idx]; }

    const std::vector<Arista>& obtenerAdyacentes(int idx) const {
        return adyacencia[idx];
    }

    // Muestra el grafo: para cada vertice, imprime sus aristas
    void mostrar(void (*procesarVertice)(const T&, int),
                 void (*procesarArista)(const T&, int)) const {
        for (int i = 0; i < (int)vertices.size(); i++) {
            procesarVertice(vertices[i], -1);
            for (const auto& a : adyacencia[i]) {
                if (a.destino > i)  // cada arista solo una vez
                    procesarArista(vertices[a.destino], a.peso);
            }
        }
    }
};
