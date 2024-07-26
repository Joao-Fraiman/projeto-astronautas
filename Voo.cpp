#include "Voo.h"

Voo::Voo(int codigo)
    : codigo(codigo), planejado(true), emCurso(false), finalizado(false),
      sucesso(false) {}
