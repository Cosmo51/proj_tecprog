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

    sf::FloatRect limitesJogador = p->getBody().getGlobalBounds();
    sf::FloatRect limitesPlataforma = body.getGlobalBounds();

    float baseJogador = limitesJogador.position.y + limitesJogador.size.y;
    float topoPlataforma = limitesPlataforma.position.y;

    if (baseJogador >= topoPlataforma && baseJogador <= topoPlataforma + 5.f && p->getVelY() >= 0.f)
    {
        p->setPosicao(limitesJogador.position.x, topoPlataforma - limitesJogador.size.y);
        p->pararQueda();
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

