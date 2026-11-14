#include "Personagens.h"

using namespace Personagens;

Inimigo::Inimigo():nivel_maldade(0)
{
    velocidadeY = 0.f;
}

Inimigo::~Inimigo(){

}

void Inimigo::salvarDataBuffer(){

}

void Inimigo::pararQueda()
{
    velocidadeY = 0.f;
}

float Inimigo::getVelocidadeY() const
{
    return velocidadeY;
}

sf::Vector2f Inimigo::getPosicaoAnterior() const
{
    return posicaoAnterior;
}
