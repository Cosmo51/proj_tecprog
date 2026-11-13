#include "Obstaculos.h"

using namespace Obstaculos;

Plataforma::Plataforma():altura(0)
{
    body.setFillColor(sf::Color::Green);
}

Plataforma::~Plataforma(){

}

void Plataforma::executar(){

}


void Plataforma::obstaculizar(Jogador* p)
{
    if (p == nullptr)
        return;

    sf::FloatRect jogador = p->getBody().getGlobalBounds();
    sf::FloatRect plataforma = body.getGlobalBounds();

    sf::Vector2f anterior = p->getPosicaoAnterior();

    float esqJ = jogador.position.x;
    float dirJ = esqJ + jogador.size.x;
    float topoJ = jogador.position.y;
    float baseJ = topoJ + jogador.size.y;

    float esqP = plataforma.position.x;
    float dirP = esqP + plataforma.size.x;
    float topoP = plataforma.position.y;
    float baseP = topoP + plataforma.size.y;

    float esqAnterior = anterior.x;
    float dirAnterior = anterior.x + jogador.size.x;
    float topoAnterior = anterior.y;
    float baseAnterior = anterior.y + jogador.size.y;

    // Colisao por cima
    if (baseAnterior <= topoP && baseJ >= topoP && p->getVelY() >= 0.f)
    {
        p->setPosicao(esqJ, topoP - jogador.size.y);
        p->pararQueda();
    }

    // Colisao por baixo
    else if (topoAnterior >= baseP && topoJ <= baseP && p->getVelY() < 0.f)
    {
        p->setPosicao(esqJ, baseP);
        p->pararSubida();
    }

    // Colisao pela esquerda
    else if (dirAnterior <= esqP && dirJ >= esqP)
    {
        p->setPosicao(esqP - jogador.size.x, topoJ);
    }

    // Colisao pela direita
    else if (esqAnterior >= dirP && esqJ <= dirP)
    {
        p->setPosicao(dirP, topoJ);
    }
}


void Plataforma::salvar(){

}

void Plataforma::configurar(float x, float y, float largura, float altura)
{
    body.setSize(sf::Vector2f(largura, altura));
    body.setPosition(sf::Vector2f(x, y));

    this->altura = static_cast<int>(altura);
}

