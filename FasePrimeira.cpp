#include "Fases.h"

using namespace Fases;

FasePrimeira::FasePrimeira() :
galinha(nullptr),
limitedireita(nullptr),
limiteesquerda(nullptr)
{
    criarInimgos();
    criarObstaculo();
}

FasePrimeira::~FasePrimeira()
{

}

void FasePrimeira::executar()
{
    lista_ents.percorrer();

    if (galinha != nullptr)
    {
        if (galinha->verificarAtaque())
        {
            criarProjeteis();
        }
    }

    GC.tratarColisoesInimgsObstacs();
    GC.tratarColisoesJogsInimgs();


    if (galinha != nullptr && !galinha->getAtivo())
    {
        galinha = nullptr;
    }

    GC.removerInimigosInativos(lista_ents);

    GC.tratarColisoesJogsObstacs();
    GC.tratarColisoesProjeteisObstacs();
    GC.tratarColisoesJogsProjeteis();
    GC.removerProjeteisInativos(lista_ents);

    lista_ents.desenhar();
}



void FasePrimeira::criarInimMedios()
{
    galinha = new Galinha();


    lista_ents.incluir(galinha);
    GC.incluirInimigo(galinha);
}

void FasePrimeira::criarObstMedios()
{

    Obst_Medio* lama = new Obst_Medio();

    lista_ents.incluir(lama);
    GC.incluirObstaculo(lama);

}

void FasePrimeira::criarPlataformas()
{
    Fase::criarPlataformas();

    Plataforma* plataforma = new Plataforma();
    lista_ents.incluir(plataforma);
    GC.incluirObstaculo(plataforma);
    plataforma->configurar(120.f, 250.f, 50.f, 10.f);
}

void FasePrimeira::criarInimgos()
{
    Fase::criarInimFaceis();
    criarInimMedios();
}

void FasePrimeira::criarObstaculo()
{

    criarPlataformas();
    criarObstMedios();

    limitedireita = new LimitesGeograficos();
    lista_ents.incluir(limitedireita);
    limitedireita->direita();

    limiteesquerda = new LimitesGeograficos();
    lista_ents.incluir(limiteesquerda);
    limiteesquerda->esquerda();
}

void FasePrimeira::setJogador(Jogador* pJ)
{
    Fase::setJogador(pJ);

    if (galinha != nullptr)
    {
        galinha->setJogador(pJ);
    }
}

void FasePrimeira::criarProjeteis()
{
    criarOvo();
}

void FasePrimeira::criarOvo()
{
    if (galinha == nullptr || pJogador == nullptr)
        return;

    Ovo* ovo = new Ovo();

    float xGalinha = galinha->getPosicao().x;
    float yGalinha = galinha->getPosicao().y;

    float xJogador = pJogador->getPosicao().x;

    float direcao = 1.f;

    if (xJogador < xGalinha)
    {
        direcao = -1.f;
    }

    ovo->configurar(xGalinha + 10.f, yGalinha + 45.f, direcao);

    lista_ents.incluir(ovo);
    GC.incluirProjetil(ovo);
}






