// solicita 3 frases.
// escreve as frases em um arquivo .txt
// le o arquivo e retorna os nomes comecados em maiusculas


#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main() {

	cout << "testes.cpp !" << endl;

	string frase1, frase2, frase3;

	string *p;
	p = &frase1;
	string str = *p;

	ofstream fout;	

	int opcao;
	while (opcao != 1 && opcao != 2) {
		cout << "<<1>> para escrever frases.\n<<2>> para analisar frases." << endl;
		cin >> opcao;
	}

	switch (opcao) {
		default:
			cout << "Nenhuma opcao escolhida!" << endl;
			break;

		case 1:
			fout.open("frases.txt");
			if (fout.fail()) {
				cout << "Erro escrevendo arquivo!" << endl;
			}
			for (int i=1; i<=3; i++) {
				while (str.empty()) {
					cout << "Informe a frase" << i << ": " << endl;
					getline(cin, *p);
					str = *p;
					if (!str.empty()) {
						fout << str << endl;
					}
				}
				p++;
				str = *p;
			}
			fout.close();
			break;

		case 2:
			string palavra;
			int contador{0};
			ifstream fin;
			fin.open("frases.txt");
			if (!fin) {
				cout << "Erro lendo arquivo!" << endl;
			} else {
				cout << "Arquivo: " << endl;
			}
			while (!fin.eof()) {
				getline(fin, palavra);
				if (!fin.eof()) {
					cout << palavra << endl;
					// anlises
					
				}
			}
			fin.close();
			break;
	}
}



