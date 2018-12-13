#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


using namespace std;


const int ID_largura = 8;
const int NOME_largura = 20;
const int EMAIL_largura = 25;
const int NUM_largura = 10;
const int TOTAL_largura = 100;



struct funcionario {
    int id;
    string nome;
    double salario;
    double he;
    double ps;
    string email;
};


void lerArquivoFunc(vector <funcionario>& v_func);
void registrarFunc();
void Menu();
void Tarefa(vector <funcionario>& v_func, int opcao);
void adicionarFunc(vector <funcionario>& v_func);
int procurarFunc(vector <funcionario> v_func, int funcionarioAlvo);
void salvar(vector <funcionario> v_func);
void mostrarFunc(vector <funcionario> v_func);
void funcInfo(funcionario f);
double salarioLiq(funcionario f);
bool deletarFunc(vector <funcionario>& v_func, int funcionarioAlvo);



////////////////////////////////////////////////////////////////////////////

int main()
{
	//registrarFunc();

	vector <funcionario> v_func;
	lerArquivoFunc(v_func);

	Menu();

	int opcao;
	bool sair=false;
	while (!sair) {
        cout << "Informe a opcao desejada:" << endl;
        cin >> opcao;
        if (opcao == 6) {
            sair = true;
        } else {
            Tarefa(v_func, opcao);
        }
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////


void lerArquivoFunc(vector <funcionario>& v_func) {
    ifstream fin;
    fin.open("funcionarios.txt");
    if (!fin) {
        cout << "Erro lendo arquivo!" << endl;
    }
    string linha;
    int contador{0};
    while (!fin.eof()) {
        std::getline(fin, linha);
        if (!fin.eof()) {
                contador++;
        }
        istringstream iss(linha);
        string funcID, funcNome, funcSalario, he, ps, funcEmail;
        std::getline(iss, funcID, ',');
        std::getline(iss, funcNome, ',');
        std::getline(iss, funcSalario, ',');
        std::getline(iss, he, ',');
        std::getline(iss, ps, ',');
        std::getline(iss, funcEmail, ',');

        funcionario temp_var;
        // converte string em inteiro
        temp_var.id = atoi(funcID.c_str());
        temp_var.nome = funcNome;
        temp_var.salario = atof(funcSalario.c_str());
        temp_var.he = atof(he.c_str());
        temp_var.ps = atof(ps.c_str());
        temp_var.email = funcEmail;

        v_func.push_back(temp_var);
    }
    fin.close();
    //cout << "Total " << contador << " registros lidos no arquivo." << endl;
}



void Menu() {
    cout << "<< 1 >> Adicionar funcionario\n"
         << "<< 2 >> Informacoes do funcionario\n"
         << "<< 3 >> Procurar funcionario\n"
         << "<< 4 >> Remover funcionario\n"
         << "<< 5 >> Salvar\n"
         << "<< 6 >> Sair" << endl;
}



void Tarefa(vector <funcionario>& v_func, int opcao) {
    switch(opcao) {
        default:
            break;
        case 1: cout << "Adicionar funcionario" << endl;
            adicionarFunc(v_func);
            break;

        case 2: cout << "Informacoes dos funcionarios" << endl;
            mostrarFunc(v_func);
            break;

        case 3: cout << "Procurar funcionario" << endl;
            int funcionarioAlvo;
            cout << "Informe o ID do funcionario:";
            cin >> funcionarioAlvo;
	    if (procurarFunc(v_func, funcionarioAlvo) == -1) {
	    	cout << "Funcionario nao encontrado!" << endl;
            } else {
		cout << "Funcionario encontrado em i::" << procurarFunc(v_func, funcionarioAlvo) << endl;
		funcInfo(v_func[procurarFunc(v_func, funcionarioAlvo)]);
	    }
            break;

        case 4: cout << "Remover funcionario" << endl;
	    int funcionarioDel;
            cout << "Informe o ID do funcionario:";
            cin >> funcionarioDel;
	    deletarFunc(v_func,funcionarioDel);
            break;

        case 5: cout << "Salvar" << endl;
            salvar(v_func);
            break;

        case 6: cout << "Sair" << endl;
            break;
    }
}



void adicionarFunc(vector <funcionario>& v_func) {
    funcionario temp_var;
    bool duplicado = false;
    do {
        cout << "ID do funcionario:";
        cin >> temp_var.id;
        duplicado = false;
        if (procurarFunc(v_func, temp_var.id) != -1) {
            duplicado = true;
            cout << "ID " << temp_var.id << " ja existe!" << endl;
        }
    } while (duplicado);
    cout << "Nome: ";
    cin.clear();
    cin.ignore(INT8_MAX,'\n');
    getline(cin, temp_var.nome);
    cout << "Salario (R$):";
    cin >> temp_var.salario;
    cout << "hora extra:";
    cin >> temp_var.he;
    cout << "plano de saude:";
    cin >> temp_var.ps;
    cout << "email:";
    cin.clear();
    cin.ignore(INT8_MAX,'\n');
    getline(cin, temp_var.email);

    v_func.push_back(temp_var);

    cout << "Funcionario ID " << temp_var.id << " adicionado com sucesso!" << endl;
}



int procurarFunc(vector <funcionario> v_func, int funcionarioAlvo) {
    for (int i=0; i<v_func.size()-1; i++) {
        if (v_func[i].id == funcionarioAlvo) {
            return i;
        }
    }
    return -1;
}



bool deletarFunc(vector <funcionario>& v_func, int funcionarioAlvo) {
	int indice = procurarFunc(v_func, funcionarioAlvo);
	if (indice == -1) {
		return false;
	}
	funcInfo(v_func[indice]);
	char op;
	while (op != 's' && op != 'n') {
		cout << "Deletar funcionario ? [s ou n]:" << endl;
		cin >> op;
	}
	if (op == 's') {
		v_func.erase(v_func.begin() + indice);
		return true;
	}
	return false;
}





void mostrarFunc(vector <funcionario> v_func) {
    cout << endl;
    cout << std::setw(ID_largura) << left << "ID"
         << std::setw(NOME_largura) << left << "Nome"
         << std::setw(EMAIL_largura) << left << "Email"
         << std::setw(NUM_largura) << left << "Base"
         << std::setw(NUM_largura) << left << "H.E."
         << std::setw(NUM_largura) << left << "P.S."
         << std::setw(NUM_largura) << left << "Liq." << endl;
    cout << std::setw(TOTAL_largura) << setfill('-') << " " << endl;
    cout << setfill(' ');

    double totalBase = 0.0;
    double totalPS = 0.0;
    double totalHE = 0.0;
    double totalLiq = 0.0;

    for (vector <funcionario>::iterator it=v_func.begin(); it != v_func.end(); it++) {
        funcInfo(*it);

        totalBase += it -> salario; // v_func[it].base
        totalPS += it -> ps;
        totalHE += it -> he;
        totalLiq += salarioLiq(*it);
    }
    cout << std::setw(TOTAL_largura) << setfill('-') << " " << endl;
    cout << setfill(' ');

    cout << std::setw(ID_largura) << left << "Total"
         << std::setw(NOME_largura) << left << "In (R$)"
         << std::setw(EMAIL_largura) << " "
         << std::setw(NUM_largura) << left << setprecision(2) << left << fixed << totalBase
         << std::setw(NUM_largura) << left << setprecision(2) << left << fixed << totalHE
         << std::setw(NUM_largura) << left << setprecision(2) << left << fixed << totalPS
         << std::setw(NUM_largura) << left << setprecision(2) << left << fixed << totalLiq
         << endl;

}



void funcInfo(funcionario f) {
    if (f.id != 0) {
        cout << std::setw(ID_largura) << left << f.id
         << std::setw(NOME_largura) << left << f.nome
         << std::setw(EMAIL_largura) << left << f.email
         << std::setw(NUM_largura) << left << f.salario
         << std::setw(NUM_largura) << left << f.he
         << std::setw(NUM_largura) << left << f.ps
         << std::setw(NUM_largura) << left << salarioLiq(f)
         << endl;
    }
}



double salarioLiq(funcionario f) {
    return f.salario - (f.he + f.ps);
}





void salvar(vector <funcionario> v_func) {
	int id, he, ps;
	double salario;
	string nome, email;

	ofstream fout;
	fout.open("funcionarios.txt");
	if (!fout) {
		cout << "Erro escrevendo arquivo!" << endl;
	}

	for (int i=0; i<v_func.size(); i++) {
		if (!fout.eof() && v_func[i].id != 0) {
		    id = v_func[i].id;
		    nome = v_func[i].nome;
		    salario = v_func[i].salario;
		    he = v_func[i].he;
		    ps = v_func[i].ps;
		    email = v_func[i].email;
		    fout << id << "," 
			 << nome << "," 
			 << salario << "," 
			 << he << "," 
			 << ps << "," 
			 << email << endl;
        	}
	}
}





void registrarFunc() {
	int id, num1, num2;
	double salario;
	string nome, email;

	ofstream fout;
	fout.open("funcionarios.txt");
	if (!fout) {
	cout << "Erro escrevendo arquivo!" << endl;
	}
	int n;
	cout << "Numero de funcionarios:" << endl;
	cin >> n;

	for (int i=0; i<n; i++) {
	cout << "ID:" << endl;
	cout << "Nome:" << endl;
	cout << "Salario:" << endl;
	cout << "num1:" << endl;
	cout << "num2:" << endl;
	cout << "Email:" << endl;

	fout << id << "," << nome << "," << salario << "," << num1 << "," << num2 << "," << email << endl;
	}
}



