#ifndef SISTEMAGESTAO_H
#define SISTEMAGESTAO_H

#include "Astronauta.h"
#include "Voo.h"
#include <string>
#include <unordered_map>

class SistemaGestao {
private:
  std::unordered_map<std::string, Astronauta *> astronautas;
  std::unordered_map<int, Voo *> voos;

public:
  void cadastrarAstronauta(const std::string &cpf, const std::string &nome,
                           int idade);
  void cadastrarVoo(int codigo);
  void adicionarAstronautaEmVoo(const std::string &cpf, int codigo);
  void removerAstronautaDeVoo(const std::string &cpf, int codigo);
  void lancarVoo(int codigo);
  void explodirVoo(int codigo);
  void finalizarVoo(int codigo);
  void listarTodosOsVoos();
  void listarAstronautasMortos();
};

#endif
