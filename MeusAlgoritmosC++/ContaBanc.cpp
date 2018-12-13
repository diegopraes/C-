#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


struct ContaBanc {
	int numero;
	string cliente;
	double saldo;
};

ContaBanc contaInfo() {
	ContaBanc cont;
	cout << "Informe o numero da conta:" << endl;
	cin >> cont.numero;
	cout << "Informe nome do cliente:" << endl;
	cin >> cont.cliente;
	cout << "Saldo inicial:" << endl;
	cin >> cont.saldo;
	return cont;
}

void mostrarContaInfo(ContaBanc& cont) {
	cout << "-----------------------------------------" << endl;
	cout << "Numero da conta:" << cont.numero << endl;
	cout << "Nome do cliente:" << cont.cliente << endl;
	cout << "Saldo: $" << cont.saldo << endl;
	cout << "-----------------------------------------" << endl;
}


ContaBanc debitarConta(ContaBanc& cont) {
	double valor;
	cout << "Informe o valor a ser debitado:" << endl;
	cin >> valor;
	bool saldoDisp = false;
	if (cont.saldo > valor) {
		saldoDisp = true;
	}
	else {
		cout << "Saldo insuficiente!" << endl;
	}
	if (saldoDisp) {
		cont.saldo -= valor;
	}
	return cont;
}


ContaBanc creditarConta(ContaBanc& cont) {
	double valor;
	cout << "Informe o valor a ser creditado" << endl;
	cin >> valor;
	cont.saldo += valor;
	return cont;
}





int main() {

	ContaBanc conta1;
	int opcao;

	do {
		cout << "<<1>> Criar conta.\n"
		     << "<<2>> Mostrar informacoes.\n"
		     << "<<3>> Debitar a conta.\n"
		     << "<<4>> Creditar a conta.\n" << endl;
		     << "<<5>> Sair.\n" << endl;
		cin >> opcao;
		
		switch(opcao) {
			default:
				cout << "Nenhuma opcao escolhida!" << endl;
				break;
			
			case 1:
				conta1 = contaInfo();
				break;
			case 2:
				mostrarContaInfo(conta1);
				break;
			case 3:
				debitarConta(conta1);
				break;
			case 4:
				creditarConta(conta1);
				break;
			case 5:
				break;
		}
	} while (opcao != 5);
}

