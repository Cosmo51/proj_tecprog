#pragma once
#include "Gerenciadores.h"
#include "Personagens.h"
#include "Fases.h"

using namespace Personagens;
using namespace Fases;
using namespace Gerenciadores;

class Jogo
{
private:
    Gerenciador_Grafico GG;
    Jogador pJog1;
    FasePrimeira fase1;
    FaseSegunda fase2;

public:
    Jogo();
    ~Jogo();
    void executar();
};
