#include <iostream>
#include <vector>
#include "Estudiante.h"
#include "merge_sort.h"
#include "binary_search.h"
using namespace std;

bool compararEstudiantesNota(const Estudiante& a, const Estudiante& b) {
	return a.getNota() < b.getNota();
}

bool compararEstudiantesCursoSort(const Estudiante& a, const Estudiante& b) {
	return a.getCurso() < b.getCurso();
}

int compararEstudiantesCurso(int a, Estudiante b) {
	return a - b.getCurso();
}

int main() {
	vector<Estudiante> estudiantes;
	int n = 400;
	vector<string>seccionesDemo = { "15611", "17651", "17832", "18321", "16185", "14894" };
	for (int i = 0; i < n; i++) {
		int randomId = i + 1;
		int randomCurso = 1 + rand() % (10 - 1 + 1);
		string randomSeccion = seccionesDemo[0 + rand() % (seccionesDemo.size()-1 - 0 + 1)];
		int randomMes = 1 + rand() % (12 - 1 + 1);
		int randomNota = 0 + rand() % (20 - 0 + 1);
		estudiantes.push_back(Estudiante(randomId, randomCurso, randomSeccion, randomMes, randomNota));
	}
	cout << "Estudiantes generados: " << estudiantes.size() << endl;
	for (auto& es : estudiantes) {
		es.toStr();
	}
	cout << endl;



	cout << "Estudiantes ordenados por nota: " << endl;
	mergeSort(estudiantes, compararEstudiantesNota);
	for (auto& es : estudiantes) {
		es.toStr();
	}
	cout << endl;

	// Reordenar por curso para la busqueda binaria
	mergeSort(estudiantes, compararEstudiantesCursoSort);

	cout << "Ingrese el curso que busca: ";
	int cursoBuscado;
	cin >> cursoBuscado;
	int index = binarySearch(estudiantes, cursoBuscado, compararEstudiantesCurso);
	if (index != -1) {
		cout << "Curso: " << cursoBuscado << " encontrado en la posicion: " << index << "\n";
		cout << (index % 2 == 0 ? "" : "Curso electivo\n");
	}
	else {
		cout << "No encontrado\n";
	}
	
	system("pause>0");
	return 0;
}