#include "SistemaGestao.h"
#include <iostream>
#include <regex>

using namespace std;

void imprimeMenu() {
  cout << "\n";
  cout << "-------------------Sistema de Gestão-----------------\n";
  cout << "1-) Cadastrar Astronauta\n";
  cout << "2-) Cadastrar Voo\n";
  cout << "3-) Adicionar Astronauta\n";
  cout << "4-) Remover Astronauta\n";
  cout << "5-) Lançar Voo\n";
  cout << "6-) Explodir Voo\n";
  cout << "7-) Finalizar Voo\n";
  cout << "8-) Listar Voo\n";
  cout << "9-) Listar Mortos\n";
  cout << "10-) Finalizar Sistema\n";
  cout << "------------------------------------------------------\n";
  cout << "\n";
  cout << "Digite o número da operação que você deseja realizar: ";
}
bool validarCPF(const string &cpf) {
  regex cpfRegex("\\d{11}");
  return regex_match(cpf, cpfRegex);
}

bool validarNome(const string &nome) {
  regex nomeRegex("^[a-zA-Z\\s]+$");
  return !nome.empty() && regex_match(nome, nomeRegex);
}


int main() {
  SistemaGestao sistema;
  int comando;

  do {
    imprimeMenu();
    std::string cpf;
    std::string nome;
    int idade;
    int codigo;

    cin >> comando;
    switch (comando) {
    case 1:
      cout << "\nDigite o CPF do astronauta (somente números): ";
      cin >> cpf;
      if (!validarCPF(cpf)) {
        cout << "CPF inválido. Deve conter 11 dígitos.\n";
        break;
      }

      cout << "Digite o nome do astronauta: ";
      cin.ignore();
      getline(cin, nome);
      if (!validarNome(nome)) {
        cout << "Nome inválido. Deve conter apenas letras e espaços.\n";
        break;
      }

      cout << "Digite a idade do astronauta: ";
      cin >> idade;
      
      cout << "\n";
      sistema.cadastrarAstronauta(cpf, nome, idade);
      break;
    case 2:
      cout << "\n";
      cout << "Digite o código do voo: ";
      cin >> codigo;
      cout << "\n";
      sistema.cadastrarVoo(codigo);
      break;
    case 3:
      cout << "\n";
      cout << "Digite o CPF do astronauta: ";
      cin >> cpf;
      cout << "Digite o código do voo: ";
      cin >> codigo;
      cout << "\n";
      sistema.adicionarAstronautaEmVoo(cpf, codigo);
      break;
    case 4:
      cout << "\n";
      cout << "Digite o CPF do astronauta: ";
      cin >> cpf;
      cout << "Digite o código do voo: ";
      cin >> codigo;
      cout << "\n";
      sistema.removerAstronautaDeVoo(cpf, codigo);
      break;
    case 5:
      cout << "\n";
      cout << "Digite o código do voo: ";
      cin >> codigo;
      cout << "\n";
      sistema.lancarVoo(codigo);
      break;
    case 6:
      cout << "\n";
      cout << "Digite o código do voo: ";
      cin >> codigo;
      cout << "\n";
      sistema.explodirVoo(codigo);
      break;
    case 7:
      cout << "\n";
      cout << "Digite o código do voo: ";
      cin >> codigo;
      cout << "\n";
      sistema.finalizarVoo(codigo);
      break;
    case 8:
      cout << "\n";
      sistema.listarTodosOsVoos();
      break;
    case 9:
      cout << "\n";
      sistema.listarAstronautasMortos();
      break;
    case 10:
      cout << "\n";
      cout << "Muito obrigado por utilizar nosso sistema de gestão. Adeus!\n";
      break;
    default:
      cout << "\n";
      cout << "Opção inválida. Tente novamente.\n";
      break;
    }
  } while (comando != 10);

  return 0;
}
