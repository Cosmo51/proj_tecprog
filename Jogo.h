#pragma once
#include<SFML/Graphics.hpp>
#include "Personagens.h"
#include "Fases.h"

using namespace Personagens;
using namespace Fases;

class Jogo
{
private:
    sf::RenderWindow window;

    Jogador pJog1;
    FasePrimeira fase1;

public:
    Jogo();
    ~Jogo();
    void executar();
};

