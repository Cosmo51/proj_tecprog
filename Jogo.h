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
    sf::RectangleShape shape;
    Jogador pJog1;
    Gerenciador_Grafico GG;

public:
    Jogo();
    ~Jogo();
    void executar();
};
