
#include "Fases.h"

using namespace Fases;

FasePrimeira::FasePrimeira()
{
    // Configuracao das plataformas
    plat1.configurar(0.f, 390.f, 400.f, 10.f);
    plat2.configurar(120.f, 250.f, 50.f, 10.f);

    // Configuracao dos limites geograficos
    limitedireita.direita();
    limiteesquerda.esquerda();

    // Inclusao dos objetos na lista da fase
    lista_ents.incluir(&aranha);
    lista_ents.incluir(&galinha);

    lista_ents.incluir(&plat1);
    lista_ents.incluir(&plat2);

    lista_ents.incluir(&limitedireita);
    lista_ents.incluir(&limiteesquerda);
}


FasePrimeira::~FasePrimeira()
{
}

void FasePrimeira::executar()
{
    // Movimentacao da aranha
    lista_ents.percorrer();

    // Colisoes do jogador com as plataformas
    if (pJogador != nullptr)
    {
        if (GC.verificarColisao(pJogador, &plat1))
        {
            plat1.obstaculizar(pJogador);
        }

        if (GC.verificarColisao(pJogador, &plat2))
        {
            plat2.obstaculizar(pJogador);
        }
    }

    // Colisao da aranha com o chao
    if (GC.verificarColisao(&aranha, &plat1))
    {
        sf::FloatRect limites =
            aranha.getBody().getGlobalBounds();

        if (limites.position.y + limites.size.y >= 390.f &&
            aranha.getVelocidadeY() >= 0.f)
        {
            aranha.setPosicao(
                limites.position.x,
                390.f - limites.size.y
            );

            aranha.pararQueda();
        }
    }

    // Desenho dos objetos da fase
    if (window != nullptr)
    {
        plat1.setWindow(window);
        plat2.setWindow(window);

        aranha.setWindow(window);
        galinha.setWindow(window);

        limitedireita.setWindow(window);
        limiteesquerda.setWindow(window);

        lista_ents.desenhar();
    }
}

void FasePrimeira::criarInimMedios()
{
}

void FasePrimeira::criarObstMedios()
{
}

void FasePrimeira::criarInimgos()
{
}

void FasePrimeira::criarObstaculo()
{
}




