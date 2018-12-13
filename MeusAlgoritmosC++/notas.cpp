
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

double mediaNotas(string notas);
char notaConceito(double media);


int main() {

	ifstream fin;
	fin.open("notas.txt");
	if (!fin) {
		cout << "Erro lendo arquivo!" << endl;
		exit(1);
	}

	ofstream fout;
	fout.open("NotasFinais.txt");
	if (fout.fail()) {
		cout << "Erro escrevendo arquivo!" << endl;
		exit(1);
	}

	fout << std::setw(15) << left << "Nome" << " " 
			     << std::setw(7) << left << "Media" << " " 
			     << std::setw(5) << left << "Conceito" << " " << endl;
			fout << string(35, '-') << endl;

	string linha;
	while(!fin.eof()) {
		getline(fin,linha);
		//cout << linha << endl;
		istringstream issAluno(linha);
		string aluno;
		string notas;
		// pega parte esquerda da string dividida por ':'
		getline(issAluno, aluno, ':');
		// do que restou, pega parte esquerda dividida por ':'
		getline(issAluno, notas, ':');
		double media = mediaNotas(notas);
		char conceito = notaConceito(mediaNotas(notas));
		if (!fin.eof()) {
			fout << std::setw(17) << aluno
			     << std::setw(7) << setprecision(2) << fixed << media
			     << std::setw(5) << conceito << endl;
		}
	}
	fin.close();			
}



double mediaNotas(string notas) {
	istringstream issNotas(notas);
	string nota;
	int notaTotal{0}, contador{0};
	while (!issNotas.eof()) {
			getline(issNotas, nota, ',');
			notaTotal += atoi(nota.c_str());
			contador++;
	}
	double media = (double)notaTotal / contador;
	return media;
}


char notaConceito(double media) {
	char conceito;
	if (media < 60) {
		conceito = 'F';
	} else if (media > 60 && media < 70) {
		conceito = 'D';
	} else if (media > 70 && media < 80) {
		conceito = 'C';
	} else if (media > 80 && media < 90) {
		conceito = 'B';
	} else { 
		conceito ='A';
	}
	return conceito;
}
	

