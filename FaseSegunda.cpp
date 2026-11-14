#include "Fases.h"

using namespace Fases;

FaseSegunda::FaseSegunda()
{
    criarObstaculo();
}

FaseSegunda::~FaseSegunda(){

}

void FaseSegunda::criarChefoes(){

}

void FaseSegunda::criarObstDificeis()
{
    Obst_Dificil* ratoeira = new Obst_Dificil();

    lista_ents.incluir(ratoeira);
    GC.incluirObstaculo(ratoeira);
}

void FaseSegunda::criarProjeteis(){

}

void FaseSegunda::criarInimgos()
{
    criarInimFaceis();
    criarChefoes();
}

void FaseSegunda::criarObstaculo()
{
    criarObstDificeis();
}

