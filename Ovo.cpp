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
    std::ofstream arquivo("projeteis.txt", std::ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Ovo" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << velocidadeX << " "
                << std::endl;

        arquivo.close();
    }
}

bool Ovo::carregar(std::ifstream& arquivo)
{
    float posX, posY;
    float velX;

    if (arquivo >> posX >> posY >> velX)
    {
        setPosicao(posX, posY);

        velocidadeX = velX;

        return true;
    }

    return false;
}

void Ovo::configurar(float x, float y, float direcao)
{
    setPosicao(x, y);

    velocidadeX = 0.5f * direcao;
}

