#include "Personagens.h"

using namespace Personagens;

Inimigo::Inimigo(float x, float y) : Personagem(x, y), nivel_maldade(1), forca(1)
{
    velocidadeY = 0.f;
    ativo = true;
    limiteEsquerdo = 200.f;
    limiteDireito = 399.f;
}

Inimigo::~Inimigo(){

}

int Inimigo::getForca() const
{
    return forca;
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

bool Inimigo::getAtivo() const
{
    return ativo;
}

void Inimigo::desativar()
{
    ativo = false;
}

void Inimigo::configurarPatrulha(float esquerda, float direita)
{
    limiteEsquerdo = esquerda;
    limiteDireito = direita;
}
