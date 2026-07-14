#include <iostream>
#include "Grafo.h"
using namespace std;

int generarVertice() {
	return 10 + rand() % (99 - 10 + 1);
}

int generarGrado() {
	return 0 + rand() % (3 - 0 + 1);
}

int generarPesoArco() {
	return 5 + rand() % (50 - 5 + 1);
}

void procesarVertice(const int& valorVertice, int gradoSalida, int gradoLlegada) {
	cout << "\n---\nVertice " << valorVertice << ": ";
	cout << " (Salida: " << gradoSalida << ", Llegada: " << gradoLlegada << ")";
}

void procesarAristaSalida(const int& nodoVinculado, int peso) {
	cout << " -> " << nodoVinculado << "(peso: " << peso << ")";
}

void procesarAristaLlegada(const int& nodoVinculado, int peso) {
	cout << " <- " << nodoVinculado << "(peso: " << peso << ")";
}

int main() {
	srand(time(nullptr));
	Grafo<int>grafo;
	grafo.registroAleatorio(
		6,
		generarVertice,
		generarGrado,
		generarPesoArco
	);
	grafo.mostrar(procesarVertice, procesarAristaSalida, procesarAristaLlegada);
	system("pause>0");
	return 0;
}