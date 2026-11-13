#include "Obstaculos.h"

using namespace Obstaculos;

Obst_Medio::Obst_Medio()
{
    body.setSize(sf::Vector2f(70.f, 8.f));
    body.setFillColor(sf::Color(120, 75, 35));
    body.setPosition(sf::Vector2f(250.f, 382.f));
}

Obst_Medio::~Obst_Medio(){

}

void Obst_Medio::executar(){

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

