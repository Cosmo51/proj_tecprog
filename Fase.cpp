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

<<<<<<< HEAD
void Fase::criarPlataformas()
{
    Plataforma* chao = new Plataforma();

    chao->configurar(0.f, 740.f, 1000.f, 10.f);

    lista_ents.incluir(chao);
    GC.incluirObstaculo(chao);
=======
void Fase::criarPlataformas()
{
    Plataforma* chao = new Plataforma();

    chao->configurar(0.f, 740.f, 1000.f, 10.f);

    lista_ents.incluir(chao);
    GC.incluirObstaculo(chao);
>>>>>>> 4ca3bc9b27626093d96e0e68ee8a5edadfd3c7fb
}

void Fase::criarCenario(){

}

void Fase::setJogador(Jogador* pJ)
{
    pJogador = pJ;
    GC.setJogador(pJ);
}



