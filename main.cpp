#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <locale>
#include <sstream>
#include <string>

using namespace std;

struct Participante {
	
    int ID;
    string Nome;
    int Semestre;
    int AnoIngressao;
    string Curso;
    Participante* prox;
    bool contribuinte = false;
};

struct Contribuinte {
	
	int IDParticipante;
    int Mes;
    int Ano;
    float Valor;
    Contribuinte* prox;
    string Curso;
};

struct ListaParticipantes {
	
    Participante* primeiro;
};

struct ListaContribuintes {
    Contribuinte* primeiro;
};

void AdicionaContribuinte(ListaParticipantes *lista, ListaContribuintes *cont, int id);
int PegaId(ListaParticipantes *lista);
void AbrirArquivoTxt(ListaParticipantes *lista, const string& nomeArquivo);
void AbrirArquivoTxtContribuidores(ListaContribuintes* lista, const string& nomeArquivo);
void initializeQueue(ListaParticipantes *lista);
void initializeQueueCont(ListaContribuintes *lista);
bool isEmpty(ListaParticipantes *lista);
bool isEmptyContribuinte(ListaContribuintes *lista);
void enqueue(ListaParticipantes *lista, Participante* novoParticipante);
void enqueueContribuinte(ListaContribuintes *lista, Contribuinte* novoContribuinte);
void dequeue(ListaParticipantes *lista);
void dequeueContribuinte(ListaParticipantes *lista);
void displayQueue(ListaParticipantes *lista);
void displayContribuinte(ListaContribuintes *lista);
void destroyQueue(ListaParticipantes *lista);
void salvarDados(ListaParticipantes *lista, const string& nomeArquivo);
void salvarDadosContribuidores(ListaContribuintes *lista, const string& nomeArquivo);
void InsereParticipanteAluno(Participante* participante, int nextID);
void editarParticipante(ListaParticipantes *lista, int id);

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    ListaContribuintes listaContribuintes;
    initializeQueueCont(&listaContribuintes);
	
	ListaContribuintes ContribuintesDSM;
	initializeQueueCont(&listaContribuintes);
	
	ListaContribuintes ContribuintesSI;
	initializeQueueCont(&listaContribuintes);
	
	ListaContribuintes ContribuintesGE;
	initializeQueueCont(&listaContribuintes);
	
	ListaParticipantes listaParticipantes;
    initializeQueue(&listaParticipantes);
    
    
    AbrirArquivoTxt(&listaParticipantes, "participantes.txt");
	AbrirArquivoTxtContribuidores(&listaContribuintes, "contribuintes.txt");
	
	
	int idEditar = 0;
    int nextID = PegaId(&listaParticipantes) + 1;
    if(nextID == 0)
    {
    	nextID = 1;
	}
	int opcao5 = 0;
	
    int opcao;
    do {
        system("cls");
        cout << endl;
        cout << "Bem-vindo à Turma do Café" << endl;
        cout << "Escolha uma opção:" << endl;
        cout << "1. Adicionar Participante" << endl;
        cout << "2. Mostrar Participantes" << endl;
        cout << "3. Editar dados" << endl;
        cout << "4. Gravar Participantes" << endl;
        cout << "5. Cadastrar contribuição" << endl;
        cout << "6. Exibir contribuinte" << endl;
        cout << "Opção: ";
        cin >> opcao;
        cout << endl;

        switch(opcao) {
            case 1: {
                system("cls");
                Participante* novoParticipante = new Participante;
                InsereParticipanteAluno(novoParticipante, nextID);
                enqueue(&listaParticipantes, novoParticipante);
                nextID++; 
                break;
            }
            case 2:
            	system("cls");
                displayQueue(&listaParticipantes);
                break;
            case 3:
                system("cls");
                displayQueue(&listaParticipantes);
                cout << "ID do participante para editar: ";
                cin >> idEditar;
                editarParticipante(&listaParticipantes, idEditar);
                break;
            case 4:
                salvarDados(&listaParticipantes, "participantes.txt");
                break;
            case 5:
                system("cls");
                
                do
                {
                	displayQueue(&listaParticipantes);
                	cout << endl;
                	cout << "Para sair, digite [0]" << endl;
                	cout << endl;
                	cout << "Digite o ID do usuário: ";
                	cin >> opcao5;
                	if(opcao5 == 0)
                	{
                		system("cls");
					}
					else if(opcao5 != 0)
					{
						AdicionaContribuinte(&listaParticipantes, &listaContribuintes, opcao5);
					}
					system("cls");
                	salvarDadosContribuidores(&listaContribuintes, "contribuintes.txt");
                	
				}
                while(opcao5 != 0);
                
                
            case 6:
                system("cls");
                displayContribuinte(&listaContribuintes);
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }

        system("pause");
    } while(opcao != 8);

    destroyQueue(&listaParticipantes);
    return 0;
}

