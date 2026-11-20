#include "Obstaculos.h"

using namespace Obstaculos;

Obst_Medio::Obst_Medio()
{
    definirTamanho(70.f, 8.f);
    definirCor(sf::Color(120, 75, 35));
    setPosicao(250.f, 382.f);
}

Obst_Medio::~Obst_Medio(){

}

void Obst_Medio::executar(){

}

void Obst_Medio::configurar(float x, float y)
{
    setPosicao(x, y);
}

void Obst_Medio::salvar(){

}

void Obst_Medio::obstaculizar(Jogador* p)
{
    if (p != nullptr)
    {
        p->diminuirVelocidade();
    }
}

