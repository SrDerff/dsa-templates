#pragma once
#include <string>
using namespace std;

class Estudiante {
private:
	int idEstudiante;
	int curso;
	string seccion;
	int mes;
	int nota;
public:
	Estudiante(int id, int curs, string sec, int m, int notaVal) {
		idEstudiante = id;
		curso = curs;
		seccion = sec;
		this->mes = m;
		nota = notaVal;
	}
	~Estudiante(){}
	int getIdEstudiante() const { return idEstudiante; }
	int getCurso() const { return curso; }
	string getSeccion() const { return seccion; }
	int getMes() const { return mes; }
	int getNota() const { return nota; }
	void toStr() const {
		cout << "ID: "<< idEstudiante << ", Curso: " << curso << ", Seccion: " << seccion << ", Mes: " << mes << ", Nota: " << nota << endl;
	}
};