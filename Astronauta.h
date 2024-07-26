#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <string>
#include <vector>

class Astronauta {
public:
  std::string cpf;
  std::string nome;
  int idade;
  bool disponivel;
  bool morto;
  std::vector<int> voos;

  Astronauta(const std::string &cpf, const std::string &nome, int idade);
};

#endif
