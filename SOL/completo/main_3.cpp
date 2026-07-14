#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
using namespace std;

bool compararEnteros(const int& a, const int& b) {
	return a < b;
}

int generarValor() {
	return 10 + rand() % 90;  // 10..99
}

int generarGrado() {
	return rand() % 4;  // 0..3
}

int generarPeso() {
	return 5 + rand() % 46;  // 5..50
}

void mostrarVertice(const int& v, int gSalida, int gLlegada) {
	cout << "\n---\nVertice: " << v;
	cout << "  (Salida: " << gSalida << ", Llegada: " << gLlegada << ")";
}

void mostrarAristaSalida(const int& dest, int peso) {
	cout << " -> " << dest << "(peso:" << peso << ")";
}

void mostrarAristaLlegada(const int& orig, int peso) {
	cout << " <- " << orig << "(peso:" << peso << ")";
}

int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	Grafo<int> grafo(compararEnteros);
	grafo.registroAleatorio(6, generarValor, generarGrado, generarPeso);
	grafo.mostrar(mostrarVertice, mostrarAristaSalida, mostrarAristaLlegada);
	cout << endl;
	system("pause>0");
	return 0;
}