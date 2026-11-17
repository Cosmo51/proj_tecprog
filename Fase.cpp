#include "Fases.h"

using namespace Fases;

Fase::Fase() : pJogador(nullptr)
{
}


Fase::~Fase(){

}

void Fase::executar(){

}

void Fase::criarInimFaceis()
{
    criarInimFaceis(355.f, 290.f, 200.f, 399.f);
}

void Fase::criarInimFaceis(float x, float y, float esquerda, float direita)
{
    Aranha* aranha = new Aranha();
    aranha->setPosicao(x, y);
    aranha->configurarPatrulha(esquerda, direita);

    lista_ents.incluir(aranha);
    GC.incluirInimigo(aranha);
}

void Fase::criarPlataformas()
{
    Plataforma* chao = new Plataforma();

    chao->configurar(0.f, 590.f, 800.f, 10.f);

    lista_ents.incluir(chao);
    GC.incluirObstaculo(chao);
}

void Fase::criarCenario(){

}

void Fase::setJogador(Jogador* pJ)
{
    pJogador = pJ;
    GC.setJogador(pJ);
}



