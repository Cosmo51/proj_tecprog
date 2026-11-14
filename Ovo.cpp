#include "Entidades.h"

using namespace Entidades;

Ovo::Ovo()
{
    velocidadeX = 0.5f;

    body.setSize(sf::Vector2f(10.f, 10.f));
    body.setFillColor(sf::Color::White);
}

Ovo::~Ovo()
{
}

void Ovo::executar()
{
    if (ativo)
    {
        body.move(sf::Vector2f(velocidadeX, 0.f));
    }
}

void Ovo::salvar()
{
}

void Ovo::configurar(float x, float y, float direcao)
{
    body.setPosition(sf::Vector2f(x, y));

    velocidadeX = 0.5f * direcao;
}

