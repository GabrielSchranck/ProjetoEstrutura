#include <iostream>
#include <locale>
using namespace std;

struct Integrante
{
	int ID;
	string Nome;
	int Semestre;
	int AnoIngressao;
	string Curso;
	//1-DSM, 2-SI, 3-GE
};



void InsereIntegrante();

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "Portuguese");
	
	
	
	return 0;
}

void InsereIntegrante()
	{
		cout << "Cadastro de Integrante" << endl;
		cout << "Informe seu nome: ";
		cin >> 	Nome;
		cout << "Informe seu semestre: ";
		cin >> Semestre;
		cout << "Insira o ano que você iniciu na FATEC: ";
		cin >> AnoIngressao;
		cout << "Escolha o seu curso: " << endl;
		cout << "[1]DSM     [2]SI     [3]GE" << endl;
		cout << "Curso: ";
		cin >> Curso;
		if(Curso == "1")
		{
			Curso = "DSM";
		}
		else if(Curso == "2")
		{
			Curso = "SI";
		}
		else if(Curso == "3")
		{
			Curso = "GE";
		}
		else
		{
			cout << "Número inválido";
		}	
	}
