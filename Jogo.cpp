#include "Jogo.h"

Jogo::Jogo()
{
    fase1.setJogador(&pJog1);
    executar();
}

Jogo::~Jogo() {}

void Jogo::executar()
{
    while (GG.estaAberta())
    {
        GG.tratarEventos();
        GG.limpar();

        pJog1.mover();
        pJog1.saiuDoChao();
        fase1.executar();
        pJog1.desenhar();

        GG.mostrar();
    }
}