void AdicionaContribuinte(ListaParticipantes *listaParticipantes, ListaContribuintes *listaContribuintes, int id) {
    Participante* atual = listaParticipantes->primeiro;
    bool encontrado = false;
    bool anoConfirmado = true;

    while (atual != NULL) {
        if (atual->ID == id) {
            encontrado = true;

            Contribuinte *novoContribuinte = new Contribuinte();
            novoContribuinte->IDParticipante = atual->ID;
            atual->contribuinte = true;

           
            while (anoConfirmado) {
                system("cls");
                cout << "Ano de contribuição: ";
                cin >> novoContribuinte->Ano;

                if (novoContribuinte->Ano < atual->AnoIngressao) {
                    system("cls");
                    cout << "Você deve fornecer um ano maior ou igual ao ano de ingresso!" << endl;
                    system("pause");
                } else {
                    anoConfirmado = false;
                }
            }

            system("cls");
            cout << "Mês de contribuição: ";
            cin >> novoContribuinte->Mes;

            system("cls");
            cout << "Valor da contribuição: ";
            cin >> novoContribuinte->Valor;

            enqueueContribuinte(listaContribuintes, novoContribuinte);

            system("cls");
            cout << "Contribuinte cadastrado com sucesso!" << endl;
            system("pause");
            system("cls");

            
            ofstream arquivoCurso;
            if (atual->Curso == "DSM") {
                novoContribuinte->Curso = "DSM";
                arquivoCurso.open("contribuintes_DSM.txt", ios::out | ios::app);
            } else if (atual->Curso == "SI") {
                novoContribuinte->Curso = "SI";
                arquivoCurso.open("contribuintes_SI.txt", ios::out | ios::app);
            } else if (atual->Curso == "GE") {
                novoContribuinte->Curso = "GE";
                arquivoCurso.open("contribuintes_GE.txt", ios::out | ios::app);
            } else {
                cout << "Curso não reconhecido para salvar o contribuinte." << endl;
                break; 
            }

            if (arquivoCurso.is_open()) {
                arquivoCurso << "ID: " << novoContribuinte->IDParticipante << "\n"
                             << "Curso: " << novoContribuinte->Curso << "\n"
                             << "Ano de contribuição: " << novoContribuinte->Ano << "\n"
                             << "Mês de contribuição: " << novoContribuinte->Mes << "\n"
                             << "Valor: " << novoContribuinte->Valor << "\n\n";
                arquivoCurso.close();
                cout << "Contribuinte salvo no arquivo do curso " << atual->Curso << " com sucesso." << endl;
            } else {
                cout << "Erro ao abrir arquivo para salvar contribuinte do curso " << atual->Curso << endl;
            }

            break;
        }

        atual = atual->prox;
    }

    if (!encontrado) {
        cout << "Participante com o ID " << id << " não encontrado." << endl;
    }
}

int PegaId(ListaParticipantes *lista) {
    if (isEmpty(lista)) {
        cout << "A lista está vazia." << endl;
        return -1; 
    }

    Participante* atual = lista->primeiro;

   
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    return atual->ID;
}

void AbrirArquivoTxtContribuidores(ListaContribuintes* lista, const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    string linha;

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            if (linha.find("ID:") == 0) {
                Contribuinte* novoContribuinte = new Contribuinte;
                novoContribuinte->IDParticipante = atoi(linha.substr(4).c_str());

                if (getline(arquivo, linha) && linha.size() >= 21)
                    novoContribuinte->Mes = atoi(linha.substr(21).c_str());
                else {
                    cerr << "Erro ao ler o Mês de contribuição." << endl;
                    delete novoContribuinte;
                    continue;
                }

                if (getline(arquivo, linha) && linha.size() >= 21)
                    novoContribuinte->Ano = atoi(linha.substr(21).c_str());
                else {
                    cerr << "Erro ao ler o Ano de contribuição." << endl;
                    delete novoContribuinte;
                    continue;
                }

                if (getline(arquivo, linha) && linha.size() >= 7)
                    novoContribuinte->Valor = atoi(linha.substr(7).c_str());
                else {
                    cerr << "Erro ao ler o Valor." << endl;
                    delete novoContribuinte;
                    continue;
                }

                novoContribuinte->prox = NULL;
                enqueueContribuinte(lista, novoContribuinte);
            }
        }
        arquivo.close();
        cout << "Dados do arquivo " << nomeArquivo << " foram lidos e adicionados à lista." << endl;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }
}

