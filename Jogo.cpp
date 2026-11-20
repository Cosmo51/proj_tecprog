#include "Jogo.h"
#include <iostream>

Jogo::Jogo()
{
    fase1.setJogador(&pJog1);
    fase2.setJogador(&pJog1);
    executar();
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{
    while (GG.estaAberta())
    {
        GG.tratarEventos();

        if (!GG.estaAberta())
            break;

        GG.limpar();

        pJog1.mover();
        pJog1.saiuDoChao();
        fase2.executar();

        if (fase1.getVenceu())
        {
            std::cout << "FASE 1 CONCLUIDA!" << std::endl;
            std::cout << "Pontuacao final: "
                      << pJog1.getPontos() << std::endl;
            break;
        }

        if (fase2.getVenceu())
        {
            std::cout << "FASE 2 CONCLUIDA!" << std::endl;
            std::cout << "Pontuacao final: " << pJog1.getPontos() << std::endl;
            break;
        }

        if (pJog1.getVidas() <= 0)
        {
            std::cout << "GAME OVER!" << std::endl;
            std::cout << "Pontuacao final: "
                      << pJog1.getPontos() << std::endl;

            break;
        }

        pJog1.desenhar();

        GG.mostrar();
    }
}

