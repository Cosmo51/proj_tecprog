#pragma once
#include<SFML/Graphics.hpp>
#include "Personagens.h"
#include "Gerenciadores.h"

using namespace Personagens;
using namespace Gerenciadores;

//Segui o tutorial do SFML.
class Jogo
{
private:
    sf::RenderWindow window;
    Jogador pJog1;
    Inim_Facil inimFacil;
    Gerenciador_Grafico GG;

public:
    Jogo();
    ~Jogo();
    void executar();
};
