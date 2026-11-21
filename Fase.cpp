#include "Fases.h"

using namespace Fases;

Fase::Fase() : pJogador(nullptr)
{
}


Fase::~Fase(){

}

void Fase::executar(){

}

void Fase::criarCenario(){

}

void Fase::setJogador(Jogador* pJ)
{
    pJogador = pJ;
    GC.setJogador(pJ);
}