void AbrirArquivoTxt(ListaParticipantes *lista, const string& nomeArquivo){
    ifstream arquivo(nomeArquivo.c_str());
    string linha;

    if(arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            if (linha.find("ID:") == 0) {
                Participante* novoParticipante = new Participante;
                novoParticipante->ID = atoi(linha.substr(4).c_str());
                getline(arquivo, linha); novoParticipante->Nome = linha.substr(6);
                getline(arquivo, linha); novoParticipante->Semestre = atoi(linha.substr(10).c_str());
                getline(arquivo, linha); novoParticipante->AnoIngressao = atoi(linha.substr(18).c_str());
                getline(arquivo, linha); novoParticipante->Curso = linha.substr(7);
                novoParticipante->prox = NULL;
                enqueue(lista, novoParticipante);
                
                void enqueue(ListaParticipantes *lista, Participante* novoParticipante);
            }
        }
        arquivo.close();
        cout << "Dados do arquivo " << nomeArquivo << " foram lidos e adicionados à lista." << endl;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }
}

void initializeQueue(ListaParticipantes *lista) {
    lista->primeiro = NULL;
}

void initializeQueueCont(ListaContribuintes *lista) {
    lista->primeiro = NULL;
}

bool isEmpty(ListaParticipantes *lista) {
    return (lista->primeiro == NULL);
}

bool isEmptyContribuinte(ListaContribuintes *lista){
	return (lista->primeiro == NULL);
}

void enqueue(ListaParticipantes *lista, Participante* novoParticipante) {
    novoParticipante->prox = NULL;
    if (isEmpty(lista)) {
        lista->primeiro = novoParticipante;
    } else {
        Participante* atual = lista->primeiro;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoParticipante;
    }
}

void enqueueContribuinte(ListaContribuintes *lista, Contribuinte* novoContribuinte) {
    novoContribuinte->prox = NULL;
    if (isEmptyContribuinte(lista)) {
        lista->primeiro = novoContribuinte;
    } else {
        Contribuinte* atual = lista->primeiro;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoContribuinte;
    }
}

void dequeue(ListaParticipantes *lista) {
    if (!isEmpty(lista)) {
        Participante* temp = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        delete temp;
    } else {
        cout << "Erro: a lista está vazia." << endl;
    }
}

void dequeueContribuinte(ListaContribuintes *lista) {
    if (!isEmptyContribuinte(lista)) {
        Contribuinte* temp = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        delete temp;
    } else {
        cout << "Erro: a lista está vazia." << endl;
    }
}

void displayContribuinte(ListaContribuintes *lista){
	if(!isEmptyContribuinte(lista)){
		Contribuinte* atual = lista->primeiro;
		cout << "Lista de contribuintes:" << endl;
		while (atual != NULL){
			cout << "ID do Contribuinte: " << atual->IDParticipante << ", Mês de contribuição: " << atual->Mes << ", ano de contribuição: " << atual->Ano << ", valor: " << atual->Valor << ",00" << endl;
			atual = atual->prox;
		}
	}else {
		cout << "A lista está vazia." << endl;
	}
}

void displayQueue(ListaParticipantes *lista) {
    if (!isEmpty(lista)) {
        Participante* atual = lista->primeiro;
        cout << "Lista de Participantes:" << endl;
        while (atual != NULL) {
        	
            cout << "ID: " << atual->ID << ", Nome: " << atual->Nome << ", Semestre: " << atual->Semestre 
			<< ", Ano de Ingresso: " << atual->AnoIngressao << ", Curso: " << atual->Curso << endl;
            atual = atual->prox;
        }
    } else {
        cout << "A lista está vazia." << endl;
    }
}

void destroyQueue(ListaParticipantes *lista) {
    while (!isEmpty(lista)) {
        dequeue(lista);
    }
}

void salvarDados(ListaParticipantes *lista, const string& nomeArquivo) {
    cout << "Tentando salvar dados em: " << nomeArquivo << endl;
    ofstream arquivo(nomeArquivo.c_str(), ios::out); 
    if (arquivo.is_open()) {
        Participante* atual = lista->primeiro;
        while (atual != NULL) {
            arquivo << "ID: " << atual->ID << "\n" << "Nome: " << atual->Nome << "\n" 
                    << "Semestre: " << atual->Semestre << "\n" << "Ano de Ingressão: " << atual->AnoIngressao << "\n" << "Curso: " << atual->Curso << "\n" << endl;
            atual = atual->prox;
        }
        arquivo.close();
        cout << "Dados salvos com sucesso em " << nomeArquivo << endl;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }
}

