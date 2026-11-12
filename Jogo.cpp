#include "Jogo.h"
#include <iostream>

Jogo::Jogo():
window(sf::VideoMode({400, 400}), "Jogo")
{
    window.setFramerateLimit(240);

    pJog1.setWindow(&window);

    fase1.setWindow(&window);
    fase1.setJogador(&pJog1);

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

        // Atualizacao do jogador
        pJog1.mover();
        pJog1.saiuDoChao();

        // Atualizacao dos objetos da fase
        fase1.executar();

        // Desenho do jogador
        pJog1.desenhar();

        window.display();
    }
}



