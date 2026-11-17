#include "Entidades.h"

using namespace Entidades;

Ovo::Ovo()
{
    velocidadeX = 0.5f;

    definirTamanho(10.f, 10.f);
    definirCor(sf::Color::White);
}

Ovo::~Ovo()
{
}

void Ovo::executar()
{
    if (ativo)
    {
        moverFigura(velocidadeX, 0.f);
    }
}

void Ovo::salvar()
{
}

void Ovo::configurar(float x, float y, float direcao)
{
    setPosicao(x, y);

    velocidadeX = 0.5f * direcao;
}

