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
	
	//funcionalidades do sistema
	bool Professor;
	bool Aluno;
	bool funcionario;
	int CursosEscolhidos[3];
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
        cout << "4. Editar Participantes" << endl;
        cout << "5. Cadastrar Contribuição" << endl;
        cout << "6. Editar Contribuintes" << endl;
        cout << "7. Editar Contribuintes por Curso" << endl;
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
        					system("cls");
        					InsereParticipanteAluno(ptrParticipante);
        				break;
        				case 2:
        					system("cls");
        					InsereParticipanteProfessor(ptrParticipante);
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
	bool enquanto = true;
	int cursos;
	int professor;
	int cursoOpcao = 0;
	
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
		cout << "Em que ano você entrou na FATEC: ";
		cin >> I->AnoIngressao;
		
		if(I->AnoIngressao > currentYear)
		{
			system("cls");
			cout << "O ano informado não deve ser maior que o ano atual" << endl;
			enquanto = true;
		}
		else
		{
			system("cls");
			enquanto = false;
		}
	}
	while(enquanto);
	do
	{
		cout << "Você é professor?" << endl;
		cout << "[1]Sim" << endl;
		cout << "[2]Não" << endl;
		cout << "Sua resposta aqui: ";
		cin >> professor;
		
		if(professor == 1)
		{
			I->Aluno = false;
			I->funcionario = false;
			I->Professor = true;
			enquanto = false;
			system("cls");
		}
		else if(professor == 2)
		{
			I->Professor = false;
			I->Aluno = false;
			I->funcionario = true;
			enquanto = false;
			system("cls");
		}
		else
		{
			system("cls");
			cout << "Escolha uma opção válida" << endl;
			enquanto = true;
		}
		
	}
	while(enquanto);
	
	if(I->Professor == true) {
        cout << "Para quantos cursos você dá aula: ";
        cin >> I->Semestre;

        int numCursos = I->Semestre;
        int cursosDisponiveis[3] = {1, 2, 3};
        int cursosEscolhidos[3] = {0, 0, 0};

        do
		{
            system("cls");
            cout << "Escolha os cursos" << endl;
            cout << endl;
            for (int i = 0; i < 3; i++) {
                if (cursosDisponiveis[i] != 0) {
                    switch (cursosDisponiveis[i]) {
                        case 1: cout << "[1] DSM "; break;
                        case 2: cout << "[2] SI "; break;
                        case 3: cout << "[3] GE "; break;
                    }
                }
            }
            cout << endl << "Curso: ";
            cin >> cursoOpcao;

            bool opcaoValida = false;
            for (int i = 0; i < 3; i++) 
			{
                if (cursosDisponiveis[i] == cursoOpcao) 
				{
                    opcaoValida = true;
                    cursosEscolhidos[i] = cursoOpcao;
                    cursosDisponiveis[i] = 0; 
                    numCursos--;
                }
            }

            if (!opcaoValida) 
			{
                cout << "Opção inválida. Tente novamente." << endl;
                system("pause");
            }
        }
        while(numCursos > 0);
		
        
        for (int i = 0; i < 3; i++) 
		{
            I->CursosEscolhidos[i] = cursosEscolhidos[i];
        }

        cout << "Cursos selecionados: ";
        for (int i = 0; i < 3; i++) 
		{
            if (cursosEscolhidos[i] != 0) 
			{
                switch (cursosEscolhidos[i]) 
				{
                    case 1: cout << "DSM "; break;
                    case 2: cout << "SI "; break;
                    case 3: cout << "GE "; break;
                }
            }
        }
        cout << endl;
    }
}
