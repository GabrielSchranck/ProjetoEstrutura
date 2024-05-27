#include <iostream>
#include <locale>
using namespace std;

struct Participante
{
	int ID;
	string Nome;
	int Semestre;
	int AnoIngressao;
	string Curso;
	//1-DSM, 2-SI, 3-GE
};


void MenuDeOpcoes();
void InsereParticipante(Participante *I);

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "Portuguese");
	MenuDeOpcoes();
	
	
	return 0;
}

void MenuDeOpcoes()
{
	int opcao;
	
	do
	{
		cout << "Bem vindo(a) à Turma do Café" << endl;
        cout << "Escolha uma das opções" << endl;
        cout << "1. Inserir Participante" << endl;
        cout << "2. Editar Participante" << endl;
        cout << "3. Carregar Participantes" << endl;
        cout << "4. Gravar Participantes" << endl;
        cout << "5. Cadastrar Contribuição" << endl;
        cout << "6. Gravar Contribuintes" << endl;
        cout << "7. Gravar Contribuintes por Curso" << endl;
        cout << "8. Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;
        
        switch(opcao)
        {
        	case 1:
        		break;
        	case 2:
        		break;
        	case 3:
        		break;
        	case 4:
        		break;
        	case 5:
        		break;
        	case 6:
        		break;
        	case 7:
        		break;
        	case 8:
        		break;
        	default:
                cout << "Opção inválida! Tente novamente." << endl;
		}
	}
	while(opcao != 8);
}

void InsereParticipante(Participante* I)
{
	cout << "Cadastro de Participante" << endl;
	cout << "Informe seu nome: ";
	cin >> I->Nome;
	cout << "Informe seu semestre: ";
	cin >> I->Semestre;
	cout << "Insira o ano que você iniciou na FATEC: ";
	cin >> I->AnoIngressao;
	
	int cursoOpcao;
	cout << "Escolha o seu curso: " << endl;
	cout << "[1] DSM     [2] SI     [3] GE" << endl;
	cout << "Curso: ";
	cin >> cursoOpcao;
	
	switch(cursoOpcao) {
		case 1:
			I->Curso = "DSM";
			break;
		case 2:
			I->Curso = "SI";
			break;
		case 3:
			I->Curso = "GE";
			break;
		default:
			cout << "Número inválido" << endl;
			I->Curso = "Indefinido";
			break;
	}
	
	cout << "Participante cadastrado com sucesso!" << endl;
}
