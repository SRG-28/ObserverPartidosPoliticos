#pragma once
#include<iostream>
#include<sstream>
#include<Windows.h>
using namespace std;
class Partido {
protected:
	int valorPLN;
	int valorPUSC;
	int valorPAC;
public:
	Partido();
	virtual~Partido();
	virtual void update(int, int, int) = 0;  
	virtual string toString() = 0; 
	virtual void graficando() = 0; 
	virtual int getValor1();
	virtual int getValor2();
	virtual int getValor3();

};

Partido::Partido()
{
	cout << "Creando Partido Politico" << endl;
	valorPLN = 0;
	valorPUSC = 0;
	valorPAC = 0;
}

Partido::~Partido()
{
	cout << "Eliminando Partido Politico" << endl;
}

int Partido::getValor1() {
	return valorPLN;
}

int Partido::getValor2() {
	return valorPUSC;
}

int Partido::getValor3() {
	return valorPAC;
}

//Fin de la Interfaz

class PartidoPLN : public Partido {//observador particular o privado
private:
	string nombre;
	//extras del partido
public:
	PartidoPLN() :Partido() {
		nombre = "Partido Liberación Nacional";
	}
	virtual ~PartidoPLN() {

	}
	//el tribu envia info a los paramentros y se actualizan a cada atributo 
	virtual void update(int a, int b, int c) {
		this->valorPLN += a;//sumando todos los votos de PLN en un solo atributo
		this->valorPUSC += b;
		this->valorPAC += c;
	}

	virtual string toString() {
		stringstream a;
		a << "---------PLN---------" << endl
			<< "---Partido Liberacion Nacional---" << endl
			<< "Voto del PLN No1.." << valorPLN << endl
			<< "Voto del PUSC No2.." << valorPUSC << endl
			<< "Voto del PAC No1.." << valorPAC << endl;
		return a.str();
	}

	void graficando() {

	}
};

class PartidoPUSC : public Partido {//observador particular o privado
private:
	string nombre;
	//extras del partido
public:
	PartidoPUSC() :Partido() {
		nombre = "Partido Liberación Nacional";
	}
	virtual ~PartidoPUSC() {

	}
	//el tribu envia info a los paramentros y se actualizan a cada atributo 
	virtual void update(int a, int b, int c) {
		this->valorPLN += a;//sumando todos los votos de PLN en un solo atributo
		this->valorPUSC += b;
		this->valorPAC += c;
	}

	virtual string toString() { return 0; }
	/*virtual string toString() {
		stringstream a;
		a << "---------PUSC---------" << endl
			<< "---Partido Unidad Social Cristiana---" << endl
			<< "Voto del PLN No1.." << valorPLN << endl
			<< "Voto del PUSC No2.." << valorPUSC << endl
			<< "Voto del PAC No1.." << valorPAC << endl;
		return a.str();
	}*/

	void graficando() {
		cout << "---Partido Unidad Social Cristiana---" << endl;
		cout << "1-PLN";
		for (int i = 0; i < valorPLN / 100; i++)

			cout << "*"; cout << endl;
		cout << endl;
		cout << "2-PUSC";
		for (int i = 0; i < valorPUSC / 100; i++)

			cout << "*"; cout << endl;

		cout << "3-PAC";
		for (int i = 0; i < valorPAC / 100; i++)

			cout << "*"; cout << endl;

	}
};


////SUBJECT

class Tribunal {
	//clase observada por los observer
private:
	int mesaNum;
	int valor1;
	int valor2;
	int valor3;

	//subjet siempre tiene contenedor, puede ser por aparte por orden
	Partido** vec;
	int can;
	int tam;

public:
	Tribunal();
	virtual ~Tribunal();
	void attach(Partido* par);
	void setValores(int valorPLN, int valorPUSC, int valorPac);

	//dentro de set siempre se tienen que llamar a notify
	void notify();

	//estos de arriba son los infaltables


	//este resto ayuda en el maquillaje del TSE...
	void conteoVotosMesa();//gente cuenta votos y los mete en valor1,  2 o 3
	//llama a set valores para actualizarlos
	//llama a notify 

	void infoMesa(); //es mera impresión de la info de la mesa
	void solicitarNuevaMesa();

};


Tribunal::Tribunal() {
	mesaNum = 0;
	valor1 = 0;
	valor2 = 0;
	valor3 = 0;

	vec = new Partido * [5];
	tam = 5;
	can = 0;
}

Tribunal::~Tribunal() {
	delete vec;
}


void Tribunal::attach(Partido* par) {
	vec[can++] = par;
}

void Tribunal::setValores(int vpln, int vpusc, int vpac) {
	valor1 = vpln;
	valor2 = vpusc;
	valor3 = vpac;
	notify();
}

void Tribunal::notify() {//actualiza a todos los suscriptores
	for (int i = 0; i < can; i++)
	{
		vec[i]->update(valor1, valor2, valor3);
	}
}

void Tribunal::conteoVotosMesa() {
	int v1, v2, v3;
	v1 = 1 + rand() % (101 - 1);//num aleatorio entre 1-100
	v2 = 1 + rand() % (101 - 1);
	v3 = 1 + rand() % (101 - 1);
	mesaNum = 1 + rand() % (10001 - 1);//num aleatorio entre 1-10000
	this->setValores(v1, v2, v3);
}

void Tribunal::infoMesa() {
	cout << "No. mesa" << endl;
	cout << "votos PLN" << valor1 << endl;
	cout << "votos PUSC" << valor2 << endl;
	cout << "votos PAC" << valor3 << endl;
}
void Tribunal::solicitarNuevaMesa() {
	this->conteoVotosMesa();
}

int main() {
	cout << "Participacion Popular" << endl;
	cout << "construyendo partidos" << endl;

	Partido* obv1 = new PartidoPLN();
	Partido* obv2 = new PartidoPUSC();

	cout << "Crear Tribunal Supremo De Elecciones" << endl;
	Tribunal objTribunal;
	cout << "Suscribirse" << endl;
	objTribunal.attach(obv1);
	objTribunal.attach(obv2);
	//objTribunal.attach(obv3);
	cout << "...................................................." << endl;
	int x = 0;
	system("pause");

	while (x < 100) {
		system("cls");
		cout << ".......Informacion Tribunal Supremo de Elecciones......" << endl;
		objTribunal.solicitarNuevaMesa();
		objTribunal.infoMesa();
		cout << "........Partidos Totalizados.........." << endl;
		cout << endl << endl;
		cout << "..............PLN......................." << endl;
		cout << obv1->toString();
		cout << endl << endl;
		cout << "..............PUSC......................." << endl;
		obv2->graficando();
		Sleep(1000);

	}
	system("pause");
	return 0;
}