void salvarDadosContribuidores(ListaContribuintes *lista, const string& nomeArquivo) {
    cout << "Tentando salvar dados em: " << nomeArquivo << endl;
    
	ofstream arquivo(nomeArquivo.c_str(), ios::out); 
    if (arquivo.is_open()) {
        Contribuinte* atual = lista->primeiro;
        while (atual != NULL) {
            arquivo << "ID: " << atual->IDParticipante << "\n" << "Mês de contribuição: " << atual->Mes << "\n" << "ano de contribuição: " 
			<< atual->Ano << "\n" << "valor: " << atual->Valor << endl;
			
            atual = atual->prox;
        }
        arquivo.close();
        cout << "Dados salvos com sucesso em " << nomeArquivo << endl;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }
}

void InsereParticipanteAluno(Participante* I, int nextID) {
    I->ID = nextID;

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
    do {
        enquanto = true;
        cout << "Informe seu semestre: ";
        cin >> I->Semestre;
        
        if (I->Semestre < 1 || I->Semestre > 6) {
            system("cls");
            cout << "Você deve informar um semestre entre 1 e 6" << endl;
            enquanto = true;        
        } else {
            enquanto = false;
            system("cls");
        }
    } while(enquanto);

    do {
        cout << "Insira o ano que você iniciou na FATEC: ";
        cin >> I->AnoIngressao;
        
        if (I->AnoIngressao < currentYear - 10 || I->AnoIngressao > currentYear) {
            system("cls");
            cout << "Ano de iniciação inválido, informe um ano entre " << currentYear - 10 << " e " << currentYear << endl;
            enquanto = true;
        } else {
            enquanto = false;
            system("cls");
        }
    } while(enquanto);
    
    do {
        cout << "Escolha o seu curso: " << endl;
        cout << "[1] DSM     [2] SI     [3] GE" << endl;
        cout << "Curso: ";
        cin >> cursoOpcao;
    
        switch(cursoOpcao) {
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
    } while(enquanto);

    cout << "Participante cadastrado com sucesso!" << endl;
    cout << endl;
    cout << "ID: " << I->ID << endl;
    cout << I->Nome << " do " << I->Semestre << "° semestre de " << I->Curso << ", Ano de integração à FATEC: " << I->AnoIngressao << endl;
    cout << endl;
}

void editarParticipante(ListaParticipantes *lista, int id) {
    Participante* atual = lista->primeiro;
    bool encontrado = false;

    while (atual != NULL) {
        if (atual->ID == id) {
            encontrado = true;
            
            int resposta = 0;
            
            do
            {
                system("cls");
                cout << "Nome: " << atual->Nome << ", Semestre: " << atual->Semestre << ", Ano que entrou: " << atual->AnoIngressao << ", Curso: " << atual->Curso << endl;
                cout << "O que você deseja modificar?" << endl;
                cout << "[1]-Nome " << endl;
                cout << "[2]-Semestre" << endl;
                cout << "[3]-Ano de integrassão" << endl;
                cout << "[4]-Curso" << endl;
                cout << "[5]-Sair" << endl;
                cout << "Sua resposta: ";
                cin >> resposta;
                
                if(resposta == 1)
                {
                    system("cls");
                    cout << "Digite o novo nome: ";
                    cin >> atual->Nome;
                }
                
                if(resposta == 2)
                {
                	int semestre = 0;
                    system("cls");
                    cout << "Digite o semestre correto: ";
                    cin >> semestre;
                    
                    if(semestre >=1 && semestre <= 6)
                    {
                    	atual->Semestre = semestre;
					}
					else
					{
						cout << "Informe um semestre entre 1 e 6" <<endl;
						system("pause");
					}
                }
                if(resposta == 3)
                {
                	time_t t = time(0);   
    				tm* now = localtime(&t);  
    				int currentYear = now->tm_year + 1900;  
    				int ano = 0;
    				
    				
                    system("cls");
                    cout << "Digite o ano de integrassão correto: ";
                    cin >> ano;
                    
                    if(ano <= currentYear && ano >= currentYear -10)
                    {
                    	atual->AnoIngressao = ano;
					}
					else
					{
						cout << "Informe um ano válido" <<endl;
						system("pause");
					}
                }
                if(resposta == 4)
                {
                	int curso;
                	
                    system("cls");
                    cout << "[1] DSM     [2] SI     [3] GE" << endl;
                    cout << "Curso: ";
                    cin >> curso;
                    
                    
                    
                    if(curso == 1)
                    {
                    	atual->Curso = "DSM";
					}
					else if(curso == 2)
					{
						atual->Curso = "SI";
					}
					else if(curso == 3)
					{
						atual->Curso = "GE";
					}
					else
					{
						cout << "Escolha inválida" <<endl;
						system("pause");
					}
                }
            }
            while(resposta != 5);
            
            system("cls");
            cout << "Participante editado com sucesso!" << endl;
            break; 
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        cout << "Participante com o ID " << id << " não encontrado." << endl;
    }
}



