#include <iostream>
#include <conio.h>
#include <string>
#include "MiArbol.h"
using namespace std;

bool comparar(const int& a, const int& b) {
	return a < b;
}

void procesar(const int& a) {
	cout << a << " ";
}

int extraer(const int& a) {
	return a;
}

int menu() {
	cout << "1. Insertar elemento\n";
	cout << "2. Promedio arbol: \n";
	cout << "3. Mostrar preOrden: \n";
	cout << "4. Sumar digitos mayor: \n";
	cout << "5. Salir\n";
	cout << "\nElegir opcion: \n";
	int op;
	cin >> op;
	return op;
}

int main() {
	MiArbol<int> arbol(comparar, procesar);
	int op = -1;
	while (op != 6) {
		op = menu();
		switch (op) {
		case 1: {
			int elem;
			cout << "Ingrese el elemento: ";
			cin >> elem;
			arbol.insertar(elem);
			cout << "Insertado correctamente" << endl;
			break;
		}
		case 2: {
			int inicio, final;
			cout << "Ingrese el inicio: ";
			cin >> inicio;
			cout << "Ingrese el final: ";
			cin >> final;
			float promedio = arbol.promedio_rango(inicio, final, extraer);
			cout << "Promedio: " << promedio << "\n";
			break;
		}
		case 3: {
			arbol.preOrden();
			cout << endl;
			break;
		}
		case 4: {
			int* maxNum = arbol.maximo();
			if (maxNum == nullptr) {
				cout << "El arbol esta vacio." << endl;
				break;
			}
			string strNum = to_string(*maxNum);
			int sum = 0;
			for (auto& ch : strNum) {
				sum += ch - '0';
			}
			cout << "Suma de digitos del mayor: " << sum<<"\n";
			break;
		}
		}
		if (op == 5) break;
		cout << "Ingrese cualquier tecla para continuar..." << endl;
		getch();
		system("cls");
	}
	return 0;
}