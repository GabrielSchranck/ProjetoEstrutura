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
};


struct Fila {
    Participante* frente;
    Participante* tras;
};


void initializeQueue(Fila *f);
bool isEmpty(Fila *f);
void enqueue(Fila *f, Participante* novoParticipante);
void dequeue(Fila *f);
void displayQueue(Fila *f);
void destroyQueue(Fila *f);
void salvarDados(Fila *f, const string& nomeArquivo);
void carregarDados(Fila *f, const string& nomeArquivo);
void InsereParticipanteAluno(Participante* I, int nextID);
int obterUltimoID(const string& nomeArquivo);


int main() {
	setlocale(LC_ALL, "Portuguese");
    Fila filaParticipantes;
    initializeQueue(&filaParticipantes);

    int ultimoID = obterUltimoID("participantes.txt");
    if (ultimoID == -1) {
        cout << "Erro ao obter o último ID do arquivo." << endl;
        return 1; 
    }
    
   
    static int nextID = ultimoID + 1;

    int opcao;
    do {
        system("cls");
        cout << endl;
        cout << "Bem-vindo à Turma do Café" << endl;
        cout << "Escolha uma opção:" << endl;
        cout << "1. Adicionar Participante" << endl;
        cout << "2. Visualizar Participantes" << endl;
        cout << "3. Remover Participante" << endl;
        cout << "4. Salvar Dados em Arquivo" << endl;
        cout << "5. Carregar Dados de Arquivo" << endl;
        cout << "6. Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;
        cout << endl;

        switch(opcao) {
            case 1: {
            	system("cls");
                Participante* novoParticipante = new Participante;
                InsereParticipanteAluno(novoParticipante, nextID);
                enqueue(&filaParticipantes, novoParticipante);
                nextID++; 
                break;
            }
            case 2:
                displayQueue(&filaParticipantes);
                break;
            case 3:
                dequeue(&filaParticipantes);
                break;
            case 4:
                salvarDados(&filaParticipantes, "participantes.txt");
                break;
            case 5:
                carregarDados(&filaParticipantes, "participantes.txt");
                break;
            case 6:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }

        system("pause");
    } while(opcao != 6);

    destroyQueue(&filaParticipantes);
    return 0;
}


void initializeQueue(Fila *f) {
    f->frente = NULL;
    f->tras = NULL;
}

bool isEmpty(Fila *f) {
    return (f->frente == NULL);
}

void enqueue(Fila *f, Participante* novoParticipante) {
    if (isEmpty(f)) {
        f->frente = novoParticipante;
    } else {
        f->tras->prox = novoParticipante;
    }
    f->tras = novoParticipante;
}

void dequeue(Fila *f) {
    if (!isEmpty(f)) {
        Participante* temp = f->frente;
        f->frente = f->frente->prox;
        delete temp;
    } else {
        cout << "Erro: a fila está vazia." << endl;
    }
}

void displayQueue(Fila *f) {
    if (!isEmpty(f)) {
        Participante* atual = f->frente;
        cout << "Fila de Participantes:" << endl;
        while (atual != NULL) {
            cout << "ID: " << atual->ID << ", Nome: " << atual->Nome << ", Semestre: " << atual->Semestre << ", Ano de Ingresso: " << atual->AnoIngressao << ", Curso: " << atual->Curso << endl;
            atual = atual->prox;
        }
    } else {
        cout << "A fila está vazia." << endl;
    }
}

void destroyQueue(Fila *f) {
    while (!isEmpty(f)) {
        dequeue(f);
    }
}

void salvarDados(Fila *f, const string& nomeArquivo) {
    cout << "Tentando salvar dados em: " << nomeArquivo << endl;
    ofstream arquivo(nomeArquivo.c_str(), ios::app); 
    if (arquivo.is_open()) {
        Participante* atual = f->frente;
        while (atual != NULL) {
            arquivo << atual->ID << "," << atual->Nome << "," << atual->Semestre << "," << atual->AnoIngressao << "," << atual->Curso << endl;
            atual = atual->prox;
        }
        arquivo.close();
        cout << "Dados salvos com sucesso em " << nomeArquivo << endl;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }
}

void carregarDados(Fila *f, const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    if (arquivo.is_open()) {
        int id, semestre, anoIngressao;
        string nome, curso;
        while (arquivo >> id >> nome >> semestre >> anoIngressao >> curso) {
            Participante* novoParticipante = new Participante;
            novoParticipante->ID = id;
            novoParticipante->Nome = nome;
            novoParticipante->Semestre = semestre;
            novoParticipante->AnoIngressao = anoIngressao;
            novoParticipante->Curso = curso;
            novoParticipante->prox = NULL;
            enqueue(f, novoParticipante);
        }
        arquivo.close();
        cout << "Dados carregados com sucesso de " << nomeArquivo << endl;
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
        
        if (I->AnoIngressao < currentYear - 5 || I->AnoIngressao > currentYear) {
            system("cls");
            cout << "Ano de iniciação inválido, informe um ano entre " << currentYear - 5 << " e " << currentYear << endl;
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
    system("pause");
    system("cls");
    cout << endl;
    cout << "ID: " << I->ID << endl;
    cout << I->Nome << " do " << I->Semestre << "° semestre de " << I->Curso << ", Ano de integração à FATEC: " << I->AnoIngressao << endl;
    cout << endl;
}

int obterUltimoID(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    if (arquivo.is_open()) {
        int ultimoID = 0;
        string linha;
        while (getline(arquivo, linha)) {
            if (!linha.empty()) {
                istringstream ss(linha);
                string token;
                getline(ss, token, ',');
                int id;
                ss >> id; 
                if (id > ultimoID) {
                    ultimoID = id;
                }
            }
        }
        arquivo.close();
        return ultimoID;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return -1;
    }
}



