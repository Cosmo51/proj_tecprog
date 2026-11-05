#include "Jogo.h"


//implementei como foi feito no tutorial do SFML.
Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo")
{
    executar();
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{
    //sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

