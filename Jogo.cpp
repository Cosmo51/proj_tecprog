#include "Jogo.h"



Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo"),
plat1(0, 390, 400, 10),
plat2(120, 250, 50, 10)//(x, y[partindo de cima], largura, altura)
{
    pJog1.setWindow(&window);
    inimFacil.setWindow(&window);
    inimMedio.setWindow(&window);
    plat1.setWindow(&window);
    plat2.setWindow(&window);
    limitedireita.direita();
    limitedireita.setWindow(&window);
    limiteesquerda.esquerda();
    limiteesquerda.setWindow(&window);

    executar();
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        pJog1.mover(0);

        plat1.draw();
        plat2.draw();
        pJog1.draw();
        inimFacil.draw();
        inimMedio.draw();
        limitedireita.draw();
        limiteesquerda.draw();
        window.display();
    }
}

