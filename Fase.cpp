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

void Fase::criarPlataformas(){

}

void Fase::criarCenario(){

}

void Fase::setJogador(Jogador* pJ)
{
    pJogador = pJ;
    GC.setJogador(pJ);
}



