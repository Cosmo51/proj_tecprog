
#include "Fases.h"

using namespace Fases;

FasePrimeira::FasePrimeira() :
aranha(nullptr),
galinha(nullptr),
plat1(nullptr),
plat2(nullptr),
limitedireita(nullptr),
limiteesquerda(nullptr)
{
    aranha = new Aranha();
    lista_ents.incluir(aranha);

    galinha = new Galinha();
    lista_ents.incluir(galinha);

    plat1 = new Plataforma();
    lista_ents.incluir(plat1);
    GC.incluirObstaculo(plat1);
    plat1->configurar(0.f, 390.f, 400.f, 10.f);

    plat2 = new Plataforma();
    lista_ents.incluir(plat2);
    GC.incluirObstaculo(plat2);
    plat2->configurar(120.f, 250.f, 50.f, 10.f);

    limitedireita = new LimitesGeograficos();
    lista_ents.incluir(limitedireita);
    limitedireita->direita();

    limiteesquerda = new LimitesGeograficos();
    lista_ents.incluir(limiteesquerda);
    limiteesquerda->esquerda();
}

FasePrimeira::~FasePrimeira()
{

}

void FasePrimeira::executar()
{
    // Executar os objetos da lista
    lista_ents.percorrer();

    // Colisoes do jogador com as plataformas
    GC.tratarColisoesJogsObstacs();

    // Colisao da aranha com o chao
    if (GC.verificarColisao(aranha, plat1))
    {
        sf::FloatRect limites = aranha->getBody().getGlobalBounds();

        if (limites.position.y + limites.size.y >= 390.f && aranha->getVelocidadeY() >= 0.f)
        {
            aranha->setPosicao(limites.position.x, 390.f - limites.size.y);

            aranha->pararQueda();
        }
    }

    // Desenhar os objetos da fase
    if (window != nullptr)
    {
        lista_ents.setWindow(window);
        lista_ents.desenhar();
    }
}

void FasePrimeira::criarInimMedios()
{
    Galinha* galinha = new Galinha();

    lista_ents.incluir(galinha);
    GC.incluirInimigo(galinha);
}

void FasePrimeira::criarObstMedios()
{
}

void FasePrimeira::criarInimgos()
{
    criarInimFaceis();
    criarInimMedios();
}

void FasePrimeira::criarObstaculo()
{

}




