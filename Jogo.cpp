#include "Jogo.h"


//implementei como foi feito no tutorial do SFML.
Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo")
{
    pJog1.setWindow(&window);
    inimFacil.setWindow(&window);

    executar();
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{
    //sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        pJog1.draw();
        inimFacil.draw();
        window.display();
    }
}

