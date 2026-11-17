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
    Aranha* aranha = new Aranha();

    lista_ents.incluir(aranha);
    GC.incluirInimigo(aranha);
}

void Fase::criarPlataformas()
{
    Plataforma* chao = new Plataforma();

    lista_ents.incluir(chao);
    GC.incluirObstaculo(chao);

    chao->configurar(0.f, 390.f, 400.f, 10.f);
}

void Fase::criarCenario(){

}

void Fase::setJogador(Jogador* pJ)
{
    pJogador = pJ;
    GC.setJogador(pJ);
}



