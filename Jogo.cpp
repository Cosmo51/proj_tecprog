#include "Jogo.h"

//implementei como foi feito no tutorial do SFML.
Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo")
{
    Executar();
}

Jogo::~Jogo()
{

}

void Jogo::Executar()
{
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
