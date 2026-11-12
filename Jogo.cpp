#include "Jogo.h"
#include <iostream>

Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo")
{
    window.setFramerateLimit(240);
    pJog1.setWindow(&window);
    Aranha.setWindow(&window);
    Galinha.setWindow(&window);
    plat1.configurar(0.f, 390.f, 400.f, 10.f);
    plat2.configurar(120.f, 250.f, 50.f, 10.f);
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

        pJog1.mover();
        Aranha.mover();
        pJog1.saiuDoChao();

        if (GC.verificarColisao(&pJog1, &plat1))
        {
            plat1.obstaculizar(&pJog1);
        }

        if (GC.verificarColisao(&pJog1, &plat2))
        {
            plat2.obstaculizar(&pJog1);
        }

        plat1.desenhar();
        plat2.desenhar();
        pJog1.desenhar();
        Aranha.desenhar();
        Galinha.desenhar();
        limitedireita.desenhar();
        limiteesquerda.desenhar();
        window.display();
    }
}

