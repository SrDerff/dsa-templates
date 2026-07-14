#pragma once
#include <iostream>
#include <vector>
#include <queue>
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
        adyacencia[origen].push_back({ destino, peso });
        adyacencia[destino].push_back({ origen, peso });
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
    // generarVertice: funcion que retorna el valor de un vertice
    // generarGrado  : funcion que retorna cuantas aristas tendra un vertice (0..3)
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

    int cantidadVertices() const { return vertices.size(); }

    const T& obtenerVertice(int idx) const { return vertices[idx]; }

    const std::vector<Arista>& obtenerAdyacentes(int idx) const {
        return adyacencia[idx];
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