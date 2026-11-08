#include "Jogo.h"


//implementei como foi feito no tutorial do SFML.
Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo"),
shapeJogador(sf::Vector2f(50.f,100.f)),
shapeInimigo(sf::Vector2f(50.f,100.f))
{
    shapeJogador.setFillColor(sf::Color::Blue);
    shapeJogador.setPosition(sf::Vector2f(20.f, 170.f));

    shapeInimigo.setFillColor(sf::Color::Red);
    shapeInimigo.setPosition(sf::Vector2f(330.f, 170.f));

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

        window.draw(shapeJogador);
        window.draw(shapeInimigo);


        window.display();
    }
}

