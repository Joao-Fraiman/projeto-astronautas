#include "SistemaGestao.h"
#include <algorithm>
#include <iostream>

using namespace std;

void SistemaGestao::cadastrarAstronauta(const std::string &cpf,
                                        const std::string &nome, int idade) {
  if (astronautas.find(cpf) == astronautas.end()) {
    astronautas[cpf] = new Astronauta(cpf, nome, idade);
    cout << "Astronauta " << nome << " cadastrado com sucesso.\n";
  } else {
    cout << "Astronauta com CPF " << cpf << " já está cadastrado.\n";
  }
}

void SistemaGestao::cadastrarVoo(int codigo) {
  if (voos.find(codigo) == voos.end()) {
    voos[codigo] = new Voo(codigo);
    cout << "Voo " << codigo << " cadastrado com sucesso.\n";
  } else {
    cout << "Voo com código " << codigo << " já está cadastrado.\n";
  }
}

void SistemaGestao::adicionarAstronautaEmVoo(const std::string &cpf,
                                             int codigo) {
  if (astronautas.find(cpf) != astronautas.end() &&
      voos.find(codigo) != voos.end()) {
    Astronauta *astronauta = astronautas[cpf];
    Voo *voo = voos[codigo];

    if (voo->planejado) {
      voo->passageiros.push_back(astronauta);
      astronauta->voos.push_back(codigo);
      cout << "Astronauta " << astronauta->nome << " adicionado ao voo "
           << codigo << " com sucesso.\n";
    } else {
      cout << "Não é possível adicionar astronautas a um voo que não está em "
              "planejamento.\n";
    }
  } else {
    cout << "Astronauta ou Voo não encontrados.\n";
  }
}

void SistemaGestao::removerAstronautaDeVoo(const std::string &cpf, int codigo) {
  if (astronautas.find(cpf) != astronautas.end() &&
      voos.find(codigo) != voos.end()) {
    Astronauta *astronauta = astronautas[cpf];
    Voo *voo = voos[codigo];

    if (voo->planejado) {
      auto it =
          find(voo->passageiros.begin(), voo->passageiros.end(), astronauta);
      if (it != voo->passageiros.end()) {
        voo->passageiros.erase(it);
        auto it_voo =
            find(astronauta->voos.begin(), astronauta->voos.end(), codigo);
        if (it_voo != astronauta->voos.end()) {
          astronauta->voos.erase(it_voo);
        }
        cout << "Astronauta " << astronauta->nome << " removido do voo "
             << codigo << " com sucesso.\n";
      } else {
        cout << "Astronauta não encontrado no voo.\n";
      }
    } else {
      cout << "Não é possível remover astronautas de um voo que não está em "
              "planejamento.\n";
    }
  } else {
    cout << "Astronauta ou Voo não encontrados.\n";
  }
}

void SistemaGestao::lancarVoo(int codigo) {
  if (voos.find(codigo) != voos.end()) {
    Voo *voo = voos[codigo];

    if (voo->planejado && !voo->passageiros.empty()) {
      bool todosDisponiveis = true;
      for (Astronauta *astro : voo->passageiros) {
        if (!astro->disponivel) {
          todosDisponiveis = false;
          break;
        }
      }

      if (todosDisponiveis) {
        voo->planejado = false;
        voo->emCurso = true;
        for (Astronauta *astro : voo->passageiros) {
          astro->disponivel = false;
        }
        cout << "Voo " << codigo << " lançado com sucesso.\n";
      } else {
        cout << "Todos os astronautas devem estar disponíveis para lançar o "
                "voo.\n";
      }
    } else {
      cout << "Voo não está em planejamento ou não possui astronautas "
              "suficientes.\n";
    }
  } else {
    cout << "Voo não encontrado.\n";
  }
}

void SistemaGestao::explodirVoo(int codigo) {
  if (voos.find(codigo) != voos.end()) {
    Voo *voo = voos[codigo];

    if (voo->emCurso) {
      voo->emCurso = false;
      voo->finalizado = true;
      voo->sucesso = false;

      for (Astronauta *astro : voo->passageiros) {
        astro->morto = true;
      }
      cout << "Voo " << codigo << " explodiu. Todos os astronautas morreram.\n";
    } else {
      cout << "Voo não está em curso.\n";
    }
  } else {
    cout << "Voo não encontrado.\n";
  }
}

void SistemaGestao::finalizarVoo(int codigo) {
  if (voos.find(codigo) != voos.end()) {
    Voo *voo = voos[codigo];

    if (voo->emCurso) {
      voo->emCurso = false;
      voo->finalizado = true;
      voo->sucesso = true;

      for (Astronauta *astro : voo->passageiros) {
        astro->disponivel = true;
      }
      cout << "Voo " << codigo << " finalizado com sucesso.\n";
    } else {
      cout << "Voo não está em curso.\n";
    }
  } else {
    cout << "Voo não encontrado.\n";
  }
}

void SistemaGestao::listarTodosOsVoos() {
  if (voos.empty()) {
    cout << "Não há nenhum voo programado.\n";
    return;
  }

  for (auto &pair : voos) {
    Voo *voo = pair.second;
    cout << "Voo " << voo->codigo << " - ";
    if (voo->planejado)
      cout << "Planejado\n";
    else if (voo->emCurso)
      cout << "Em curso\n";
    else
      cout << "Finalizado - " << (voo->sucesso ? "Com sucesso" : "Explodido")
           << "\n";

    for (Astronauta *astro : voo->passageiros) {
      cout << "  Astronauta: " << astro->nome << " (CPF: " << astro->cpf
           << ")\n";
    }
  }
}

void SistemaGestao::listarAstronautasMortos() {
    cout << "Astronautas mortos:\n";
    bool encontrouMorto = false;

    for (auto &pair : astronautas) {
        Astronauta *astro = pair.second;
        if (astro->morto) {
            encontrouMorto = true;
            cout << "CPF: " << astro->cpf << ", Nome: " << astro->nome << "\n";
            cout << "Voos que participou: ";
            for (int codigo : astro->voos) {
                cout << codigo << " ";
            }
            cout << "\n";
        }
    }

    if (!encontrouMorto) {
        cout << "Não há nenhum astronauta morto.\n";
    }
}
