#pragma once
#include "Gerenciadores.h"
#include "Personagens.h"
#include "Fases.h"
#include "Menu.h"

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
    Menu menu;
    bool noMenu;
    int faseAtual;
    bool pausado;

public:
    Jogo();
    ~Jogo();
    void executar();
    void iniciarJogo(int fase = 1);
    void sair();
    void pausar(bool pausa);
};
