#include "Entidades.h"

using namespace Entidades;

Novelo::Novelo()
{
    velocidadeX = 0.f;
    velocidadeY = 0.f;
    gravidade = 0.01f;

    definirTamanho(15.f, 15.f);
    definirCor(sf::Color::Cyan);
}

Novelo::~Novelo()
{
}

void Novelo::executar()
{
    if (ativo)
    {
        velocidadeY += gravidade;

        moverFigura(velocidadeX, velocidadeY);
    }
}

void Novelo::salvar()
{
}

void Novelo::configurar(float x, float y, float direcao)
{
    setPosicao(x, y);

    velocidadeX = 0.7f * direcao;
    velocidadeY = -1.5f;
}

