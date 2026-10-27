#pragma once
#include<SFML/Graphics.hpp>

//Segui o tutorial do SFML.
class Jogo
{
private:
    sf::RenderWindow window;
    sf::RectangleShape shape;

public:
    Jogo();
    ~Jogo();
    void Executar();
};
