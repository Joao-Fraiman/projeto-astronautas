#ifndef VOO_H
#define VOO_H

#include "Astronauta.h"
#include <vector>

class Voo {
public:
  int codigo;
  std::vector<Astronauta *> passageiros;
  bool planejado;
  bool emCurso;
  bool finalizado;
  bool sucesso;

  Voo(int codigo);
};

#endif
