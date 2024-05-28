#include <iostream>
#include <locale>
#include <ctime>
using namespace std;

struct Participante
{
	int ID;
	string Nome;
	int Semestre;
	int AnoIngressao;
	string Curso;
	//1-DSM, 2-SI, 3-GE
	bool Professor;
};

void MenuDeOpcoes();
void InsereParticipanteAluno(Participante *I);
void InsereParticipanteProfessor(Participante *I);

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "Portuguese");
	MenuDeOpcoes();
	
	
	return 0;
}

void MenuDeOpcoes()
{
	int opcao;
	Participante participante;  
    Participante* ptrParticipante = &participante;
    int AlunoFuncionario;
	
	
	do
	{
		system("cls");
		cout << endl;
		cout << "Bem vindo(a) à Turma do Café" << endl;
        cout << endl;
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
        cout << endl;
        
        
        switch(opcao)
        {
        	case 1:
        		do
        		{
	        		system("cls");
	        		cout << "Você é aluno ou funcionário?" << endl;
	        		cout << "[1]Aluno" << endl;
	        		cout << "[2]Funcionário" << endl;
	        		cout << "[3]Voltar" << endl;
	        		cout << "Sua resposta: "; 
	        		cin >> AlunoFuncionario;
	        		
        			switch(AlunoFuncionario)
        			{
        				case 1:
        					InsereParticipanteAluno(ptrParticipante);
        				break;
        				case 2:
        				
        				break;
        				case 3:
        				break;
        				default:
        					system("cls");
        					cout << "Você deve escolher uma das opções" << endl;
        					system("pause");
					}
				}
        		while(AlunoFuncionario != 3);
        		
        		
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
        		cout << "Saindo..." << endl;
        		break;
        	default:
                cout << "Opção inválida! Tente novamente." << endl;
                system("pause");
		}
	}
	while(opcao != 8);
}

void InsereParticipanteAluno(Participante* I)
{
	I->Professor = false;
	bool enquanto = true;
	int cursoOpcao;
	
	time_t t = time(0);   
    tm* now = localtime(&t);  
    int currentYear = now->tm_year + 1900;  
	
	cout << "Cadastro de Participante" << endl;
	cout << endl;
	cout << "Informe seu nome: ";
	cin >> I->Nome;
	system("cls");
	do
	{
		enquanto = true;
		cout << "Informe seu semestre: ";
		cin >> I->Semestre;
		
		if(I->Semestre < 1 || I->Semestre > 6)
		{
			system("cls");
			cout << "Você deve informar um semestre entre 1 e 6" << endl;
			enquanto = true;		
		}
		else if(I->Semestre >= 1 || I->Semestre <=6)
		{
			enquanto = false;
			system("cls");
		}
	}
	while(enquanto);

	do
	{
		cout << "Insira o ano que você iniciou na FATEC: ";
		cin >> I->AnoIngressao;
		
		if(I->AnoIngressao < currentYear - 5 || I->AnoIngressao > currentYear)
		{
			system("cls");
			cout << "Ano de iniciação inválido, informe um ano entre " << currentYear - 5 << " e " << currentYear << endl;
			enquanto = true;
		}
		else if(I->AnoIngressao >= currentYear - 5 || I->AnoIngressao <= currentYear)
		{
			enquanto = false;
			system("cls");
		}
	}
	while(enquanto);
	
	do
	{
		
		cout << "Escolha o seu curso: " << endl;
		cout << "[1] DSM     [2] SI     [3] GE" << endl;
		cout << "Curso: ";
		cin >> cursoOpcao;
	
		switch(cursoOpcao) 
		{
			case 1:
				I->Curso = "DSM";
				enquanto = false;
				system("cls");
			break;
			case 2:
				I->Curso = "SI";
				enquanto = false;
				system("cls");
			break;
			case 3:
				I->Curso = "GE";
				enquanto = false;
				system("cls");
			break;
			default:
				system("cls");
				cout << "Número inválido" << endl;
				I->Curso = "Indefinido";
				enquanto = true;
		}
		
	}
	while(enquanto);
	cout << "Participante cadastrado com sucesso!" << endl;
	cout << endl;
	cout <<  I->Nome << " do " << I->Semestre << "° semestre de " << I->Curso << ", Ano de integração à FATEC: " << I->AnoIngressao << endl;
	cout << endl;
	system("pause");
	cout << endl;
}

void InsereParticipanteProfessor(Participante *I)
{
	I->Professor = true;
	bool enquanto = true;
	int cursoOpcao;
	
	time_t t = time(0);   
    tm* now = localtime(&t);  
    int currentYear = now->tm_year + 1900;  
	
	cout << "Cadastro de Participante" << endl;
	cout << endl;
	cout << "Informe seu nome: ";
	cin >> I->Nome;
	system("cls");
}
