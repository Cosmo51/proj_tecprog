#pragma once
#include<SFML/Graphics.hpp>
#include "Personagens.h"
#include "Gerenciadores.h"
#include "Obstaculos.h"

using namespace Personagens;
using namespace Gerenciadores;

//Segui o tutorial do SFML.
class Jogo
{
private:
    sf::RenderWindow window;
    Jogador pJog1;
    Inim_Facil inimFacil;
    Inim_Medio inimMedio;
    Plataforma plat1;
    Plataforma plat2;
    Gerenciador_Grafico GG;
    LimitesGeograficos limitedireita;
    LimitesGeograficos limiteesquerda;

public:
    Jogo();
    ~Jogo();
    void executar();
};
